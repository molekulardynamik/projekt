#pragma once
#include <vector>
#include <list>

#include "Particle.h"
#include "ParticleHandler.h"

namespace Simulation
{

	typedef std::list<Particle*>::iterator PParticleIterator;

	class ParticleCell
	{
	public:
		enum CellType
		{
			InnerCell,
			LeftBoundry,
			RightBoundry,
			BottomBoundry,
			TopBoundry,
			Corner
		};

		ParticleCell(int i, utils::Vector<double, 3>& pos, double* r);
		CellType& cellType();

		void insert(Particle* pParticle);
		void remove(Particle* pParticle);
		bool contains(Particle* pParticle);

		int count();
		Particle* operator[](int i);

		void iterateParticles(ParticleHandler& handler);
		void iterateParticlePairs(ParticleHandler& handler);
		void iterateParticlePairsExclusive(ParticleHandler& handler);

		void combineParticlePairs(ParticleCell& other, ParticleHandler& handler);
		void combineParticlePairsExclusive(ParticleCell& other, ParticleHandler& handler);	

		utils::Vector<double, 3>& pos(){
			return position;
		}

		int index(){
			return selfIndex;
		}

	private:
		std::list<Particle*> pParticles;

		int selfIndex;
		utils::Vector<double, 3> position;
		double* pRCutOff;
		CellType type;
	};


	class ParticleContainer
	{
		enum BoundryCondition
		{
			OutFlow,
			Reflecting,
			Periodic,
		};

	public:
		ParticleContainer();

		void init(char* filename);

		void updateCells();

		int count();
		int countVisible();

		Particle& operator[](int i);

		void iterateParticles(ParticleHandler& handler);
		void iterateParticlePairs(ParticleHandler& handler);
		void iterateParticlePairsExclusive(ParticleHandler& handler);

		void iterateBoundryCells();

		double getCutOff();

	private:
		void findCell(utils::Vector<double, 3> position, int* cell);
		void flatten(int x, int y, int* cell);
		void expand(int* x, int* y, int cell);

	private:
		std::vector<Particle> particlePool;
		std::vector<Particle> dummies;
		std::list<Particle*> liveParticles;

		int visible;

		double rCutOff;
		int numCellsX, numCellsY;
		std::vector<ParticleCell> cells;

		struct BoundryHaloPair
		{
			ParticleCell* boundryCell;
			ParticleCell* haloCell;
			BoundryCondition condition;

			BoundryHaloPair(ParticleCell* b, ParticleCell* h, BoundryCondition c)
				: boundryCell(b), haloCell(h), condition(c)
			{

			}
		};

		std::vector<BoundryHaloPair> boundryHaloPairs;
	};
};
