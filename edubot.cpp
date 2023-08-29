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
	return !(*this < other);
}

bool Angle::operator<(Angle other) {
	return fabs(this->value) < fabs(other.value);
}

bool Angle::operator<=(Angle other) {
	return !(*this > other);
}

Angle Angle::operator+(Angle other) {
	return Angle(this->value + other.value);
}

Angle Angle::operator+=(Angle other) {
	return *this = *this + other;
}

Angle Angle::operator-(Angle other) {
	return Angle(this->value - other.value);
}

Angle Angle::operator-=(Angle other) {
	return *this = *this - other;
}

Angle Angle::operator-() {
	return Angle(-this->value);
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
	#if (COUNTERDRIFT)
//		this->counter_drift(CENTER_TOLERANCE, FAR_DISTANCE, FALLBACK_DISTANCE);
	#endif

	if (this->getBumper(0)) {
		int side;
		if (rand()%2 == 0) side = -1;
		else side = 1;
		
		this->move(-MID_SPEED);
		this->sleepMilliseconds(2000);
		this->safe_rotate(RIGHT_ANGLE * side);
	} else if (this->getBumper(1)) {
		int side;
		if (rand()%2 == 0) side = -1;
		else side = 1;
		
		this->move(-MID_SPEED);
		this->sleepMilliseconds(2000);
		this->safe_rotate(RIGHT_ANGLE * side);
	}
	
	double front_distance = this->get_distance(Sonar::Front);
	
	double safety_multiplier = (front_distance + SAFETY_OFFSET) / this->safe_distance;
	safety_multiplier = fmax(fmin(safety_multiplier, 1), 0);
	
	double speed = base_speed * safety_multiplier;
	
	this->move(speed);
	this->sleepMilliseconds(MOVE_WAIT);

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

#if (COUNTERDRIFT)
	void Edubot::counter_drift(double tolerance, double too_far, double fallback) {
		double left_distance  = get_distance(Sonar::Left);
		double right_distance = get_distance(Sonar::Right);

		// if (left_distance  >= too_far) left_distance  = fallback;
		// if (right_distance >= too_far) right_distance = fallback;
		
		if (left_distance >= too_far || right_distance >= too_far) {
			return;
		}

		double diff = right_distance - left_distance;
		double abs_diff = fabs(diff);

		Angle adjustment_turn = Angle(0);

		double counter_angle = pow(abs_diff * COUNTER_ANGLE_MULTIPLIER, COUNTER_ANGLE_EXPONENT) + MIN_COUNTER_ANGLE;

		std::cout << abs_diff << std::endl;

		// (diff > 0) -> (right_distance > left_distance) -> (robô muito para a esquerda) -> (deve rotacionar no sentido horário)
		if (diff > 0) {
			adjustment_turn = counter_angle;
		} else {
			adjustment_turn = -counter_angle;
		}

		this->safe_rotate(adjustment_turn);
		this->move(SLOW_SPEED);
		this->sleepMilliseconds(ADJUSTMENT_TIME);
	}
#endif

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
