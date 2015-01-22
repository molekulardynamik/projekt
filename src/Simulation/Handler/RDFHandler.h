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
	/// \class RDFHandler
	class RDFHandler : public ParticleHandler
	{
	public:
		RDFHandler(double r, double rCutOff, int wallT, std::string name) :
			dr(r), wallType(wallT), filename(name)
		{


			counts.resize(std::ceil(rCutOff / r));
		}

		void reset()
		{
			for(int i=0; i<counts.size(); i++)
			{
				counts[i] = 0;
			}
		}

		void compute(Particle& p1, Particle& p2)
		{
			if(p1.getType() == wallType || p2.getType() == wallType)
				return;

			utils::Vector<double, 3> diff = p1.getX() - p2.getX();
			double dist = diff.L2Norm();
			if(dist / dr < counts.size())
				counts[dist / dr]++;
		}

		void analize(int iteration)
		{
			std::stringstream name;
			name << filename << "_" << iteration << ".csv";
			std::ofstream file(name.str().c_str());

			for(int i=0; i<counts.size(); i++)
			{
				double ri = dr *i;
				double volume = ri + dr;
				volume = volume * volume * volume;
				volume = volume - ri * ri * ri;
				volume = 4 * M_PI / 3 * volume;

				file << i * dr << "," << counts[i] / volume << std::endl;
			}

			file.close();
		}

	private:
		int wallType;

		double dr;
		std::vector<int> counts;

		std::string filename;
	};

}

