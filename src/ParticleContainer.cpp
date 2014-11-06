#include "ParticleContainer.h"
#include "FileReader.h"

using namespace Simulation;
using namespace utils;
using namespace std;

void ParticleContainer::init(char* filename)
{
	FileReader fileReader;
	fileReader.readFile(particles, filename);
}

void ParticleContainer::iterateParticles(ParticleHandler& handler)
{
	for (int i = 0; i < particles.size(); i++)
	{
		Particle& p = particles[i];

		handler.compute(p);
	}
}

void ParticleContainer::iterateParticlePairs(ParticleHandler& handler)
{
	for (int i = 0; i < particles.size(); i++)
	{
		Particle& p1 = particles[i];
		for (int j = 0; j < particles.size(); j++)
		{
			Particle& p2 = particles[j];
			if (i != j)
			{
				handler.compute(p1, p2);
			}
		}
	}
}