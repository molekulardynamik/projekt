PSE Molekulardynamik WS14 - Implementation
=======

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
		
			 
			 
