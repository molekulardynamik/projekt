#include "ParticleContainer.h"
#include <omp.h>

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

	createCells();

	// distribute particles
	for (int i = 0; i < particles.size(); i++)
	{
		Particle& particle = particles[i];
		ParticleCell& cell = findCell(particle.getX());
		cell.addParticle(particle);
	}

	LOG4CXX_DEBUG(containerLogger, "finished creating Container");
}

void ParticleContainer::createCells()
{
	vector<vector<ParticleCell>*> tempDomains;

	int numThreads = 1;
#pragma omp parallel shared(numThreads)
	{
		numThreads = omp_get_num_threads();
	}


	domainSize_ = ceil(numCells_[0] / (double) numThreads);
	if(domainSize_ < 3)
	{
		numThreads = floor(numCells_[0] / 3.0);
		domainSize_ = ceil(numCells_[0] / (double) numThreads);
	}

	omp_set_num_threads(numThreads);

#pragma omp parallel shared(numThreads)
	{
		numThreads = omp_get_num_threads();
	}


	particleDomains_.resize(numThreads);

#pragma omp parallel for
	for (int d = 0; d < particleDomains_.size(); d++)
	{
		particleDomains_[d] = new vector<ParticleCell>();
	}
#pragma omp barrier

	LOG4CXX_DEBUG(containerLogger,
			"threads : " << particleDomains_.size() << " domainSize " << domainSize_);

	// create Cells
	vector<ParticleCell> particleCells;

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

				int d = floor(x / domainSize_);

				particleDomains_[d]->push_back(
						ParticleCell(i, d, position, rCutOff_));
				i++;
			}
		}
	}

	i = 0;
	// bind neighbors
	for (int x = 0; x < numCells_[0]; x++)
	{
		for (int y = 0; y < numCells_[1]; y++)
		{
			for (int z = 0; z < numCells_[2]; z++)
			{
				ParticleCell& cell = findCell(x, y, z);

				if (i == 55)
				{
					int f = 0;
					LOG4CXX_DEBUG(containerLogger, "found it" << f);
				}

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
				else
				{
					cell.setCellType(ParticleCell::InnerCell);
				}

				if (cell.getIndex() == 55)
					LOG4CXX_DEBUG(containerLogger,
							"cell 55 type: " << cell.getCellType() << " x: " << x << ", y: " << y << ", z: " << z);


				bool xN[3];
				xN[0] = left;
				xN[1] = true;
				xN[2] = right;
				bool yN[3];
				yN[0] = bottom;
				yN[1] = true;
				yN[2] = top;
				bool zN[3];
				zN[0] = front;
				zN[1] = true;
				zN[2] = back;

				int i=0;
				for(int iz = 0; iz < 3; iz++)
				{
					for(int iy = 0; iy < 3; iy++)
					{
						for(int ix = 0; ix < 3; ix++)
						{
							if(ix == 1 && iy == 1 && iz == 1)
								continue;
							if(xN[ix] && yN[iy] && zN[iz])
								cell.setNeighbor(&findCell(x - 1 + ix, y - 1 + iy, z - 1 + iz), (ParticleCell::Neighborhood)i);

							i++;
						}
					}
				}


//				if (left && bottom && front)
//					cell.setNeighbor(&findCell(x - 1, y - 1, z - 1),
//							ParticleCell::LeftBottomFront);
//				if (bottom && front)
//					cell.setNeighbor(&findCell(x, y - 1, z - 1),
//							ParticleCell::BottomFront);
//				if (right && bottom && front)
//					cell.setNeighbor(&findCell(x + 1, y - 1, z - 1),
//							ParticleCell::RightBottomFront);
//				if (left && front)
//					cell.setNeighbor(&findCell(x - 1, y, z - 1),
//							ParticleCell::LeftFront);
//				if (front)
//					cell.setNeighbor(&findCell(x, y, z - 1),
//							ParticleCell::Front);
//				if (right && front)
//					cell.setNeighbor(&findCell(x + 1, y, z - 1),
//							ParticleCell::RightFront);
//				if (left && top && front)
//					cell.setNeighbor(&findCell(x - 1, y + 1, z - 1),
//							ParticleCell::LeftTopFront);
//				if (top && front)
//					cell.setNeighbor(&findCell(x, y + 1, z - 1),
//							ParticleCell::TopFront);
//				if (right && top && front)
//					cell.setNeighbor(&findCell(x + 1, y + 1, z - 1),
//							ParticleCell::RightTopFront);
//
//				if (left && bottom)
//					cell.setNeighbor(&findCell(x - 1, y - 1, z),
//							ParticleCell::LeftBottom);
//				if (bottom)
//					cell.setNeighbor(&findCell(x, y - 1, z),
//							ParticleCell::Bottom);
//				if (right && bottom)
//					cell.setNeighbor(&findCell(x + 1, y - 1, z),
//							ParticleCell::RightBottom);
//				if (left)
//					cell.setNeighbor(&findCell(x - 1, y, z),
//							ParticleCell::Left);
//				if (right)
//					cell.setNeighbor(&findCell(x + 1, y, z),
//							ParticleCell::Right);
//				if (left && top)
//					cell.setNeighbor(&findCell(x - 1, y + 1, z),
//							ParticleCell::LeftTop);
//				if (top)
//					cell.setNeighbor(&findCell(x, y + 1, z), ParticleCell::Top);
//
//				if (right && top)
//					cell.setNeighbor(&findCell(x + 1, y + 1, z),
//							ParticleCell::RightTop);
//
//				if (left && bottom && back)
//					cell.setNeighbor(&findCell(x - 1, y - 1, z + 1),
//							ParticleCell::LeftBottomBack);
//				if (bottom && back)
//					cell.setNeighbor(&findCell(x, y - 1, z + 1),
//							ParticleCell::BottomBack);
//				if (right && bottom && back)
//					cell.setNeighbor(&findCell(x + 1, y - 1, z + 1),
//							ParticleCell::RightBottomBack);
//				if (left && back)
//					cell.setNeighbor(&findCell(x - 1, y, z + 1),
//							ParticleCell::LeftBack);
//				if (back)
//					cell.setNeighbor(&findCell(x, y, z + 1),
//							ParticleCell::Back);
//				if (right && back)
//					cell.setNeighbor(&findCell(x + 1, y, z + 1),
//							ParticleCell::RightBack);
//				if (left && top && back)
//					cell.setNeighbor(&findCell(x - 1, y + 1, z + 1),
//							ParticleCell::LeftTopBack);
//				if (top && back)
//					cell.setNeighbor(&findCell(x, y + 1, z + 1),
//							ParticleCell::TopBack);
//				if (right && top && back)
//					cell.setNeighbor(&findCell(x + 1, y + 1, z + 1),
//							ParticleCell::RightTopBack);

				//LOG4CXX_DEBUG(containerLogger, "cell " << i  << " has " << cell.countNeighbors() << " neighbors" << " and is " << cell.getCellType());
				//cell.printNeighbors();

				i++;
			}
		}
	}

}

