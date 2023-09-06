/*
 * Extensão da EdubotLib
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

// Ângulo no formato [-180, 180], em graus
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

	// Retorna o Ângulo mais próximo a uma das `sections` seções
	Angle discrete(unsigned int sections, Angle offset);
	
	// Transformar em [0, 360]
	double format_0to360();
};

class Edubot : public EdubotLib {
	public:
		// Uma distância segura a partir da qual é seguro andar em alta velocidade
		double safe_distance = 1.8f;

		// Tempo máximo que o robô leva para rotacionar
		double rotation_duration = 2000;


		Edubot();

		// Retorna a distancia do sonar em metros
		// Uma abstração em cima de getSonar() que recebe um enum ao inves de um size_t
		double get_distance(Sonar sonar);

		// Retorna o ângulo que o robô forma 
		// É o oposto de getTheta()
		// Isso porque theta é positivo no sentido anti-horário, enquanto rotate() é positivo no horário
		Angle get_angle();
		
		// Mover, cuidando para não bater na parede
		// Retorna a distância da frente
		double safe_advance(double base_speed);
		
		// Rotacionar, esperando o tempo necessï¿½rio
		void safe_rotate(Angle angle);

		// Rotacionar o robô até um ângulo relativo à posição inicial do robô
		void set_angle(Angle angle);


	#if (COUNTERDRIFT)
		public:
			Angle get_intended_theta();

			// Ajusta o ângulo uma vez para intended_theta
			void adjust_angle();

			// Ajusta o ângulo para intended_theta até entrar na tolerância
			void adjust_angle_until(Angle tolerance);
		
			// Move o robô lateralmente, a fim de colocá-lo no meio da pista até a distância lateral do obstáculo desejada
			// Bloqueia o resto do programa até o fim do ajuste
			void center_self(double tolerance, double too_far, double fallback);

		private:
			// "Teta esperado" proveniente das rotações solicitadas do programa
			// O robô utilizará este ângulo para counterar o drift
			Angle intended_theta = Angle(0);
	#endif

	#if (SIM_DRIFT != 0)
		public:
			// Reinicia o timer do drift
			void reset_drift_cooldown();

			// Override de EdubotLib::move()
			bool move(double speed);
			
		private:
			// Em que instante o robô simulado irá realizar um drift
			std::chrono::time_point<std::chrono::high_resolution_clock> drift_instant;
			
	#endif
};
