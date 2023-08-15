#pragma once

#include "edubot.hpp"


class VirtualEdubot : public Edubot {
	public:
		int move_wait = 10;

		// H� um bug no simulador que permite que o rob� adquira uma velocidade absurda
		// quando move() � chamado muitas vezes. Logo, esta nova vers�o da fun��o leva em conta
		// um cooldown que impede chamadas consecutivas muito r�pidas
		bool move(double speed) override;
};
