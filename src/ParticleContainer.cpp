#include "ParticleContainer.h"
#include "FileReader.h"
#include <algorithm>

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace Simulation;
using namespace utils;
using namespace std;

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

// Define static logger variable
LoggerPtr containerLogger(Logger::getLogger("ParticleContanier"));


ParticleCell::ParticleCell(int i, Vector<double, 3>& pos, double* r)
	: selfIndex(i), position(pos), type(InnerCell), pRCutOff(r)
{
}

ParticleCell::CellType& ParticleCell::cellType()
{
	return type;
}

void ParticleCell::insert(Particle* pParticle)
{
	Vector<double, 3> delta = pParticle->getX() - position;
	if ((delta[0] > *pRCutOff || delta[1] > *pRCutOff) && type == InnerCell)
	{
		LOG4CXX_DEBUG(containerLogger, "Particle does not fit in cell");
		LOG4CXX_DEBUG(containerLogger, "Cell: x: " << position[0] << " y: " << position[1] << ", P: x: " << pParticle->getX()[0] << " y: " << pParticle->getX()[1]);
		LOG4CXX_DEBUG(containerLogger, "cutoff: " << *pRCutOff);
	}
	else
	{
		pParticles.push_back(pParticle);
		pParticle->setCell(selfIndex);
	}
}

void ParticleCell::remove(Particle* pParticle)
{
	pParticles.remove(pParticle);
	pParticle->setCell(-1);
}

int ParticleCell::count()
{
	return pParticles.size();
}

bool ParticleCell::contains(Particle* pParticle)
{
	return find(pParticles.begin(), pParticles.end(), pParticle) != pParticles.end();
}

Particle* ParticleCell::operator[](int i)
{
	PParticleIterator it = pParticles.begin();
	advance(it, i);
	return *it;
}

void ParticleCell::iterateParticles(ParticleHandler& handler)
{
	for (PParticleIterator i = pParticles.begin(); i != pParticles.end(); i++)
	{
		Particle& p = **i;

		handler.compute(p);
	}
}

void ParticleCell::iterateParticlePairs(ParticleHandler& handler)
{
	for (PParticleIterator i = pParticles.begin(); i != pParticles.end(); i++)
	{
		Particle& p1 = **i;
		for (PParticleIterator j = pParticles.begin(); j != pParticles.end(); j++)
		{
			Particle& p2 = **j;
			if (*i != *j)
			{
				handler.compute(p1, p2);
			}
		}
	}
}

void ParticleCell::iterateParticlePairsExclusive(ParticleHandler& handler)
{
	for (PParticleIterator i = pParticles.begin(); i != pParticles.end(); i++)
	{
		Particle& p1 = **i;
		for (PParticleIterator j = i; j != pParticles.end(); j++)
		{
			if (*i != *j)
			{
				Particle& p2 = **j;
				handler.computeExclusive(p1, p2);
			}
		}
	}
}

void ParticleCell::combineParticlePairs(ParticleCell& other, ParticleHandler& handler)
{
	for (PParticleIterator i = pParticles.begin(); i != pParticles.end(); i++)
	{
		Particle& p1 = **i;
		for (PParticleIterator j = other.pParticles.begin(); j != other.pParticles.end(); j++)
		{
			Particle& p2 = **j;
			handler.compute(p1, p2);
		}
	}
}

void ParticleCell::combineParticlePairsExclusive(ParticleCell& other, ParticleHandler& handler)
{
	for (PParticleIterator i = pParticles.begin(); i != pParticles.end(); i++)
	{
		Particle& p1 = **i;
		for (PParticleIterator j = other.pParticles.begin(); j != other.pParticles.end(); j++)
		{
			Particle& p2 = **j;
			handler.computeExclusive(p1, p2);
		}
	}
}








ParticleContainer::ParticleContainer()
{
	particlePool.clear();
}

