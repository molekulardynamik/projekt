#include "Thermostat.h"
#include "MaxwellBoltzmannDistribution.h"

using namespace Simulation;
using namespace std;

Thermostat::Thermostat(ParticleContainer& cont)
	: container(cont)
{
}

void Thermostat::scaleTemperature(double scaling)
{
	for (int p = 0; p < container.countVisible(); p++)
	{
		Particle& particle = container[p];
		if (!particle.isVisible())
			continue;

		particle.getV() = particle.getV() * scaling;
	}
}

double Thermostat::calcKineticEnergy()
{
	double energy = 0;

	for (int p = 0; p < container.countVisible(); p++)
	{
		Particle& particle = container[p];
		if (!particle.isVisible())
			continue;

		energy += (particle.getV() * particle.getV()) * particle.getM() * 0.5;
	}

	return energy;
}

void Thermostat::applyTemperature(double temp)
{
	int numDimensions = 2; // bad
	double desiredEnergy = container.countVisible() * numDimensions * 0.5 * temp;
	double currentEnergy = calcKineticEnergy();

	double scaling = sqrt(desiredEnergy / currentEnergy);

	scaleTemperature(scaling);
}

void Thermostat::applyInitialTemperature(double temp)
{
	double constMass = 1;
	double meanVelocity; 

	for (int p = 0; p < container.countVisible(); p++)
	{
		Particle& particle = container[p];
		if (!particle.isVisible())
			continue;

		meanVelocity = sqrt(temp / particle.getM());
		MaxwellBoltzmannDistribution(particle, meanVelocity, 2);
	}
}