#pragma once

#include "side.hpp"


// `true` indica que o simulador será utilizado. `false` significa que o Edubot real será utilizado.
#define SIMULATION true

// A classe do robô terá um "teta esperado", que é o teta esperado devido às rotações solicitadas pelo programa.
// O robô utilizará este ângulo para counterar o drift
#define COUNTERDRIFT false

// Qual parede o robô vai seguir
// -1 é esquerda, 1 é direita
#define PREFERRED_SIDE -1

// Quantas rotações o robô fará para seguir a parede
#define ROTATION_STEPS 4

// Quantos graus de imprecisão o ângulo do robô pode estar
#define ANGLE_HIGH_TOLERANCE 6.0
#define ANGLE_LOW_TOLERANCE  4.0

#define ADJUSTMENT_TIME 800


#if (SIMULATION)
	// Força do drift simulado do simulador
	// Valores:
	// 	0: Drift desligado
	//   1 a 180: Força do drift para a direita
	//   -1 a -180: Força do drift para a esquerda
	#define SIM_DRIFT -50

     // O quanto dura o drift do robô simulado, em milissegundos
	#define SIM_DRIFT_TIME 1
	
	// Quanto tempo entre o fim de um drift e o começo do outro, em milissegundos
	#define SIM_DRIFT_COOLDOWN 1
	
	// Máxima velocidade considerada segura
	#define HIGH_SPEED .1
	
	// Velocidade mais segura para detecções mais precisas
	#define MID_SPEED .06
	
	// Velocidade para manobrar
	#define SLOW_SPEED .03
	
	// Distância que o robô tentará permanecer da parede
	#define WALL_DISTANCE .12

	// Fora destes valores, o robô vai se ajustar para manter a distância
	#define MIN_WALL_DISTANCE .10
	#define MAX_WALL_DISTANCE .14

	// Distância a partir da qual o robô considera "seguro" andar em alta velocidade
	#define SAFE_DISTANCE 1.0

	// Distância considerada "longe" para decidir se não há parede na direção
	#define FAR_DISTANCE .3
	
	// Tempo máximo que o robô leva para rotacionar
	#define ROTATION_DURATION 1500
	
	// Tipo WALL_DISTANCE, mas no momento da rotação
	#define ROTATION_RADIUS .18

	// Tempo mínimo que o robô vai andar após rotacionar para o lado da parede que está seguindo a cada passo
	#define MIN_ROTSTEP_MOVE 500

	// Imprecisão de distância permitida do robô não estar no centro
	#define CENTER_TOLERANCE .08

	#define FALLBACK_DISTANCE .12

	#define RIGHT_ANGLE 90
	
	#define OVERSHOOT_TIME 1000
#else
	// Máxima velocidade considerada segura
	#define HIGH_SPEED .1
	
	// Velocidade mais segura para detecções mais precisas
	#define MID_SPEED .06
	
	// Velocidade para manobrar
	#define SLOW_SPEED .03
	
	// Distância que o robô tentará permanecer da parede
	#define WALL_DISTANCE 15.0

	// Fora destes valores, o robô vai se ajustar para manter a distância
	#define MIN_WALL_DISTANCE 12.0
	#define MAX_WALL_DISTANCE 18.0

	// Distância a partir da qual o robô considera "seguro" andar em alta velocidade
	#define SAFE_DISTANCE 100.0

	// Distância considerada "longe" para decidir se não há parede
	#define FAR_DISTANCE 30.0

	// Tempo máximo que o robô leva para rotacionar
	#define ROTATION_DURATION 2000
	
	// Tipo WALL_DISTANCE, mas no momento da rotação
	#define ROTATION_RADIUS 18.0

	// Tempo mínimo que o robô vai andar após rotacionar para o lado da parede que está seguindo a cada passo
	#define MIN_ROTSTEP_MOVE 200

	// Imprecisão de distância permitida do robô não estar no centro
	#define CENTER_TOLERANCE 8.0

	#define FALLBACK_DISTANCE 15.0
	
	#define RIGHT_ANGLE 75

	#define OVERSHOOT_TIME 1000
#endif
