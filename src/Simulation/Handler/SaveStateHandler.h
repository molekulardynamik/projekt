#pragma once
#include "ParticleHandler.h"
#include "../../simulation.h"

namespace Simulation
{
class SaveStateHandler : public ParticleHandler
{
public:
	SaveStateHandler(particleArray_t& particleArray) :
		particleArray_(particleArray)
	{
	}

	void compute(Particle& p)
	{
		vec3d_t savePos, saveVel;
		savePos.X() = p.getX()[0];
		savePos.Y() = p.getX()[1];
		savePos.Z() = p.getX()[2];
		saveVel.X() = p.getV()[0];
		saveVel.Y() = p.getV()[1];
		saveVel.Z() = p.getV()[2];

		particle_t saveParticle(savePos, saveVel);
		saveParticle.type() = p.getType();
		particleArray_.particle().push_back(saveParticle);
	}
private:
	particleArray_t& particleArray_;
};
}
