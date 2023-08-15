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

	// Estabelecer conexão
	if (!edubot.connect()) {
		std::cout << "Nao foi possivel conectar-se ao Edubot" << std::endl;
	} else {
		edubot.max_distance = MAX_DISTANCE;

		double distance;
		
		// Esperar até o valor do sonar frontal ser atualizado
		// Enquanto o robô não enviar um sinal de atualização do sonar frontal, o valor é zero
		do {
			edubot.sleepMilliseconds(1);
			distance = edubot.get_distance(Sonar::Front);
		} while (distance == 0);

		MazeSolver maze = MazeSolver();
				
		while (edubot.isConnected()) {
			double front_distance = edubot.get_distance(Sonar::Front);
				
			// Seguir a parede da esquerda (arbitrário; poderia ser direita) até não haver mais parede à esquerda
			while (maze.should_follow()) {
				// Virar à esquerda se houver caminho
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
			    		// Virar à direita se houver obstrução
			    		edubot.safe_rotate(90);
			    		maze.rotated_right();
			    		break;
			    	}
			}

			// Se o MazeSolver disser que não é para seguir a parede
			if (!maze.should_follow()) {
				double front_distance = edubot.get_distance(Sonar::Front);
				
				// Seguir reto até encontrar um obstáculo
			    	while (front_distance > FRONT_STOP_DISTANCE) {
			        	front_distance = edubot.safe_advance(HIGH_SPEED);
			    	}
		
				// Então, converter à direita (arbitrário; poderia ser esquerda)
				// E avisar o MazeSolver que houve uma rotação à direita
				edubot.safe_rotate(90);
				maze.rotated_right();
			}
		}
	}

	return 0;
}
