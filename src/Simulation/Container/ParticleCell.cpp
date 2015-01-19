#include "ParticleCell.h"

#include <log4cxx/logger.h>

using namespace Simulation;
using namespace utils;
using namespace std;

using namespace log4cxx;

// Define static logger variable
LoggerPtr cellLogger(Logger::getLogger("ParticleCell"));


void ParticleCell::moveParticle(ParticleCell& from, ParticleCell& to,
		Particle& particle)
{
	to.addParticle(particle);
	from.removeParticle(particle);
}

ParticleCell::ParticleCell(int index, int domain, Vector<double, 3> leftBottomFront, double size) :
		index_(index), domain_(domain), leftBottomFrontCorner_(leftBottomFront), size_(size), cellType_(InnerCell)
{
	for (int i = 0; i < 26; i++)
	{
		neighbors_[i] = 0;
	}
}

void ParticleCell::setCellType(CellType cellType)
{
	cellType_ = cellType;
}

ParticleCell::CellType ParticleCell::getCellType()
{
	return cellType_;
}


void ParticleCell::setNeighbor(ParticleCell* neighbor,
		Neighborhood neighborhood)
{
	neighbors_[neighborhood] = neighbor;
}

int ParticleCell::countNeighbors()
{
	int count = 0;
	for(int i=0; i<26; i++)
	{
		if(neighbors_[i])
			count++;
	}

	return count;
}

void ParticleCell::printNeighbors()
{
	stringstream out;
	out << "Cell " << index_ << " has neighbor ";
	for(int i=0; i<26; i++)
	{
		if(neighbors_[i])
			out << neighbors_[i]->getIndex() << " ,";
	}

	LOG4CXX_DEBUG(cellLogger, out.str());
}

void ParticleCell::setOppositeHaloCell(ParticleCell* haloCell)
{
	oppositeHaloCell_ = haloCell;
}

ParticleCell* ParticleCell::getOppositeHaloCell()
{
	return oppositeHaloCell_;
}


int ParticleCell::getIndex()
{
	return index_;
}

Vector<double, 3> ParticleCell::getLeftBottomFrontCorner()
{
	return leftBottomFrontCorner_;
}

void ParticleCell::addParticle(Particle& particle)
{
	if (!checkParticle(particle))
		return;

	if(particles_.size() >5000)
	{
		LOG4CXX_ERROR(cellLogger, "Too many particles");
		return;
	}

	if(boundaryConditions[cellType_] == Periodic)
	{
		Vector<double, 3> diff = oppositeHaloCell_->leftBottomFrontCorner_ - leftBottomFrontCorner_;
		particle.getX() = particle.getX() + diff;
		oppositeHaloCell_->addParticle(particle);
	}
	else
	{
		particles_.push_back(particle);
		particles_.back().getCell() = domain_;
	}
}

void ParticleCell::removeParticle(Particle& particle)
{
	particles_.remove(particle);
}

void ParticleCell::checkParticles()
{

	// iterates through all particles in this cell and checks if they still belong to this cell
	// if not, the particle is moved to the correct neighbor
	// since the iterator is then obsolete, we have to restart the iteration

	int i = 0;
	list<Particle>::iterator iter = particles_.begin();
	while(iter!=particles_.end())
	{
		if (!checkParticle(*iter))
		{
			iter = particles_.begin();
			advance(iter, i);
		}
		else
		{
			++i;
			++iter;
		}
	}
}

int ParticleCell::countParticles()
{
	return particles_.size();
}

bool ParticleCell::checkParticle(Particle& particle)
{
	Vector<double, 3>& position = particle.getX();
	if (position[0] < leftBottomFrontCorner_[0] && neighbors_[Left])
		moveParticle(*this, *neighbors_[Left], particle);
	else if (position[0] >= leftBottomFrontCorner_[0] + size_ && neighbors_[Right])
		moveParticle(*this, *neighbors_[Right], particle);
	else if (position[1] < leftBottomFrontCorner_[1] && neighbors_[Bottom])
		moveParticle(*this, *neighbors_[Bottom], particle);
	else if (position[1] >= leftBottomFrontCorner_[1] + size_ && neighbors_[Top])
		moveParticle(*this, *neighbors_[Top], particle);
	else if(position[2] < leftBottomFrontCorner_[2] && neighbors_[Front])
		moveParticle(*this, *neighbors_[Front], particle);
	else if(position[2] >= leftBottomFrontCorner_[2] + size_ && neighbors_[Back])
		moveParticle(*this, *neighbors_[Back], particle);
	else
		return true;

	return false;
}

void ParticleCell::iterateParticles(ParticleHandler& handler)
{
	list<Particle>::iterator iter;
	for (iter = particles_.begin(); iter != particles_.end(); ++iter)
	{
		handler.compute(*iter);
	}
}

