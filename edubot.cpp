#pragma once

#include <cmath>


void Edubot::safe_charge() {
    	while (this->get_distance(Sonar::Front) > this->min_distance) {
        	this->safe_advance();
    	}
}

void Edubot::safe_advance() {
	float safety_multiplier = this->get_distance(Sonar::Front) / this->max_distance;
	safety_multiplier = fmax(fmin(safety_multiplier, 1), 0);
	
	float speed = this->max_speed * safety_multiplier;
	
	this->move(speed);
}

void Edubot::safe_rotate(float angle) {
    	this->rotate(angle);
    	this->sleepMilliseconds(angle * this->inverse_angular_velocity);
    	this->stop();
}

double Edubot::get_distance(Sonar sonar) {
    	return getSonar((size_t)sonar);
}

bool Edubot::move(double velocity) {
	return this->EdubotLib::move(velocity);
}
