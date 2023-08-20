/*
 * Extensão da EdubotLib
 * Macros para o Edubot
 */

#pragma once

#include "side.hpp"


enum class Sonar {
    Left         = 0,
    MidLeft      = 1,
    FrontLeft    = 2,
    Front        = 3,
    FrontRight   = 4,
    MidRight     = 5,
    Right        = 6
};

struct Angle {
	double value;


	Angle(double value);

	operator double() const;
};

class Edubot : public EdubotLib {
	public:
		// Uma distância segura a partir da qual é seguro andar em alta velocidade
		double safe_distance = 1.8f;

		// Tempo máximo que o robô leva para rotacionar
		double rotation_duration = 2000;


		// Retorna a distancia do sonar em metros
		// Uma abstração em cima de getSonar() que recebe um enum ao inves de um size_t
		double get_distance(Sonar sonar);

		// Retorna o ângulo que o robô forma 
		// É o oposto de getTheta()
		// Isso porque theta é positivo no sentido anti-horário, enquanto rotate() é positivo no horário
		double get_angle();

		// Retorna o ângulo mais próximo a uma das `sections` seções, que começam a ser medidas na (rotação incial do robô) + `offset`
		double discrete_angle(unsigned int sections, double offset);
		
		// Mover, cuidando para não bater na parede
		// Retorna a distância da frente
		double safe_advance(double base_speed);
		
		// Rotacionar, esperando o tempo necessário
		void safe_rotate(Angle angle);

		// Rotacionar o robô até um ângulo relativo à posição inicial do robô
		void set_angle(Angle angle);

		// Move o robô lateralmente, com cuidado para não bater, até a distância lateral do obstáculo desejada
		// Bloqueia o resto do programa até o fim do ajuste
		void adjust_sideways(Side side, double min_distance, double max_distance);
};