void ParticleCell::iterateParticlePairs(ParticleHandler& handler)
{
	list<Particle>::iterator iter1, iter2;

	if(cellType_ == InnerCell)
	{
		// Iterate through cell
		for (iter1 = particles_.begin(); iter1 != particles_.end(); ++iter1)
		{
			Particle& p1 = *iter1;
			for (iter2 = particles_.begin(); iter2 != particles_.end(); ++iter2)
			{
				Particle& p2 = *iter2;
				if(&p1 != &p2)
					handler.compute(p1, p2);
			}
		}
	}

	// Iterate through neighbors
	for (iter1 = particles_.begin(); iter1 != particles_.end(); ++iter1)
	{
		for(int i=0; i<26; i++)
		{
			if(neighbors_[i])
			{
				list<Particle>& neighborParticles = neighbors_[i]->particles_;
				Particle& p1 = *iter1;
				for (iter2 = neighborParticles.begin(); iter2 != neighborParticles.end(); ++iter2)
				{
					Particle& p2 = *iter2;
					if(&p1 != &p2)
						handler.compute(p1, p2);
				}
			}
		}
	}
}

void ParticleCell::iterateParticlePairsSymmetric(ParticleHandler& handler)
{
	list<Particle>::iterator iter1, iter2;

	if(cellType_ == InnerCell)
	{
		// Iterate through cell
		for (iter1 = particles_.begin(); iter1 != particles_.end(); ++iter1)
		{
			Particle& p1 = *iter1;
			for (iter2 = iter1; iter2 != particles_.end(); ++iter2)
			{
				Particle& p2 = *iter2;
				if(&p1 != &p2)
					handler.computeSymmetric(p1, p2);
			}
		}
	}

	// Iterate through neighbors
	for (iter1 = particles_.begin(); iter1 != particles_.end(); ++iter1)
	{
		for(int i=0; i<13; i++)
		{
			if(neighbors_[i])
			{
				list<Particle>& neighborParticles = neighbors_[i]->particles_;
				Particle& p1 = *iter1;
				for (iter2 = neighborParticles.begin(); iter2 != neighborParticles.end(); ++iter2)
				{
					Particle& p2 = *iter2;
					if(&p1 != &p2)
						handler.computeSymmetric(p1, p2);
				}
			}
		}
	}
}


void ParticleCell::applyBoundaryCondition()
{
	if(cellType_ == InnerCell)
		return;

	BoundaryCondition cond;
	if(cellType_ > Corner)
		cond = boundaryConditions[cellType_];
	else if(cellType_ == Corner)
	{
		if(boundaryConditions[LeftBoundary] == Periodic ||
				boundaryConditions[RightBoundary] == Periodic ||
				boundaryConditions[BottomBoundary] == Periodic ||
				boundaryConditions[TopBoundary] == Periodic ||
				boundaryConditions[FrontBoundary] == Periodic ||
				boundaryConditions[BackBoundary] == Periodic)
			cond = Periodic;
		else
			cond = OutFlow;
	}

	if(cond == OutFlow)
	{

	}
	else if(cond == Reflecting)
	{
		applyReflectionCondition();
	}
	else if(cond == Periodic)
	{
		applyPeriodicCondition();
	}
}

void ParticleCell::applyReflectionCondition()
{
	ParticleCell* haloCell;
	Vector<double, 3> mid(0.0);
	int axis;


	if(cellType_ == LeftBoundary)
	{
		haloCell = neighbors_[Right];
		mid = haloCell->leftBottomFrontCorner_;
		axis = 0;
	}
	else if(cellType_ == RightBoundary)
	{
		haloCell = neighbors_[Left];
		mid = leftBottomFrontCorner_;
		axis = 0;
	}
	else if(cellType_ == BottomBoundary)
	{
		haloCell = neighbors_[Top];
		mid = haloCell->leftBottomFrontCorner_;
		axis = 1;
	}
	else if(cellType_ == TopBoundary)
	{
		haloCell = neighbors_[Bottom];
		mid = leftBottomFrontCorner_;
		axis = 1;
	}
	else if(cellType_ == FrontBoundary)
	{
		haloCell = neighbors_[Back];
		mid = haloCell->leftBottomFrontCorner_;
		axis = 2;
	}
	else if(cellType_ == BackBoundary)
	{
		haloCell = neighbors_[Front];
		mid = leftBottomFrontCorner_;
		axis = 2;
	}
	else
	{
		LOG4CXX_ERROR(cellLogger, "ERROR");
		return;
	}

	list<Particle>::iterator iter;
	for (iter = haloCell->particles_.begin(); iter != haloCell->particles_.end(); ++iter)
	{
		Vector<double, 3> position = iter->getX();
		position[axis] = mid[axis];

		Vector<double, 3> velocity(0.0);


		particles_.push_back(Particle(position, velocity, 1));
	}
}

void ParticleCell::applyPeriodicCondition()
{
	Vector<double, 3> diff = leftBottomFrontCorner_ - oppositeHaloCell_->leftBottomFrontCorner_;
	list<Particle>::iterator iter;
	for (iter = oppositeHaloCell_->particles_.begin(); iter != oppositeHaloCell_->particles_.end(); ++iter)
	{
		Vector<double, 3> position = iter->getX() + diff;
		Vector<double, 3> velocity(0.0);


		particles_.push_back(Particle(position, velocity, 1));

		//LOG4CXX_DEBUG(cellLogger, "copy from " << iter->getX()[0] << ", " << iter->getX()[1] << " to " << position[0] << ", " << position[1]);
	}
}


void ParticleCell::clearBoundary()
{
	if(cellType_ == InnerCell)
			return;

	particles_.clear();
}
