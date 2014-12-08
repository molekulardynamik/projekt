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

		enum CellType
		{
			InnerCell		= 0, 
			LeftBoundry		= 1 << 0,
			RightBoundry	= 1 << 1,
			BottomBoundry	= 1 << 2,
			TopBoundry		= 1 << 3
		};

		enum BoundryCondition
		{
			OutFlow,
			Reflecting
		};

	public:
		ParticleContainer()
		{
			cells.clear();
			boundryCells.clear();
			boundryConditions.clear();
			particles.clear();
		};
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
		void iterateBoundryCells();

		void updateCells();

	private:
		void findCell(utils::Vector<double, 3> position, int* cell);
		void flatten(int x, int y, int* c);
		void expand(int c, int* x, int* y);

		char cellType(int x, int y);
		char cellType(int c);

		int getReflectingCell(int boundrycell);

	private:
		double rCutOff;
		int numCellsX, numCellsY;
		bool reflective;

		int liveParticles;
		int numDummies;

		std::vector<ParticleCell> cells;
		std::vector<int> boundryCells;
		std::vector<BoundryCondition> boundryConditions;
		std::vector<Particle> particles;

	};
};
