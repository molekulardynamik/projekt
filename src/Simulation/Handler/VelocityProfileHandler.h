#pragma once
#include "ParticleHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>

namespace Simulation
{
	/// \class SmoothedLennardJonesHandler
	/// \brief Computes force  applied by Lennard-Jones potential
	class VelocityProfileHandler : public ParticleHandler
	{
	public:
		VelocityProfileHandler(int numB, double binS, int wallT, std::string filename) :
			numBins(numB), binSize(binS), wallType(wallT), profileName(filename)
		{
			velocities.resize(numBins);
			counts.resize(numBins);
		}

		void reset()
		{
			for (int i = 0; i < numBins; i++)
			{
				velocities[i] = 0;
				counts[i] = 0;
			}
		}

		void compute(Particle& p)
		{
			if (p.getType() == wallType)
				return;

			int bin = p.getX()[0] / binSize;
			velocities[bin] += p.getV()[1];
			counts[bin] += 1;
		}

		void analize(int iteration)
		{
			std::stringstream filename;
			filename << profileName << iteration << ".csv";
			std::ofstream file(filename.str().c_str());

			for (int i = 0; i < numBins; i++)
			{
				if (counts[i] != 0)
					file << velocities[i] / counts[i];
				else
					file << 0;

				file << "," << counts[i] << std::endl;
			}

			file.close();
		}
	private:
		int wallType;
		int numBins;
		double binSize;
		std::vector<double> velocities;
		std::vector<int> counts;

		std::string profileName;

	};

}
