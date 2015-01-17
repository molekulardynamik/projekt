#pragma once
#include "ParticleHandler.h"

namespace Simulation
{
/// \class ForceResetHandler
/// \brief resets force of zarticle to zero
class ForceResetHandler: public ParticleHandler
{
public:
	void compute(Particle& p)
	{
		p.getOldF() = p.getF();
		double zeros[3] =
		{ 0, 0, 0 };
		p.getF() = utils::Vector<double, 3>(zeros);
	}
};
}
