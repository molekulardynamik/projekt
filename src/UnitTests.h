#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include "cppunit/TestCaller.h"
#include "cppunit/TestResult.h"

#include <vector>
#include "Simulation/Container/ParticleContainer.h"

class ParticleContainerTest : public CppUnit::TestCase
{
public:
	void setUp();
	void tearDown();

	void testParticleValues();
	void testParticleFunction();

	static CppUnit::Test *suite();

private:
	char* testFilename;
	struct TestParticle
	{
		double x, y, z;
		double vx, vy, vz;
		double m;
	};
	std::vector<TestParticle> testParticles;
	class TestHandler : public Simulation::ParticleHandler
	{
	public:

		void compute(Simulation::Particle& p)
		{
			p.getX()[0] *= 100;
			p.getX()[1] *= 200;
			p.getX()[2] *= 300;
			p.getV()[0] *= 400;
			p.getV()[1] *= 500;
			p.getV()[2] *= 600;
		};
	};
};
