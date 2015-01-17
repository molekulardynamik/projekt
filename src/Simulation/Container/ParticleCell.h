#pragma once

#include <list>
#include <map>

#include "../Particle.h"
#include "../Handler/ParticleHandler.h"

namespace Simulation
{

class ParticleCell
{
public:
	static void moveParticle(ParticleCell& from, ParticleCell& to, Particle& particle);


public:
	enum Neighborhood
	{
		BottomLeft = 0,
		Bottom = 1,
		BottomRight = 2,
		Left = 3,
		Right = 4,
		TopLeft = 5,
		Top = 6,
		TopRight = 7
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
		TopBoundary
	};

	enum BoundaryCondition
	{
		None,
		OutFlow,
		Reflecting,
		Periodic
	};

public:
	ParticleCell(int index, utils::Vector<double, 3> bottomLeft, double size);

	void setCellType(CellType cellType);
	CellType getCellType();

	void setNeighbor(ParticleCell* neighbor, Neighborhood neighborhood);
	int countNeighbors();
	void printNeighbors();

	void setOppositeHaloCell(ParticleCell* haloCell);
	ParticleCell* getOppositeHaloCell();

	int getIndex();
	utils::Vector<double, 3> getBottomLeftCorner();

	void addParticle(Simulation::Particle& particle);
	void removeParticle(Simulation::Particle& particle);
	void checkParticles();

	int countParticles();

	/// Iterates over all particles in cell an executes particle handler
	void iterateParticles(ParticleHandler& handler);

	/// Iterates over all particles pairs in cell an executes particle handler
	void iterateParticlePairs(ParticleHandler& handler);

	/// Iterates over all particles pairs in cell an executes particle handler
	void iterateParticlePairsSymmetric(ParticleHandler& handler);

	void applyBoundaryCondition();
	void clearBoundary();

private:
	bool checkParticle(Simulation::Particle& particle);

	void applyReflectionCondition();
	void applyPeriodicCondition();

private:
	int index_;
	ParticleCell* neighbors_[8];
	ParticleCell* oppositeHaloCell_;
	utils::Vector<double, 3> bottomLeftCorner_;
	double size_;
	CellType cellType_;


	std::list<Simulation::Particle> particles_;

public:
	static std::map<CellType,BoundaryCondition> boundaryConditions;
};

}
