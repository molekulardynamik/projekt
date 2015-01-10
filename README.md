PSE Molekulardynamik WS14 - Implementation
=======


How to set up the environment (contents of envMolSim.sh):

copy and paste each line below seperately on the command line:

module load xerces/3.1

export CPLUS_INCLUDE_PATH=/scratch/t1221/di34muv/libraries/apr-util-1.5.4/include/:$CPLUS_INCLUDE_PATH

export CPLUS_INCLUDE_PATH=/scratch/t1221/di34muv/libraries/apr-1.5.1/include/:$CPLUS_INCLUDE_PATH

export CPLUS_INCLUDE_PATH=/scratch/t1221/di34muv/libraries/cppunit-1.13.2/include/:$CPLUS_INCLUDE_PATH

export CPLUS_INCLUDE_PATH=/scratch/t1221/di34muv/libraries/apache-log4cxx-0.10.0/src/main/include/:$CPLUS_INCLUDE_PATH

export CPLUS_INCLUDE_PATH=/lrz/sys/libraries/xerces/3.1/include/:$CPLUS_INCLUDE_PATH

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/scratch/t1221/di34muv/libraries/apr-util-1.5.4/.libs/

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/scratch/t1221/di34muv/libraries/apr-1.5.1/.libs/

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/scratch/t1221/di34muv/libraries/cppunit-1.13.2/src/cppunit/.libs/

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/scratch/t1221/di34muv/libraries/apache-log4cxx-0.10.0/src/main/cpp/.libs/

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/lrz/sys/libraries/xerces/3.1/lib/

export LIBRARY_PATH=$LIBRARY_PATH:$LD_LIBRARY_PATH



How to use:

call "./MolSim \<inputfile\> \<endTime\> \<deltaTime\> \<g_grav\> \<initialTemp\>"

or "./MolSim \<inputfile\> \<endTime\> \<deltaTime\> \<g_grav\> \<initialTemp\> -save" if you want to save the state of your finished simulation

Inputfile:

Used to initialize particles. Can define cuboids, spheres, single particles, particle types, the cutOff radius and the domain size


Format:

-Cuboids:

	"cuboids:
	 x: <x1> <x2> <x3>
	 v: <v1> <v2> <v3>
	 n: <n1> <n2> <n3>
	 h: <h>
	 type: <type>
	 end"
	
-Spheres:

	"sphere:
	 x: <x1> <x2> <x3>
	 v: <v1> <v2> <v3>
	 n: <radius>
	 h: <h>
	 type: <type>
	 end"

-Single particles:

	"particle:
	 x: <x1> <x2> <x3>
	 v: <v1> <v2> <v3>
	 type: <type>
	 end"
	 
-Particle types:

	"type:
	 m: <mass>
	 e: <epsilon>
	 o: <sigma>
	 end"
	 
-CutOff radius:

	"rCutOff: <radius>"
	
-Domain size:

	*domain: <DX> <DY>"
		
			 
			 
