#include "ParticleGenerator.h"

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace Simulation;
using namespace utils;
using namespace std;

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

// Define static logger variable
LoggerPtr generatorLogger(Logger::getLogger("ParticleGenerator"));

void ParticleGenerator::readFile(auto_ptr<simulation_t> simulationConfig,
		vector<Particle>& particles)
{
	int numCuboids = 0;
	int numSpheres = 0;

	for (simulation_t::type_const_iterator i(simulationConfig->type().begin());
			i != simulationConfig->type().end(); ++i)
	{
		ParticleProperty prop;
		prop.mass = i->mass();
		prop.e = i->epsilon();
		prop.o = i->sigma();

		ParticleProperty::push(prop);
	}

	for (simulation_t::cuboid_const_iterator i(
			simulationConfig->cuboid().begin());
			i != simulationConfig->cuboid().end(); ++i)
	{
		int type;
		double x[3];
		double v[3];
		int n[3];
		double h;

		type = i->type();
		x[0] = i->position().X();
		x[1] = i->position().Y();
		x[2] = i->position().Z();
		v[0] = i->initialVelocity().X();
		v[1] = i->initialVelocity().Y();
		v[2] = i->initialVelocity().Z();
		n[0] = i->particleCount().X();
		n[1] = i->particleCount().Y();
		n[2] = i->particleCount().Z();
		h = i->spacing();

		ParticleGenerator::generateCuboid(Vector<double, 3>(x),
				Vector<double, 3>(v), Vector<int, 3>(n), h, type, particles);
		numCuboids++;

		LOG4CXX_DEBUG(generatorLogger, "generated cuboid ");
	}

	for (simulation_t::sphere_const_iterator i(
			simulationConfig->sphere().begin());
			i != simulationConfig->sphere().end(); ++i)
	{
		int type;
		double x[3];
		double v[3];
		int n;
		double h;

		type = i->type();
		x[0] = i->position().X();
		x[1] = i->position().Y();
		x[2] = i->position().Z();
		v[0] = i->initialVelocity().X();
		v[1] = i->initialVelocity().Y();
		v[2] = i->initialVelocity().Z();
		n = i->radius();
		h = i->spacing();

		ParticleGenerator::generateSphere(Vector<double, 3>(x),
				Vector<double, 3>(v), n, h, type, particles);
		numSpheres++;

		LOG4CXX_DEBUG(generatorLogger,
				"generated sphere " << v[0] << " " << v[1] << " " << v[2]);
	}

	if(simulationConfig->particles().present())
	{
		for (particleArray_t::particle_const_iterator i(
					simulationConfig->particles().get().particle().begin());
					i != simulationConfig->particles().get().particle().end(); ++i)
			{
				int type;
				double x[3];
				double v[3];
				type = i->type().get();
				x[0] = i->position().X();
				x[1] = i->position().Y();
				x[2] = i->position().Z();
				v[0] = i->velocity().X();
				v[1] = i->velocity().Y();
				v[2] = i->velocity().Z();

				Vector<double, 3> pos(x), vel(v);

				particles.push_back(Particle(pos,vel,type));
			}
	}

	LOG4CXX_INFO(generatorLogger,
			"generated " << numCuboids << (numCuboids != 1 ? " cuboids" : " cuboid") <<" and " << numSpheres << (numSpheres != 1 ? " spheres" : " sphere") << ".");
}

void ParticleGenerator::generateCuboid(Vector<double, 3> bottomLeftFront,
		Vector<double, 3> initialVelocity, Vector<int, 3> numParticles,
		double h, int type, vector<Particle>& particles)
{
	for (int x = 0; x < numParticles[0]; x++)
	{
		for (int y = 0; y < numParticles[1]; y++)
		{
			for (int z = 0; z < numParticles[2]; z++)
			{
				Vector<double, 3> pos = bottomLeftFront;
				pos[0] += x * h;
				pos[1] += y * h;
				pos[2] += z * h;

				Vector<int, 3> index;
				index[0] = x;
				index[1] = y;
				index[2] = z;

				Particle p(pos, initialVelocity, type, index);

				particles.push_back(p);
			}
		}
	}
}

void ParticleGenerator::generateSphere(Vector<double, 3> center,
		Vector<double, 3> initialVelocity, int numParticles, double h, int type,
		vector<Particle>& particles)
{
	assert(false);

	for (int x = -numParticles; x < numParticles + 1; x++)
	{
		for (int y = -numParticles; y < numParticles + 1; y++)
		{
			for (int z = -numParticles; z < numParticles + 1; z++)
			{
				if (sqrt(x * x + y * y + z * z) <= numParticles)
				{
					Vector<double, 3> pos = center;
					pos[0] += x * h;
					pos[1] += y * h;
					pos[2] += y * h;

					Particle p(pos, initialVelocity, type);

					particles.push_back(p);
				}
			}
		}
	}
}
