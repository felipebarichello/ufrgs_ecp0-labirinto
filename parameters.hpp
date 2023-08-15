#pragma once


// Verdadeiro indica que o simulador será utilizado. Falso significa que o Edubot real será utilizado
#define SIMULATION 1

// Distância a partir da qual o robô considera "seguro" andar em alta velocidade
#define SAFE_DISTANCE 1

// Distância que o robô tentará permanecer da parede
#define WALL_DISTANCE .12

// Distância considerada "longe" para decidir se não há parede
#define FAR_DISTANCE .3

// Máxima velocidade considerada segura
#define HIGH_SPEED .5

// Velocidade mais segura para detecções mais precisas
#define MID_SPEED .4

// Velocidade para manobrar
#define SLOW_SPEED .2

// Quantas rotações o robô fará para seguir a parede
#define ROTATION_STEPS 6

#if (SIMULATION)
	// Quando utilizando o simulador, tempo de sleep após mover, em milissegundos, para evitar bugs
	#define SIMULATION_MOVE_WAIT 10
	
	// Tempo máximo que o robô leva para rotacionar
	#define ROTATION_DURATION 1500
#else
	// Tempo máximo que o robô leva para rotacionar
	#define ROTATION_DURATION 2000
#endif
