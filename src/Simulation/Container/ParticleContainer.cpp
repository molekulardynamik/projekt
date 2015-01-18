#include "ParticleContainer.h"

#include <log4cxx/logger.h>

using namespace Simulation;
using namespace utils;
using namespace std;

using namespace log4cxx;

// Define static logger variable
LoggerPtr containerLogger(Logger::getLogger("ParticleContanier"));

std::map<ParticleCell::CellType, ParticleCell::BoundaryCondition> ParticleCell::boundaryConditions;

ParticleContainer::ParticleContainer(
		std::auto_ptr<simulation_t> simulationConfig)
{
	LOG4CXX_DEBUG(containerLogger, "creating Container");

	ParticleCell::boundaryConditions[ParticleCell::LeftBoundary] =
			(ParticleCell::BoundaryCondition) simulationConfig->boundaries().X();
	ParticleCell::boundaryConditions[ParticleCell::RightBoundary] =
			(ParticleCell::BoundaryCondition) simulationConfig->boundaries().X();
	ParticleCell::boundaryConditions[ParticleCell::BottomBoundary] =
			(ParticleCell::BoundaryCondition) simulationConfig->boundaries().Y();
	ParticleCell::boundaryConditions[ParticleCell::TopBoundary] =
			(ParticleCell::BoundaryCondition) simulationConfig->boundaries().Y();
	ParticleCell::boundaryConditions[ParticleCell::FrontBoundary] =
			(ParticleCell::BoundaryCondition) simulationConfig->boundaries().Z();
	ParticleCell::boundaryConditions[ParticleCell::BackBoundary] =
			(ParticleCell::BoundaryCondition) simulationConfig->boundaries().Z();

	ParticleProperty::wallType() = simulationConfig->wallType();

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
			"DomainX: " << domain_[0] << " DomainY: " << domain_[1] << " DomainZ: " << domain_[2] << " rCutOff: " << rCutOff_);
	LOG4CXX_DEBUG(containerLogger,
			"NumCellsX: " << numCells_[0] << " NumCellsY: " << numCells_[1] << " NumCellsZ: " << numCells_[2]);
	LOG4CXX_DEBUG(containerLogger, "Particles: " << particles.size());

	// create Cells
	int i = 0;
	for (int x = 0; x < numCells_[0]; x++)
	{
		for (int y = 0; y < numCells_[1]; y++)
		{
			for (int z = 0; z < numCells_[2]; z++)
			{
				Vector<double, 3> position(0.0);
				position[0] = (x - 1) * rCutOff_;
				position[1] = (y - 1) * rCutOff_;
				position[2] = (z - 1) * rCutOff_;

				particleCells_.push_back(ParticleCell(i, position, rCutOff_));
				//LOG4CXX_DEBUG(containerLogger,"created cell  " << particleCells_.back().getIndex() << " at position " << particleCells_.back().getBottomLeftCorner()[0] << ", " << particleCells_.back().getBottomLeftCorner()[1]);

				i++;
			}
		}
	}

	// bind neighbors
	i = 0;
	for (int x = 0; x < numCells_[0]; x++)
	{
		for (int y = 0; y < numCells_[1]; y++)
		{
			for (int z = 0; z < numCells_[2]; z++)
			{
				ParticleCell& cell = particleCells_[i];

				bool left = x != 0;
				bool right = x != numCells_[0] - 1;

				bool bottom = y != 0;
				bool top = y != numCells_[1] - 1;

				bool front = z != 0;
				bool back = z != numCells_[2] - 1;

				if (!(left && right && bottom && top && front && back))
				{
					int oX = x, oY = y, oZ = z;

					if (!left && right)
						oX = numCells_[0] - 2;
					else if (left && !right)
						oX = 1;

					if (!bottom && top)
						oY = numCells_[1] - 2;
					else if (bottom && !top)
						oY = 1;

					if (!front && back)
						oZ = numCells_[2] - 2;
					else if (front && !back)
						oZ = 1;

					cell.setOppositeHaloCell(&findCell(oX, oY, oZ));

					if (!left && right && bottom && top && front && back)
					{
						cell.setCellType(ParticleCell::LeftBoundary);
					}
					else if (!right && left && bottom && top && front && back)
					{
						cell.setCellType(ParticleCell::RightBoundary);
					}
					else if (!bottom && left && right && top && front && back)
					{
						cell.setCellType(ParticleCell::BottomBoundary);
					}
					else if (!top && left && right && bottom && front && back)
					{
						cell.setCellType(ParticleCell::TopBoundary);
					}
					else if (!front && left && right && bottom && back)
					{
						cell.setCellType(ParticleCell::FrontBoundary);
					}
					else if (!back && left && right && bottom && front)
					{
						cell.setCellType(ParticleCell::BackBoundary);
					}
					else
					{
						cell.setCellType(ParticleCell::Corner);

					}

					//if(cell.getCellType() != ParticleCell::Corner)
					//	LOG4CXX_DEBUG(containerLogger, "boundry at " << cell.getBottomLeftCorner()[0] << ", " << cell.getBottomLeftCorner()[1]
					//								<< " with oppositeHaloCell at " << cell.getOppositeHaloCell()->getBottomLeftCorner()[0] << ", " <<  cell.getOppositeHaloCell()->getBottomLeftCorner()[1]);
				}

				if (left && bottom && front)
					cell.setNeighbor(&findCell(x - 1, y - 1, z - 1),
							ParticleCell::LeftBottomFront);
				if (bottom && front)
					cell.setNeighbor(&findCell(x, y - 1, z - 1),
							ParticleCell::BottomFront);
				if (right && bottom && front)
					cell.setNeighbor(&findCell(x + 1, y - 1, z - 1),
							ParticleCell::RightBottomFront);
				if (left && front)
					cell.setNeighbor(&findCell(x - 1, y, z - 1),
							ParticleCell::LeftFront);
				if (front)
					cell.setNeighbor(&findCell(x, y, z - 1),
							ParticleCell::Front);
				if (right && front)
					cell.setNeighbor(&findCell(x + 1, y, z - 1),
							ParticleCell::RightFront);
				if (left && top && front)
					cell.setNeighbor(&findCell(x - 1, y + 1, z - 1),
							ParticleCell::LeftTopFront);
				if (top && front)
					cell.setNeighbor(&findCell(x, y + 1, z - 1),
							ParticleCell::TopFront);
				if (right && top && front)
					cell.setNeighbor(&findCell(x + 1, y + 1, z - 1),
							ParticleCell::RightTopFront);

				if (left && bottom)
					cell.setNeighbor(&findCell(x - 1, y - 1, z),
							ParticleCell::LeftBottom);
				if (bottom)
					cell.setNeighbor(&findCell(x, y - 1, z),
							ParticleCell::Bottom);
				if (right && bottom)
					cell.setNeighbor(&findCell(x + 1, y - 1, z),
							ParticleCell::RightBottom);
				if (left)
					cell.setNeighbor(&findCell(x - 1, y, z),
							ParticleCell::Left);
				if (right)
					cell.setNeighbor(&findCell(x + 1, y, z),
							ParticleCell::Right);
				if (left && top)
					cell.setNeighbor(&findCell(x - 1, y + 1, z),
							ParticleCell::LeftTop);
				if (top)
					cell.setNeighbor(&findCell(x, y + 1, z), ParticleCell::Top);

				if (right && top)
					cell.setNeighbor(&findCell(x + 1, y + 1, z),
							ParticleCell::RightTop);

				if (left && bottom && back)
					cell.setNeighbor(&findCell(x - 1, y - 1, z + 1),
							ParticleCell::LeftBottomBack);
				if (bottom && back)
					cell.setNeighbor(&findCell(x, y - 1, z + 1),
							ParticleCell::BottomBack);
				if (right && bottom && back)
					cell.setNeighbor(&findCell(x + 1, y - 1, z + 1),
							ParticleCell::RightBottomBack);
				if (left && back)
					cell.setNeighbor(&findCell(x - 1, y, z + 1),
							ParticleCell::LeftBack);
				if (back)
					cell.setNeighbor(&findCell(x, y, z + 1),
							ParticleCell::Back);
				if (right && back)
					cell.setNeighbor(&findCell(x + 1, y, z + 1),
							ParticleCell::RightBack);
				if (left && top && back)
					cell.setNeighbor(&findCell(x - 1, y + 1, z + 1),
							ParticleCell::LeftTopBack);
				if (top && back)
					cell.setNeighbor(&findCell(x, y + 1, z + 1),
							ParticleCell::TopBack);
				if (right && top && back)
					cell.setNeighbor(&findCell(x + 1, y + 1, z + 1),
							ParticleCell::RightTopBack);

				//LOG4CXX_DEBUG(containerLogger, "cell " << i  << " has " << cell.countNeighbors() << " neighbors" << " and is " << cell.getCellType());
				//cell.printNeighbors();

				i++;
			}
		}
	}

	// distribute particles
	for (int i = 0; i < particles.size(); i++)
	{
		Particle& particle = particles[i];
		ParticleCell& cell = findCell(particle.getX());
		cell.addParticle(particle);

	}

	LOG4CXX_DEBUG(containerLogger, "finished creating Container");
}