void ParticleContainer::init(char* filename)
{
	LOG4CXX_DEBUG(containerLogger, "init");

	bool reflective;
	double domainX, domainY;
	
	FileReader fileReader;
	fileReader.readFile(particlePool, filename, &reflective, &domainX, &domainY, &rCutOff);

	numCellsX = ceil(domainX / rCutOff) + 2;
	numCellsY = ceil(domainY / rCutOff) + 2;

	LOG4CXX_DEBUG(containerLogger, "DomainX: " << domainX << " DomainY: " << domainY << " rCutOff: " << rCutOff);
	LOG4CXX_DEBUG(containerLogger, "NumCellsX: " << numCellsX << " NumCellsY: " << numCellsY);

	// create Cells
	int i = 0;
	for (int x = 0; x < numCellsX; x++)
	{
		for (int y = 0; y < numCellsY; y++)
		{
			Vector<double, 3> position(0.0);
			position[0] = (x - 1) * rCutOff;
			position[1] = (y - 1) * rCutOff;

			cells.push_back(ParticleCell(i, position, &rCutOff));
			i++;
		}
	}

	LOG4CXX_DEBUG(containerLogger, "NumCells: " << i << " == " << (int)cells.size());

	// find Boundries
	i = 0;
	for(int x = 0; x < numCellsX; x++)
	{
		for (int y = 0; y < numCellsY; y++)
		{
			ParticleCell& cell = cells[i];


			if ((x == 0 && y == 0) ||
				(x == 0 && y == numCellsY - 1) ||
				(x == numCellsX - 1 && y == 0) ||
				(x == numCellsX - 1 && y == numCellsY - 1))
			{
				cell.cellType() = ParticleCell::Corner;
			}
			else if (x == 0)
			{
				cell.cellType() = ParticleCell::LeftBoundry;
				ParticleCell& other = cells[i + numCellsY];

				boundryHaloPairs.push_back(BoundryHaloPair(&cell, &other, Periodic));
			}
			else if (x == numCellsX - 1)
			{
				cell.cellType() = ParticleCell::RightBoundry;
				ParticleCell& other = cells[i - numCellsY];

				boundryHaloPairs.push_back(BoundryHaloPair(&cell, &other, Periodic));
			}
			else if (y == 0)
			{
				cell.cellType() = ParticleCell::BottomBoundry;
				ParticleCell& other = cells[i + 1];

				boundryHaloPairs.push_back(BoundryHaloPair(&cell, &other, Reflecting));
			}
			else if (y == numCellsY - 1)
			{
				cell.cellType() = ParticleCell::TopBoundry;
				ParticleCell& other = cells[i - 1];

				boundryHaloPairs.push_back(BoundryHaloPair(&cell, &other, Reflecting));
			}

			i++;
		}
	}

	LOG4CXX_DEBUG(containerLogger, "NumBoundries: " << (int)boundryHaloPairs.size());

	LOG4CXX_DEBUG(containerLogger, "Particles: " << (int)particlePool.size());

	for (int p = 0; p < particlePool.size(); p++)
	{
		liveParticles.push_back(&(particlePool[p]));
	}

	LOG4CXX_DEBUG(containerLogger, "LiveParticles: " << (int)liveParticles.size());
}

void ParticleContainer::updateCells()
{
	visible = 0;

	for (int d = 0; d < dummies.size(); d++)
	{
		Particle* pDummy = &(dummies[d]);
		liveParticles.push_back(pDummy);
	}

	for (int p = 0; p < liveParticles.size(); p++)
	{
		Particle& particle = (*this)[p];

		if (particle.isVisible())
			visible++;

		int cell;
		findCell(particle.getX(), &cell);

		if (cell < 0 || cell >= cells.size())
		{
			LOG4CXX_ERROR(containerLogger, "invalid Cell: " << cell);
			continue;
		}

		int oldCell = particle.getCell();


		if (oldCell < 0 || oldCell >= cells.size())
			oldCell = -1;

		if (oldCell != -1)
			cells[oldCell].remove(&particle);

		cells[cell].insert(&particle);
	}

	/*for (int p = 0; p < particlePool.size(); p++)
	{
		Particle& particle = particlePool[p];
		LOG4CXX_DEBUG(containerLogger, "particle " << p << " in cell " << particle.getCell());
	}

	for (int d = 0; d < dummies.size(); d++)
	{
		Particle& particle = dummies[d];
		LOG4CXX_DEBUG(containerLogger, "dummy " << d << " in cell " << particle.getCell());
	}*/

	for (int p = 0; p < liveParticles.size(); p++)
	{ 
		Particle& particle = (*this)[p];
		int cell = particle.getCell();

		if ( cell < 0 || cell >= cells.size())
			LOG4CXX_ERROR(containerLogger, "invalid Cell " << cell << " at particle " << p);

		if (!cells[cell].contains(&particle))
			LOG4CXX_ERROR(containerLogger, "invalid Cell Particle Pair: " << cell);
	}
}

