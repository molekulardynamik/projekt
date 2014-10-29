#include "MoleculeContainer.h"

using namespace Simulation;
using namespace std;

MoleculeContainer::MoleculeContainer(char* filename)
{
	FileReader fileReader;
	fileReader.readFile(particles, filename);
}

