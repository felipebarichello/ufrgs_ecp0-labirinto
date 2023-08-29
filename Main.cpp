#include <iostream>
#include "libs/EdubotLib.hpp"
#include <time.h>
#include <stdlib.h>

EdubotLib *edubotLib = new EdubotLib();

int main(){
	srand(time(NULL));
	int direcao;
	edubotLib->connect();
	edubotLib->sleepMilliseconds(2000);
	while(1){
          while(!(edubotLib->getSonar(3) <= 0.21) && !(edubotLib->getBumper(0)) && !(edubotLib->getBumper(1))){
          	edubotLib->move(0.5);
          	edubotLib->sleepMilliseconds(200);      	
          	std::cout << "laço" << std::endl;
		}
		edubotLib->stop();
		edubotLib->sleepMilliseconds(50);
		std::cout << "fora do laço" << std::endl;			
		switch (rand()%2){
			case 0:edubotLib->rotate(90);
				break;
			case 1:edubotLib->rotate(-90);	
			}				
		edubotLib->sleepMilliseconds(1500);
	}
	edubotLib->disconnect();
	std::cout << "Could not connect on robot!" << std::endl;
	return 0;
	}
