#pragma once
#include <vector>

#include "Particle.h"
#include "FileReader.h"

namespace Simulation
{
	/// <summary> Container class for managing Molecules
	class MoleculeContainer
	{
	public:
		MoleculeContainer(){}
		MoleculeContainer(char* filename);
		
		/// <returns> Number of Molecules; 
		int count()
		{
			return particles.size();
		}
		
		/// <returns> Particle at location i
		Particle& operator[](int i)
		{
			return particles[i];
		}


	private:
		std::vector<Particle> particles;
	};
};
