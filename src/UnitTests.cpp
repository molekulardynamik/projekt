#include "UnitTests.h"
#include <iostream>
#include <fstream>
#include <stdio.h>

#include "ParticleHandler.h"

using namespace CppUnit;
using namespace std;

Test* ParticleContainerTest::suite()
{
	CppUnit::TestSuite* suiteOfTests = new CppUnit::TestSuite("SimpleTest");
	suiteOfTests->addTest(new CppUnit::TestCaller<ParticleContainerTest>("Test for values", &ParticleContainerTest::testParticleValues));
	suiteOfTests->addTest(new CppUnit::TestCaller<ParticleContainerTest>("Test for function", &ParticleContainerTest::testParticleFunction));
	return suiteOfTests;
}

void ParticleContainerTest::setUp()
{
	testParticles.push_back({ 1, 2, 3, 4, 5, 6, 7 });
	testParticles.push_back({ 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7 });
	testParticles.push_back({-1.0, 2.0, -3.3, 4.4, -5.5, 0, 7.7});

	testFilename = "testData.txt";
	ofstream file(testFilename);

	file << "Planets" << endl;
	file << testParticles.size() << endl;
	for (int i = 0; i < (int)testParticles.size(); i++)
	{
		file<< testParticles[i].x << " "
			<< testParticles[i].y << " "
			<< testParticles[i].z << "    "
			<< testParticles[i].vx << " "
			<< testParticles[i].vy << " "
			<< testParticles[i].vz << "    "
			<< testParticles[i].m << "\n";
	}

	file.close();
}

void ParticleContainerTest::tearDown()
{
	remove(testFilename);
}

void ParticleContainerTest::testParticleValues()
{
	Simulation::ParticleContainer container;
	container.init(testFilename);

	CPPUNIT_ASSERT(container.count() == testParticles.size());
	for (int i = 0; i < container.count(); i++)
	{
		Simulation::Particle& p = container[i];
		TestParticle& tp = testParticles[i];
		utils::Vector<double, 3> pos = p.getX(), vel = p.getV();
		double m = p.getM();

		CPPUNIT_ASSERT(pos[0] == tp.x);
		CPPUNIT_ASSERT(pos[1] == tp.y);
		CPPUNIT_ASSERT(pos[2] == tp.z);
		CPPUNIT_ASSERT(vel[0] == tp.vx);
		CPPUNIT_ASSERT(vel[1] == tp.vy);
		CPPUNIT_ASSERT(vel[2] == tp.vz);
		CPPUNIT_ASSERT(m == tp.m);
	}
}

void ParticleContainerTest::testParticleFunction()
{
	Simulation::ParticleContainer container;
	container.init(testFilename);

	TestHandler th;
	container.iterateParticles(th);

	for (int i = 0; i < container.count(); i++)
	{
		Simulation::Particle& p = container[i];
		TestParticle& tp = testParticles[i];
		utils::Vector<double, 3> pos = p.getX(), vel = p.getV();
		double m = p.getM();

		CPPUNIT_ASSERT(pos[0] == tp.x * 100);
		CPPUNIT_ASSERT(pos[1] == tp.y * 200);
		CPPUNIT_ASSERT(pos[2] == tp.z * 300);
		CPPUNIT_ASSERT(vel[0] == tp.vx* 400);
		CPPUNIT_ASSERT(vel[1] == tp.vy* 500);
		CPPUNIT_ASSERT(vel[2] == tp.vz* 600);
	}
}