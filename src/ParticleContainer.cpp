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

bool ParticleContainer::init(string filename)
{
	LOG4CXX_DEBUG(containerLogger, "init");

	
	FileReader fileReader;
	if(!fileReader.readFile(particlePool, filename, &domainX, &domainY, &rCutOff))
		return false;

	ParticleProperty wallProp;
	for (int pr = 0; pr < ParticleProperty::count(); pr++)
	{
		wallProp.e += ParticleProperty::get(pr).e;
		wallProp.o += ParticleProperty::get(pr).o;
		wallProp.mass += ParticleProperty::get(pr).mass;
	}

	wallProp.e /= ParticleProperty::count();
	wallProp.o /= ParticleProperty::count();
	wallProp.mass /= ParticleProperty::count();
	wallProp.mass *= 1000;

	wallType = ParticleProperty::count();
	ParticleProperty::push(wallProp);


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

	// find Boundaries
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
				cell.cellType() = ParticleCell::LeftBoundary;
				ParticleCell& other = cells[i + numCellsY];

				boundaryHaloPairs.push_back(BoundaryHaloPair(&cell, &other, Periodic));
			}
			else if (x == numCellsX - 1)
			{
				cell.cellType() = ParticleCell::RightBoundary;
				ParticleCell& other = cells[i - numCellsY];

				boundaryHaloPairs.push_back(BoundaryHaloPair(&cell, &other, Periodic));
			}
			else if (y == 0)
			{
				cell.cellType() = ParticleCell::BottomBoundary;
				ParticleCell& other = cells[i + 1];

				boundaryHaloPairs.push_back(BoundaryHaloPair(&cell, &other, Reflecting));
			}
			else if (y == numCellsY - 1)
			{
				cell.cellType() = ParticleCell::TopBoundary;
				ParticleCell& other = cells[i - 1];

				boundaryHaloPairs.push_back(BoundaryHaloPair(&cell, &other, Reflecting));
			}

			i++;
		}
	}

	LOG4CXX_DEBUG(containerLogger, "NumBoundaries: " << (int)boundaryHaloPairs.size());

	LOG4CXX_DEBUG(containerLogger, "Particles: " << (int)particlePool.size());

	for (int p = 0; p < particlePool.size(); p++)
	{
		liveParticles.push_back(&(particlePool[p]));
	}

	updateCells();

	LOG4CXX_DEBUG(containerLogger, "LiveParticles: " << (int)liveParticles.size());

	return true;
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

		int x, y;
		expand(&x, &y, i);

		bool left = x != 0;
		bool right = x != numCellsX - 1;

		bool bottom = y != 0;
		bool top = y != numCellsY -1;

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

		int x, y;
		expand(&x, &y, i);

		bool left = x != 0;
		bool right = x != numCellsX - 1;

		bool top = y != numCellsY - 1;

		if (right)
			cells[i].combineParticlePairsExclusive(cells[i + numCellsY], handler);

		if (top)
			cells[i].combineParticlePairsExclusive(cells[i + 1], handler);

		if (left && top)
			cells[i].combineParticlePairsExclusive(cells[i - numCellsY + 1], handler);
		if (right && top)
			cells[i].combineParticlePairsExclusive(cells[i + numCellsY + 1], handler);
	}
}

void ParticleContainer::iterateBoundaryCells()
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

	for (int b = 0; b < boundaryHaloPairs.size(); b++)
	{
		BoundaryHaloPair boundaryHalo = boundaryHaloPairs[b];
		ParticleCell& boundaryCell = *boundaryHaloPairs[b].boundaryCell;
		ParticleCell& haloCell = *boundaryHaloPairs[b].haloCell;

		switch (boundaryHalo.condition)
		{
		case Periodic:{

			int boundaryX, boundaryY;
			expand(&boundaryX, &boundaryY, boundaryCell.index());

			int haloX, haloY;
			expand(&haloX, &haloY, haloCell.index());

			if (boundaryX != haloX && boundaryY != haloY)
				LOG4CXX_DEBUG(containerLogger, "Boundary does not match Halo");


			int oBoundaryIndex, oHaloindex;

			switch (boundaryCell.cellType())
			{
			case ParticleCell::LeftBoundary:
				flatten(numCellsX - 1, boundaryY, &oBoundaryIndex);
				flatten(numCellsX - 2, boundaryY, &oHaloindex);
				break;
			case ParticleCell::RightBoundary:
				flatten(0, boundaryY, &oBoundaryIndex);
				flatten(1, boundaryY, &oHaloindex);
				break;
			case ParticleCell::BottomBoundary:
				flatten(boundaryX, numCellsY - 1, &oBoundaryIndex);
				flatten(boundaryX, numCellsY - 2, &oHaloindex);
				break;
			case ParticleCell::TopBoundary:
				flatten(boundaryX, 0, &oBoundaryIndex);
				flatten(boundaryX, 1, &oHaloindex);
				break;
			default:
				LOG4CXX_DEBUG(containerLogger, "Not a boundary");
			}

			expand(&boundaryX, &boundaryY, oBoundaryIndex);
			expand(&haloX, &haloY, oHaloindex);

			if (boundaryX != haloX && boundaryY != haloY)
				LOG4CXX_DEBUG(containerLogger, "Boundary does not match Halo");


			ParticleCell& otherBoundaryCell = cells[oBoundaryIndex];
			ParticleCell& otherHaloCell = cells[oHaloindex];

			Vector<double, 3> delta = otherBoundaryCell.pos() - haloCell.pos();

			for (int p = 0; p < haloCell.count(); p++)
			{
				Particle& particle = *haloCell[p];
				Vector<double, 3> position = particle.getX() + delta;
				Vector<double, 3> velocity(0.0);
				int type = particle.getType();
				dummies.push_back(Particle(position, velocity, type, false));
			}

			for (int p = 0; p < boundaryCell.count(); p++)
			{
				Particle& particle = *boundaryCell[p];
				Vector<double, 3> position = particle.getX() + delta;
				particle.getX() = position;
			}

			break;

		}
		case Reflecting:{
			//LOG4CXX_DEBUG(containerLogger, "Reflect");
			
			Vector<double, 3> mid;
			int a;

			switch (boundaryCell.cellType())
			{
			case ParticleCell::LeftBoundary:
				mid = haloCell.pos();
				a = 0;
				break;
			case ParticleCell::RightBoundary:
				mid = boundaryCell.pos();
				a = 0;
				break;
			case ParticleCell::BottomBoundary:
				mid = haloCell.pos();
				a = 1;
				break;
			case ParticleCell::TopBoundary:
				mid = boundaryCell.pos();
				a = 1;
				break;
			default:
				LOG4CXX_ERROR(containerLogger, "invalid boundary");
				continue;
			}

			for (int p = 0; p < haloCell.count(); p++)
			{
				Particle& particle = *haloCell[p];

				Vector<double, 3> position = particle.getX();
				position[a] = mid[a];

				Vector<double, 3> velocity(0.0);

				dummies.push_back(Particle(position, velocity, wallType, false));

				//LOG4CXX_DEBUG(containerLogger, "added dummy cell: " << dummies.back().getCell() << ", now " << (int)liveParticles.size() << " live Ps");
			}
			break;
		}
		case OutFlow:
		{
			//LOG4CXX_DEBUG(containerLogger, "outflow");

			for (int p = 0; p < boundaryCell.count(); p++)
			{
				Particle* pParticle = boundaryCell[p];
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

double ParticleContainer::getDomainX()
{
	return domainX;
}

double ParticleContainer::getDomainY()
{
	return domainY;
}

int ParticleContainer::getWallType()
{
	return wallType;
}
