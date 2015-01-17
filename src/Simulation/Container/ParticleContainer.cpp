#include "ParticleContainer.h"

#include <log4cxx/logger.h>

using namespace Simulation;
using namespace utils;
using namespace std;

using namespace log4cxx;

// Define static logger variable
LoggerPtr containerLogger(Logger::getLogger("ParticleContanier"));

std::map<ParticleCell::CellType,ParticleCell::BoundaryCondition> ParticleCell::boundaryConditions;


ParticleContainer::ParticleContainer(
		std::auto_ptr<simulation_t> simulationConfig)
{
	LOG4CXX_DEBUG(containerLogger, "creating Container");

	ParticleCell::boundaryConditions[ParticleCell::BottomBoundary] = (ParticleCell::BoundaryCondition)simulationConfig->boundaries().Bottom();
	ParticleCell::boundaryConditions[ParticleCell::LeftBoundary] = (ParticleCell::BoundaryCondition)simulationConfig->boundaries().Left();
	ParticleCell::boundaryConditions[ParticleCell::RightBoundary] = (ParticleCell::BoundaryCondition)simulationConfig->boundaries().Right();
	ParticleCell::boundaryConditions[ParticleCell::TopBoundary] = (ParticleCell::BoundaryCondition)simulationConfig->boundaries().Top();


	// setUp
	domain_[0] = simulationConfig->domain().X();
	domain_[1] = simulationConfig->domain().Y();
	domain_[2] = simulationConfig->domain().Z();
	rCutOff_ = simulationConfig->rCutOff();

	numCells_[0] = ceil(domain_[0] / rCutOff_) + 2;
	numCells_[1] = ceil(domain_[1] / rCutOff_) + 2;
	numCells_[2] = ceil(domain_[2] / rCutOff_) + 2;

	vector<Particle> particles;
	ParticleGenerator::readFile(simulationConfig, particles);




	LOG4CXX_DEBUG(containerLogger,
			"DomainX: " << domain_[0] << " DomainY: " << domain_[1] << " rCutOff: " << rCutOff_);
	LOG4CXX_DEBUG(containerLogger,
			"NumCellsX: " << numCells_[0] << " NumCellsY: " << numCells_[1]);
	LOG4CXX_DEBUG(containerLogger,
			"Particles: " << particles.size());

	// create Cells
	int i = 0;
	for (int x = 0; x < numCells_[0]; x++)
	{
		for (int y = 0; y < numCells_[1]; y++)
		{
			Vector<double, 3> position(0.0);
			position[0] = (x - 1) * rCutOff_;
			position[1] = (y - 1) * rCutOff_;

			particleCells_.push_back(ParticleCell(i, position, rCutOff_));
			//LOG4CXX_DEBUG(containerLogger,"created cell  " << particleCells_.back().getIndex() << " at position " << particleCells_.back().getBottomLeftCorner()[0] << ", " << particleCells_.back().getBottomLeftCorner()[1]);

			i++;
		}
	}

	// bind neighbors
	i = 0;
	for (int x = 0; x < numCells_[0]; x++)
	{
		for (int y = 0; y < numCells_[1]; y++)
		{
			ParticleCell& cell = particleCells_[i];

			bool left = x != 0;
			bool right = x != numCells_[0] - 1;

			bool bottom = y != 0;
			bool top = y != numCells_[1] - 1;

			if(!(left && right && bottom && top))
			{
				if(!bottom && left && right && top)
				{
					cell.setCellType(ParticleCell::BottomBoundary);
					cell.setOppositeHaloCell(&findCell(x, numCells_[1] - 2));
				}
				else if(!left && right && bottom && top)
				{
					cell.setCellType(ParticleCell::LeftBoundary);
					cell.setOppositeHaloCell(&findCell(numCells_[0] - 2, y));
				}
				else if(!right && left && bottom && top)
				{
					cell.setCellType(ParticleCell::RightBoundary);
					cell.setOppositeHaloCell(&findCell(1, y));
				}
				else if(!top && left && right && bottom)
				{
					cell.setCellType(ParticleCell::TopBoundary);
					cell.setOppositeHaloCell(&findCell(x, 1));
				}
				else
				{
					cell.setCellType(ParticleCell::Corner);
					if(!bottom && !left && right && top)
						cell.setOppositeHaloCell(&findCell(numCells_[0] - 2, numCells_[1] - 2));
					else if(!bottom && !right && left && top)
						cell.setOppositeHaloCell(&findCell(1, numCells_[1] - 2));
					else if(!top && !left && right && bottom)
						cell.setOppositeHaloCell(&findCell(numCells_[0] - 2, 1));
					else if(!top && !right && left && bottom)
						cell.setOppositeHaloCell(&findCell(1, 1));
				}

				//if(cell.getCellType() != ParticleCell::Corner)
				//	LOG4CXX_DEBUG(containerLogger, "boundry at " << cell.getBottomLeftCorner()[0] << ", " << cell.getBottomLeftCorner()[1]
				//								<< " with oppositeHaloCell at " << cell.getOppositeHaloCell()->getBottomLeftCorner()[0] << ", " <<  cell.getOppositeHaloCell()->getBottomLeftCorner()[1]);
			}

			int neighborIndex;

			if(bottom && left)
				cell.setNeighbor(&findCell(x-1, y-1), ParticleCell::BottomLeft);
			if(bottom)
				cell.setNeighbor(&findCell(x, y-1), ParticleCell::Bottom);
			if(bottom && right)
				cell.setNeighbor(&findCell(x+1, y-1), ParticleCell::BottomRight);
			if(left)
				cell.setNeighbor(&findCell(x-1, y), ParticleCell::Left);
			if(right)
				cell.setNeighbor(&findCell(x+1, y), ParticleCell::Right);
			if(top && left)
				cell.setNeighbor(&findCell(x-1, y+1), ParticleCell::TopLeft);
			if(top)
				cell.setNeighbor(&findCell(x, y+1), ParticleCell::Top);
			if(top && right)
				cell.setNeighbor(&findCell(x+1, y+1), ParticleCell::TopRight);

			//LOG4CXX_DEBUG(containerLogger, "cell " << i  << " has " << cell.countNeighbors() << " neighbors" << " and is " << cell.getCellType());
			//cell.printNeighbors();

			i++;
		}
	}

	// distribute particles
	for (int i = 0; i < particles.size(); i++)
	{
		Particle& particle = particles[i];
		ParticleCell& cell = findCell(particle.getX());
		cell.addParticle(particle);

		//LOG4CXX_DEBUG(containerLogger, "particle " << i << " at position " << particle.getX()[0] << ", " << particle.getX()[1]);
		//LOG4CXX_DEBUG(containerLogger,"in cell  " << cell.getIndex() << " at position " << cell.getBottomLeftCorner()[0] << ", " << cell.getBottomLeftCorner()[1]);
	}

	LOG4CXX_DEBUG(containerLogger, "finished creating Container");
}

