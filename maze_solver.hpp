#pragma once

#include "side.hpp"


class MazeSolver {
	public:
		signed char get_rotations();
	
		// Avisa que o robô virou à esquerda ou à direita, respectivamente
		void rotated(Side side);

		// Retorna se o robô deve seguir a parede (ou seguir reto)
		bool should_follow();


	private:
		// Contador de rotações do Pledge
		signed char rotations = 0;
};