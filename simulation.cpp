#include "simulation.hpp"


bool VirtualEdubot::move(double velocity) {
	bool flag = this->EdubotLib::move(velocity);
	this->sleepMilliseconds(move_wait);
	return flag;
}
