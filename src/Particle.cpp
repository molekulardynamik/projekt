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


using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;


// Define static logger variable
LoggerPtr particleLogger(Logger::getLogger("Particle"));

Particle::Particle(int type_arg) {
	type = type_arg;
	f = 0.0;
	old_f = 0.0;
	cell = -1;

	e = 0;
	o = 0;
	visible = true;
}

Particle::Particle(const Particle& other) 
	:x(other.x), v(other.v), f(other.f), old_f(other.old_f), m(other.m), e(other.e), o(other.o), type(other.type), cell(other.cell), visible(other.visible)

{
}

// Todo: maybe use initializater list instead of copy?
Particle::Particle(	utils::Vector<double, 3> x_arg,
	        utils::Vector<double, 3> v_arg,
	        double m_arg,
			double e_arg,
			double o_arg,
			bool vis,
	        int type_arg
) {
    x = x_arg;
    v = v_arg;
    m = m_arg;
    type = type_arg;
	visible = vis;
	e = e_arg;
	o = o_arg;
    f = 0.0;
    old_f = 0.0;
	cell = -1;
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

double Particle::getM() {
	return m;
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


double Particle::getE() {
	return e;
}

double Particle::getO(){
	return o;
}

std::string Particle::toString() {
	std::stringstream stream;
	stream << "Particle: X:" << x <<  " v: " << v << " f: " << f << " old_f: " << old_f << " type: " << type;
	return stream.str();
}

bool Particle::operator ==(Particle& other) {
	if ( (x == other.x) && (v == other.v) && (f == other.f) &&
			(type == other.type) & (m == other.m) && (old_f == other.old_f) && (cell == other.cell)) {
		return true;
	}

	return false;
}

std::ostream& operator<<(std::ostream& stream, Particle& p) {
	stream << p.toString();
	return stream;
}
