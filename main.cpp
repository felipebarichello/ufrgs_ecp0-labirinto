#include <iostream>
#include "libs/EdubotLib.hpp"
#include "edubot.hpp"
#include "parameters.hpp"

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
		edubot.max_speed = MAX_SPEED;
		edubot.inverse_angular_velocity = INVERSE_ANGULAR_VELOCITY;
		edubot.max_distance = MAX_DISTANCE;
		edubot.min_distance = MIN_DISTANCE;

		double distance;
		
		// Esperar at� o valor do sonar frontal ser atualizado
		// Enquanto o rob� n�o enviar um sinal de atualiza��o do sonar frontal, o valor � zero
		do {
			edubot.sleepMilliseconds(1);
			distance = edubot.get_distance(Sonar::Front);
		} while (distance == 0);
		
		while (edubot.isConnected()) {
			edubot.safe_charge();
			edubot.safe_rotate(90);
		}
	}

	return 0;
}
