#pragma once
#include <vector>
#include <list>

#include "Particle.h"
#include "ParticleContainer.h"
#include "ParticleHandler.h"

namespace Simulation
{

	class Thermostat
	{
	public:
		Thermostat(ParticleContainer& cont);

		void scaleTemperature(double scaling);
		double calcKineticEnergy();

		void applyTemperature(double temp);
		void applyInitialTemperature(double temp);

		void setTargetTemperature(double target);
		void setStartTme(double start);
		void tick(double delta);

	private:
		ParticleContainer& container;
		double targetTemperature;
		double startTime;

	};
};
