/*
 * Particle.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "../utils/Vector.h"
#include <vector>

namespace Simulation
{
	/// \class ParticleProperty
	/// \brief Stores properties for one type of particles
	class ParticleProperty
	{
	public:
		/// Contructor for property
		ParticleProperty():
			mass(0), e(0), o(0)
		{}

		double mass;		///< Mass of particle
		double e;			///< Epsilon of particle \note Used for Lennard-Jones potential
		double o;			///< Sigma of particle \note Used for Lennard-Jones potential

		/// Converts properties into a string that can be read as input again
		std::string saveProperties();

	public:

		/// Add new type of particles
		static void push(ParticleProperty& prop);

		/// Get properties for type
		/// \param i Type of particle
		static ParticleProperty& get(int i);

		/// \return Number of properties
		static int count();

		static int& wallType();

	private:
		static std::vector<ParticleProperty> properties;		///< list of all type properties
		static int wallType_;
	};



	/// \class Particle
	/// \brief Definition for particle that participates in Simulation
	class Particle {

	private:
		utils::Vector<double, 3> x;			///< The position of the particle

		utils::Vector<double, 3> v;			///< The velocity of the particle

		utils::Vector<double, 3> f;			///< The force effective on this particle

		utils::Vector<double, 3> old_f;		///< The force wich was effective on this particle

		utils::Vector<int, 3> cuboidIndex;

		int type;							///< Type, defines properties of particle

		int cell;							///< Cell which holds particle

	public:
		Particle(int type);

		Particle(const Particle& other);

		Particle(
			utils::Vector<double, 3> x_arg,
			utils::Vector<double, 3> v_arg,
			int type
		);

		Particle(
			utils::Vector<double, 3> x_arg,
			utils::Vector<double, 3> v_arg,
			int type,
			utils::Vector<int, 3> cuboidIndex
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

		int& getCell()
		{
			return cell;
		}

		utils::Vector<int, 3> getCuboidIndex();

		bool isDirectNeighbor(Particle& other);
		bool isDiagonalNeighbor(Particle& other);

		bool operator==(Particle& other);
		bool operator==(const Particle& other);

		std::string toString();

		/// Converts particle into a string that can be read as input again
		std::string saveParticle();
	};

};
std::ostream& operator<<(std::ostream& stream, Simulation::Particle& p);

#endif /* PARTICLE_H_ */
