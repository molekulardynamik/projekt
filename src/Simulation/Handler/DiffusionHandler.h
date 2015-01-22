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
	/// \class DiffusionHandler
	/// \brief Computes diffusion value and writes them to a .csv file
	class DiffusionHandler : public ParticleHandler
	{
	public:
		DiffusionHandler(int wallT, std::string filename) :
			wallType(wallT)
		{
			std::stringstream name;
			name << filename << ".csv";
			file.open(name.str().c_str());
		}
		
		/// resets gathered data
		void reset()
		{
			positionSets.clear();
		}

		/// Adds a new set of positions
		void newSet()
		{
			positionSets.push_back(std::vector<utils::Vector<double, 3> >());
		}

		/// Gathers positions and stores them in the current set
		void compute(Particle& p)
		{
			if (p.getType() == wallType)
				return;

			positionSets.back().push_back(p.getX());
		}

		/// Analizes all sets and write value for current iteration into the output file
		void analize(int iteration)
		{
			double avgVar = 0;
			for(int t=1; t<positionSets.size(); t++)
			{
				double var = 0;
				for(int p=0; p<positionSets[t].size(); p++)
				{
					double dist = (positionSets[t][p] - positionSets[0][p]).L2Norm();
					var += dist*dist;
				}
				avgVar += var / positionSets[t].size();
			}
			avgVar = avgVar / positionSets.size();

			file << iteration << "," << avgVar << std::endl;
		}

		/// Closes output file
		void close()
		{
			file.close();
		}

	private:
		int wallType;			/// < this particle type should be ignored
		std::vector<std::vector<utils::Vector<double, 3> > > positionSets;	/// < position sets in which data is store 

		std::ofstream file;		/// < output file
	};

}
