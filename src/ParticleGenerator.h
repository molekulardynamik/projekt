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
			utils::Vector<double, 3 > initialVelocity,
			utils::Vector<int, 3 > numParticles,
			double h,
			int type,
			std::vector<Particle>& particles);

		static void generateSphere(
			utils::Vector<double, 3> center,
			utils::Vector<double, 3 > initialVelocity,
			int numParticles,
			double h,
			int type,
			std::vector<Particle>& particles);

	};
}
