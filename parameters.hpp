#pragma once

#include "side.hpp"

#define LOG_ALL true

// `true` indica que o simulador será utilizado. `false` significa que o Edubot real será utilizado.
#define SIMULATION true


#if (SIMULATION)
	// Força do drift simulado do simulador
	// Valores:
	// 	0: Drift desligado
	//   1 a 180: Força do drift para a direita
	//   -1 a -180: Força do drift para a esquerda
	#define SIM_DRIFT -100

     // O quanto dura o drift do robô simulado, em milissegundos
	#define SIM_DRIFT_TIME 1
	
	// Quanto tempo entre o fim de um drift e o começo do outro, em milissegundos
	#define SIM_DRIFT_COOLDOWN 1
	
	// Máxima velocidade considerada segura
	#define HIGH_SPEED .6
	
	// Velocidade mais segura para detecções mais precisas
	#define MID_SPEED .4
	
	// Velocidade para manobrar
	#define SLOW_SPEED .3

	#define RETREAT_SPEED .3
	#define RETREAT_TIME 1000
	#define INVERSION_WAIT 500
	#define RND_INVERSION_CHANCE 7 // Em %

	#define PRE_ROTATION_WAIT 500
	#define MOVE_WAIT 500
	
	// Tempo máximo que o robô leva para rotacionar
	#define ROTATION_DURATION 1500
	
	#define TURN_ANGLE 55

	#define LEFT_BIAS 200
	#define RIGHT_BIAS 200
	#define HARD_BIAS 500
	
	#define DUMB_COUNTERDRIFT 20
	#define COUNTERDRIFT_COOLDOWN 2
#else
	// Máxima velocidade considerada segura
	#define HIGH_SPEED .4
	
	// Velocidade mais segura para detecções mais precisas
	#define MID_SPEED .3
	
	// Velocidade para manobrar
	#define SLOW_SPEED .2
	
	#define RETREAT_SPEED .3
	#define RETREAT_TIME 700
	#define INVERSION_WAIT 500
	#define RND_INVERSION_CHANCE 7 // Em %

	#define PRE_ROTATION_WAIT 500
	#define MOVE_WAIT 500

	// Tempo máximo que o robô leva para rotacionar
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
//// Qual parede o robô vai seguir
//// -1 é esquerda, 1 é direita
//#define PREFERRED_SIDE -1
//
//// Quantas rotações o robô fará para seguir a parede
//#define ROTATION_STEPS 4
//
//// Quantos graus de imprecisão o ângulo do robô pode estar
//#define ANGLE_HIGH_TOLERANCE 6.0
//#define ANGLE_LOW_TOLERANCE  4.0
//
//#define ADJUSTMENT_TIME 800
//
//// Distância a partir da qual o robô considera "seguro" andar em alta velocidade
//#define SAFE_DISTANCE 100.0
//// Fora destes valores, o robô vai se ajustar para manter a distância
//#define MIN_WALL_DISTANCE 12.0
//#define MAX_WALL_DISTANCE 18.0
//
//// Distância considerada "longe" para decidir se não há parede
//#define FAR_DISTANCE 30.0
//
//#define OVERSHOOT_TIME 1000
//
//// Tipo WALL_DISTANCE, mas no momento da rotação
//#define ROTATION_RADIUS 18.0
//
//// Imprecisão de distância permitida do robô não estar no centro
//#define CENTER_TOLERANCE .08
//
//// Tempo mínimo que o robô vai andar após rotacionar para o lado da parede que está seguindo a cada passo
//#define MIN_ROTSTEP_MOVE 200
//
//#define RIGHT_ANGLE 75
//	
//// Distância que o robô tentará permanecer da parede
//#define WALL_DISTANCE 15.0
//
//#define FALLBACK_DISTANCE .12

// A classe do robô terá um "teta esperado", que é o teta esperado devido às rotações solicitadas pelo programa.
// O robô utilizará este ângulo para counterar o drift
