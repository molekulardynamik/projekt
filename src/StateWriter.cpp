#include "StateWriter.h"

#include <iostream>
#include <fstream>

using namespace Simulation;
using namespace std;

void StateWriter::writeStateToFile(const char* filename, ParticleContainer& container)
{
	ofstream outputFile;
	outputFile.open(filename);

	outputFile << "domain: " << container.getDomainX() << " " << container.getDomainY() << endl;
	outputFile << "rCutOff: " << container.getCutOff() << endl;
	outputFile << endl;

	for (int pr = 0; pr < ParticleProperty::count(); pr++)
	{
		if (pr == container.getWallType())
			continue;

		ParticleProperty& properties = ParticleProperty::get(pr);
		outputFile << properties.saveProperties();
		outputFile << endl;
	}

	for (int p = 0; p < container.countVisible(); p++)
	{
		Particle& particle = container[p];
		outputFile << particle.saveParticle();
		outputFile << endl;
	}
}

