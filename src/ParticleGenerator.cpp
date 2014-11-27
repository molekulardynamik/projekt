#include "ParticleGenerator.h"
#include "MaxwellBoltzmannDistribution.h"

using namespace Simulation;
using namespace utils;
using namespace std;

void ParticleGenerator::generateCuboid(Vector<double, 3> bottomLeftFront, Vector<int, 3 > numParticles, double h, double mass, Vector<double, 3 > initialVelocity, double meanValue, list<Particle>& particles)
{
	for (int x = 0; x < numParticles[0]; x++)
	{
		for (int y = 0; y < numParticles[1]; y++)
		{
			for (int z = 0; z < numParticles[2]; z++)
			{
				Vector<double, 3> pos = bottomLeftFront;
				pos[0] += x*h;
				pos[1] += y*h;
				pos[2] += z*h;

				Particle p(pos, initialVelocity, mass);
				p.setDead(false);
				MaxwellBoltzmannDistribution(p, meanValue, 2);

				particles.push_back(p);
			}
		}
	}
}
