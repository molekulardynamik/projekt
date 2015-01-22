#pragma once
#include "ParticleHandler.h"
#include "../MaxwellBoltzmannDistribution.h"

namespace Simulation
{
/// \class Thermostat
/// \brief stores global data for temperature calculations
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
/// \brief applies temperature scaling to all particles
class ThermostatHandler: public ParticleHandler
{
public:
	ThermostatHandler(int wallT, utils::Vector<bool, 3> m):
		wallType(wallT), mask(m)
	{
	}

	void compute(Particle& p)
	{
		if(p.getType() == wallType)
			return;

		if(mask[0])
			p.getV()[0] *= tempScale_;
		if(mask[1])
			p.getV()[1] *= tempScale_;
		if(mask[2])
			p.getV()[2] *= tempScale_;
	}

	/// sets the target temperature
	/// \param temp target tempertaure
	/// \param interpolation value between 0 and 1 and scales the how much the thermostat effect the particles
	/// \param numParticles number of particles
	void setTargetTemp(double temp, double interpolation, int numParticles)
	{
		double desiredEnergy = numParticles * Thermostat::numDimensions() * 0.5 * temp;


		tempScale_ = sqrt(desiredEnergy / Thermostat::kineticEnergy());
		tempScale_ = tempScale_ * interpolation + (1 - interpolation);
	}

private:
	double tempScale_;
	utils::Vector<bool, 3> mask;	/// < mask for which axis should be affected
	int wallType;		/// < particles of this type should be ignored
};

/// \class BrownianMotionHandler
/// \brief applies initail velocity based on temperature 
class BrownianMotionHandler : public ParticleHandler
{
public:
	BrownianMotionHandler(int initTemp, int wallT) :
		initialTemp_(initTemp), wallType(wallT)
	{
	}

	void compute(Particle& p)
	{
		if(p.getType() == wallType)
			return;
		double meanVelocity = sqrt(initialTemp_ / p.getM());
		MaxwellBoltzmannDistribution(p, meanVelocity, Thermostat::numDimensions());
	}

private:
	double initialTemp_;
	int wallType;		/// < particles of this type should be ignored
};

/// \class KineticEnergyHandler
/// \brief calculates kinetic energy in the simulation
class KineticEnergyHandler : public ParticleHandler
{
public:
	KineticEnergyHandler(int wallT, utils::Vector<bool, 3> m):
		wallType(wallT), mask(m)
	{
	}

	void compute(Particle& p)
	{
		if(p.getType() == wallType)
			return;

		utils::Vector<double, 3> vel = p.getV();
		if(!mask[0])
			vel[0] = 0;
		if(!mask[1])
			vel[1] = 0;
		if(!mask[2])
			vel[2] = 0;
		Thermostat::kineticEnergy() += (vel * vel) * p.getM() * 0.5;
	}

	void reset()
	{
		Thermostat::kineticEnergy() = 0;
	}

private:
	int wallType;		/// < particles of this type should be ignored
	utils::Vector<bool, 3> mask;	/// < mask for which axis should be affected
};

}