void ParticleContainer::updateCells()
{
	for (int d = 0; d < particleDomains_.size(); d++)
	{
		vector<ParticleCell>* particleCells = particleDomains_[d];
		for (int i = 0; i < particleCells->size(); i++)
		{
			(*particleCells)[i].checkParticles();
		}
	}
}

int ParticleContainer::countParticles()
{
	int numParticles = 0;
	for (int d = 0; d < particleDomains_.size(); d++)
	{
		vector<ParticleCell>* particleCells = particleDomains_[d];
		for (int i = 0; i < particleCells->size(); i++)
		{
			numParticles += (*particleCells)[i].countParticles();
		}
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
	int cell, domain;
	domain = floor(cellX / domainSize_);
	cellX = cellX % domainSize_;

	flatten(cellX, cellY, cellZ, &cell);

	//LOG4CXX_DEBUG(containerLogger, "find cell for " << cellX << ", " << cellY << ", " << cellZ << " = " << cell << " at domain " << domain);
	//LOG4CXX_DEBUG(containerLogger, "domain size " << particleDomains_[domain]->size());

	return (*particleDomains_[domain])[cell];
}

void ParticleContainer::flatten(int cellX, int cellY, int cellZ, int* cell)
{
	*cell = cellX * numCells_[1] * numCells_[2] + cellY * numCells_[2] + cellZ;
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
#pragma omp parallel for
	for (int d = 0; d < particleDomains_.size(); d++)
	{
		vector<ParticleCell>* particleCells = particleDomains_[d];
		for (int i = 0; i < particleCells->size(); i++)
		{
			(*particleCells)[i].iterateParticles(handler);
		}
	}
#pragma omp barrier
}

void ParticleContainer::iterateParticlesSingleThreaded(ParticleHandler& handler)
{
	for (int d = 0; d < particleDomains_.size(); d++)
	{
		vector<ParticleCell>* particleCells = particleDomains_[d];
		for (int i = 0; i < particleCells->size(); i++)
		{
			(*particleCells)[i].iterateParticles(handler);
		}
	}
}

void ParticleContainer::iterateParticlePairs(ParticleHandler& handler)
{
	LOG4CXX_ERROR(containerLogger, "IJ");
	for (int d = 0; d < particleDomains_.size(); d++)
	{
		vector<ParticleCell>* particleCells = particleDomains_[d];
		for (int i = 0; i < particleCells->size(); i++)
		{
			(*particleCells)[i].iterateParticlePairs(handler);
		}
	}
}

//void ParticleContainer::iterateParticlePairsSymmetric(ParticleHandler& handler)
//{
//	for (int d = 0; d < particleDomains_.size(); d++)
//	{
//		vector<ParticleCell>* particleCells = particleDomains_[d];
//		for (int i = 0; i < particleCells->size(); i++)
//		{
//			(*particleCells)[i].iterateParticlePairsSymmetric(handler);
//		}
//	}
//}

void ParticleContainer::iterateParticlePairsSymmetric(ParticleHandler& handler)
{
#pragma omp parallel for
	for (int d = 0; d < particleDomains_.size(); d++)
	{
		vector<ParticleCell>* particleCells = particleDomains_[d];
		for (int i = 0; i < particleCells->size(); i++)
		{
			int x = floor(i / (numCells_[1] * numCells_[2]));
			if(x >= 2)
				(*particleCells)[i].iterateParticlePairsSymmetric(handler);
		}
	}
#pragma omp barrier

#pragma omp parallel for
	for (int d = 0; d < particleDomains_.size(); d++)
	{
		vector<ParticleCell>* particleCells = particleDomains_[d];
		for (int i = 0; i < particleCells->size(); i++)
		{
			int x = floor(i / (numCells_[1] * numCells_[2]));
			if (x <= 1)
				(*particleCells)[i].iterateParticlePairsSymmetric(handler);
		}
	}
#pragma omp barrier
}


void ParticleContainer::iterateBoundaries()
{
	for (int d = 0; d < particleDomains_.size(); d++)
	{
		vector<ParticleCell>* particleCells = particleDomains_[d];
		for (int i = 0; i < particleCells->size(); i++)
		{
			(*particleCells)[i].applyBoundaryCondition();
		}
	}
}

void ParticleContainer::clearBoundaries()
{
#pragma omp parallel for
	for (int d = 0; d < particleDomains_.size(); d++)
	{
		vector<ParticleCell>* particleCells = particleDomains_[d];
		for (int i = 0; i < particleCells->size(); i++)
		{
			(*particleCells)[i].clearBoundary();
		}

		for (int i = 0; i < particleCells->size(); i++)
		{
			if ((*particleCells)[i].countParticles() != 0
					&& (*particleCells)[i].getCellType()
							!= ParticleCell::InnerCell)
				LOG4CXX_ERROR(containerLogger, "boundary nicht leer");
		}
	}
#pragma omp barrier
}

