#include <cppunit/ui/text/TestRunner.h>
#include "UnitTests.h"

#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "ParticleContainer.h"
#include "ParticleHandler.h"

#include <cstring>
#include <cstdlib>
#include <iostream>

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace std;
using namespace Simulation;

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

// Define static logger variable
LoggerPtr logger(Logger::getLogger("main"));



/**
 * plot the particles to a xyz-file
 */
void plotParticles(int iteration);

ParticleContainer container;

double start_time = 0;
double end_time = 1000;
double delta_t = 0.014;



int main(int argc, char* argsv[]) 
{
	DOMConfigurator::configure("Log4cxxConfig.xml");
	LOG4CXX_INFO(logger, "Hello from MolSim for PSE!");

	if (argc == 2 && strcmp(argsv[1], "-test") == 0)
	{
		LOG4CXX_INFO(logger, "Running test suit...");
		CppUnit::TextUi::TestRunner runner;
		runner.addTest(ParticleContainerTest::suite());
		runner.run();
		return 0;		
	}
	else if (argc != 4) 
	{
		LOG4CXX_ERROR(logger, "Errounous programme call!");
		LOG4CXX_ERROR(logger, "use /MolSim <filename> <t_end> <t_delta>");
		LOG4CXX_ERROR(logger, "or /MolSim -test");
		return 0;
	}



	double current_time = start_time;

	end_time = atof(argsv[2]);
	delta_t = atof(argsv[3]);	

	container.init(argsv[1]);

	PositionHandler ph = PositionHandler(delta_t);
	VelocityHandler vh = VelocityHandler(delta_t);
	GravityHandler gh = GravityHandler(delta_t);
	LennardJonesHandler ljh = LennardJonesHandler(delta_t);

	// the forces are needed to calculate x, but are not given in the input file.
	container.iterateParticles(ljh);
	container.iterateParticlePairs(ljh);

	int iteration = 0;

	 // for this loop, we assume: current x, current f and current v are known
	while (current_time < end_time) {
		// calculate new x
		container.iterateParticles(ph);

		// store old f
		container.iterateParticles(ljh);

		// calculate new f
		container.iterateParticlePairs(ljh);

		// calculate new v
		container.iterateParticles(vh);

		iteration++;
		if (iteration % 10 == 0) {
			plotParticles(iteration);
		}
		LOG4CXX_INFO(logger, "Finished iteration " << iteration);

		current_time += delta_t;
	}

	LOG4CXX_INFO(logger, "output written. Terminating now...");
	return 0;
}


void plotParticles(int iteration) {

	string out_name("/media/sf_Shared/vtkOutput/MD_vtk");

	outputWriter::VTKWriter writer;
	writer.initializeOutput(container.count());

	for(int i=0; i<container.count(); i++)
	{
		Particle& p = container[i];
		writer.plotParticle(p);
	}	
	writer.writeFile(out_name, iteration);
	
}
