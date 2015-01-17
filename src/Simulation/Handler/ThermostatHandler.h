#pragma once
#include "ParticleHandler.h"
#include "../MaxwellBoltzmannDistribution.h"

namespace Simulation
{
class Thermostat
{
public:
	static int& numDimensions()
	{
		static int dim_;
		return dim_;
	}

	static double& kineticEnergy()
	{
		static double kineticEnergy_;
		return kineticEnergy_;
	}
};

/// \class ThermostatHandler
class ThermostatHandler: public ParticleHandler
{
public:
	ThermostatHandler()
	{
	}

	void compute(Particle& p)
	{
		 p.getV() = p.getV() * tempScale_;
	}

	void setTargetTemp(double temp, double interpolation, int numParticles)
	{
		double desiredEnergy = numParticles * Thermostat::numDimensions() * 0.5 * temp;


		tempScale_ = sqrt(desiredEnergy / Thermostat::kineticEnergy());
		tempScale_ = tempScale_ * interpolation + (1 - interpolation);
	}

private:
	double tempScale_;
};

class BrownianMotionHandler : public ParticleHandler
{
public:
	BrownianMotionHandler(int initTemp) :
		initialTemp_(initTemp)
	{
	}

	void compute(Particle& p)
	{
		double meanVelocity = sqrt(initialTemp_ / p.getM());
		MaxwellBoltzmannDistribution(p, meanVelocity, Thermostat::numDimensions());
	}

private:
	double initialTemp_;
};

class KineticEnergyHandler : public ParticleHandler
{
public:
	KineticEnergyHandler()
	{
	}

	void compute(Particle& p)
	{
		Thermostat::kineticEnergy() += (p.getV() * p.getV()) * p.getM() * 0.5;
	}

	void reset()
	{
		Thermostat::kineticEnergy() = 0;
	}
};

}
