#include "StateWriter.h"

#include <iostream>
#include <fstream>

using namespace Simulation;
using namespace std;

void StateWriter::writeStateToFile(char* filename, ParticleContainer& container)
{
	ofstream outputFile;
	outputFile.open(filename);


}

