/*
 * VTKWriter.h
 *
 *  Created on: 01.03.2010
 *      Author: eckhardw
 */

#ifndef VTKWRITER_H_
#define VTKWRITER_H_

#include "../Simulation/Particle.h"
#include <list>

#include "vtk-unstructured.h"

namespace outputWriter {

/**
 * This class implements the functionality to generate vtk output from particles.
 */
class VTKWriter {

public:
	VTKWriter();

	virtual ~VTKWriter();

	/**
	 * set up internal data structures and prepare to plot a particle.
	 */
	void initializeOutput(int numParticles);

	/**
	 * plot type, mass, position, velocity and force of a particle.
	 *
	 * @note: initializeOutput() must have been called before.
	 */
	void plotParticle(Simulation::Particle& p);

	/**
	 * writes the final output file.
	 *
	 * @param filename the base name of the file to be written.
	 * @param iteration the number of the current iteration,
	 *        which is used to generate an unique filename
	 */
	void writeFile(const std::string& filename, int iteration);

private:
	VTKFile_t* vtkFile;
};

}

#endif /* VTKWRITER_H_ */
