#include <cppunit/ui/text/TestRunner.h>
#include "UnitTests.h"

#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "ParticleContainer.h"
#include "ParticleHandler.h"
#include "Thermostat.h"
#include "StateWriter.h"

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <ctime>

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

//#include "hello.hxx"


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
	else if (argc != 6 && argc != 7) 
	{
		LOG4CXX_ERROR(logger, "Errounous programme call!");
		LOG4CXX_ERROR(logger, "use /MolSim <filename> <t_end> <t_delta> <g_grav> <temp>");
		LOG4CXX_ERROR(logger, "use /MolSim <filename> <t_end> <t_delta> <g_grav> <temp> -save");
		//LOG4CXX_ERROR(logger, "or /MolSim -test");
		return 0;
	}

	bool saveState = false;
	if (argc == 7)
		saveState = strcmp(argsv[6], "-save") == 0;

	double current_time = start_time;

	double gravity = atof(argsv[4]);
	double temperature = atof(argsv[5]);

	cout << "grav " << gravity << " temp " << temperature << endl;

	end_time = atof(argsv[2]);
	delta_t = atof(argsv[3]);	

	container.init(argsv[1]);


	Thermostat thermostat(container);
	if (temperature != 0)
		thermostat.applyInitialTemperature(40);

	PositionHandler ph = PositionHandler(delta_t);
	VelocityHandler vh = VelocityHandler(delta_t);
	ForceReset fr = ForceReset();
	GravityHandler gh = GravityHandler(gravity);
	LennardJonesHandler ljh = LennardJonesHandler(delta_t, container.getCutOff());

	// the forces are needed to calculate x, but are not given in the input file.
	
	container.iterateParticles(ljh);
	container.iterateParticlePairsExclusive(ljh);

	int iteration = 0;
	int lastTrace = 0;

	LOG4CXX_INFO(logger, "start iterating, " << end_time / delta_t << " iterations in total");
	 // for this loop, we assume: current x, current f and current v are known
	
	// loops until end_time is reached
	while (current_time < end_time) {

		//LOG4CXX_DEBUG(logger, "boundries");
		// apply BoudryConditions to BoundryCells
		container.iterateBoundaryCells();

		//LOG4CXX_DEBUG(logger, "update");
		// find cell for each particle based on its location
		container.updateCells();

		//LOG4CXX_DEBUG(logger, "iterate1");
		// calculate new Position for each Particle (ph --> PositionHandler) 
		container.iterateParticles(ph);

		//LOG4CXX_DEBUG(logger, "iterate2");
		// clear Force for each Particle (ljh -> leonard jones Handler)
		container.iterateParticles(fr);

		//LOG4CXX_DEBUG(logger, "iterate2");
		// apply Graviti to each Particle (gh -> gravity handler)
		container.iterateParticles(gh);

		//LOG4CXX_DEBUG(logger, "iteratePairs");
		// calculate new Force for each Particle Pair (ljh -> leonard jones Handler)
		container.iterateParticlePairsExclusive(ljh);


		//LOG4CXX_DEBUG(logger, "iterate4");
		// calculate new Velocty for each Particle based on its force (vh --> velocity Handler)
		container.iterateParticles(vh);

		if ((iteration % 1000) == 0 && temperature != 0)
			thermostat.applyTemperature(40);

		iteration++;

		// write Particles to file
		if (iteration % 10 == 0) {
			plotParticles(iteration);
		}
		lastTrace++;
		// print símulation status
		if (lastTrace >= (end_time / delta_t / 100.0))
		{
			LOG4CXX_INFO(logger, (100.0 * iteration * delta_t / end_time) << " %");
			lastTrace = 0;
		}

		current_time += delta_t;
		//LOG4CXX_DEBUG(logger, "end");
	}

	LOG4CXX_INFO(logger, "output written. Terminating now...");

	time(&end);
	LOG4CXX_INFO(logger, "Simulation took " << end - start << " seconds");

	if (saveState)
	{
		string outputFile = "savedState.txt";

		StateWriter::writeStateToFile(outputFile.c_str(), container);


		LOG4CXX_INFO(logger, "State written in " << outputFile);
	}

	return 0;
}


void plotParticles(int iteration) {

	string out_name("../vtkOutput/MD_vtk");

	outputWriter::VTKWriter writer;
	writer.initializeOutput(container.countVisible());
	for(int i=0; i<container.count(); i++)
	{
		Particle& p = container[i];
		if (p.isVisible())
			writer.plotParticle(p);
	}	
	writer.writeFile(out_name, iteration);
}
