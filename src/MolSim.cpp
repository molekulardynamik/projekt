#include <cppunit/ui/text/TestRunner.h>
#include "UnitTests.h"

#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "Simulation/Handler/Handler.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "config.h"
#include "Simulation/StateWriter.h_old"
#include "Simulation/Thermostat.h_old"

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
void plotParticles(int iteration, string out_name,
		ParticleContainer& container);

int main(int argc, char* argsv[])
{
	time_t start, end;
	time(&start);

	DOMConfigurator::configure("Log4cxxConfig.xml");
	LOG4CXX_INFO(logger, "Hello from MolSim for PSE!");

	// Load Configuration
	const char* configFile = "config.xml";
	if (argc == 2)
		configFile = argsv[1];

	auto_ptr < config_t > config;
	auto_ptr<simulation_t> simulationConfig;
	try
	{
		config = configSim(configFile);
		simulationConfig = simulation(config->simulationFile());
	} catch (const xml_schema::exception& e)
	{
		LOG4CXX_ERROR(logger, e);
		return 1;
	}

	// set variables
	double current_time = 0;
	double end_time = config->end();
	double delta_time = config->delta();

	double gravity = simulationConfig->gravity();
	int numDims = simulationConfig->thermostat().numDimensions();
	double initialTemp = simulationConfig->thermostat().initialTemp();
	double temperature = simulationConfig->thermostat().targetTemp();

	int iteration = 0;
	int lastTrace = 0;
	int outputSkip = config->output().iterations();

	int thermoSkip = simulationConfig->thermostat().step();
	int thermoStart = simulationConfig->thermostat().startTime() / delta_time;
	int thermoTarget = simulationConfig->thermostat().targetTime() / delta_time;

	string out_name = config->output().dir() + config->output().filename();
	int thermostatStep = simulationConfig->thermostat().step();

	LOG4CXX_DEBUG(logger, "grav " << gravity << " temp " << temperature);

	// initialize container
	ParticleContainer container(simulationConfig);


	// initialize handler
	OutputHandler outputHandler;
	PositionHandler positionHandler(delta_time);
	VelocityHandler velocityHandler(delta_time);
	ForceResetHandler forceResetHandler;
	GravityHandler gravityHandler(gravity);
	LennardJonesHandler lennardJonesHandler(delta_time, container.getRCutOff());
	BrownianMotionHandler brownianHandler(initialTemp);
	ThermostatHandler thermostatHandler;
	KineticEnergyHandler kineticHandler;
	DebugHandler debugH;

	// initial setup
	Thermostat::numDimensions() = numDims;

	if(initialTemp != 0)
		container.iterateParticles(brownianHandler);
	container.iterateParticles(forceResetHandler);
	if(gravity != 0)
		container.iterateParticles(gravityHandler);
	container.iterateParticlePairsSymmetric(lennardJonesHandler);


	LOG4CXX_INFO(logger,
			"start iterating, " << end_time / delta_time << " iterations in total");

	// loops until end_time is reached
	while (current_time < end_time)
	{
		container.updateCells();

		container.iterateBoundaries();

		container.iterateParticles(positionHandler);

		container.iterateParticles(forceResetHandler);
		if(gravity != 0)
			container.iterateParticles(gravityHandler);
		container.iterateParticlePairsSymmetric(lennardJonesHandler);


		container.clearBoundaries();

		container.iterateParticles(velocityHandler);

		if (((iteration - thermoStart) % thermoSkip) == 0 && iteration >= thermoStart && temperature != 0)
		{
			kineticHandler.reset();
			container.iterateParticles(kineticHandler);

			double interpolation = (iteration - thermoStart) / (double)(thermoTarget - thermoStart);
			interpolation = max(0.0, min(1.0, interpolation));

			thermostatHandler.setTargetTemp(temperature, interpolation, container.countParticles());
			container.iterateParticles(thermostatHandler);
		}

		// write Particles to file
		if (iteration % outputSkip == 0)
		{
			outputHandler.init(container.countParticles());
			container.iterateParticles(outputHandler);
			outputHandler.finish(out_name, iteration);
		}

		iteration++;

		lastTrace++;
		// print simulation status
		if (lastTrace >= (end_time / delta_time / 100.0))
		{
			LOG4CXX_INFO(logger,
					(100.0 * iteration * delta_time / end_time) << " %");
			lastTrace = 0;
		}

		current_time += delta_time;
		//LOG4CXX_DEBUG(logger, " " << container.countParticles() << " particles in scene");
	}

	time(&end);
	LOG4CXX_INFO(logger, "Simulation took " << end - start << " seconds");

	if(config->saveFile().present())
	{
		string saveFilename = config->saveFile().get();
		simulationConfig = simulation(config->simulationFile());

		simulation_t saveSim(
				simulationConfig->thermostat(),
				simulationConfig->gravity(),
				simulationConfig->domain(),
				simulationConfig->boundaries(),
				simulationConfig->wallType(),
				simulationConfig->rCutOff());

		saveSim.thermostat().initialTemp() = 0;
		saveSim.thermostat().startTime() -= end_time;
		saveSim.thermostat().targetTime() -= end_time;
		saveSim.thermostat().startTime() = max(saveSim.thermostat().startTime(), 0);
		saveSim.thermostat().targetTime() = max(saveSim.thermostat().targetTime(), 0);

		saveSim.type() = simulationConfig->type();

		particleArray_t saveParticles;
		SaveStateHandler saveStateHandler(saveParticles);
		container.iterateParticles(saveStateHandler);

		saveSim.particles(saveParticles);

		xml_schema::namespace_infomap map;
		map[""].name = "";
		map[""].schema = "simulation.xsd";


		std::ofstream ofs (saveFilename.c_str());
		simulation(ofs, saveSim, map);

		LOG4CXX_INFO(logger, "wrote simulation to " << saveFilename);
	}

	LOG4CXX_INFO(logger, "Terminating now...");

	return 0;
}
