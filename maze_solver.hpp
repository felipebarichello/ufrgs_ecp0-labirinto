#pragma once

#include "side.hpp"


class MazeSolver {
	public:
		// Avisa que o rob� virou � esquerda ou � direita, respectivamente
		void rotated(Side side);

		// Retorna se o rob� deve seguir a parede (ou seguir reto)
		bool should_follow();

	private:
		signed char rotations = 0;
};