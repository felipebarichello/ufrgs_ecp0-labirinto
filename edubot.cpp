#pragma once

#include "edubot.hpp"
#include <cmath>
#include "macros.hpp"


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

Edubot::Edubot() {
	#if (SIM_DRIFT != 0)
		this->reset_drift_cooldown();
	#endif
}

double Edubot::get_distance(Sonar sonar) {
    	return getSonar((size_t)sonar);
}

Angle Edubot::get_angle() {
	return -this->getTheta();
}

Angle Edubot::discrete_angle(unsigned int sections, Angle offset) {
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

#if (SIM_DRIFT != 0)
	void Edubot::reset_drift_cooldown() {
		auto now = std::chrono::high_resolution_clock::now();
		constexpr auto drift_cooldown = std::chrono::milliseconds(SIM_DRIFT_COOLDOWN);
		this->drift_instant = now + drift_cooldown;
	}

	bool Edubot::move(double speed) {
		auto now = std::chrono::high_resolution_clock::now();
		auto time_until_drift = std::chrono::duration_cast<std::chrono::milliseconds>(this->drift_instant - now);
		constexpr auto zero_duration = std::chrono::milliseconds::zero();
		
		if (time_until_drift < zero_duration) {
			this->rotate(SIM_DRIFT);
			this->sleepMilliseconds(SIM_DRIFT_TIME);
			reset_drift_cooldown();
		}
		
		return this->EdubotLib::move(speed);
	}
#endif
