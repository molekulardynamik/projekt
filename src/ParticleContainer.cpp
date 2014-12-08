#include "ParticleContainer.h"
#include "FileReader.h"

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

void ParticleContainer::ParticleCell::insert(Particle* p)
{
	particles.push_back(p);
}

void ParticleContainer::ParticleCell::remove(Particle* p)
{
	particles.remove(p);
}

Particle* ParticleContainer::ParticleCell::operator[](int i)
{
	PParticleIterator it = particles.begin();
	advance(it, i);
	return *it;
}

int ParticleContainer::ParticleCell::count()
{
	return particles.size();
}

void ParticleContainer::ParticleCell::empty()
{
	for (PParticleIterator i = particles.begin(); i != particles.end(); i++)
	{
		(**i).setDead(true);
	}
	particles.clear();
}

void ParticleContainer::ParticleCell::iterateParticles(ParticleHandler& handler)
{
	for (PParticleIterator i = particles.begin(); i != particles.end(); i++)
	{
		Particle& p = **i;

		handler.compute(p);
	}
}

void ParticleContainer::ParticleCell::iterateParticlePairs(ParticleHandler& handler)
{
	for (PParticleIterator i = particles.begin(); i != particles.end(); i++)
	{
		Particle& p1 = **i;
		for (PParticleIterator j = particles.begin(); j != particles.end(); j++)
		{
			Particle& p2 = **j;
			if (*i != *j)
			{
				handler.compute(p1, p2);
			}
		}
	}
}

void ParticleContainer::ParticleCell::iterateParticlePairsExclusive(ParticleHandler& handler)
{
	for (PParticleIterator i = particles.begin(); i != particles.end(); i++)
	{
		Particle& p1 = **i;
		for (PParticleIterator j = i; j != particles.end(); j++)
		{
			if (*i != *j)
			{
				Particle& p2 = **j;
				handler.computeExclusive(p1, p2);
			}
		}
	}
}

void ParticleContainer::ParticleCell::combineParticlePairs(ParticleContainer::ParticleCell& other, ParticleHandler& handler)
{
	for (PParticleIterator i = particles.begin(); i != particles.end(); i++)
	{
		Particle& p1 = **i;
		for (PParticleIterator j = other.particles.begin(); j != other.particles.end(); j++)
		{
			Particle& p2 = **j;
			handler.compute(p1, p2);
		}
	}
}

void ParticleContainer::ParticleCell::combineParticlePairsExclusive(ParticleContainer::ParticleCell& other, ParticleHandler& handler)
{
	for (PParticleIterator i = particles.begin(); i != particles.end(); i++)
	{
		Particle& p1 = **i;
		for (PParticleIterator j = other.particles.begin(); j != other.particles.end(); j++)
		{
			Particle& p2 = **j;
			handler.computeExclusive(p1, p2);
		}
	}
}

void ParticleContainer::init(char* filename)
{

	double domainX, domainY;
	FileReader fileReader;

	fileReader.readFile(particles, filename, &reflective, &domainX, &domainY, &rCutOff);


	LOG4CXX_DEBUG(containerLogger, "init");

	numCellsX = ceil(domainX / rCutOff) + 2;
	numCellsY = ceil(domainY / rCutOff) + 2;


	for (int x = 0; x < numCellsX; x++)
	{
		for (int y = 0; y < numCellsY; y++)
		{
			cells.push_back(ParticleCell());

			char cT = cellType(x, y);

			if (cT != InnerCell)
			{
				int cell;
				flatten(x, y, &cell);
				boundryCells.push_back(cell);

				if (reflective)
					boundryConditions.push_back(Reflecting);

				/*if ((cT & BottomBoundry) || (cT & TopBoundry))
					boundryConditions.push_back(Reflecting);
				else if ((cT & LeftBoundry) || (cT & RightBoundry))
					boundryConditions.push_back(OutFlow);
				else
					LOG4CXX_DEBUG(containerLogger, "BoundryError");*/
			}
		}

	}

	updateCells();
	for (int i = 0; i < cells.size(); i++)
	{
		if (cells[i].count() != 0)
			LOG4CXX_DEBUG(containerLogger, " " << cells[i].count() << " particles in cell " << i);
	}
}


void ParticleContainer::updateCells()
{
	liveParticles = 0;
	for (int i = 0; i < particles.size(); i++)
	{
		Particle& p = particles[i];

		if (p.isDead())
			continue;

		liveParticles++;

		int oldCell = p.getCell();
		int cell;
		findCell(p.getX(), &cell);

		if (cell == oldCell)
		{
			continue;
		}

		if (oldCell != -1)
			cells[oldCell].remove(&p);

		if (cell != -1)
			cells[cell].insert(&p);


		p.setCell(cell);
		p.setType(cell); // for visualization purpuses#
	}
}

void ParticleContainer::findCell(utils::Vector<double, 3> position, int* cell)
{
	int x = floor(position[0] / (double)rCutOff);
	int y = floor(position[1] / (double)rCutOff);

	if (x < 0)
		x = 0;
	else if (x > numCellsX-1)
		x = numCellsX-1;

	if (y < 0)
		y = 0;
	else if (y > numCellsY-1)
		y = numCellsY-1;

	flatten(x, y, cell);
}

void ParticleContainer::flatten(int x, int y, int* c)
{
	*c = x + y * numCellsX;
}

void ParticleContainer::expand(int c, int* x, int* y)
{
	*x = c % numCellsX;
	*y = floor(c / numCellsX);
}

