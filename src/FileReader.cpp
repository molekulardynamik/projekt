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

//#include "../cuboid-pskel.hxx"


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


void FileReader::readFile(std::vector<Simulation::Particle>& particles, char* filename) {
    std::ifstream input_file(filename);
    string tmp_string;

    if (input_file.is_open()) {

    	getline(input_file, tmp_string);
		LOG4CXX_INFO(fileReaderLogger, "Read line: " << tmp_string);

    	while (tmp_string.size() == 0 || tmp_string[0] == '#') {
    		getline(input_file, tmp_string);
			LOG4CXX_INFO(fileReaderLogger, "Read line: " << tmp_string);
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
			LOG4CXX_INFO(fileReaderLogger, "Reading " << num_particles);

			getline(input_file, tmp_string);
			LOG4CXX_INFO(fileReaderLogger, "Read line: " << tmp_string);

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
				Particle p(x, v, m);
				particles.push_back(p);

				getline(input_file, tmp_string);
				LOG4CXX_INFO(fileReaderLogger, "Read line: " << tmp_string);
			}
		}
		else if (tmp_string == "Cuboids")
		{
			getline(input_file, tmp_string);

			int num_cuboids = 0;
			double h = 0, m = 0, mean = 0;
			double x[] = { 0, 0, 0 };
			double v[] = { 0, 0, 0 };
			int n[] = { 0, 0, 0 };

			istringstream numstream(tmp_string);
			numstream >> num_cuboids;
			LOG4CXX_INFO(fileReaderLogger, "Reading " << num_cuboids);
			getline(input_file, tmp_string);
			LOG4CXX_INFO(fileReaderLogger, "Read line: " << tmp_string);

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

				datastream >> h;
				datastream >> m;
				datastream >> mean;

				ParticleGenerator::generateCuboid(Vector<double,3>(x), Vector<int, 3>(n), h, m, Vector<double, 3>(v), mean, particles);

				getline(input_file, tmp_string);
				LOG4CXX_INFO(fileReaderLogger, "Read line: " << tmp_string);
			}
		}
    } else {
		LOG4CXX_ERROR(fileReaderLogger, "Error: could not open file " << filename);
    	exit(-1);
    }

}

