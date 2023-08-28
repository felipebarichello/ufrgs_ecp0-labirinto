/*
 * Extensï¿½o da EdubotLib
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

// ï¿½ngulo no formato [-180, 180], em graus
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

	// Retorna o ï¿½ngulo mais prï¿½ximo a uma das `sections` seï¿½ï¿½es
	Angle discrete(unsigned int sections, Angle offset);
	
	// Transformar em [0, 360]
	double format_0to360();
};

class Edubot : public EdubotLib {
	public:
		// Uma distï¿½ncia segura a partir da qual ï¿½ seguro andar em alta velocidade
		double safe_distance = 1.8f;

		// Tempo mï¿½ximo que o robï¿½ leva para rotacionar
		double rotation_duration = 2000;


		Edubot();

		// Retorna a distancia do sonar em metros
		// Uma abstraï¿½ï¿½o em cima de getSonar() que recebe um enum ao inves de um size_t
		double get_distance(Sonar sonar);

		// Retorna o ï¿½ngulo que o robï¿½ forma 
		// ï¿½ o oposto de getTheta()
		// Isso porque theta ï¿½ positivo no sentido anti-horï¿½rio, enquanto rotate() ï¿½ positivo no horï¿½rio
		Angle get_angle();
		
		// Mover, cuidando para nï¿½o bater na parede
		// Retorna a distï¿½ncia da frente
		double safe_advance(double base_speed);
		
		// Rotacionar, esperando o tempo necessï¿½rio
		void safe_rotate(Angle angle);

		// Rotacionar o robï¿½ atï¿½ um ï¿½ngulo relativo ï¿½ posiï¿½ï¿½o inicial do robï¿½
		void set_angle(Angle angle);


	#if (COUNTERDRIFT)
		public:
			Angle get_intended_theta();

			// Ajusta o ângulo uma vêz para intended_theta
			void adjust_angle();

			// Ajusta o ângulo para intended_theta até entrar na tolerância
			void adjust_angle_until(Angle tolerance);
		
			// Move o robï¿½ lateralmente, a fim de colocï¿½-lo no meio da pista atï¿½ a distï¿½ncia lateral do obstï¿½culo desejada
			// Bloqueia o resto do programa atï¿½ o fim do ajuste
			void center_self(double tolerance, double too_far, double fallback);

			// Override de EdubotLib::move()
			bool move(double speed);

		private:
			// "Teta esperado" proveniente das rotaï¿½ï¿½es solicitadas do programa
			// O robï¿½ utilizarï¿½ este ï¿½ngulo para counterar o drift
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
			// Em que instante o robï¿½ simulado irï¿½ realizar um drift
			std::chrono::time_point<std::chrono::high_resolution_clock> drift_instant;
	#endif
};