void ParticleContainer::findCell(utils::Vector<double, 3> position, int* cell)
{
	int x = floor(position[0] / (double)rCutOff) + 1;
	int y = floor(position[1] / (double)rCutOff) + 1;

	if (x < 0)
		x = 0;
	else if (x > numCellsX - 1)
		x = numCellsX - 1;

	if (y < 0)
		y = 0;
	else if (y > numCellsY - 1)
		y = numCellsY - 1;

	flatten(x, y, cell);
}

void ParticleContainer::flatten(int x, int y, int* cell)
{
	*cell = x * numCellsY + y;
}

void ParticleContainer::expand(int* x, int* y, int c)
{
	*x = floor(c / numCellsY);
	*y = c % numCellsY;
}


int ParticleContainer::count()
{
	return liveParticles.size();
}

int ParticleContainer::countVisible()
{
	return visible;
}

Particle& ParticleContainer::operator[](int i)
{
	PParticleIterator it = liveParticles.begin();
	advance(it, i);
	return **it;
}


void ParticleContainer::iterateParticles(ParticleHandler& handler)
{
	for (int i = 0; i < cells.size(); i++)
	{
		cells[i].iterateParticles(handler);
	}
}

void ParticleContainer::iterateParticlePairs(ParticleHandler& handler)
{
	for (int i = 0; i < cells.size(); i++)
	{
		cells[i].iterateParticlePairs(handler);


		bool left = floor(i / numCellsY) != 0;
		bool right = (floor(i / numCellsY) + 1) != numCellsX;

		bool bottom = i % numCellsY != 0;
		bool top = (i + 1) % numCellsY  != 0;

		if (left)
			cells[i].combineParticlePairs(cells[i - numCellsY], handler);
		if (right)
			cells[i].combineParticlePairs(cells[i + numCellsY], handler);
		if (bottom)
			cells[i].combineParticlePairs(cells[i - 1], handler);
		if (top)
			cells[i].combineParticlePairs(cells[i + 1], handler);

		if (left && bottom)
			cells[i].combineParticlePairs(cells[i - numCellsY - 1], handler);
		if (left && top)
			cells[i].combineParticlePairs(cells[i - numCellsY + 1], handler);
		if (right && bottom)
			cells[i].combineParticlePairs(cells[i + numCellsY - 1], handler);
		if (right && top)
			cells[i].combineParticlePairs(cells[i + numCellsY + 1], handler);
	}
}

void ParticleContainer::iterateParticlePairsExclusive(ParticleHandler& handler)
{
	for (int i = 0; i < cells.size(); i++)
	{

		cells[i].iterateParticlePairsExclusive(handler);

		bool left = floor(i / numCellsY) != 0;
		bool right = (floor(i / numCellsY) + 1) != numCellsX;

		bool top = (i + 1) % numCellsY != 0;

		if (right && cells.size() >(i + 1))
			cells[i].combineParticlePairsExclusive(cells[i + numCellsY], handler);

		if (top && cells.size() > (i + numCellsX))
			cells[i].combineParticlePairsExclusive(cells[i + 1], handler);

		if (left && top && cells.size() > (i - 1 + numCellsX))
			cells[i].combineParticlePairsExclusive(cells[i - numCellsY + 1], handler);
		if (right && top && cells.size() > (i + 1 + numCellsX))
			cells[i].combineParticlePairsExclusive(cells[i + numCellsY + 1], handler);
	}
}

