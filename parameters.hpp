#pragma once


// Verdadeiro indica que o simulador será utilizado. Falso significa que o Edubot real será utilizado
#define SIMULATION 1

#define MAX_DISTANCE 1
#define FRONT_STOP_DISTANCE .1
#define SIDE_TURN_DISTANCE .3
#define SIDE_MANEUVER_DISTANCE .15
#define FOLLOW_OVERSHOOT 500
#define OVERSHOOT_SPEED .3
#define HIGH_SPEED .5
#define MID_SPEED .4
#define MANEUVER_SPEED .2

#if (SIMULATION)
	#define SIMULATION_MOVE_WAIT 10
#endif