char ParticleContainer::cellType(int x, int y)
{
	bool left = x == 0;
	bool right = x == numCellsX - 1;
	bool bottom = y == 0;
	bool top = y == numCellsY - 1;

	char output = InnerCell;

	if (left)
		output |= LeftBoundry;
	if (right)
		output |= RightBoundry;
	if (bottom)
		output |= BottomBoundry;
	if (top)
		output |= TopBoundry;


	return output;
}

char ParticleContainer::cellType(int c)
{
	int x, y;
	expand(c, &x, &y);
	return cellType(x, y);
}

int ParticleContainer::getReflectingCell(int boundryCell)
{
	int x, y;
	expand(boundryCell, &x, &y);

	bool left = x == 0;
	bool right = x == numCellsX - 1;
	bool bottom = y == 0;
	bool top = y == numCellsY - 1;

	int cell = -1;

	if(left && !top && !bottom)
		flatten(1, y, &cell);
	else if (right && !top && !bottom)
		flatten(numCellsX - 2, y, &cell);
	else if (bottom && !left && !right)
		flatten(x, 1, &cell);
	else if (top && !left && !right)
		flatten(x, numCellsY - 2, &cell);

	return cell;
}

int ParticleContainer::count()
{
	return particles.size();
}

int ParticleContainer::live()
{
	return liveParticles;
}

Particle& ParticleContainer::operator[](int i)
{
	return particles[i];
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


		bool left = (i % numCellsX) != 0;
		bool right = (i + 1 % numCellsX) != 0;

		bool bottom = floor(i / numCellsX) != 0;
		bool top = (floor(i / numCellsX) + 1) != numCellsY;

		if (left)
			cells[i].combineParticlePairs(cells[i - 1], handler);
		if (right)
			cells[i].combineParticlePairs(cells[i + 1], handler);
		if (bottom)
			cells[i].combineParticlePairs(cells[i - numCellsX], handler);
		if (top)
			cells[i].combineParticlePairs(cells[i + numCellsX], handler);

		if (left && bottom)
			cells[i].combineParticlePairs(cells[i - 1 - numCellsX], handler);
		if (left && top)
			cells[i].combineParticlePairs(cells[i - 1 + numCellsX], handler);
		if (right && bottom)
			cells[i].combineParticlePairs(cells[i + 1 - numCellsX], handler);
		if (right && top)
			cells[i].combineParticlePairs(cells[i + 1 + numCellsX], handler);
	}
}

void ParticleContainer::iterateParticlePairsExclusive(ParticleHandler& handler)
{
	for (int i = 0; i < cells.size(); i++)
	{

		cells[i].iterateParticlePairsExclusive(handler);

		bool left = (i % numCellsX) != 0;
		bool right = (i + 1 % numCellsX) != 0;

		bool top = (floor(i / numCellsX) + 1) != numCellsY;

		if (right && cells.size() > (i +1))
			cells[i].combineParticlePairsExclusive(cells[i + 1], handler);

		if (top && cells.size() > (i + numCellsX))
			cells[i].combineParticlePairsExclusive(cells[i + numCellsX], handler);

		if (left && top && cells.size() > (i - 1 + numCellsX))
			cells[i].combineParticlePairsExclusive(cells[i - 1 + numCellsX], handler);
		if (right && top && cells.size() > (i + 1 + numCellsX))
			cells[i].combineParticlePairsExclusive(cells[i + 1 + numCellsX], handler);
	}
}

void ParticleContainer::iterateBoundryParticles(ParticleHandler& handler)
{
	for (int i = 0; i < boundryCells.size(); i++)
	{
		cells[boundryCells[i]].iterateParticles(handler);
	}
}

void ParticleContainer::iterateBoundryCells()
{
	for (int i = 0; i < boundryCells.size(); i++)
	{
		int boundry = boundryCells[i];

		cells[boundry].empty();
	}


	for (int d = 0; d < numDummies; d++)
	{
		particles.pop_back();
	}
	numDummies = 0;

	for (int i = 0; i < boundryCells.size(); i++)
	{
		int boundry = boundryCells[i];
		int bx, by;
		expand(boundry, &bx, &by);

		switch (boundryConditions[i])
		{
		case Reflecting:
		{
			int cell = getReflectingCell(boundry);
			int cellX, cellY;
			expand(cell, &cellX, &cellY);

			if (cell != -1 && cell < cells.size())
			{
				if (cellType(cell) != InnerCell)
				{
					LOG4CXX_ERROR(containerLogger, "reflecting cell cannot be a boundrycell");
					continue;
				}

				for (int p = 0; p < cells[cell].count(); p++)
				{

					Vector<double, 3> position = cells[cell][p]->getX();
					Vector<double, 3> cellPosition(0.0);
					cellPosition[0] = cellX * rCutOff;
					cellPosition[1] = cellY* rCutOff;

					Vector<double, 3> delta = position - cellPosition;

					if (cellY > by)
						delta[1] = -0.01;
					else if (cellY < by)
						delta[1] = rCutOff + 0.01;
					else if (cellX > bx)
						delta[0] = -0.01;
					else if (cellX < bx)
						delta[0] = rCutOff + 0.01;

					position = cellPosition + delta;
					Vector<double, 3> velocity;
					velocity[0] = velocity[1] = velocity[2] = 0;

					int dummyIndex = particles.size();
					Particle dummy(position, velocity, 10000);
					dummy.setDead(true);


					particles.push_back(dummy);
					cells[boundry].insert(&(particles[dummyIndex]));

					numDummies++;
				}
			}
		}
		break;

		default:
			break;
		}
	}
}