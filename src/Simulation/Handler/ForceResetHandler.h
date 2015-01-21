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
		p.getF() = utils::Vector<double, 3>(0.0);
	}
};
}
