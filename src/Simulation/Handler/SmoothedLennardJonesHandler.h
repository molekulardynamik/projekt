#pragma once
#include "ParticleHandler.h"

namespace Simulation
{
	/// \class SmoothedLennardJonesHandler
	/// \brief Computes force  applied by smoothed Lennard-Jones potential
	class SmoothedLennardJonesHandler : public ParticleHandler
	{
	public:
		SmoothedLennardJonesHandler(double r, double rl) :
			rCutOff(r), rL(rl)
		{
		}

		/// Nonsymmetric computation
			void compute(Particle& p1, Particle& p2)
			{
				double e = (p1.getE() + p2.getE()) / 2;
				double o = sqrt(p1.getO() * p2.getO());

				double dist = (p1.getX() - p2.getX()).L2Norm();
				if (dist > rCutOff)
					return;

				double sqrtDist = dist * dist;

				double scalar = 24 * e / sqrtDist * (pow(o / dist, 6) - 2 * pow(o / dist, 12));
				scalar = scalar * smooth(dist);

				p1.getF() = p1.getF() + (scalar * (p2.getX() - p1.getX()));
			}

			/// Symmetric computation
			void computeSymmetric(Particle& p1, Particle& p2)
			{
				double e = (p1.getE() + p2.getE()) / 2;
				double o = sqrt(p1.getO() * p2.getO());

				double dist = (p1.getX() - p2.getX()).L2Norm();
				if (dist > rCutOff)
					return;

				double sqrtDist = dist * dist;

				double scalar = 24 * e / sqrtDist * (pow(o / dist, 6) - 2 * pow(o / dist, 12));
				scalar = scalar * smooth(dist);

				utils::Vector<double, 3> force = (scalar * (p2.getX() - p1.getX()));
				p1.getF() = p1.getF() + force;
				p2.getF() = p2.getF() - force;
			}

			double smooth(double dist)
			{
				if(dist <= rL)
					return 1;
				else if(dist < rCutOff)
				{
					double term1 = (dist - rL);
					term1 = term1 * term1;

					double term2 = rCutOff - rL;
					term2 = term2*term2*term2;
					term2 = (3 * rCutOff - rL -  2 * dist) / term2;

					return 1 - term1 * term2;
				}
			}

	private:
		double rCutOff;
		double rL;

	};

}
