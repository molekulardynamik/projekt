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

		void reset()
		{
			positionSets.clear();
		}

		void newSet()
		{
			positionSets.push_back(std::vector<utils::Vector<double, 3> >());
		}

		void compute(Particle& p)
		{
			if (p.getType() == wallType)
				return;

			positionSets.back().push_back(p.getX());
		}

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

		void close()
		{
			file.close();
		}

	private:
		int wallType;
		std::vector<std::vector<utils::Vector<double, 3> > > positionSets;

		std::ofstream file;
	};

}
