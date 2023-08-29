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
double rnd_side(bool, bool);


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
				
				edubot.move(-0.5);
				edubot.sleepMilliseconds(500);
				
				edubot.neutral();
				edubot.sleepMilliseconds(500);

				edubot.safe_rotate(rnd_side(left_b, right_b));
			} else {
				if (rand()%100 < 5) {
					edubot.move(-0.5);
					edubot.sleepMilliseconds(2000);
					edubot.stop();
					edubot.safe_rotate(rnd_side(false, false));
					continue;
				}
				
				edubot.move(0.4);
				edubot.sleepMilliseconds(500);
			}
		}

		std::cout << "Conexão perdida" << std::endl;
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

double rnd_side(bool left_b, bool right_b) {
	int bias = 0;

	if (left_b) {
		bias -= 300;
	}

	if (right_b) {
		bias += 300;
	}

	if (rand()%1000 < 500 + bias) {
		return -TURN_ANGLE;
	} else {
		return TURN_ANGLE;
	}
}
