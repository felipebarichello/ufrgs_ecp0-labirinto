#pragma once

#include "edubot.hpp"


class VirtualEdubot : public Edubot {
	public:
		int move_wait = 10;

		// Há um bug no simulador que permite que o robô adquira uma velocidade absurda
		// quando move() é chamado muitas vezes. Logo, esta nova versão da função leva em conta
		// um cooldown que impede chamadas consecutivas muito rápidas
		bool move(double speed) override;
};
