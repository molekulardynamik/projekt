/*
 * Particle.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "utils/Vector.h"
#include <vector>

namespace Simulation
{
	class ParticleProperty
	{
	public:
		ParticleProperty():
			mass(0), e(0), o(0)
		{}

		double mass;
		double e;
		double o;
		// static

	public:
		static void push(ParticleProperty& prop);

		static ParticleProperty& get(int i);

		static int count();

	private:
		static std::vector<ParticleProperty> properties;
	};

	class StaticPropert
	{

	};

	class Particle {

	private:

		/** the position of the particle */
		utils::Vector<double, 3> x;

		/** the velocity of the particle */
		utils::Vector<double, 3> v;

		/** the force effective on this particle */
		utils::Vector<double, 3> f;

		/** the force wich was effective on this particle */
		utils::Vector<double, 3> old_f;

		/** type of the particle. Use it for whatever you want (e.g. to seperate
		 * molecules belonging to different bodies, matters, and so on)
		 */
		int type;

		/** cell in wich holds the particle*/
		int cell;

		bool visible;

	public:
		Particle(int type, bool vivible = true);

		Particle(const Particle& other);

		Particle(
				// for visualization, we need always 3 coordinates
				// -> in case of 2d, we use only the first and the second
			utils::Vector<double, 3> x_arg,
			utils::Vector<double, 3> v_arg,
			int type,
			bool vis = true
		);

		virtual ~Particle();

		utils::Vector<double, 3>& getX();

		utils::Vector<double, 3>& getF();

		utils::Vector<double, 3>& getOldF();

		utils::Vector<double, 3>& getV();

		double getM();

		double getE();

		double getO();

		int getType();
		void setType(int t);

		int getCell();
		void setCell(int c);

		bool isVisible();

		bool operator==(Particle& other);

		std::string toString();
	};

};
std::ostream& operator<<(std::ostream& stream, Simulation::Particle& p);

#endif /* PARTICLE_H_ */
