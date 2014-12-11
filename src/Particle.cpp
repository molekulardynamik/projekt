/*
 * Particle.cpp
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#include "Particle.h"

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include <sstream>
#include <iostream>

using namespace Simulation;
using namespace std;

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;


// Define static logger variable
LoggerPtr particleLogger(Logger::getLogger("Particle"));


vector<ParticleProperty> ParticleProperty::properties;

std::string ParticleProperty::saveProperties()
{
	std::stringstream stream;
	stream << "type:" << endl;
	stream << "m: " << mass << endl;
	stream << "e: " << e << endl;
	stream << "o: " << o << endl;
	stream << "end" << endl;
	return stream.str();
}


void ParticleProperty::push(ParticleProperty& prop)
{
	properties.push_back(prop);
}

ParticleProperty& ParticleProperty::get(int i)
{
	return properties[i];
}

int ParticleProperty::count()
{
	return properties.size();
}


Particle::Particle(int type_arg, bool vis /*= true*/) 
	: x(0.0), v(0.0), f(0.0), old_f(0.0), type(type_arg), cell(-1), visible(vis)
{

}

Particle::Particle(const Particle& other) 
	:x(other.x), v(other.v), f(other.f), old_f(other.old_f), type(other.type), cell(other.cell), visible(other.visible)

{

}

// Todo: maybe use initializater list instead of copy?
Particle::Particle(	
	utils::Vector<double, 3> x_arg,
	utils::Vector<double, 3> v_arg,
	int type_arg,
	bool vis /* = true*/)
	: x(x_arg), v(v_arg), f(0.0), old_f(0.0), type(type_arg), cell(-1), visible(vis)
{
}

Particle::~Particle() {
}

utils::Vector<double, 3>& Particle::getX() {
	return x;
}

utils::Vector<double, 3>& Particle::getV() {
	return v;
}

utils::Vector<double, 3>& Particle::getF() {
	return f;
}

utils::Vector<double, 3>& Particle::getOldF() {
	return old_f;
}

int Particle::getType() {
	return type;
}
void Particle::setType(int t) {
	type = t;
}

int Particle::getCell() {
	return cell;
}
void Particle::setCell(int c) {
	cell = c;
}

bool Particle::isVisible(){
	return visible;
}

double Particle::getM()
{
	return ParticleProperty::get(type).mass;
}

double Particle::getE()
{
	return ParticleProperty::get(type).e;
}

double Particle::getO()
{
	return ParticleProperty::get(type).o;
}

std::string Particle::toString() {
	std::stringstream stream;
	stream << "Particle: X:" << x <<  " v: " << v << " f: " << f << " old_f: " << old_f << " type: " << type << " cell: " << cell << (visible ? " visible" : " invisible");
	return stream.str();
}

std::string Particle::saveParticle() 
{
	std::stringstream stream;
	stream << "particle:" << endl;
	stream << "x: " << x[0] << " " << x[1] << " " << x[2] << endl;
	stream << "v: " << v[0] << " " << v[1] << " " << v[2] << endl;
	stream << "type: " << type << endl;
	stream << "end" << endl;
	return stream.str();
}

bool Particle::operator ==(Particle& other) {
	if ((x == other.x) && (v == other.v) && (f == other.f) &&
		(type == other.type) && (old_f == other.old_f) && 
		(cell == other.cell) && (visible == other.visible) )
		return true;

	return false;
}

std::ostream& operator<<(std::ostream& stream, Particle& p) {
	stream << p.toString();
	return stream;
}
