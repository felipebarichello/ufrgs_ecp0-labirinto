#pragma once

#include <cmath>


Angle::Angle(double value) {
	while (value > 180.0) {
		value -= 360.0;
	}

	while (value < -180.0) {
		value += 360.0;
	}
	
	this->value = value;
}

Angle::operator double() const {
	return this->value;
}

double Edubot::get_distance(Sonar sonar) {
    	return getSonar((size_t)sonar);
}

double Edubot::get_angle() {
	return -this->getTheta();
}

double Edubot::discrete_angle(unsigned int sections, double offset) {
	return (this->get_angle() + offset) / sections * sections;
}

double Edubot::safe_advance(double base_speed) {
	double front_distance = this->get_distance(Sonar::Front);
	
	double safety_multiplier = front_distance / this->safe_distance;
	safety_multiplier = fmax(fmin(safety_multiplier, 1), 0);
	
	double speed = base_speed * safety_multiplier;
	
	this->move(speed);

	return front_distance;
}

void Edubot::safe_rotate(Angle angle) {
    	this->rotate(angle);
    	this->sleepMilliseconds(this->rotation_duration);
}

void Edubot::set_angle(Angle angle) {
	Angle dangle = (Angle)angle - (Angle)this->get_angle();
	this->safe_rotate(dangle);
}

void Edubot::adjust_sideways(Side side, double min_distance, double max_distance) {
	Sonar side_sonar;
	
	switch (side) {
		case Side::Left:
			side_sonar = Sonar::Left;
			break;
			
		case Side::Right:
			side_sonar = Sonar::Right;
			break;
	}

	while (true) {
		double side_distance = get_distance(side_sonar);

		if (side_distance < min_distance) {
			this->set_angle(this->discrete_angle(4, -45));
		} else if (side_distance > max_distance) {
			this->set_angle(this->discrete_angle(4, -45));
		} else {
			break;
		}

		this->sleepMilliseconds(1);
	}
}