void ParticleContainer::updateCells()
{
	for (int i = 0; i < particleCells_.size(); i++)
	{
		particleCells_[i].checkParticles();
	}
}

int ParticleContainer::countParticles()
{
	int numParticles = 0;
	for (int i = 0; i < particleCells_.size(); i++)
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
	int z = floor(position[2] / (double) rCutOff_) + 1;

	return findCell(x, y, z);
}

ParticleCell& ParticleContainer::findCell(int cellX, int cellY, int cellZ)
{
	int cell;
	flatten(cellX, cellY, cellZ, &cell);

	return particleCells_[cell];
}

void ParticleContainer::flatten(int cellX, int cellY, int cellZ, int* cell)
{
	*cell = cellX * numCells_[1] * numCells_[2] + cellY * numCells_[2]+ cellZ;
}

void ParticleContainer::expand(int* cellX, int* cellY, int* cellZ, int c)
{
	*cellX = floor(c / (numCells_[1] * numCells_[2]));
	c -= *cellX * numCells_[1] * numCells_[2];
	*cellY = floor(c / numCells_[2]);
	c -= *cellY * numCells_[2];
	*cellZ = c;
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
		if (particleCells_[i].countParticles() != 0
				&& particleCells_[i].getCellType() != ParticleCell::InnerCell)
			LOG4CXX_ERROR(containerLogger, "boundary nicht leer");
	}
}

