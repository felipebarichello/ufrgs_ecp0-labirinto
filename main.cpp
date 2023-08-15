#include <iostream>
#include "libs/EdubotLib.hpp"
#include "edubot.hpp"
#include "parameters.hpp"
#include "maze_solver.hpp"

#if (SIMULATION)
#include "simulation.hpp"
#endif

#include "includes.hpp"


int main() {
	#if (SIMULATION)
	VirtualEdubot edubot = VirtualEdubot();
	edubot.move_wait = SIMULATION_MOVE_WAIT;
	#else
	Edubot edubot = Edubot();
	#endif

	// Estabelecer conex�o
	if (!edubot.connect()) {
		std::cout << "Nao foi possivel conectar-se ao Edubot" << std::endl;
	} else {
		edubot.max_distance = MAX_DISTANCE;

		double distance;
		
		// Esperar at� o valor do sonar frontal ser atualizado
		// Enquanto o rob� n�o enviar um sinal de atualiza��o do sonar frontal, o valor � zero
		do {
			edubot.sleepMilliseconds(1);
			distance = edubot.get_distance(Sonar::Front);
		} while (distance == 0);

		MazeSolver maze = MazeSolver();
				
		while (edubot.isConnected()) {
			double front_distance = edubot.get_distance(Sonar::Front);
				
			// Seguir a parede da esquerda (arbitr�rio; poderia ser direita) at� n�o haver mais parede � esquerda
			while (maze.should_follow()) {
				// Virar � esquerda se houver caminho
				if (edubot.get_distance(Sonar::Left) >= SIDE_TURN_DISTANCE) {
					// Ir virando devagarinho
					for (char i = 0; i < 6; i++) {
						edubot.safe_rotate(-15);
						
						while (edubot.get_distance(Sonar::Left) < SIDE_MANEUVER_DISTANCE) {
							edubot.move(MANEUVER_SPEED);
						}
					}
					
					maze.rotated_left();
					edubot.move(OVERSHOOT_SPEED);
					edubot.sleepMilliseconds(FOLLOW_OVERSHOOT);
					break;
				}

				if (front_distance > FRONT_STOP_DISTANCE) {
			        	front_distance = edubot.safe_advance(MID_SPEED);
				} else {
			    		// Virar � direita se houver obstru��o
			    		edubot.safe_rotate(90);
			    		maze.rotated_right();
			    		break;
			    	}
			}

			// Se o MazeSolver disser que n�o � para seguir a parede
			if (!maze.should_follow()) {
				double front_distance = edubot.get_distance(Sonar::Front);
				
				// Seguir reto at� encontrar um obst�culo
			    	while (front_distance > FRONT_STOP_DISTANCE) {
			        	front_distance = edubot.safe_advance(HIGH_SPEED);
			    	}
		
				// Ent�o, converter � direita (arbitr�rio; poderia ser esquerda)
				// E avisar o MazeSolver que houve uma rota��o � direita
				edubot.safe_rotate(90);
				maze.rotated_right();
			}
		}
	}

	return 0;
}
