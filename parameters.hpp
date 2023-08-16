#pragma once


// Verdadeiro indica que o simulador será utilizado. Falso significa que o Edubot real será utilizado
#define SIMULATION 1

// Quantas rotações o robô fará para seguir a parede
#define ROTATION_STEPS 6


#if (SIMULATION)
	// Máxima velocidade considerada segura
	#define HIGH_SPEED .5
	
	// Velocidade mais segura para detecções mais precisas
	#define MID_SPEED .4
	
	// Velocidade para manobrar
	#define SLOW_SPEED .2
	
	// Distância que o robô tentará permanecer da parede
	#define WALL_DISTANCE .12

	// Distância a partir da qual o robô considera "seguro" andar em alta velocidade
	#define SAFE_DISTANCE 1

	// Distância considerada "longe" para decidir se não há parede
	#define FAR_DISTANCE .3
	
	// Tempo máximo que o robô leva para rotacionar
	#define ROTATION_DURATION 1500
	
	// Tipo WALL_DISTANCE, mas no momento da rotação
	#define ROTATION_RADIUS .18
#else
	// Máxima velocidade considerada segura
	#define HIGH_SPEED .1
	
	// Velocidade mais segura para detecções mais precisas
	#define MID_SPEED .06
	
	// Velocidade para manobrar
	#define SLOW_SPEED .03
	
	// Distância que o robô tentará permanecer da parede
	#define WALL_DISTANCE 15.0

	// Distância a partir da qual o robô considera "seguro" andar em alta velocidade
	#define SAFE_DISTANCE 100

	// Distância considerada "longe" para decidir se não há parede
	#define FAR_DISTANCE 30

	// Tempo máximo que o robô leva para rotacionar
	#define ROTATION_DURATION 2000
	
	// Tipo WALL_DISTANCE, mas no momento da rotação
	#define ROTATION_RADIUS 18.0
#endif
