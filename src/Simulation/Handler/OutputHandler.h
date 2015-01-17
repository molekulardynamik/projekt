#pragma once
#include "ParticleHandler.h"
#include "../../outputWriter/VTKWriter.h"

namespace Simulation
{
/// \class OutputHandler
/// \brief writes output
class OutputHandler: public ParticleHandler
{
public:
	OutputHandler() :
			ParticleHandler()
	{
	}

	void compute(Particle& p)
	{
		writer_.plotParticle(p);
	}

	void init(int particleCount)
	{
		writer_.initializeOutput(particleCount);
	}
	void finish(std::string out_name, int iteration)
	{
		writer_.writeFile(out_name, iteration);
	}

private:
	outputWriter::VTKWriter writer_;
};
}
