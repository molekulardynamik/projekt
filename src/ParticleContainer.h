#pragma once
#include <vector>
#include <list>

#include "Particle.h"
#include "ParticleHandler.h"

namespace Simulation
{
	/// <summary> Container class for managing particles
	class ParticleContainer
	{
	private:
		typedef std::list<Particle>::iterator ParticleIterator;

		class ParticleCell
		{
		public:
			typedef std::list<Particle*>::iterator PParticleIterator;

		public:
			void insert(Particle* p);
			void remove(Particle* p);
			Particle* operator[](int i);

			int count();
			void empty();

			void iterateParticles(ParticleHandler& handler);
			void iterateParticlePairs(ParticleHandler& handler);
			void iterateParticlePairsExclusive(ParticleHandler& handler);

			void combineParticlePairs(ParticleCell& other, ParticleHandler& handler);
			void combineParticlePairsExclusive(ParticleCell& other, ParticleHandler& handler);
		private:
			std::list<Particle*> particles;
		};

	public:
		ParticleContainer(){};
		void init(char* filename);
		
		/// <returns> Number of Particles; 
		int count();

		int live();
		
		/// <returns> Particle at location i
		Particle& operator[](int i);

		void iterateParticles(ParticleHandler& handler);
		void iterateParticlePairs(ParticleHandler& handler);
		void iterateParticlePairsExclusive(ParticleHandler& handler);

		void iterateBoundryParticles(ParticleHandler& handler);
		void emptyBoundryCells();

		void updateCells();

	private:
		void findCell(utils::Vector<double, 3> position, int* cell);
		void flatten(int x, int y, int* c);
		void expand(int c, int* x, int* y);

		bool isBoundry(int x, int y);
		bool isBoundry(int c);

	private:
		double rCutOff;
		int numCellsX, numCellsY;

		int liveParticles;

		std::vector<ParticleCell> cells;
		std::vector<int> boundryCells;
		std::list<Particle> particles;
	};
};
