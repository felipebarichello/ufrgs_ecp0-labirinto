#include "simulation.hpp"


bool VirtualEdubot::move(double speed) {
	bool flag = this->EdubotLib::move(speed);
	this->sleepMilliseconds(move_wait);
	return flag;
}
