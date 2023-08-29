#include <iostream>
#include "libs/EdubotLib.hpp"
#include "edubot.hpp"
#include "maze_solver.hpp"
#include "side.hpp"
#include "macros.hpp"
#include <stdlib.h>
#include <time.h>

#include "includes.hpp"


void snooze();


int main() {
	Edubot edubot = Edubot();

	// Estabelecer conexão
	if (!edubot.connect()) {
		std::cout << "Nao foi possivel conectar-se ao Edubot" << std::endl;
	} else {
		double front_distance;
		
  		srand(time(NULL));
  		
		edubot.safe_distance = SAFE_DISTANCE;
		edubot.rotation_duration = ROTATION_DURATION;
		
		// Esperar até o valor do sonar frontal ser atualizado
		// Enquanto o robô não enviar um sinal de atualização do sonar frontal, o valor é zero
		do {
			snooze();
			front_distance = edubot.get_distance(Sonar::Front);
		} while (front_distance == 0);

		// ATENÇÃO:
		// Dentro de qualquer loop que repete por muito tempo, TODOS os seus caminhos devem "sleepar" a thread em algum momento
		while (edubot.isConnected()) {
			bool left_b = edubot.getBumper(0);
			bool right_b = edubot.getBumper(1);
			
			if (left_b || right_b) {
				edubot.neutral();
				edubot.sleepMilliseconds(500);
				
				edubot.move(-HIGH_SPEED);
				edubot.sleepMilliseconds(500);
				
				edubot.neutral();
				edubot.sleepMilliseconds(500);
				

				if (left_b) {
					edubot.rotate(RIGHT_ANGLE * 0.8);
					edubot.sleepMilliseconds(2000);
				} else {
					edubot.rotate(-RIGHT_ANGLE * 0.8);
					edubot.sleepMilliseconds(2000);
				}
			} else {
				edubot.move(HIGH_SPEED);
				edubot.sleepMilliseconds(500);
			}
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
