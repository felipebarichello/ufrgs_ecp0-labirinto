#pragma once


// Verdadeiro indica que o simulador ser� utilizado. Falso significa que o Edubot real ser� utilizado
#define SIMULATION 1

// Quantas rota��es o rob� far� para seguir a parede
#define ROTATION_STEPS 6


#if (SIMULATION)
	// M�xima velocidade considerada segura
	#define HIGH_SPEED .5
	
	// Velocidade mais segura para detec��es mais precisas
	#define MID_SPEED .4
	
	// Velocidade para manobrar
	#define SLOW_SPEED .2
	
	// Dist�ncia que o rob� tentar� permanecer da parede
	#define WALL_DISTANCE .12

	// Dist�ncia a partir da qual o rob� considera "seguro" andar em alta velocidade
	#define SAFE_DISTANCE 1

	// Dist�ncia considerada "longe" para decidir se n�o h� parede
	#define FAR_DISTANCE .3
	
	// Tempo m�ximo que o rob� leva para rotacionar
	#define ROTATION_DURATION 1500
	
	// Tipo WALL_DISTANCE, mas no momento da rota��o
	#define ROTATION_RADIUS .18
#else
	// M�xima velocidade considerada segura
	#define HIGH_SPEED .1
	
	// Velocidade mais segura para detec��es mais precisas
	#define MID_SPEED .06
	
	// Velocidade para manobrar
	#define SLOW_SPEED .03
	
	// Dist�ncia que o rob� tentar� permanecer da parede
	#define WALL_DISTANCE 15.0

	// Dist�ncia a partir da qual o rob� considera "seguro" andar em alta velocidade
	#define SAFE_DISTANCE 100

	// Dist�ncia considerada "longe" para decidir se n�o h� parede
	#define FAR_DISTANCE 30

	// Tempo m�ximo que o rob� leva para rotacionar
	#define ROTATION_DURATION 2000
	
	// Tipo WALL_DISTANCE, mas no momento da rota��o
	#define ROTATION_RADIUS 18.0
#endif