void ParticleContainer::updateCells()
{
	for(int i=0; i<particleCells_.size(); i++)
	{
		particleCells_[i].checkParticles();
	}
}

int ParticleContainer::countParticles()
{
	int numParticles = 0;
	for(int i=0; i<particleCells_.size(); i++)
	{
		numParticles += particleCells_[i].countParticles();
	}
	return numParticles;
}

double ParticleContainer::getRCutOff()
{
	return rCutOff_;
}


ParticleCell& ParticleContainer::findCell(Vector<double, 3> position)
{
	int x = floor(position[0] / (double) rCutOff_) + 1;
	int y = floor(position[1] / (double) rCutOff_) + 1;

	return findCell(x,y);
}

ParticleCell& ParticleContainer::findCell(int cellX, int cellY)
{
	int cell;
	flatten(cellX, cellY, &cell);

	return particleCells_[cell];
}


void ParticleContainer::flatten(int cellX, int cellY, int* cell)
{
	*cell = cellX * numCells_[1] + cellY;
}

void ParticleContainer::expand(int* cellX, int* cellY, int c)
{
	*cellX = floor(c / numCells_[1]);
	*cellY = c % numCells_[1];
}

void ParticleContainer::iterateParticles(ParticleHandler& handler)
{
	for (int i = 0; i < particleCells_.size(); i++)
	{
		particleCells_[i].iterateParticles(handler);
	}
}

void ParticleContainer::iterateParticlePairs(ParticleHandler& handler)
{
	for (int i = 0; i < particleCells_.size(); i++)
	{
		particleCells_[i].iterateParticlePairs(handler);
	}
}

void ParticleContainer::iterateParticlePairsSymmetric(ParticleHandler& handler)
{
	for (int i = 0; i < particleCells_.size(); i++)
	{
		particleCells_[i].iterateParticlePairsSymmetric(handler);
	}
}

void ParticleContainer::iterateBoundaries()
{
	for (int i = 0; i < particleCells_.size(); i++)
	{
		particleCells_[i].applyBoundaryCondition();
	}
}

void ParticleContainer::clearBoundaries()
{
	for (int i = 0; i < particleCells_.size(); i++)
	{
		particleCells_[i].clearBoundary();
	}

	for (int i = 0; i < particleCells_.size(); i++)
	{
		if(particleCells_[i].countParticles() != 0 && particleCells_[i].getCellType() != ParticleCell::InnerCell)
			LOG4CXX_ERROR(containerLogger, "boundary nicht leer");
	}
}

