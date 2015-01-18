#pragma once

#include <vector>

#include "../Particle.h"
#include "../Handler/ParticleHandler.h"
#include "ParticleGenerator.h"

#include "ParticleCell.h"

namespace Simulation
{

class ParticleContainer
{
public:
	/// Initializes particle container with data from file
	/// \param simulationFile File which will be read
	ParticleContainer(std::auto_ptr<simulation_t> simulationConfig);

	void updateCells();

	int countParticles();

	double getRCutOff();

	/// Iterates over all particles an executes particle handler
	void iterateParticles(ParticleHandler& handler);

	/// Iterates over all particle pairs (only neighboring cells are considered) and executes particle pair handler
	void iterateParticlePairs(ParticleHandler& handler);

	/// Iterates over all particle pairs (only neighboring cells are considered) and executes exclusive particle pair handler.
	/// \note Every particle will be handled only once. This is faster but requires a symmetrical computation.
	void iterateParticlePairsSymmetric(ParticleHandler& handler);


	void iterateBoundaries();
	void clearBoundaries();

private:
	/// Finds 1D cell index based on given poistion
	/// \param position Position of Particle
	/// \param cell Pointer to 1D cell index
	ParticleCell& findCell(utils::Vector<double, 3> position);

	ParticleCell& findCell(int cellX, int cellY, int cellZ);

	///	 Converts 2D indices to a 1D index
	/// \param cellX, cellY 2D indices
	/// \param cell Pointer to 1D cell index
	void flatten(int cellX, int cellY, int cellZ, int* cell);

	/// Converts a 1D index to 2D indices
	/// \param cellX, cellY Pointers to 2D indices
	/// \param cell 1D cell index
	void expand(int* cellX, int* cellY, int* cellZ, int cell);

private:
	std::vector<ParticleCell> particleCells_;
	utils::Vector<double, 3> domain_;
	utils::Vector<int, 3> numCells_;
	double rCutOff_;
};

}
