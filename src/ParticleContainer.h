#pragma once
#include <vector>
#include <list>

#include "Particle.h"
#include "ParticleHandler.h"

namespace Simulation
{

	typedef std::list<Particle*>::iterator PParticleIterator;

	/// \class ParticleCell
	/// \brief Stores pointers to particles which lie in this cell
	class ParticleCell
	{
	public:

		/// \enum CellType
		/// Defines whether cell is boundary or not
		enum CellType
		{
			InnerCell,
			LeftBoundary,
			RightBoundary,
			BottomBoundary,
			TopBoundary,
			Corner
		};

		/// Constructor for particle cell
		/// \param i Index of cell in 1D cell list
		/// \param pos Position of cell (lower left-hand corner)
		/// \param r Pointer to cutoff radius
		ParticleCell(int i, utils::Vector<double, 3>& pos, double* r);

		/// \return Celltype of cell
		CellType& cellType();

		/// Assigns particle to cell
		void insert(Particle* pParticle);

		/// Renoves particle from cell
		void remove(Particle* pParticle);

		/// \return Whether particle lies in cell
		bool contains(Particle* pParticle);

		/// \return Number of particles associated with cell
		int count();

		/// \param i Index of particle in cell
		/// \return Pointer to particle at index i
		Particle* operator[](int i);

		/// Iterates over all live particles in cell an executes particle handler
		void iterateParticles(ParticleHandler& handler);

		/// Iterates over all live particles pairs in cell an executes particle handler
		void iterateParticlePairs(ParticleHandler& handler);

		/// Iterates over all live particles pairs in cell an executes particle handler
		/// \note Every particle will be handled only once. This is faster but requires a symmetrical computation.
		void iterateParticlePairsExclusive(ParticleHandler& handler);

		/// Iterates over all live particles pairs in this and other cell
		void combineParticlePairs(ParticleCell& other, ParticleHandler& handler);

		/// Iterates over all live particles pairs in this and other cell
		/// \note Every particle will be handled only once. This is faster but requires a symmetrical computation.
		void combineParticlePairsExclusive(ParticleCell& other, ParticleHandler& handler);	


		/// \return Position of cell
		utils::Vector<double, 3>& pos(){
			return position;
		}

		/// \return Index of cell in 1D cell list
		int index(){
			return selfIndex;
		}

	private:
		std::list<Particle*> pParticles;		///< List of pointers to particles in this cell

		int selfIndex;							///< Index of cell in 1D cell list
		utils::Vector<double, 3> position;		///< Position of cell
		double* pRCutOff;						///< Pointer to cutoff radius
		CellType type;							///< Type of cell
	};


	/// \class ParticleContainer
	/// 
	/// \brief Stores particles and handles accesses and computations
	/// 
	/// This class stores all particles participating in the simulation. 
	/// It is recommended to access particles only over this class.
	/// For performance purposes all particles are assigned to different cells
	/// to avoid unnecessary computations over large distances. This implies that
	/// every computation which involes two or more particles can be neglected at a
	/// certain distance ( the cutOff radius).
	/// It is possible to specify a boundary condition for each boundary of simulation space.
	class ParticleContainer
	{

		/// Specifies behavior of a boundary cell
		enum BoundaryCondition
		{
			OutFlow,				///< Particles which leave the simulation space will be deleted
			Reflecting,				///< Particles will be reflected on the boundaries
			Periodic,				///< Particles will enter the simulation space on the opposite side
		};

	public:
		ParticleContainer();


		/// Initializes particle container with data from file
		/// \param filename File which will be read
		void init(char* filename);


		/// Assigns particles to cells based on their location 
		void updateCells();

		/// \return Number of live particles
		int count();

		/// \return Number of live and visible particles
		int countVisible();

		/// \param i Index of particle
		/// \return Particle at index i
		Particle& operator[](int i);

		/// Iterates over all live particles an executes particle handler
		void iterateParticles(ParticleHandler& handler);

		/// Iterates over all live particle pairs (only neighbouring cells are considered) and executes particle pair handler
		void iterateParticlePairs(ParticleHandler& handler);

		/// Iterates over all live particle pairs (only neighbouring cells are considered) and executes exclusive particle par handler. 
		/// \note Every particle will be handled only once. This is faster but requires a symmetrical computation.
		void iterateParticlePairsExclusive(ParticleHandler& handler);

		/// Iterates over all boundry cells and handles boundary behavior
		void iterateBoundaryCells();

		/// \return Cutoff radius
		double getCutOff();

	private:

		/// Finds 1D cell index based on given poistion
		/// \param position Position of Particle
		/// \param cell Pointer to 1D cell index 
		void findCell(utils::Vector<double, 3> position, int* cell);

		///	 Converts 2D indices to a 1D index
		/// \param x, y 2D indices
		/// \param cell Pointer to 1D cell index
		void flatten(int x, int y, int* cell);

		/// Converts a 1D index to 2D indices
		/// \param x, y Pointers to 2D indices
		/// \param cell 1D cell index
		void expand(int* x, int* y, int cell);

	private:
		std::vector<Particle> particlePool;			///< List of every particle which was created at startup
		std::vector<Particle> dummies;				///< List of dummy particles which are needed to handle boundary behavior
		std::list<Particle*> liveParticles;			///< List of pointers to live particles that should be computed

		int visible;								///< Number of visible particles

		double rCutOff;								///< Cutoff radius
		int numCellsX, numCellsY;					///< Number of cells in X/Y - Direction
		std::vector<ParticleCell> cells;			///< List of all cells (including boundaries) \note This is a 1D representation of a 2D grid


		struct BoundaryHaloPair
		{
			ParticleCell* boundaryCell;
			ParticleCell* haloCell;
			BoundaryCondition condition;

			BoundaryHaloPair(ParticleCell* b, ParticleCell* h, BoundaryCondition c)
				: boundaryCell(b), haloCell(h), condition(c)
			{

			}
		};
		std::vector<BoundaryHaloPair> boundaryHaloPairs;	///< List of all boundary-halo pair, except conrner cells

		int wallType;								///< Type index of wall properties
	};
};
