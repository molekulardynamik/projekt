/*
 * FileReader.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#ifndef FILE_READER_H_
#define FILE_READER_H_

#include "Particle.h"
#include <vector>

class FileReader {

public:
	FileReader();
	virtual ~FileReader();

	void readFile(std::vector<Simulation::Particle>& particles, char* filename);
};

#endif /* FILE_READER_H_ */
