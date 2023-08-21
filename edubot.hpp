/*
 * Extens�o da EdubotLib
 * Macros para o Edubot
 */

#pragma once

#include <chrono>
#include "side.hpp"
#include "macros.hpp"


enum class Sonar {
    Left         = 0,
    MidLeft      = 1,
    FrontLeft    = 2,
    Front        = 3,
    FrontRight   = 4,
    MidRight     = 5,
    Right        = 6
};

// �ngulo no formato [-180, 180], em graus
struct Angle {
	double value;


	Angle(double value);

	operator double() const;

	// Somar dois �ngulos
	Angle operator+(Angle other);
	
	// Somar dois �ngulos e atribuir o resultado
	void operator+=(Angle other);

	// Retorna o �ngulo mais pr�ximo a uma das `sections` se��es
	Angle discrete(unsigned int sections, Angle offset);
	
	// Transformar em [0, 360]
	double format_0to360();
};

class Edubot : public EdubotLib {
	public:
		// Uma dist�ncia segura a partir da qual � seguro andar em alta velocidade
		double safe_distance = 1.8f;

		// Tempo m�ximo que o rob� leva para rotacionar
		double rotation_duration = 2000;


		Edubot();

		// Retorna a distancia do sonar em metros
		// Uma abstra��o em cima de getSonar() que recebe um enum ao inves de um size_t
		double get_distance(Sonar sonar);

		// Retorna o �ngulo que o rob� forma 
		// � o oposto de getTheta()
		// Isso porque theta � positivo no sentido anti-hor�rio, enquanto rotate() � positivo no hor�rio
		Angle get_angle();
		
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


		#if (SIM_DRIFT != 0)
			// Em que instante o rob� simulado ir� realizar um drift
			std::chrono::time_point<std::chrono::high_resolution_clock> drift_instant;


			// Reinicia o timer do drift
			void reset_drift_cooldown();

			// Override de EdubotLib::move()
			bool move(double speed);
		#endif
};
