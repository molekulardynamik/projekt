/*
 * FileReader.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#ifndef FILE_READER_H_
#define FILE_READER_H_

#include "Particle.h"
#include <list>

class FileReader {

public:
	FileReader();
	virtual ~FileReader();

	void readFile(std::list<Simulation::Particle>& particles, char* filename, double* domainX, double* domainY, double* rCutOff );
};

#endif /* FILE_READER_H_ */
