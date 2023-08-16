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
		double delta_theta = -90. / ROTATION_STEPS;
		double front_distance;
		
		edubot.safe_distance = SAFE_DISTANCE;
		edubot.rotation_duration = ROTATION_DURATION;

		
		// Esperar até o valor do sonar frontal ser atualizado
		// Enquanto o robô não enviar um sinal de atualização do sonar frontal, o valor é zero
		do {
			edubot.sleepMilliseconds(1);
			front_distance = edubot.get_distance(Sonar::Front);
		} while (front_distance == 0);

		MazeSolver maze = MazeSolver();
				
		while (edubot.isConnected()) {
			front_distance = edubot.get_distance(Sonar::Front);
				
			// Seguir a parede da esquerda (arbitrário; poderia ser direita) até não haver mais parede à esquerda
			while (maze.should_follow()) {
				// Virar à esquerda se houver caminho
				if (edubot.get_distance(Sonar::Left) >= FAR_DISTANCE) {
					// Ir virando devagarinho
					for (char i = 0; i < ROTATION_STEPS; i++) {
						edubot.safe_rotate(delta_theta);
						
						while (edubot.get_distance(Sonar::Left) < WALL_DISTANCE) {
							edubot.move(SLOW_SPEED);
						}
					}
					
					maze.rotated_left();
					break;
				}

				if (front_distance > WALL_DISTANCE) {
			        	front_distance = edubot.safe_advance(MID_SPEED);
				} else {
			    		// Virar à direita se houver obstrução
			    		edubot.safe_rotate(90);
			    		maze.rotated_right();
			    		break;
			    	}
			}

			// Quando o MazeSolver disser que não é para seguir a parede
			
			front_distance = edubot.get_distance(Sonar::Front);
			
			// Seguir reto atï¿½ encontrar um obstï¿½culo
		    	while (front_distance > WALL_DISTANCE) {
		        	front_distance = edubot.safe_advance(HIGH_SPEED);
		    	}
	
			// Então, converter à direita (arbitrário; poderia ser esquerda)
			// E avisar o MazeSolver que houve uma rotação à direita
			edubot.safe_rotate(90);
			maze.rotated_right();
		}
	}

	return 0;
}
