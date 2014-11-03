
#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "ParticleContainer.h"
#include "ParticleHandler.h"

#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace Simulation;

/**** forward declaration of the calculation functions ****/

/**
 * calculate the force for all particles
 */
void calculateF();

/**
 * calculate the position for all particles
 */
void calculateX();

/**
 * calculate the position for all particles
 */
void calculateV();

/**
 * plot the particles to a xyz-file
 */
void plotParticles(int iteration);

ParticleContainer container;

double start_time = 0;
double end_time = 1000;
double delta_t = 0.014;


int main(int argc, char* argsv[]) {

	cout << "Hello from MolSim for PSE!" << endl;
	if (argc != 4) {
		cout << "Errounous programme call! " << endl;
		cout << "./molsym filename t_end t_delta" << endl;
	}

	/*FileReader fileReader;
	fileReader.readFile(particles, argsv[1]);*/

	container = ParticleContainer(argsv[1]);

	PositionHandler ph = PositionHandler(delta_t);
	VelocityHandler vh = VelocityHandler(delta_t);
	ForceHandler fh = ForceHandler(delta_t);

	// the forces are needed to calculate x, but are not given in the input file.
	container.iterateParticles(fh);
	container.iterateParticlePairs(fh);

	double current_time = start_time;

	end_time = atof(argsv[2]);
	delta_t = atof(argsv[3]);

	int iteration = 0;

	 // for this loop, we assume: current x, current f and current v are known
	while (current_time < end_time) {
		// calculate new x
		container.iterateParticles(ph);

		// store old f
		container.iterateParticles(fh);
		// calculate new f
		container.iterateParticlePairs(fh);

		// calculate new v
		container.iterateParticles(vh);

		iteration++;
		if (iteration % 10 == 0) {
			plotParticles(iteration);
		}
		cout << "Iteration " << iteration << " finished." << endl;

		current_time += delta_t;
	}

	cout << "output written. Terminating now..." << endl;
	return 0;
}


void plotParticles(int iteration) {

	string out_name("/media/sf_Shared/MD_vtk");

	outputWriter::VTKWriter writer;
	writer.initializeOutput(container.count());

	for(int i=0; i<container.count(); i++)
	{
		Particle& p = container[i];
		writer.plotParticle(p);
	}
	
	writer.writeFile(out_name, iteration);
	
}
