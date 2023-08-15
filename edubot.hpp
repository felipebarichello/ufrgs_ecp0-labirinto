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
		// O inverso da distância máxima que será considerada para 
		// Operações de multiplicação são muito mais rápidas que divisões para o computador
		// Logo, como esta variável geralmente é um divisor, armazena-se seu inverso
		float max_distance = 1.8f;

		// Mover, cuidando para não bater na parede
		// Retorna a distância da frente
		double safe_advance(double base_speed);
		
		// Rotacionar, esperando o tempo necessário
		void safe_rotate(double angle);
		
		// Retorna a distancia do sonar em metros
		// Uma abstração em cima de getSonar() que recebe um enum ao inves de um size_t
		double get_distance(Sonar sonar);

		virtual bool move(double velocity);
};
