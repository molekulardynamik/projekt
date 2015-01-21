#pragma once
#include "ParticleHandler.h"

namespace Simulation
{
/// \class ForceResetHandler
/// \brief resets force of zarticle to zero
class PickHandler: public ParticleHandler
{
public:
	PickHandler():
		pickStart(0.0), pickEnd(0.0), pickForce(0.0)
	{
	}

	PickHandler(utils::Vector<int, 3> pickPosition, utils::Vector<int, 3> pickSize, utils::Vector<double, 3> pickF):
		pickForce(pickF)
	{
		pickStart = pickPosition;
		pickEnd = pickPosition + pickSize;
	}

	void compute(Particle& p)
	{
		utils::Vector<int, 3> index = p.getCuboidIndex();
		if(pickStart <= index && index < pickEnd)
			p.getF() = p.getF() + pickForce;
	}
private:
	utils::Vector<int, 3> pickStart;
	utils::Vector<int, 3> pickEnd;
	utils::Vector<double, 3> pickForce;
};
}
