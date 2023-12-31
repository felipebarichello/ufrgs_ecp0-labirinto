#pragma once


// Verdadeiro indica que o simulador ser� utilizado. Falso significa que o Edubot real ser� utilizado
#define SIMULATION 1

// Quantas rota��es o rob� far� para seguir a parede
#define ROTATION_STEPS 6

// M�xima velocidade considerada segura
#define HIGH_SPEED .3

// Velocidade mais segura para detec��es mais precisas
#define MID_SPEED .2

// Velocidade para manobrar
#define SLOW_SPEED .1

// Dist�ncia que o rob� tentar� permanecer da parede
#define WALL_DISTANCE .05

// Dist�ncia a partir da qual o rob� considera "seguro" andar em alta velocidade
#define SAFE_DISTANCE 1

// Dist�ncia considerada "longe" para decidir se n�o h� parede
#define FAR_DISTANCE .3

// Tempo m�ximo que o rob� leva para rotacionar
#define ROTATION_DURATION 1500

// Tipo WALL_DISTANCE, mas no momento da rota��o
#define ROTATION_RADIUS .08

// Tempo m�nimo que o rob� vai andar ap�s rotacionar para o lado da parede que est� seguindo a cada passo
#define MIN_ROTSTEP_MOVE 400
