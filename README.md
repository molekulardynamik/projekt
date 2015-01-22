PSE Molekulardynamik WS14 - Implementation
=======

How to use:

call ./MolSim Blatt5/<config>:
	for task 1 : ./MolSim Blatt5/task1.xml
	for task 2 and 3: ./MolSim Blatt5/task2-3.xml
	for task 4: ./MolSim Blatt5/task4.xml
	for task 5:
		- first call ./MolSim Baltt5/task5.xml
		- this creates a file called "equilibrated_fluid.xml"
		- copy this file twice and name it cooling.xml and superCooling.xml
		- adjust thermostat parameters in these files
		- run ./MolSim Blatt5/task5.1.xml and ./MolSim Blatt5/task5.2.xml
	

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
			 
