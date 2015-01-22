#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "Simulation/Handler/Handler.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <omp.h>

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

#ifdef _OPENMP


    LOG4CXX_DEBUG(logger, "openMp enabled");


#endif

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

	double rCutOff = simulationConfig->rCutOff();
	double rL = 0;
	bool useSmoothedLJ = simulationConfig->smoothedLJRadius().present();
	if(useSmoothedLJ)
		rL = simulationConfig->smoothedLJRadius().get();

	int wallType = simulationConfig->wallType();

	utils::Vector<double, 3> gravity;
	gravity[0] = simulationConfig->gravity().X();
	gravity[1] = simulationConfig->gravity().Y();
	gravity[2] = simulationConfig->gravity().Z();
	bool enableGravity = gravity[0] != 0 || gravity[1] != 0 || gravity[2] != 0;

	bool enableMembrane = simulationConfig->membrane().present();
	double r0, k, ljTruncation;
	utils::Vector<int, 3> pickPos, pickSize;
	utils::Vector<double, 3> pickForce;
	int pickDuration;
	if(enableMembrane)
	{
		r0 = simulationConfig->membrane().get().r0();
		k = simulationConfig->membrane().get().k();
		ljTruncation = simulationConfig->membrane().get().ljTruncation();

		pickPos[0] = simulationConfig->membrane().get().pickIndex().X();
		pickPos[1] = simulationConfig->membrane().get().pickIndex().Y();
		pickPos[2] = simulationConfig->membrane().get().pickIndex().Z();

		pickSize[0] = simulationConfig->membrane().get().pickSize().X();
		pickSize[1] = simulationConfig->membrane().get().pickSize().Y();
		pickSize[2] = simulationConfig->membrane().get().pickSize().Z();

		pickForce[0] = simulationConfig->membrane().get().pickForce().X();
		pickForce[1] = simulationConfig->membrane().get().pickForce().Y();
		pickForce[2] = simulationConfig->membrane().get().pickForce().Z();

		pickDuration = simulationConfig->membrane().get().pickDuration() / delta_time;

	}


	int numDims = simulationConfig->thermostat().numDimensions();
	double initialTemp = simulationConfig->thermostat().initialTemp();
	double temperature = simulationConfig->thermostat().targetTemp();
	utils::Vector<bool, 3> thermoMask(true);
	if(simulationConfig->thermostat().mask().present())
	{
		thermoMask[0] = simulationConfig->thermostat().mask().get().X();
		thermoMask[1] = simulationConfig->thermostat().mask().get().Y();
		thermoMask[2] = simulationConfig->thermostat().mask().get().Z();

	}

	int iteration = 0;
	int lastTrace = 0;
	int outputSkip = config->output().iterations();


	int thermoSkip = simulationConfig->thermostat().step();
	int thermoStart = simulationConfig->thermostat().startTime() / delta_time;
	int thermoTarget = simulationConfig->thermostat().targetTime() / delta_time;

	string out_name = config->output().dir() + config->output().filename();
	int thermostatStep = simulationConfig->thermostat().step();

	bool enableProfiling = config->output().profile().present();
	string profileName;
	int profileIterations;
	if (enableProfiling)
	{
		profileName = config->output().profile().get().filename();
		profileIterations = config->output().profile().get().iterations();
	}

	LOG4CXX_DEBUG(logger, "grav " << gravity.toString() << " temp " << temperature);

	// initialize container
	ParticleContainer container(simulationConfig);

	// initialize handler
	OutputHandler outputHandler;
	PositionHandler positionHandler(delta_time, wallType);
	VelocityHandler velocityHandler(delta_time, wallType);
	ForceResetHandler forceResetHandler;
	GravityHandler gravityHandler(gravity);
	LennardJonesHandler lennardJonesHandler(rCutOff);
	SmoothedLennardJonesHandler smoothedLennardJonesHandler(rCutOff, rL);
	HarmonicPotentialHandler harmonicDirectHandler, harmonicDiagonalHandler;
	PickHandler pickHandler;
	if(enableMembrane)
	{
		lennardJonesHandler = LennardJonesHandler(ljTruncation);
		harmonicDirectHandler = HarmonicPotentialHandler(r0, k, true);
		harmonicDiagonalHandler = HarmonicPotentialHandler(sqrt(2)*r0, k, false);
		pickHandler = PickHandler(pickPos, pickSize, pickForce);
	}
	BrownianMotionHandler brownianHandler(initialTemp, wallType);
	ThermostatHandler thermostatHandler(wallType, thermoMask);
	KineticEnergyHandler kineticHandler(wallType, thermoMask);
	VelocityProfileHandler velocityProfileHandler(50, 0.7, wallType, profileName);
	DiffusionHandler diffusionHandler(wallType, "diffusion");
	RDFHandler rdfHandler(rCutOff / 100.0 , rCutOff, wallType, "RDF");
	DebugHandler debugH;

	// initial setup
	Thermostat::numDimensions() = numDims;
	if(initialTemp != 0)
		container.iterateParticles(brownianHandler);
	container.iterateParticles(forceResetHandler);
	if(enableGravity)
		container.iterateParticles(gravityHandler);
	if(enableMembrane)
	{
		container.iterateParticles(pickHandler);
		container.iterateParticlePairsSymmetric(harmonicDirectHandler);
		container.iterateParticlePairsSymmetric(harmonicDiagonalHandler);
	}
	if(useSmoothedLJ)
		container.iterateParticlePairsSymmetric(smoothedLennardJonesHandler);
	else
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
		if(enableGravity)
			container.iterateParticles(gravityHandler);
		if(enableMembrane)
		{
			if(iteration < pickDuration)
				container.iterateParticles(pickHandler);
			container.iterateParticlePairsSymmetric(harmonicDirectHandler);
			container.iterateParticlePairsSymmetric(harmonicDiagonalHandler);
		}
		if(useSmoothedLJ)
			container.iterateParticlePairsSymmetric(smoothedLennardJonesHandler);
		else
			container.iterateParticlePairsSymmetric(lennardJonesHandler);

		container.clearBoundaries();

		container.iterateParticles(velocityHandler);

		if (((iteration - thermoStart) % thermoSkip) == 0 && iteration >= thermoStart && temperature != 0)
		{
			kineticHandler.reset();
			container.iterateParticlesSingleThreaded(kineticHandler);

			double interpolation = 1;
			if((thermoTarget - thermoStart) != 0)
			{
				interpolation = (iteration - thermoStart) / (double)(thermoTarget - thermoStart);
				interpolation = max(0.0, min(1.0, interpolation));
			}

			thermostatHandler.setTargetTemp(temperature, interpolation, container.countParticles());
			container.iterateParticles(thermostatHandler);
		}

		// write Particles to file
		if (iteration % outputSkip == 0)
		{
			outputHandler.init(container.countParticles());
			container.iterateParticlesSingleThreaded(outputHandler);
			outputHandler.finish(out_name, iteration);
		}

		if (enableProfiling && iteration % profileIterations == 0)
		{
			velocityProfileHandler.reset();
			container.iterateParticlesSingleThreaded(velocityProfileHandler);
			velocityProfileHandler.analize(iteration);
		}

		if(true && iteration % 1000 < 10)
		{
			if(iteration % 1000 == 0)
				diffusionHandler.reset();
			diffusionHandler.newSet();
			container.iterateParticlesSingleThreaded(diffusionHandler);
			if(iteration % 1000 == 9)
				diffusionHandler.analize(iteration - 9);
		}
		if(true && iteration % 10000 == 0)
		{
			rdfHandler.reset();
			container.iterateParticlePairs(rdfHandler);
			rdfHandler.analize(iteration);
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

	diffusionHandler.close();

	if(config->saveFile().present())
	{
		string saveFilename = config->saveFile().get();
		simulationConfig = simulation(config->simulationFile());


		simulation_t saveSim(simulationConfig->thermostat(),
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

		saveSim.smoothedLJRadius() = simulationConfig->smoothedLJRadius();
		saveSim.membrane() = simulationConfig->membrane();
		saveSim.type() = simulationConfig->type();

		particleArray_t saveParticles;
		SaveStateHandler saveStateHandler(saveParticles);
		container.iterateParticlesSingleThreaded(saveStateHandler);

		saveSim.particles(saveParticles);

		xml_schema::namespace_infomap map;
		map[""].name = "";
		map[""].schema = "simulation.xsd";

		std::ofstream ofs (saveFilename.c_str());
		simulation(ofs, saveSim, map);

		ofs.close();

		LOG4CXX_INFO(logger, "wrote simulation to " << saveFilename.c_str());

	}

	LOG4CXX_INFO(logger, "Terminating now...");

	return 0;
}
