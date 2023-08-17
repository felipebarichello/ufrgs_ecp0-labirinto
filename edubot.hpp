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
		// Uma dist�ncia segura a partir da qual � seguro andar em alta velocidade
		double safe_distance = 1.8f;

		// Tempo m�ximo que o rob� leva para rotacionar
		double rotation_duration = 2000;


		// Mover, cuidando para n�o bater na parede
		// Retorna a dist�ncia da frente
		double safe_advance(double base_speed);
		
		// Rotacionar, esperando o tempo necess�rio
		void safe_rotate(double angle);
		
		// Retorna a distancia do sonar em metros
		// Uma abstra��o em cima de getSonar() que recebe um enum ao inves de um size_t
		double get_distance(Sonar sonar);
};
