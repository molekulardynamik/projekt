/*
 * FileReader.cpp
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#include "FileReader.h"
#include "ParticleGenerator.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace Simulation;
using namespace utils;

FileReader::FileReader() {
}

FileReader::~FileReader() {
}


void FileReader::readFile(std::vector<Simulation::Particle>& particles, char* filename) {
    std::ifstream input_file(filename);
    string tmp_string;

    if (input_file.is_open()) {

    	getline(input_file, tmp_string);
    	cout << "Read line: " << tmp_string << endl;

    	while (tmp_string.size() == 0 || tmp_string[0] == '#') {
    		getline(input_file, tmp_string);
    		cout << "Read line: " << tmp_string << endl;
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
			cout << "Reading " << num_particles << "." << endl;
			getline(input_file, tmp_string);
			cout << "Read line: " << tmp_string << endl;

			for (int i = 0; i < num_particles; i++) {
				istringstream datastream(tmp_string);

				for (int j = 0; j < 3; j++) {
					datastream >> x[j];

				}
				for (int j = 0; j < 3; j++) {
					datastream >> v[j];
				}
				if (datastream.eof()) {
					cout << "Error reading file: eof reached unexpectedly reading from line " << i << endl;
					exit(-1);
				}
				datastream >> m;
				Particle p(x, v, m);
				particles.push_back(p);

				getline(input_file, tmp_string);
				cout << "Read line: " << tmp_string << endl;
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
			cout << "Reading " << num_cuboids << "." << endl;
			getline(input_file, tmp_string);
			cout << "Read line: " << tmp_string << endl;

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
				cout << "Read line: " << tmp_string << endl;
			}
		}
    } else {
    	std::cout << "Error: could not open file " << filename << std::endl;
    	exit(-1);
    }

}

