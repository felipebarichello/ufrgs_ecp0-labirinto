#include "parameters.hpp"
#include "side.hpp"
#include "edubot.hpp"


// Compatilidade com par�metros antigos
#ifndef PREFERRED_SIDE
	#define PREFERRED_SIDE -1
#endif

// Lado din�mico
#if   (PREFERRED_SIDE == -1)
	#define OTHER_SIDE 1
	
	#define PREFERRED_SIDE_SONAR  Sonar::Left
	#define PREFERRED_MID_SONAR   Sonar::MidLeft
	#define PREFERRED_FRONT_SONAR Sonar::FrontLeft
#elif (PREFERRED_SIDE == 1)
	#define OTHER_SIDE -1
	
	#define PREFERRED_SIDE_SONAR  Sonar::Right
	#define PREFERRED_MID_SONAR   Sonar::MidRight
	#define PREFERRED_FRONT_SONAR Sonar::FrontRight
#else
	#error "Valor ilegal para PREFERRED_SIDE"
#endif

// �ngulo para o lado preferido e para o outro, respectivamente
#define p_angle(angle) angle * (double)PREFERRED_SIDE
#define o_angle(angle) angle * (double)OTHER_SIDE

// Quanto o rob� deve rotacionar a cada itera��o ao virar para o lado preferido
#define DELTA_THETA 90.0 * PREFERRED_SIDE / ROTATION_STEPS
