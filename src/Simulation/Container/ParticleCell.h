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
	utils::Vector<double, 3> getLeftBottomFrontCorner();

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
	ParticleCell* neighbors_[26];
	ParticleCell* oppositeHaloCell_;
	utils::Vector<double, 3> leftBottomFrontCorner_;
	double size_;
	CellType cellType_;


	std::list<Simulation::Particle> particles_;

public:
	static std::map<CellType,BoundaryCondition> boundaryConditions;
};

}
