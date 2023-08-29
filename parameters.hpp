#pragma once

#include "side.hpp"

#define LOG_ALL true

// `true` indica que o simulador ser� utilizado. `false` significa que o Edubot real ser� utilizado.
#define SIMULATION true


#if (SIMULATION)
	// For�a do drift simulado do simulador
	// Valores:
	// 	0: Drift desligado
	//   1 a 180: For�a do drift para a direita
	//   -1 a -180: For�a do drift para a esquerda
	#define SIM_DRIFT -100

     // O quanto dura o drift do rob� simulado, em milissegundos
	#define SIM_DRIFT_TIME 1
	
	// Quanto tempo entre o fim de um drift e o come�o do outro, em milissegundos
	#define SIM_DRIFT_COOLDOWN 1
	
	// M�xima velocidade considerada segura
	#define HIGH_SPEED .6
	
	// Velocidade mais segura para detec��es mais precisas
	#define MID_SPEED .4
	
	// Velocidade para manobrar
	#define SLOW_SPEED .3

	#define RETREAT_SPEED .3
	#define RETREAT_TIME 1000
	#define INVERSION_WAIT 500
	#define RND_INVERSION_CHANCE 7 // Em %

	#define PRE_ROTATION_WAIT 500
	#define MOVE_WAIT 500
	
	// Tempo m�ximo que o rob� leva para rotacionar
	#define ROTATION_DURATION 1500
	
	#define TURN_ANGLE 55

	#define LEFT_BIAS 200
	#define RIGHT_BIAS 200
	#define HARD_BIAS 500
	
	#define DUMB_COUNTERDRIFT 20
	#define COUNTERDRIFT_COOLDOWN 2
#else
	// M�xima velocidade considerada segura
	#define HIGH_SPEED .4
	
	// Velocidade mais segura para detec��es mais precisas
	#define MID_SPEED .3
	
	// Velocidade para manobrar
	#define SLOW_SPEED .2
	
	#define RETREAT_SPEED .3
	#define RETREAT_TIME 700
	#define INVERSION_WAIT 500
	#define RND_INVERSION_CHANCE 7 // Em %

	#define PRE_ROTATION_WAIT 500
	#define MOVE_WAIT 500

	// Tempo m�ximo que o rob� leva para rotacionar
	#define ROTATION_DURATION 2000

	#define TURN_ANGLE 50

	#define LEFT_BIAS 200
	#define RIGHT_BIAS 200
	#define HARD_BIAS 600

	#define DUMB_COUNTERDRIFT 0
	#define COUNTERDRIFT_COOLDOWN 0
#endif


// Desligados

//#define COUNTERDRIFT false
//
//// Qual parede o rob� vai seguir
//// -1 � esquerda, 1 � direita
//#define PREFERRED_SIDE -1
//
//// Quantas rota��es o rob� far� para seguir a parede
//#define ROTATION_STEPS 4
//
//// Quantos graus de imprecis�o o �ngulo do rob� pode estar
//#define ANGLE_HIGH_TOLERANCE 6.0
//#define ANGLE_LOW_TOLERANCE  4.0
//
//#define ADJUSTMENT_TIME 800
//
//// Dist�ncia a partir da qual o rob� considera "seguro" andar em alta velocidade
//#define SAFE_DISTANCE 100.0
//// Fora destes valores, o rob� vai se ajustar para manter a dist�ncia
//#define MIN_WALL_DISTANCE 12.0
//#define MAX_WALL_DISTANCE 18.0
//
//// Dist�ncia considerada "longe" para decidir se n�o h� parede
//#define FAR_DISTANCE 30.0
//
//#define OVERSHOOT_TIME 1000
//
//// Tipo WALL_DISTANCE, mas no momento da rota��o
//#define ROTATION_RADIUS 18.0
//
//// Imprecis�o de dist�ncia permitida do rob� n�o estar no centro
//#define CENTER_TOLERANCE .08
//
//// Tempo m�nimo que o rob� vai andar ap�s rotacionar para o lado da parede que est� seguindo a cada passo
//#define MIN_ROTSTEP_MOVE 200
//
//#define RIGHT_ANGLE 75
//	
//// Dist�ncia que o rob� tentar� permanecer da parede
//#define WALL_DISTANCE 15.0
//
//#define FALLBACK_DISTANCE .12

// A classe do rob� ter� um "teta esperado", que � o teta esperado devido �s rota��es solicitadas pelo programa.
// O rob� utilizar� este �ngulo para counterar o drift
