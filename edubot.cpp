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

bool Angle::operator==(Angle other) {
	return this->value == other.value;
}

bool Angle::operator!=(Angle other) {
	return this->value != other.value;
}

bool Angle::operator>(Angle other) {
	return fabs(this->value) > fabs(other.value);
}

bool Angle::operator>=(Angle other) {
	return *this > other || *this == other;
}

bool Angle::operator<(Angle other) {
	return fabs(this->value) < fabs(other.value);
}

bool Angle::operator<=(Angle other) {
	return *this < other || *this == other;
}

Angle Angle::operator+(Angle other) {
	return Angle(this->value + other.value);
}

Angle Angle::operator+=(Angle other) {
	return *this = *this + other;
}

Angle Angle::discrete(unsigned int sections, Angle offset) {
	Angle offset_angle = (*this + offset).format_0to360();
	double section_angle = 360.0 / sections;
	unsigned int the_section_it_is_on = offset_angle / section_angle;
	double offset_discrete_angle = the_section_it_is_on * section_angle;
	return offset_discrete_angle - offset_angle;
}

double Angle::format_0to360() {
	double value = this->value;
	
	if (value < 0) {
		value = 360.0 + (double)value;
	}

	return value;
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
	Angle delta_angle = (Angle)angle - (Angle)this->get_angle();
	this->safe_rotate(delta_angle);
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
			this->set_angle(this->get_angle().discrete(4, -45));
		} else if (side_distance > max_distance) {
			this->set_angle(this->get_angle().discrete(4, -45));
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
