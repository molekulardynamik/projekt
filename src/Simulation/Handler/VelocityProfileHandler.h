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
	/// \class VelocityProfileHandler
	/// \brief Calculates velocity profile along y axis
	class VelocityProfileHandler : public ParticleHandler
	{
	public:
		VelocityProfileHandler(int numB, double binS, int wallT, std::string filename) :
			numBins(numB), binSize(binS), wallType(wallT), profileName(filename)
		{
			velocities.resize(numBins);
			counts.resize(numBins);
		}

		/// Resets data
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

		/// Analizes velocities and writes result to the output file
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
		int wallType;	/// < particles of this type should be ignored
		int numBins;	/// < number of bins in which x axis in split
		double binSize;	/// < size of a bin
		std::vector<double> velocities;
		std::vector<int> counts;

		std::string profileName;	/// < output filename

	};

}
