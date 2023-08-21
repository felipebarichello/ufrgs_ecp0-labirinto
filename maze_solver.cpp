#include "maze_solver.hpp"


signed char MazeSolver::get_rotations() {
	return this->rotations;
}

void MazeSolver::rotated(Side side) {
	this->rotations += (signed char)side;
}

bool MazeSolver::should_follow() {
	return this->rotations != 0;
}
