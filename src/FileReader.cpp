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

vector<string> splitString(string s, char c);

FileReader::FileReader() {
}

FileReader::~FileReader() {
}

/*
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

				datastream >> prop.mass;
				datastream >> prop.e;
				datastream >> prop.o;

				int type = ParticleProperty::count();
				ParticleProperty::push(prop);

				ParticleGenerator::generateCuboid(Vector<double,3>(x), Vector<int, 3>(n), Vector<double, 3>(v), type, h, particles);

				getline(input_file, tmp_string);
			}
		}
    } else {
		LOG4CXX_ERROR(fileReaderLogger, "Error: could not open file " << filename);
    	exit(-1);
    }

}
*/

void FileReader::readFile(vector<Particle>& particles, char* filename, double* domainX, double* domainY, double* rCutOff)
{
	LOG4CXX_INFO(fileReaderLogger, "Reading file: " << filename);

	std::ifstream input_file(filename);

	if (!input_file.is_open())
	{
		LOG4CXX_ERROR(fileReaderLogger, "Error: could not open file " << filename);
		exit(-1);
	}

	string line;
	while (getline(input_file, line))
	{
		if (line[0] == '#')
			continue;

		vector<string> args = splitString(line, ':');

		if (args[0] == "domain" && args.size() > 1)
		{
			istringstream domainstream(args[1]);
			domainstream >> *domainX;
			domainstream >> *domainY;
		}
		else if (args[0] == "rCutOff" && args.size() > 1)
		{
			istringstream cutofstream(args[1]);
			cutofstream >> *rCutOff;
		}
		else if (args[0] == "cuboid")
		{

			double x[3] = { 0, 0, 0 };
			double v[3] = { 0, 0, 0 };
			int n[3] = { 0, 0, 0 };
			int type = 0;
			double h = 0;

			string cuboidLine;
			while (getline(input_file, cuboidLine))
			{
				if (cuboidLine[0] == '#')
					continue;

				vector<string> cuboidArgs = splitString(cuboidLine, ':');

				if (cuboidArgs.size() > 1)
				{
					if (cuboidArgs[0] == "x")
					{
						istringstream positionstream(cuboidArgs[1]);

						for (int j = 0; j < 3; j++) {
							positionstream >> x[j];
						}
					}
					else if (cuboidArgs[0] == "v")
					{
						istringstream velocitystream(cuboidArgs[1]);

						for (int j = 0; j < 3; j++) {
							velocitystream >> v[j];
						}
					}
					else if (cuboidArgs[0] == "n")
					{
						istringstream sizestream(cuboidArgs[1]);

						for (int j = 0; j < 3; j++) {
							sizestream >> n[j];
						}
					}
					else if (cuboidArgs[0] == "h")
					{
						istringstream spacingstream(cuboidArgs[1]);
						spacingstream >> h;
					}
					else if (cuboidArgs[0] == "type")
					{
						istringstream typestream(cuboidArgs[1]);
						typestream >> type;
					}
					
				}
				else if (cuboidLine == "end")
					break;
			}			


			ParticleGenerator::generateCuboid(Vector<double, 3>(x), Vector<double, 3>(v), Vector<int, 3>(n), h, type, particles);

			LOG4CXX_DEBUG(fileReaderLogger, "generated cuboid ");
		}
		else if (args[0] == "sphere")
		{

			double x[3] = { 0, 0, 0 };
			double v[3] = { 0, 0, 0 };
			int n = 0;
			int type = 0;
			double h = 0;

			string sphereLine;
			while (getline(input_file, sphereLine))
			{
				if (sphereLine[0] == '#')
					continue;

				vector<string> sphereArgs = splitString(sphereLine, ':');

				if (sphereArgs.size() > 1)
				{
					if (sphereArgs[0] == "x")
					{
						istringstream positionstream(sphereArgs[1]);

						for (int j = 0; j < 3; j++) {
							positionstream >> x[j];
						}
					}
					else if (sphereArgs[0] == "v")
					{
						istringstream velocitystream(sphereArgs[1]);

						for (int j = 0; j < 3; j++) {
							velocitystream >> v[j];
						}
					}
					else if (sphereArgs[0] == "n")
					{
						istringstream sizestream(sphereArgs[1]);

						sizestream >> n;
					}
					else if (sphereArgs[0] == "h")
					{
						istringstream spacingstream(sphereArgs[1]);
						spacingstream >> h;
					}
					else if (sphereArgs[0] == "type")
					{
						istringstream typestream(sphereArgs[1]);
						typestream >> type;
					}

				}
				else if (sphereLine == "end")
					break;
			}


			ParticleGenerator::generateSphere(Vector<double, 3>(x), Vector<double, 3>(v), n, h, type, particles);

			LOG4CXX_DEBUG(fileReaderLogger, "generated sphere " << v[0] << " " << v[1] << " " << v[2]);
		}
		else if (args[0] == "type")
		{
			double m = 0, h = 0, e = 0, o = 0;

			string typeLine;
			while (getline(input_file, typeLine))
			{
				if (typeLine[0] == '#')
					continue;

				vector<string> typeArgs = splitString(typeLine, ':');

				if (typeArgs.size() > 1)
				{
					if (typeArgs[0] == "m")
					{
						istringstream massstream(typeArgs[1]);
						massstream >> m;
					}
					else if (typeArgs[0] == "e")
					{
						istringstream epsilonstream(typeArgs[1]);
						epsilonstream >> e;
					}
					else if (typeArgs[0] == "o")
					{
						istringstream sigmastream(typeArgs[1]);
						sigmastream >> o;
					}
				}
				else if (typeLine == "end")
					break;
			}

			ParticleProperty prop;
			prop.mass = m;
			prop.e = e;
			prop.o = o;

			ParticleProperty::push(prop);
		}
		else if (args[0] == "particle")
		{
			double x[3] = { 0, 0, 0 };
			double v[3] = { 0, 0, 0 };
			int type = 0;


			string particleLine;
			while (getline(input_file, particleLine))
			{
				if (particleLine[0] == '#')
					continue;

				vector<string> particledArgs = splitString(particleLine, ':');

				if (particledArgs.size() > 1)
				{
					if (particledArgs[0] == "x")
					{
						istringstream positionstream(particledArgs[1]);

						for (int j = 0; j < 3; j++) {
							positionstream >> x[j];
						}
					}
					else if (particledArgs[0] == "v")
					{
						istringstream velocitystream(particledArgs[1]);

						for (int j = 0; j < 3; j++) {
							velocitystream >> v[j];
						}
					}
					else if (particledArgs[0] == "type")
					{
						istringstream typestream(particledArgs[1]);
						typestream >> type;
					}
				}
				else if (particleLine == "end")
					break;
			}

			particles.push_back(Particle(x, v, type));
		}

	}

	LOG4CXX_DEBUG(fileReaderLogger, "end of File");
}


vector<string> splitString(string s, char c)
{
	vector<string> subs;
	string remainder = s;
	string sub = "";
	while (true)
	{
		sub = remainder.substr(0, remainder.find_first_of(c));

		subs.push_back(sub);

		if (remainder.length() <= sub.length())
			break;

		remainder = remainder.substr(sub.length() + 1);
	}

	return subs;
}