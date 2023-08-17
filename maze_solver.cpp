#include "maze_solver.hpp"


void MazeSolver::rotated(Side side) {
	this->rotations += (signed char)side;
}

bool MazeSolver::should_follow() {
	return this->rotations != 0;
}