void ParticleContainer::iterateBoundryCells()
{
	for (int d = 0; d < dummies.size(); d++)
	{
		Particle& dummy = dummies[d];

		int cell = dummy.getCell();
		cells[cell].remove(&dummy);
		liveParticles.remove(&dummy);

	}
	dummies.clear();
	//LOG4CXX_DEBUG(containerLogger, "iterate");

	for (int b = 0; b < boundryHaloPairs.size(); b++)
	{
		BoundryHaloPair boundryHalo = boundryHaloPairs[b];
		ParticleCell& boundryCell = *boundryHaloPairs[b].boundryCell;
		ParticleCell& haloCell = *boundryHaloPairs[b].haloCell;

		switch (boundryHalo.condition)
		{
		case Periodic:{

			int boundryX, boundryY;
			expand(&boundryX, &boundryY, boundryCell.index());

			int haloX, haloY;
			expand(&haloX, &haloY, haloCell.index());

			if (boundryX != haloX && boundryY != haloY)
				LOG4CXX_DEBUG(containerLogger, "Boundry does not match Halo");


			int oBoundryIndex, oHaloindex;

			switch (boundryCell.cellType())
			{
			case ParticleCell::LeftBoundry:
				flatten(numCellsX - 1, boundryY, &oBoundryIndex);
				flatten(numCellsX - 2, boundryY, &oHaloindex);
				break;
			case ParticleCell::RightBoundry:
				flatten(0, boundryY, &oBoundryIndex);
				flatten(1, boundryY, &oHaloindex);
				break;
			case ParticleCell::BottomBoundry:
				flatten(boundryX, numCellsY - 1, &oBoundryIndex);
				flatten(boundryX, numCellsY - 2, &oHaloindex);
				break;
			case ParticleCell::TopBoundry:
				flatten(boundryX, 0, &oBoundryIndex);
				flatten(boundryX, 1, &oHaloindex);
				break;
			default:
				LOG4CXX_DEBUG(containerLogger, "Not a boundry");
			}

			expand(&boundryX, &boundryY, oBoundryIndex);
			expand(&haloX, &haloY, oHaloindex);

			if (boundryX != haloX && boundryY != haloY)
				LOG4CXX_DEBUG(containerLogger, "Boundry does not match Halo");


			ParticleCell& otherBoundryCell = cells[oBoundryIndex];
			ParticleCell& otherHaloCell = cells[oHaloindex];

			Vector<double, 3> delta = otherBoundryCell.pos() - haloCell.pos();

			for (int p = 0; p < haloCell.count(); p++)
			{
				Particle& particle = *haloCell[p];
				Vector<double, 3> position = particle.getX() + delta;
				Vector<double, 3> velocity(0.0);
				double m = particle.getM();
				dummies.push_back(Particle(position, velocity, m, particle.getE(), particle.getO(), false));
			}

			for (int p = 0; p < boundryCell.count(); p++)
			{
				Particle& particle = *boundryCell[p];
				Vector<double, 3> position = particle.getX() + delta;
				particle.getX() = position;
			}

			break;

		}
		case Reflecting:{
			//LOG4CXX_DEBUG(containerLogger, "Reflect");
			
			Vector<double, 3> mid;
			int a;

			switch (boundryCell.cellType())
			{
			case ParticleCell::LeftBoundry:
				mid = haloCell.pos();
				a = 0;
				break;
			case ParticleCell::RightBoundry:
				mid = boundryCell.pos();
				a = 0;
				break;
			case ParticleCell::BottomBoundry:
				mid = haloCell.pos();
				a = 1;
				break;
			case ParticleCell::TopBoundry:
				mid = boundryCell.pos();
				a = 1;
				break;
			default:
				LOG4CXX_ERROR(containerLogger, "invalid boundry");
				continue;
			}

			for (int p = 0; p < haloCell.count(); p++)
			{
				Particle& particle = *haloCell[p];

				Vector<double, 3> position = particle.getX();
				position[a] = mid[a];

				Vector<double, 3> velocity(0.0);

				dummies.push_back(Particle(position, velocity, 100, particle.getE(), particle.getO(), false));

				//LOG4CXX_DEBUG(containerLogger, "added dummy cell: " << dummies.back().getCell() << ", now " << (int)liveParticles.size() << " live Ps");
			}
			break;
		}
		case OutFlow:
		{
			//LOG4CXX_DEBUG(containerLogger, "outflow");

			for (int p = 0; p < boundryCell.count(); p++)
			{
				Particle* pParticle = boundryCell[p];
				cells[pParticle->getCell()].remove(pParticle);
				liveParticles.remove(pParticle);
			}
			break;
		}
		default:
			break;
		}
		
	}

	//LOG4CXX_DEBUG(containerLogger, "end");
}


double ParticleContainer::getCutOff()
{
	return rCutOff;
}