#include "ParticleGenerator.h"
#include "MaxwellBoltzmannDistribution.h"

using namespace Simulation;
using namespace utils;
using namespace std;

void ParticleGenerator::generateCuboid(Vector<double, 3> bottomLeftFront, Vector<double, 3 > initialVelocity, Vector<int, 3 > numParticles, double h, int type, vector<Particle>& particles)
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

				Particle p(pos, initialVelocity, type, true);

				particles.push_back(p);
			}
		}
	}
}

void ParticleGenerator::generateSphere(Vector<double, 3> center, Vector<double, 3 > initialVelocity, int numParticles, double h, int type, vector<Particle>& particles)
{
	for (int x = -numParticles; x < numParticles+1; x++)
	{
		for (int y = -numParticles; y < numParticles+1; y++)
		{
			if (sqrt(x*x + y*y) <= numParticles)
			{
				Vector<double, 3> pos = center;
				pos[0] += x*h;
				pos[1] += y*h;

				Particle p(pos, initialVelocity, type, true);

				particles.push_back(p);
			}
		}
	}
}
