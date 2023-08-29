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

	// Estabelecer conex�o
	if (!edubot.connect()) {
		std::cout << "Nao foi possivel conectar-se ao Edubot" << std::endl;
	} else {
		double front_distance;
		
		edubot.safe_distance = SAFE_DISTANCE;
		edubot.rotation_duration = ROTATION_DURATION;
		
		// Esperar at� o valor do sonar frontal ser atualizado
		// Enquanto o rob� n�o enviar um sinal de atualiza��o do sonar frontal, o valor � zero
		do {
			snooze();
			front_distance = edubot.get_distance(Sonar::Front);
		} while (front_distance == 0);

		MazeSolver maze = MazeSolver();

		// ATEN��O:
		// Dentro de qualquer loop que repete por muito tempo, TODOS os seus caminhos devem "sleepar" a thread em algum momento
		while (edubot.isConnected()) {
			front_distance = edubot.get_distance(Sonar::Front);
				
			// Seguir a parede da esquerda (arbitr�rio; poderia ser direita) at� n�o haver mais parede � esquerda
			while (maze.should_follow()) {
				double side_distance = edubot.get_distance(PREFERRED_SIDE_SONAR);
				
				// Virar ao lado preferido se houver caminho
				if (side_distance >= FAR_DISTANCE) {
					// Virar
					edubot.move(SLOW_SPEED);
					edubot.sleepMilliseconds(OVERSHOOT_TIME);
					edubot.safe_rotate(p_angle(RIGHT_ANGLE));
					maze.rotated((Side)PREFERRED_SIDE);

					// Seguir at� econtrar a parede novamente (apenas se o rob� estiver seguindo uma parede)
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
						/* Ajustar posi��o lateral para se manter perto (mas n�o demais) da parede */
						
						bool adjusted = adjust(&edubot, PREFERRED_SIDE_SONAR, 1.0, true);
						if (!adjusted) adjusted = adjust(&edubot, PREFERRED_MID_SONAR, 1.4, false);
						if (!adjusted) adjusted = adjust(&edubot, PREFERRED_FRONT_SONAR, 1.4, false);

				        	front_distance = edubot.safe_advance(MID_SPEED);
					} else {
						// Virar ao lado contr�rio do preferido se houver obstru��o
						edubot.safe_rotate(o_angle(RIGHT_ANGLE));
						maze.rotated((Side)OTHER_SIDE);
					}
					
					snooze();
				}
			}

			// Quando o MazeSolver disser que n�o � para seguir a parede
			
			front_distance = edubot.get_distance(Sonar::Front);
			
			// Seguir reto at� encontrar um obst�culo
			while (front_distance > WALL_DISTANCE) {
				bool adjusted = adjust(&edubot, PREFERRED_SIDE_SONAR, 1.0, true);
				if (!adjusted) adjusted = adjust(&edubot, PREFERRED_MID_SONAR, 1.2, false);
				if (!adjusted) adjusted = adjust(&edubot, PREFERRED_FRONT_SONAR, 1.3, false);

				front_distance = edubot.safe_advance(HIGH_SPEED);	
				
				snooze();
			}
	
			// Ent�o, converter ao lado contr�rio do preferido (arbitr�rio; poderia ser esquerda)
			// E avisar o MazeSolver que houve uma rota��o para este lado
			edubot.safe_rotate(o_angle(RIGHT_ANGLE));
			maze.rotated((Side)OTHER_SIDE);

			snooze();
		}
	}

	return 0;
}


// Deixa a thread tirar uma soneca
// Sen�o ela morre de exaust�o
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

		// (deviation > 0) -> (side_distance > FOLLOW_DISTANCE) -> (rob� muito para fora) -> (deve rotacionar para dentro)
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
