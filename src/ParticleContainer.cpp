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
	fileReader.readFile(particles, filename, &domainX, &domainY, &rCutOff);

	numCellsX = ceil(domainX / rCutOff) + 2;
	numCellsY = ceil(domainY / rCutOff) + 2;

	int i = 0;
	for (int x = 0; x < numCellsX; x++)
	{
		for (int y = 0; y < numCellsY; y++)
		{
			cells.push_back(ParticleCell());

			if (isBoundry(x,y))
			{
				int cell;

				flatten(x, y, &cell);
				boundryCells.push_back(cell);
				LOG4CXX_DEBUG(containerLogger, "Boundry: " << x << ", " << y << ", " << i << " == " << cell);
			}

			i++;
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
	for (ParticleIterator i = particles.begin(); i != particles.end(); i++)
	{
		Particle& p = *i;

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

bool ParticleContainer::isBoundry(int x, int y)
{
	return (x == numCellsX - 1 || y == numCellsY - 1 || x == 0 || y == 0);
}

bool ParticleContainer::isBoundry(int c)
{
	int x, y;
	expand(c, &x, &y);
	return isBoundry(x, y);
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
	ParticleIterator it = particles.begin();
	advance(it, i);
	return *it;
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

		if (right)
			cells[i].combineParticlePairsExclusive(cells[i + 1], handler);
		if (top)
			cells[i].combineParticlePairsExclusive(cells[i + numCellsX], handler);

		if (left && top)
			cells[i].combineParticlePairsExclusive(cells[i - 1 + numCellsX], handler);
		if (right && top)
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

void ParticleContainer::emptyBoundryCells()
{
	for (int i = 0; i < boundryCells.size(); i++)
	{
		cells[boundryCells[i]].empty();
	}
}