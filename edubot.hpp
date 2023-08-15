/*
 * Extensao da EdubotLib
 * Macros para o Edubot
 */

#pragma once


enum class Sonar {
    Left         = 0,
    MidLeft      = 1,
    FrontLeft    = 2,
    Front        = 3,
    FrontRight   = 4,
    MidRight     = 5,
    Right        = 6
};

class Edubot : public EdubotLib {
	public:
		// O inverso da dist�ncia m�xima que ser� considerada para 
		// Opera��es de multiplica��o s�o muito mais r�pidas que divis�es para o computador
		// Logo, como esta vari�vel geralmente � um divisor, armazena-se seu inverso
		float max_distance = 1.8f;

		// Mover, cuidando para n�o bater na parede
		// Retorna a dist�ncia da frente
		double safe_advance(double base_speed);
		
		// Rotacionar, esperando o tempo necess�rio
		void safe_rotate(double angle);
		
		// Retorna a distancia do sonar em metros
		// Uma abstra��o em cima de getSonar() que recebe um enum ao inves de um size_t
		double get_distance(Sonar sonar);

		virtual bool move(double velocity);
};
