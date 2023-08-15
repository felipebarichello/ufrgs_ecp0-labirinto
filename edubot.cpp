#pragma once

#include <cmath>


double Edubot::safe_advance(double base_speed) {
	double front_distance = this->get_distance(Sonar::Front);
	
	double safety_multiplier = front_distance / this->max_distance;
	safety_multiplier = fmax(fmin(safety_multiplier, 1), 0);
	
	double speed = base_speed * safety_multiplier;
	
	this->move(speed);

	return front_distance;
}

void Edubot::safe_rotate(double angle) {
    	this->rotate(angle);
    	this->sleepMilliseconds(2000);
}

double Edubot::get_distance(Sonar sonar) {
    	return getSonar((size_t)sonar);
}

bool Edubot::move(double velocity) {
	return this->EdubotLib::move(velocity);
}
