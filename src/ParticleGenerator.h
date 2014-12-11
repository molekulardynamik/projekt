#pragma once
#include <vector>
#include <list>

#include "utils/Vector.h"
#include "Particle.h"

namespace Simulation
{
	/// \class ParticleGenerator
	/// \brief penerates particles in different shapes
	class ParticleGenerator
	{
	public:

		/// Generates Cuboid
		/// \param bottomLeftFront Position of cuboid
		/// \param numParticles Number of particles in each axis
		/// \param initialVelocity
		/// \param type Type which defines properties of particles
		/// \param h Distance between particles
		/// \param particles List of particles at which cuboid will be apended
		static void generateCuboid(
			utils::Vector<double, 3> bottomLeftFront,
			utils::Vector<int, 3 > numParticles,
			utils::Vector<double, 3 > initialVelocity,
			int type,
			double h,
			std::vector<Particle>& particles);
	};
}
