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
		// Força maxima do motor quando nao há obstáculos
		// 1 significa força máxima
		float max_speed = .5f;
		
		// 1 / (Velocidade angular estimada), em milissegundos por grau
		// Ou seja, os tempo estimado para o robô girar 90 graus, em milissegundos, é 90 vezes este valor
		// Operações de multiplicação são muito mais rápidas que divisões para o computador
		// Logo, como esta variável geralmente é um divisor, armazena-se seu inverso
		float inverse_angular_velocity = 20.f;
		
		// Distância mínima dos sonares que ativará algumas flags
		float min_distance = .1f;
		
		// O inverso da distância máxima que será considerada para 
		// Operações de multiplicação são muito mais rápidas que divisões para o computador
		// Logo, como esta variável geralmente é um divisor, armazena-se seu inverso
		float max_distance = 1.8f;
		
		// Avançar até encontrar uma parede (sem bater)
		void safe_charge();

		// Mover, sem bater na parede
		void safe_advance();
		
		// Rotacionar, esperando o tempo necessário
		void safe_rotate(float angle);
		
		// Retorna a distancia do sonar em metros
		// Uma abstração em cima de getSonar() que recebe um enum ao inves de um size_t
		double get_distance(Sonar sonar);

		virtual bool move(double velocity);
};
