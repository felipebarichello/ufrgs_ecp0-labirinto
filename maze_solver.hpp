#pragma once


class MazeSolver {
	public:
		// Avisa que o robô virou à esquerda ou à direita, respectivamente
		void rotated_left();
		void rotated_right();

		// Retorna se o robô deve seguir a parede (ou seguir reto)
		bool should_follow();

	private:
		signed char rotations = 0;
};