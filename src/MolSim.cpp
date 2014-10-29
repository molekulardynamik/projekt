
#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "MoleculeContainer.h"
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

MoleculeContainer molecules;

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

	molecules = MoleculeContainer(argsv[1]);

	PositionHandler ph = PositionHandler(delta_t);
	VelocityHandler vh = VelocityHandler(delta_t);
	ForceHandler fh = ForceHandler(delta_t);

	// the forces are needed to calculate x, but are not given in the input file.
	molecules.iterateParticles(fh);
	molecules.iterateParticlePairs(fh);

	double current_time = start_time;

	end_time = atof(argsv[2]);
	delta_t = atof(argsv[3]);

	int iteration = 0;

	 // for this loop, we assume: current x, current f and current v are known
	while (current_time < end_time) {
		// calculate new x
		molecules.iterateParticles(ph);
		// calculate new f
		molecules.iterateParticles(fh);
		molecules.iterateParticlePairs(fh);

		// calculate new v
		molecules.iterateParticles(vh);

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


void calculateF() 
{
	for(int i=0; i<molecules.count(); i++)
	{
		Particle& p1 = molecules[i];
		p1.getOldF() = p1.getF();
        double zeros[3] = {0,0,0};
        p1.getF() = utils::Vector<double, 3>(zeros);

		for(int j=0; j<molecules.count(); j++)
		{
			if(i != j)
			{
				Particle& p2 = molecules[j];
                                double scalar = p1.getM() * p2.getM() / pow((p1.getX() - p2.getX()).L2Norm(), 3);
				utils::Vector<double, 3> force = scalar * (p2.getX() - p1.getX());

				p1.getF() = p1.getF() + force;
			}
		}
	}
}


void calculateX() 
{
	for(int i=0; i<molecules.count(); i++)
	{
		Particle& p = molecules[i];
		utils::Vector<double,3> term1 = p.getX();
		utils::Vector<double,3> term2 = delta_t * p.getV();
		utils::Vector<double,3> term3 = pow(delta_t,2) * p.getF() *(1 / (2 * p.getM()));

		p.getX() = term1 + term2 + term3;
	}
}


void calculateV() 
{
	for(int i=0; i<molecules.count(); i++)
	{
		Particle& p = molecules[i];
		utils::Vector<double,3> term1 = p.getV();
		utils::Vector<double,3> term2 = delta_t * (p.getOldF() + p.getF()) * (1/( 2 * p.getM()));

		p.getV() = term1 + term2;
	}
}


void plotParticles(int iteration) {

	string out_name("/media/sf_Shared/MD_vtk");

	outputWriter::VTKWriter writer;
	writer.initializeOutput(molecules.count());

	for(int i=0; i<molecules.count(); i++)
	{
		Particle& p = molecules[i];
		writer.plotParticle(p);
	}
	
	writer.writeFile(out_name, iteration);
	
}
