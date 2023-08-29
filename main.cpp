#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "libs/EdubotLib.hpp"
#include "edubot.hpp"
#include "maze_solver.hpp"
#include "side.hpp"
#include "macros.hpp"

#include "includes.hpp"


void snooze();
bool adjust(Edubot*, Sonar, double, bool);


int main() {
	srand(time(NULL));
	
	Edubot edubot = Edubot();

	// Estabelecer conexão
	if (!edubot.connect()) {
		std::cout << "Nao foi possivel conectar-se ao Edubot" << std::endl;
	} else {
		double front_distance;
		
		edubot.safe_distance = SAFE_DISTANCE;
		edubot.rotation_duration = ROTATION_DURATION;
		
		// Esperar até o valor do sonar frontal ser atualizado
		// Enquanto o robô não enviar um sinal de atualização do sonar frontal, o valor é zero
		do {
			snooze();
			front_distance = edubot.get_distance(Sonar::Front);
		} while (front_distance == 0);

		MazeSolver maze = MazeSolver();

		// ATENÇÃO:
		// Dentro de qualquer loop que repete por muito tempo, TODOS os seus caminhos devem "sleepar" a thread em algum momento
		while (edubot.isConnected()) {
			front_distance = edubot.get_distance(Sonar::Front);
				
			// Seguir a parede da esquerda (arbitrário; poderia ser direita) até não haver mais parede à esquerda
			while (maze.should_follow()) {
				double side_distance = edubot.get_distance(PREFERRED_SIDE_SONAR);
				
				// Virar ao lado preferido se houver caminho
				if (side_distance >= FAR_DISTANCE) {
					// Virar
					edubot.move(SLOW_SPEED);
					edubot.sleepMilliseconds(OVERSHOOT_TIME);
					edubot.safe_rotate(p_angle(RIGHT_ANGLE));
					maze.rotated((Side)PREFERRED_SIDE);

					// Seguir até econtrar a parede novamente (apenas se o robô estiver seguindo uma parede)
					if (maze.should_follow()) {
						double left_distance = edubot.get_distance(PREFERRED_SIDE_SONAR);
						
						edubot.move(SLOW_SPEED);
						
						while (left_distance > FAR_DISTANCE) {
							snooze();
							left_distance = edubot.get_distance(PREFERRED_SIDE_SONAR);
						}
					}
				} else {
					if (front_distance > WALL_DISTANCE) {
						/* Ajustar posição lateral para se manter perto (mas não demais) da parede */
						
						bool adjusted = adjust(&edubot, PREFERRED_SIDE_SONAR, 1.0, true);
						if (!adjusted) adjusted = adjust(&edubot, PREFERRED_MID_SONAR, 1.4, false);
						if (!adjusted) adjusted = adjust(&edubot, PREFERRED_FRONT_SONAR, 1.4, false);

				        	front_distance = edubot.safe_advance(MID_SPEED);
					} else {
						// Virar ao lado contrário do preferido se houver obstrução
						edubot.safe_rotate(o_angle(RIGHT_ANGLE));
						maze.rotated((Side)OTHER_SIDE);
					}
					
					snooze();
				}
			}

			// Quando o MazeSolver disser que não é para seguir a parede
			
			front_distance = edubot.get_distance(Sonar::Front);
			
			// Seguir reto até encontrar um obstáculo
			while (front_distance > WALL_DISTANCE) {
				bool adjusted = adjust(&edubot, PREFERRED_SIDE_SONAR, 1.0, true);
				if (!adjusted) adjusted = adjust(&edubot, PREFERRED_MID_SONAR, 1.2, false);
				if (!adjusted) adjusted = adjust(&edubot, PREFERRED_FRONT_SONAR, 1.3, false);

				front_distance = edubot.safe_advance(HIGH_SPEED);	
				
				snooze();
			}
	
			// Então, converter ao lado contrário do preferido (arbitrário; poderia ser esquerda)
			// E avisar o MazeSolver que houve uma rotação para este lado
			edubot.safe_rotate(o_angle(RIGHT_ANGLE));
			maze.rotated((Side)OTHER_SIDE);

			snooze();
		}
	}

	return 0;
}


// Deixa a thread tirar uma soneca
// Senão ela morre de exaustão
void snooze() {
	#ifdef _WIN32
	    Sleep(1);
	#else
	    usleep(1000);
	#endif
}

bool adjust(Edubot* edubot, Sonar sonar, double weight, bool check_far) {
	double distance = edubot->get_distance(sonar);

	if (distance > FAR_DISTANCE) return false;
	
	double deviation = distance - FOLLOW_DISTANCE;
	double abs_deviation;

	if (check_far) {
		abs_deviation = fabs(deviation);
	} else {
		abs_deviation = -abs_deviation;
	}

	std::cout << "D " << distance << " F " << FOLLOW_DISTANCE << " S " << (int)sonar << ":   " << deviation << std::endl;
	
	if (abs_deviation > FOLLOW_DISTANCE_TOLERANCE) {
		double angle_base = abs_deviation * COUNTER_ANGLE_MULTIPLIER;
		double exp_angle = pow(angle_base, COUNTER_ANGLE_EXPONENT);
		double offset_angle = exp_angle + MIN_COUNTER_ANGLE;
		Angle counter_angle = Angle(offset_angle * weight);

		// (deviation > 0) -> (side_distance > FOLLOW_DISTANCE) -> (robô muito para fora) -> (deve rotacionar para dentro)
		if (deviation > 0) {
			counter_angle = counter_angle;
		} else {
			counter_angle = -counter_angle;
		}

		edubot->safe_rotate(p_angle(counter_angle));
		edubot->move(SLOW_SPEED);
		edubot->sleepMilliseconds(ADJUSTMENT_TIME);

		return true;
	} else {
		return false;
	}
}
