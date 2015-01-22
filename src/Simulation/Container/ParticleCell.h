#pragma once

#include <list>
#include <map>

#include "../Particle.h"
#include "../Handler/ParticleHandler.h"

namespace Simulation
{

/// \class ParticleCell
/// \brief Stores multiple particles and allows iterating through them
class ParticleCell
{
public:
	static void moveParticle(ParticleCell& from, ParticleCell& to, Particle& particle);


public:
	/// \enum Neighborhood
	/// Defines neighbor ids 
	enum Neighborhood
	{
		LeftBottomFront = 0,
		BottomFront = 1,
		RightBottomFront = 2,
		LeftFront = 3,
		Front = 4,
		RightFront = 5,
		LeftTopFront = 6,
		TopFront = 7,
		RightTopFront = 8,

		LeftBottom = 9,
		Bottom = 10,
		RightBottom = 11,
		Left = 12,
		Right = 13,
		LeftTop = 14,
		Top = 15,
		RightTop = 16,

		LeftBottomBack = 17,
		BottomBack = 18,
		RightBottomBack = 19,
		LeftBack = 20,
		Back = 21,
		RightBack = 22,
		LeftTopBack = 23,
		TopBack = 24,
		RightTopBack = 25,
	};

	/// \enum CellType
	/// Defines whether cell is boundary or not
	enum CellType
	{
		InnerCell,
		Corner,
		LeftBoundary,
		RightBoundary,
		BottomBoundary,
		TopBoundary,
		FrontBoundary,
		BackBoundary,
	};

	/// \enum BoundaryCondition
	// Defines which boundaryCondition should be applied 
	enum BoundaryCondition
	{
		None,
		OutFlow,
		Reflecting,
		Periodic
	};

public:
	ParticleCell(int index, int domain, utils::Vector<double, 3> bottomLeft, double size);

	/// Sets the celltype for the particle cell
	void setCellType(CellType cellType);
	/// \return cellType of the particle cell
	CellType getCellType();

	/// Sets the a neighbor of the particle cell 
	void setNeighbor(ParticleCell* neighbor, Neighborhood neighborhood);

	/// \return number of valid neighbors 	
	int countNeighbors();
	/// prints neighbors
	void printNeighbors();

	/// Sets opposite halo cell for the particle cell
	/// \note only affects periodic boundaries 
	void setOppositeHaloCell(ParticleCell* haloCell);
	/// \return opposite particleCell
	/// \note only valid for periodic boundaries 	
	ParticleCell* getOppositeHaloCell();

	/// \return index in the whole simulation of the particle cell
	int getIndex();
	/// \return index of subdomain
	int getDomain()
	{
		return domain_;
	}
	/// \return position of the bottom left front corner of the particle cell
	utils::Vector<double, 3> getLeftBottomFrontCorner();

	/// Adds a particle to the cell
	/// \note if the particle does not fit in this cell, it is propagated to the neighbor cells  
	void addParticle(Simulation::Particle& particle);
	/// Removes particle from cell
	void removeParticle(Simulation::Particle& particle);
	/// Checks whether all particles shoulb be in this cell
	/// \note if not, the particle is propagated to the neighbor cells
	void checkParticles();

	/// \return number of particles in cell
	int countParticles();

	/// Iterates over all particles in cell an executes particle handler
	void iterateParticles(ParticleHandler& handler);

	/// Iterates over all particles pairs in cell an executes particle handler
	void iterateParticlePairs(ParticleHandler& handler);

	/// Iterates symmetricaly over all particles pairs in cell an executes particle handler
	void iterateParticlePairsSymmetric(ParticleHandler& handler);

	/// Applies boudariecondition of the particle cell
	void applyBoundaryCondition();
	/// removes all particles in the cell
	void clearBoundary();

private:
	/// Checks whether the particles shoulb be in this cell
	/// \note if not, the particle is propagated to the neighbor cells
	bool checkParticle(Simulation::Particle& particle);

	/// Applies reflective boundary condition
	void applyReflectionCondition();
	/// Applies periodic boundary condition
	void applyPeriodicCondition();

private:
	int index_, domain_;
	ParticleCell* neighbors_[26];
	ParticleCell* oppositeHaloCell_;
	utils::Vector<double, 3> leftBottomFrontCorner_;
	double size_;						/// < size of the particle cell in one dimension
	CellType cellType_;


	std::list<Simulation::Particle> particles_;

public:
	static std::map<CellType,BoundaryCondition> boundaryConditions;		/// < map between cellType and boundary condition
};

}
