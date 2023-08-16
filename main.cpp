#include <iostream>
#include "libs/EdubotLib.hpp"
#include "edubot.hpp"
#include "parameters.hpp"
#include "maze_solver.hpp"

#include "includes.hpp"


void snooze();

int main() {
	Edubot edubot = Edubot();

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
				// Virar � esquerda se houver caminho
				if (edubot.get_distance(Sonar::Left) >= FAR_DISTANCE) {
					// Ir virando devagarinho
					for (char i = 0; i < ROTATION_STEPS; i++) {
						edubot.safe_rotate(delta_theta);
						
						while (edubot.get_distance(Sonar::Left) < WALL_DISTANCE) {
							edubot.move(SLOW_SPEED);
							snooze();
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

			    	snooze();
			}

			// Quando o MazeSolver disser que n�o � para seguir a parede
			
			front_distance = edubot.get_distance(Sonar::Front);
			
			// Seguir reto at� encontrar um obst�culo
		    	while (front_distance > WALL_DISTANCE) {
		        	front_distance = edubot.safe_advance(HIGH_SPEED);
		        	snooze();
		    	}
	
			// Ent�o, converter � direita (arbitr�rio; poderia ser esquerda)
			// E avisar o MazeSolver que houve uma rota��o � direita
			edubot.safe_rotate(90);
			maze.rotated_right();

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
