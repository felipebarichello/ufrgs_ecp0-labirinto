#pragma once

// Verdadeiro indica que o simulador será utilizado. Falso significa que o Edubot real será utilizado
#define SIMULATION 1

#define MIN_DISTANCE .1
#define MAX_DISTANCE 1

#if (SIMULATION)
	#define SIMULATION_MOVE_WAIT 10

	#define MAX_SPEED .5
	#define INVERSE_ANGULAR_VELOCITY 20.f
#else
	#define MAX_SPEED .3
	#define INVERSE_ANGULAR_VELOCITY .2
#endif
