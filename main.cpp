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
		double delta_theta = -90. / ROTATION_STEPS;
		double front_distance;
		
		edubot.safe_distance = SAFE_DISTANCE;
		edubot.rotation_duration = ROTATION_DURATION;

		
		// Esperar at� o valor do sonar frontal ser atualizado
		// Enquanto o rob� n�o enviar um sinal de atualiza��o do sonar frontal, o valor � zero
		do {
			edubot.sleepMilliseconds(1);
			front_distance = edubot.get_distance(Sonar::Front);
		} while (front_distance == 0);

		MazeSolver maze = MazeSolver();
				
		while (edubot.isConnected()) {
			front_distance = edubot.get_distance(Sonar::Front);
				
			// Seguir a parede da esquerda (arbitr�rio; poderia ser direita) at� n�o haver mais parede � esquerda
			while (maze.should_follow()) {
				// Virar � esquerda se houver caminho
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
			    		// Virar � direita se houver obstru��o
			    		edubot.safe_rotate(90);
			    		maze.rotated_right();
			    		break;
			    	}
			}

			// Quando o MazeSolver disser que n�o � para seguir a parede
			
			front_distance = edubot.get_distance(Sonar::Front);
			
			// Seguir reto at� encontrar um obst�culo
		    	while (front_distance > WALL_DISTANCE) {
		        	front_distance = edubot.safe_advance(HIGH_SPEED);
		    	}
	
			// Ent�o, converter � direita (arbitr�rio; poderia ser esquerda)
			// E avisar o MazeSolver que houve uma rota��o � direita
			edubot.safe_rotate(90);
			maze.rotated_right();
		}
	}

	return 0;
}
