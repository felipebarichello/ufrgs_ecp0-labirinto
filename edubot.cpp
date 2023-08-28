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
	#if (MOVE_COOLDOWN > 0) 
		this->reset_move_cooldown();
	#endif
	
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
		if (this->intended_theta - this->get_angle() > (Angle)ANGLE_LOW_TOLERANCE) {
			this->center_self(CENTER_TOLERANCE, FAR_DISTANCE, FALLBACK_DISTANCE);
		}
	#endif
	
	double front_distance = this->get_distance(Sonar::Front);
	
	double safety_multiplier = front_distance / this->safe_distance;
	safety_multiplier = fmax(fmin(safety_multiplier, 1), 0);
	
	double speed = base_speed * safety_multiplier;
	
	this->move(speed);

	std::cout << "To ouvindo" << std::endl;

	return front_distance;
}

void Edubot::safe_rotate(Angle angle) {
	this->rotate(angle * 0.7);
	std::cout << "Entrei" << std::endl;
	this->sleepMilliseconds(this->rotation_duration);
    	
    	#if (COUNTERDRIFT)
    		this->intended_theta += angle;
    	#endif
}

void Edubot::set_angle(Angle angle) {
	Angle delta_angle = (Angle)angle - (Angle)this->get_angle();
	this->safe_rotate(delta_angle);
}

bool Edubot::move(double speed) {
	#if (SIM_DRIFT != 0)
		auto now = std::chrono::high_resolution_clock::now();
		auto time_until_drift = std::chrono::duration_cast<std::chrono::milliseconds>(this->drift_instant - now);
		constexpr auto zero_duration = std::chrono::milliseconds::zero();
		
		if (time_until_drift < zero_duration) {
			this->rotate(SIM_DRIFT);
			this->sleepMilliseconds(SIM_DRIFT_TIME);
			reset_drift_cooldown();
		}
	#endif

	#if (MOVE_COOLDOWN > 0)
		auto now = std::chrono::high_resolution_clock::now();
		auto time_until_move = std::chrono::duration_cast<std::chrono::milliseconds>(this->move_available - now);
		constexpr auto zero_duration = std::chrono::milliseconds::zero();
		
		if (time_until_move < zero_duration) {
			reset_move_cooldown();
		} else {
			return false;
		}
	#endif
		
	return this->EdubotLib::move(speed);
}

#if (COUNTERDRIFT)
	Angle Edubot::get_intended_theta() {
		return this->intended_theta;
	}

	void Edubot::adjust_angle() {
		Angle intended_theta = this->intended_theta;
		this->set_angle(this->intended_theta);
		this->intended_theta = intended_theta;
	}

	void Edubot::adjust_angle_until(Angle tolerance) {
		while (this->intended_theta - this->get_angle() > tolerance) {
			this->adjust_angle();
		}
	}

	void Edubot::center_self(double tolerance, double too_far, double fallback) {
		this->adjust_angle_until(ANGLE_LOW_TOLERANCE);
	
		while (true) {
			double left_distance  = get_distance(Sonar::Left);
			double right_distance = get_distance(Sonar::Right);

			if (left_distance  >= too_far) left_distance  = fallback;
			if (right_distance >= too_far) right_distance = fallback;

			double diff = right_distance - left_distance;

			// Se estiver dentro da tolerância (no centro o suficiente), já está centralizado
			if (diff <= tolerance) {
				break;
			}

			Angle adjustment_turn = Angle(0);

			// (diff > 0) -> (right_distance > left_distance) -> (robô muito para a esquerda) -> (deve rotacionar no sentido horário)
			if (diff > 0) {
				adjustment_turn = 90.0;
			} else {
				adjustment_turn = -90.0;
			}

			this->safe_rotate(adjustment_turn);
			this->move(SLOW_SPEED);
			this->sleepMilliseconds(ADJUSTMENT_TIME);
			this->safe_rotate(-adjustment_turn);
	
			this->sleepMilliseconds(1);
		}

		this->adjust_angle_until(ANGLE_HIGH_TOLERANCE);
	}
#endif

#if (MOVE_COOLDOWN > 0)
	void Edubot::reset_move_cooldown() {
		auto now = std::chrono::high_resolution_clock::now();
		constexpr auto cooldown = std::chrono::milliseconds(MOVE_COOLDOWN);
		this->move_available = now + cooldown;
	}
#endif

#if (SIM_DRIFT != 0)
	void Edubot::reset_drift_cooldown() {
		auto now = std::chrono::high_resolution_clock::now();
		constexpr auto drift_cooldown = std::chrono::milliseconds(SIM_DRIFT_COOLDOWN);
		this->drift_instant = now + drift_cooldown;
	}
#endif
