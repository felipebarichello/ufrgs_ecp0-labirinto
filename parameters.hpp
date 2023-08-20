#pragma once


#include "side.hpp"

// `true` indica que o simulador ser� utilizado. `false` significa que o Edubot real ser� utilizado.
#define SIMULATION true

// Qual parede o rob� vai seguir
// -1 � esquerda, 1 � direita
#define PREFERRED_SIDE -1

// Quantas rota��es o rob� far� para seguir a parede
#define ROTATION_STEPS 4


#if (SIMULATION)
	// For�a do drift simulado do simulador
	// Valores:
	// 	0: Drift desligado
	//   1 a 180: For�a do drift para a direita
	//   -1 a -180: For�a do drift para a esquerda
	#define SIM_DRIFT 0

     // O quanto dura o drift do rob� simulado, em milissegundos
	#define SIM_DRIFT_TIME 1
	
	// Quanto tempo entre o fim de um drift e o come�o do outro, em milissegundos
	#define SIM_DRIFT_COOLDOWN 1
	
	// M�xima velocidade considerada segura
	#define HIGH_SPEED .5
	
	// Velocidade mais segura para detec��es mais precisas
	#define MID_SPEED .4
	
	// Velocidade para manobrar
	#define SLOW_SPEED .1
	
	// Dist�ncia que o rob� tentar� permanecer da parede
	#define WALL_DISTANCE .12

	// Fora destes valores, o rob� vai se ajustar para manter a dist�ncia
	#define MIN_WALL_DISTANCE .10
	#define MAX_WALL_DISTANCE .14

	// Dist�ncia a partir da qual o rob� considera "seguro" andar em alta velocidade
	#define SAFE_DISTANCE 1.0

	// Dist�ncia considerada "longe" para decidir se n�o h� parede
	#define FAR_DISTANCE .3
	
	// Tempo m�ximo que o rob� leva para rotacionar
	#define ROTATION_DURATION 1500
	
	// Tipo WALL_DISTANCE, mas no momento da rota��o
	#define ROTATION_RADIUS .18

	// Tempo m�nimo que o rob� vai andar ap�s rotacionar para o lado da parede que est� seguindo a cada passo
	#define MIN_ROTSTEP_MOVE 500
#else
	// M�xima velocidade considerada segura
	#define HIGH_SPEED .1
	
	// Velocidade mais segura para detec��es mais precisas
	#define MID_SPEED .06
	
	// Velocidade para manobrar
	#define SLOW_SPEED .03
	
	// Dist�ncia que o rob� tentar� permanecer da parede
	#define WALL_DISTANCE 15.0

	// Fora destes valores, o rob� vai se ajustar para manter a dist�ncia
	#define MIN_WALL_DISTANCE 12.0
	#define MAX_WALL_DISTANCE 18.0

	// Dist�ncia a partir da qual o rob� considera "seguro" andar em alta velocidade
	#define SAFE_DISTANCE 100.0

	// Dist�ncia considerada "longe" para decidir se n�o h� parede
	#define FAR_DISTANCE 30.0

	// Tempo m�ximo que o rob� leva para rotacionar
	#define ROTATION_DURATION 2000
	
	// Tipo WALL_DISTANCE, mas no momento da rota��o
	#define ROTATION_RADIUS 18.0

	// Tempo m�nimo que o rob� vai andar ap�s rotacionar para o lado da parede que est� seguindo a cada passo
	#define MIN_ROTSTEP_MOVE 200
#endif
