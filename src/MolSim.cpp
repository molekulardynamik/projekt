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

#include "config.hxx"

using namespace std;
using namespace Simulation;

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

// Define static logger variable
LoggerPtr logger(Logger::getLogger("main"));

auto_ptr<config_t> configuration;


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

	char* configFile = "config.xml";
	if(argc == 2)
		configFile = argsv[1];

	try
	{
		configuration = configSim(configFile);
	} catch (const xml_schema::exception& e)
	{
		LOG4CXX_ERROR(logger, e);
		return 1;
	}

	bool saveState = false;

	double current_time = start_time;

	double gravity = configuration->properties().gravity();
	double temperature = configuration->properties().thermostat().initialTemp();

	LOG4CXX_DEBUG(logger,"grav " << gravity << " temp " << temperature);

	end_time = configuration->properties().end();
	delta_t = configuration->properties().delta();

	if(!container.init(configuration->simulationFile()))
		return 1;

	Thermostat thermostat(container);
	if (temperature != 0)
		thermostat.applyInitialTemperature(configuration->properties().thermostat().initialTemp());

	PositionHandler ph = PositionHandler(delta_t);
	VelocityHandler vh = VelocityHandler(delta_t);
	ForceReset fr = ForceReset();
	GravityHandler gh = GravityHandler(gravity);
	LennardJonesHandler ljh = LennardJonesHandler(delta_t,
			container.getCutOff());

	// the forces are needed to calculate x, but are not given in the input file.

	container.iterateParticles(ljh);
	container.iterateParticlePairsExclusive(ljh);

	int iteration = 0;
	int lastTrace = 0;
	int skipIterations = configuration->output().iterations();

	LOG4CXX_INFO(logger,
			"start iterating, " << end_time / delta_t
					<< " iterations in total");
	// for this loop, we assume: current x, current f and current v are known

	// loops until end_time is reached
	while (current_time < end_time)
	{

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
		if (iteration % skipIterations == 0)
		{
			plotParticles(iteration);
		}
		lastTrace++;
		// print s�mulation status
		if (lastTrace >= (end_time / delta_t / 100.0))
		{
			LOG4CXX_INFO(logger,
					(100.0 * iteration * delta_t / end_time) << " %");
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

void plotParticles(int iteration)
{
	string out_name(configuration->output().dir() + configuration->output().filename());

	outputWriter::VTKWriter writer;
	writer.initializeOutput(container.countVisible());
	for (int i = 0; i < container.count(); i++)
	{
		Particle& p = container[i];
		if (p.isVisible())
			writer.plotParticle(p);
	}
	writer.writeFile(out_name, iteration);
}
