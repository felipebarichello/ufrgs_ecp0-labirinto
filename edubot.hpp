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

	bool operator==(Angle other);
	bool operator!=(Angle other);
	bool operator>(Angle other);
	bool operator>=(Angle other);
	bool operator<(Angle other);
	bool operator<=(Angle other);

	Angle operator+(Angle other);
	Angle operator+=(Angle other);
	Angle operator-(Angle other);
	Angle operator-=(Angle other);
	Angle operator-();

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


	#if (COUNTERDRIFT)
		public:
			Angle get_intended_theta();

			// Ajusta o �ngulo uma v�z para intended_theta
			void adjust_angle();

			// Ajusta o �ngulo para intended_theta at� entrar na toler�ncia
			void adjust_angle_until(Angle tolerance);
		
			// Move o rob� lateralmente, a fim de coloc�-lo no meio da pista at� a dist�ncia lateral do obst�culo desejada
			// Bloqueia o resto do programa at� o fim do ajuste
			void center_self(double tolerance, double too_far, double fallback);

			// Override de EdubotLib::move()
			bool move(double speed);

		private:
			// "Teta esperado" proveniente das rota��es solicitadas do programa
			// O rob� utilizar� este �ngulo para counterar o drift
			Angle intended_theta = Angle(0);
	#endif

	#if (MOVE_COOLDOWN > 0)
		private:
			std::chrono::time_point<std::chrono::high_resolution_clock> move_available;

			void reset_move_cooldown();
	#endif

	#if (SIM_DRIFT != 0)
		public:
			// Reinicia o timer do drift
			void reset_drift_cooldown();
			
		private:
			// Em que instante o rob� simulado ir� realizar um drift
			std::chrono::time_point<std::chrono::high_resolution_clock> drift_instant;
	#endif
};
