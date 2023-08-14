/*
 * Extensao da EdubotLib
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
		// For�a maxima do motor quando nao h� obst�culos
		// 1 significa for�a m�xima
		float max_speed = .5f;
		
		// 1 / (Velocidade angular estimada), em milissegundos por grau
		// Ou seja, os tempo estimado para o rob� girar 90 graus, em milissegundos, � 90 vezes este valor
		// Opera��es de multiplica��o s�o muito mais r�pidas que divis�es para o computador
		// Logo, como esta vari�vel geralmente � um divisor, armazena-se seu inverso
		float inverse_angular_velocity = 20.f;
		
		// Dist�ncia m�nima dos sonares que ativar� algumas flags
		float min_distance = .1f;
		
		// O inverso da dist�ncia m�xima que ser� considerada para 
		// Opera��es de multiplica��o s�o muito mais r�pidas que divis�es para o computador
		// Logo, como esta vari�vel geralmente � um divisor, armazena-se seu inverso
		float max_distance = 1.8f;
		
		// Avan�ar at� encontrar uma parede (sem bater)
		void safe_charge();

		// Mover, sem bater na parede
		void safe_advance();
		
		// Rotacionar, esperando o tempo necess�rio
		void safe_rotate(float angle);
		
		// Retorna a distancia do sonar em metros
		// Uma abstra��o em cima de getSonar() que recebe um enum ao inves de um size_t
		double get_distance(Sonar sonar);

		virtual bool move(double velocity);
};
