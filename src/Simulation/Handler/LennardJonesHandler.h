#pragma once
#include "ParticleHandler.h"

namespace Simulation
{
/// \class LennardJonesHandler
/// \brief Computes force  applied by Lennard-Jones potential
class LennardJonesHandler: public ParticleHandlerTimeAware
{
public:
	LennardJonesHandler(double dt, double r) :
			ParticleHandlerTimeAware(dt), rCutOff(r)
	{
	}

	/// Nonsymmetric computation
	void compute(Particle& p1, Particle& p2)
	{
		double e = (p1.getE() + p2.getE()) / 2;
		double o = sqrt(p1.getO() * p2.getO());

		double dist = (p1.getX() - p2.getX()).L2Norm();
		if (dist > rCutOff)
			return;

		double sqrtDist = dist * dist;

		double scalar = 24 * e / sqrtDist
				* (pow(o / dist, 6) - 2 * pow(o / dist, 12));

		p1.getF() = p1.getF() + (scalar * (p2.getX() - p1.getX()));
	}

	/// Symmetric computation
	void computeSymmetric(Particle& p1, Particle& p2)
	{
		double e = (p1.getE() + p2.getE()) / 2;
		double o = sqrt(p1.getO() * p2.getO());

		double dist = (p1.getX() - p2.getX()).L2Norm();
		if (dist > rCutOff)
			return;

		double sqrtDist = dist * dist;

		double scalar = 24 * e / sqrtDist
				* (pow(o / dist, 6) - 2 * pow(o / dist, 12));

		utils::Vector<double, 3> force = (scalar * (p2.getX() - p1.getX()));
		p1.getF() = p1.getF() + force;
		p2.getF() = p2.getF() - force;
	}

private:
	double rCutOff;

};

}
