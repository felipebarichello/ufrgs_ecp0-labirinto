#include "maze_solver.hpp"


void MazeSolver::rotated_left() {
	this->rotations--;
}

void MazeSolver::rotated_right() {
	this->rotations++;
}

bool MazeSolver::should_follow() {
	return this->rotations != 0;
}
