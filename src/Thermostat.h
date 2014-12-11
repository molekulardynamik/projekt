#pragma once
#include <vector>
#include <list>

#include "Particle.h"
#include "ParticleContainer.h"
#include "ParticleHandler.h"

namespace Simulation
{
	/// \class Thermostat
	/// \brief Handles temperature of particles in the simulation
	class Thermostat
	{
	public:
		Thermostat(ParticleContainer& cont);

		/// Scale temperature of simulation
		void scaleTemperature(double scaling);
		
		/// Calculate kinetic energy of simulation
		double calcKineticEnergy();

		/// Apply temperature to simulation
		void applyTemperature(double temp);

		/// Apply initial temperature to simulation
		void applyInitialTemperature(double temp);

	private:
		ParticleContainer& container;		///< Container which stores particles for temperature calculations

	};
};
