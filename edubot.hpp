/*
 * Extens�o da EdubotLib
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
		// Uma dist�ncia segura a partir da qual � seguro andar em alta velocidade
		double safe_distance = 1.8f;

		// Tempo m�ximo que o rob� leva para rotacionar
		double rotation_duration = 2000;


		// Retorna a distancia do sonar em metros
		// Uma abstra��o em cima de getSonar() que recebe um enum ao inves de um size_t
		double get_distance(Sonar sonar);

		// Retorna o �ngulo que o rob� forma 
		// � o oposto de getTheta()
		// Isso porque theta � positivo no sentido anti-hor�rio, enquanto rotate() � positivo no hor�rio
		double get_angle();

		// Retorna o �ngulo mais pr�ximo a uma das `sections` se��es, que come�am a ser medidas na (rota��o incial do rob�) + `offset`
		double discrete_angle(unsigned int sections, double offset);
		
		// Mover, cuidando para n�o bater na parede
		// Retorna a dist�ncia da frente
		double safe_advance(double base_speed);
		
		// Rotacionar, esperando o tempo necess�rio
		void safe_rotate(Angle angle);

		// Rotacionar o rob� at� um �ngulo relativo � posi��o inicial do rob�
		void set_angle(Angle angle);

		// Move o rob� lateralmente, com cuidado para n�o bater, at� a dist�ncia lateral do obst�culo desejada
		// Bloqueia o resto do programa at� o fim do ajuste
		void adjust_sideways(Side side, double min_distance, double max_distance);
};
