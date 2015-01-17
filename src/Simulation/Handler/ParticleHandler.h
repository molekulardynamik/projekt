#pragma once
#include "../Particle.h"
#include <math.h>

#include <sstream>
#include <iostream>

namespace Simulation
{
/// \class ParticleHandler
/// \brief Baseclass for handling particle computations
class ParticleHandler
{
public:

	/// Computes one single particle
	virtual void compute(Particle& p)
	{
	}

	/// Computes one particle pair
	virtual void compute(Particle& p1, Particle& p2)
	{
	}

	/// Computes one particle pair, but applies result on both particles (symmetrical computation)
	virtual void computeSymmetric(Particle& p1, Particle& p2)
	{
	}
};

/// \class ParticleHandlerTimeAware
/// \brief Baseclass for handling computations that are time dependant
class ParticleHandlerTimeAware: public ParticleHandler
{
public:

	/// \param Delta time between iterations
	ParticleHandlerTimeAware(double dt)
	{
		delta_t = dt;
	}

protected:
	double delta_t;		///< Delta time between iterations
};
}
