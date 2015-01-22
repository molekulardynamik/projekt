#pragma once
#include "ParticleHandler.h"

namespace Simulation
{
/// \class HarmonicPotentialDirectHandler
/// \brief calculates harmonnic potential between neighboring particles
class HarmonicPotentialHandler: public ParticleHandler
{
public:
	HarmonicPotentialHandler() :
			r0(0), k(0)
	{
	}
	HarmonicPotentialHandler(double r, double stiff, bool d) :
			r0(r), k(stiff), direct(d)
	{
	}

	/// Nonsymmetric computation
	void compute(Particle& p1, Particle& p2)
	{
		if(direct)
		{
			if(!p1.isDirectNeighbor(p2))
				return;
		}
		else
		{
			if(!p1.isDiagonalNeighbor(p2))
				return;
		}
		utils::Vector<double, 3> force = p2.getX() - p1.getX();
		double dist = force.L2Norm();
		double harmonic = k * (dist - r0);

		force = force * (1 / dist * harmonic);

		p1.getF() = p1.getF() + force;
	}

	/// Symmetric computation
	void computeSymmetric(Particle& p1, Particle& p2)
	{
		if(direct)
		{
			if(!p1.isDirectNeighbor(p2))
				return;
		}
		else
		{
			if(!p1.isDiagonalNeighbor(p2))
				return;
		}

		utils::Vector<double, 3> force = p2.getX() - p1.getX();
		double dist = force.L2Norm();
		double harmonic = k * (dist - r0);

		force = force * (harmonic / dist);

		p1.getF() = p1.getF() + force;
		p2.getF() = p2.getF() - force;
	}

private:
	bool direct;	/// < true if potential should be applied to direct neighbors, false for diagonal neighbors
	double r0;
	double k;

};


}
