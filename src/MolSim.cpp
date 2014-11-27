#include <cppunit/ui/text/TestRunner.h>
#include "UnitTests.h"

#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "ParticleContainer.h"
#include "ParticleHandler.h"

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <ctime>

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
	time_t start, end;
	time(&start);

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
	else if (argc == 3 && strcmp(argsv[1], "-single") == 0)
	{
		container.init(argsv[2]);

		plotParticles(0);

		LOG4CXX_INFO(logger, "BYE");
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
	int lastTrace = 0;

	LOG4CXX_INFO(logger, "start iterating, " << end_time / delta_t << " iterations in total");
	 // for this loop, we assume: current x, current f and current v are known
	while (current_time < end_time) {

		container.emptyBoundryCells();

		container.updateCells();


		// calculate new x
		container.iterateParticles(ph);

		// store old f
		container.iterateParticles(ljh);

		// calculate new f
		container.iterateParticlePairsExclusive(ljh);

		// calculate new v
		container.iterateParticles(vh);

		iteration++;
		if (iteration % 10 == 0) {
			plotParticles(iteration);
		}
		lastTrace++;
		if (lastTrace >= (end_time / delta_t / 100.0))
		{
			LOG4CXX_INFO(logger, (100.0 * iteration * delta_t / end_time) << " %");
			lastTrace = 0;
		}

		current_time += delta_t;

	}


	LOG4CXX_INFO(logger, "output written. Terminating now...");

	time(&end);
	LOG4CXX_INFO(logger, "Simulation took " << end - start << " seconds");

	return 0;
}


void plotParticles(int iteration) {

	string out_name("/media/sf_Shared/vtkOutput/MD_vtk");

	outputWriter::VTKWriter writer;
	writer.initializeOutput(container.live());

	for(int i=0; i<container.count(); i++)
	{
		Particle& p = container[i];
		if (p.isDead())
			continue;

		writer.plotParticle(p);
	}	
	writer.writeFile(out_name, iteration);
	
}
