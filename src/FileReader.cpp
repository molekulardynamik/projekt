/*
 * FileReader.cpp
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#include "FileReader.h"
#include "ParticleGenerator.h"

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>


using namespace std;
using namespace Simulation;
using namespace utils;

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;


// Define static logger variable
LoggerPtr fileReaderLogger(Logger::getLogger("FileReader"));

FileReader::FileReader() {
}

FileReader::~FileReader() {
}


void FileReader::readFile(vector<Particle>& particles, char* filename, bool* reflective, double* domainX, double* domainY, double* rCutOff) {

	LOG4CXX_INFO(fileReaderLogger, "Reading file: " << filename);
	
	std::ifstream input_file(filename);
    string tmp_string;

    if (input_file.is_open()) {

    	getline(input_file, tmp_string);

    	while (tmp_string.size() == 0 || tmp_string[0] == '#') {
    		getline(input_file, tmp_string);
    	}

		if (tmp_string == "Planets")
		{
			getline(input_file, tmp_string);

			double x[] = { 0, 0, 0 };
			double v[] = { 1, 1, 1 };
			double m = 1;
			int num_particles = 0;

			istringstream numstream(tmp_string);
			numstream >> num_particles;

			getline(input_file, tmp_string);

			for (int i = 0; i < num_particles; i++) {
				istringstream datastream(tmp_string);

				for (int j = 0; j < 3; j++) {
					datastream >> x[j];

				}
				for (int j = 0; j < 3; j++) {
					datastream >> v[j];
				}
				if (datastream.eof()) 
				{
					LOG4CXX_ERROR(fileReaderLogger, "Error reading file: eof reached unexpectedly reading from line " << i);
					exit(-1);
				}
				datastream >> m;
				Particle p(x, v, 0, true);
				particles.push_back(p);

				getline(input_file, tmp_string);
			}
		}
		else if (tmp_string == "Cuboids")
		{

			int num_cuboids = 0;
			double h = 0, m = 0, mean = 0, e = 0, o = 0;
			double x[] = { 0, 0, 0 };
			double v[] = { 0, 0, 0 };
			int n[] = { 0, 0, 0 };

			getline(input_file, tmp_string);
			(*reflective) = (tmp_string == "reflective");


			getline(input_file, tmp_string);
			istringstream domainstream(tmp_string);
			domainstream >> *domainX;
			domainstream >> *domainY;
			domainstream >> *rCutOff;


			getline(input_file, tmp_string);
			istringstream numstream(tmp_string);
			numstream >> num_cuboids;

			getline(input_file, tmp_string);

			for (int i = 0; i < num_cuboids; i++) {
				istringstream datastream(tmp_string);

				for (int j = 0; j < 3; j++) {
					datastream >> x[j];
				}
				for (int j = 0; j < 3; j++) {
					datastream >> v[j];
				}
				for (int j = 0; j < 3; j++) {
					datastream >> n[j];
				}

				ParticleProperty prop;

				datastream >> h;
				datastream >> mean;

				datastream >> prop.mass;
				datastream >> prop.e;
				datastream >> prop.o;

				int type = ParticleProperty::count();
				ParticleProperty::push(prop);

				ParticleGenerator::generateCuboid(Vector<double,3>(x), Vector<int, 3>(n), Vector<double, 3>(v), type, h, mean, particles);

				getline(input_file, tmp_string);
			}
		}
    } else {
		LOG4CXX_ERROR(fileReaderLogger, "Error: could not open file " << filename);
    	exit(-1);
    }

}

