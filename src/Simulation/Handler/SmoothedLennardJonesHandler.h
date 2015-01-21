#pragma once
#include "ParticleHandler.h"

namespace Simulation
{
	/// \class SmoothedLennardJonesHandler
	/// \brief Computes force  applied by Lennard-Jones potential
	class SmoothedLennardJonesHandler : public ParticleHandler
	{
	public:
		SmoothedLennardJonesHandler(double r) :
			rCutOff(r)
		{
		}

		/// Nonsymmetric computation
		void compute(Particle& p1, Particle& p2)
		{
		}

		/// Symmetric computation
		void computeSymmetric(Particle& p1, Particle& p2)
		{
		}

	private:
		double rCutOff;

	};

}
