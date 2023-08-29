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

		edubot.rotation_duration = ROTATION_DURATION;
		
		// Esperar até o valor do sonar frontal ser atualizado
		// Enquanto o robô não enviar um sinal de atualização do sonar frontal, o valor é zero
		do {
			snooze();
			front_distance = edubot.get_distance(Sonar::Front);
		} while (front_distance == 0);

		int counterdrift_cooldown = COUNTERDRIFT_COOLDOWN;

		// ATENÇÃO:
		// Dentro de qualquer loop que repete por muito tempo, TODOS os seus caminhos devem "sleepar" a thread em algum momento
		while (edubot.isConnected()) {
			bool left_b = edubot.getBumper(0);
			bool right_b = edubot.getBumper(1);
			
			if (left_b || right_b) {
				#if (LOG_ALL)
					std::cout << "Batida detectada" << std::endl;
				#endif
				
				edubot.neutral();
				edubot.sleepMilliseconds(INVERSION_WAIT);
				
				edubot.move(-RETREAT_SPEED);
				edubot.sleepMilliseconds(RETREAT_TIME);
				
				edubot.neutral();
				edubot.sleepMilliseconds(PRE_ROTATION_WAIT);
				
				#if (LOG_ALL)
					std::cout << "Rotação de batida" << std::endl;
				#endif

				edubot.safe_rotate(rnd_side(left_b, right_b));
			} else {
				
				if (rand()%100 < RND_INVERSION_CHANCE) {
					#if (LOG_ALL)
						std::cout << "Inversão aleatória" << std::endl;
					#endif
					
					edubot.neutral();
					edubot.sleepMilliseconds(INVERSION_WAIT);
					edubot.move(-RETREAT_SPEED);
					edubot.sleepMilliseconds(RETREAT_TIME);
					edubot.stop();
					edubot.safe_rotate(rnd_side(false, false));
					continue;
				}

				
				#if (DUMB_COUNTERDRIFT != 0)
					if (counterdrift_cooldown < 0) {
						#if (LOG_ALL)
							std::cout << "Ajuste" << std::endl;
						#endif
						
						edubot.safe_rotate(DUMB_COUNTERDRIFT);
						counterdrift_cooldown = COUNTERDRIFT_COOLDOWN;
					} else {
						counterdrift_cooldown--;
					}
				#endif

				#if (LOG_ALL)
					std::cout << "Avanço" << std::endl;
				#endif
				
				edubot.move(MID_SPEED);
				edubot.sleepMilliseconds(MOVE_WAIT);
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
		bias -= RIGHT_BIAS;
	}

	if (right_b) {
		bias += LEFT_BIAS;
	}

	if (rand()%1000 < HARD_BIAS + bias) {
		return -TURN_ANGLE;
	} else {
		return TURN_ANGLE;
	}
}
