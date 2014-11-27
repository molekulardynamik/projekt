#pragma once
#include "Particle.h"
#include <math.h>


#include <sstream>
#include <iostream>

namespace Simulation
{
	class ParticleHandler
	{
	public:
		virtual void compute(Particle& p)
		{};
		virtual void compute(Particle& p1, Particle& p2)
		{};
		virtual void computeExclusive(Particle& p1, Particle& p2)
		{};
	};



	class ParticleHandlerTimeAware : public ParticleHandler
	{
	public:
		ParticleHandlerTimeAware(double dt)
		{
			delta_t = dt;
		}

	protected:
		double delta_t;
	};

	class PositionHandler : public ParticleHandlerTimeAware
	{
	public:
		PositionHandler(double dt) : ParticleHandlerTimeAware(dt)
		{};

		void compute(Particle& p)
		{
			utils::Vector<double, 3> term1 = p.getX();
			utils::Vector<double, 3> term2 = delta_t * p.getV();
			utils::Vector<double, 3> term3 = pow(delta_t, 2) * p.getF() *(1 / (2 * p.getM()));

			p.getX() = term1 + term2 + term3;
		}
	};


	class VelocityHandler : public ParticleHandlerTimeAware
	{
	public:
		VelocityHandler(double dt) : ParticleHandlerTimeAware(dt)
		{};

		void compute(Particle& p)
		{
			utils::Vector<double, 3> term1 = p.getV();
			utils::Vector<double, 3> term2 = delta_t * (p.getOldF() + p.getF()) * (1 / (2 * p.getM()));

			p.getV() = term1 + term2;
		};
	};

	class GravityHandler : public ParticleHandlerTimeAware
	{
	public:
		GravityHandler(double dt) : ParticleHandlerTimeAware(dt)
		{};

		void compute(Particle& p)
		{
			p.getOldF() = p.getF();
			double zeros[3] = { 0, 0, 0 };
			p.getF() = utils::Vector<double, 3>(zeros);
		}

		void compute(Particle& p1, Particle& p2)
		{
			double scalar = p1.getM() * p2.getM() / pow((p1.getX() - p2.getX()).L2Norm(), 3);
			utils::Vector<double, 3> force = scalar * (p2.getX() - p1.getX());

			p1.getF() = p1.getF() + force;
		}

		void computeExclusive(Particle& p1, Particle& p2)
		{
			double scalar = p1.getM() * p2.getM() / pow((p1.getX() - p2.getX()).L2Norm(), 3);
			utils::Vector<double, 3> force = scalar * (p2.getX() - p1.getX());

			p1.getF() = p1.getF() + force;
			p2.getF() = p2.getF() - force;
		}
	};

	class LennardJonesHandler : public ParticleHandlerTimeAware
	{
	public:
		LennardJonesHandler(double dt) : ParticleHandlerTimeAware(dt)
		{};

		void compute(Particle& p)
		{
			p.getOldF() = p.getF();
			double zeros[3] = { 0, 0, 0 };
			p.getF() = utils::Vector<double, 3>(zeros);
		}

		void compute(Particle& p1, Particle& p2)
		{
			double e = 5, o = 1;

			double dist = (p1.getX() - p2.getX()).L2Norm();
			double sqrtDist = dist * dist;

			double scalar = 24 * e / sqrtDist * (pow(o / dist, 6) - 2 * pow(o / dist, 12));

			p1.getF() = p1.getF() + (scalar * (p2.getX() - p1.getX()));
		}

		void computeExclusive(Particle& p1, Particle& p2)
		{
			double e = 5, o = 1;

			double dist = (p1.getX() - p2.getX()).L2Norm();
			double sqrtDist = dist * dist;

			double scalar = 24 * e / sqrtDist * (pow(o / dist, 6) - 2 * pow(o / dist, 12));

			utils::Vector<double, 3> force = (scalar * (p2.getX() - p1.getX()));
			p1.getF() = p1.getF() + force;
			p2.getF() = p2.getF() - force;
		}

	};
}