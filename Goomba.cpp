#include "Goomba.h"
Goomba::Goomba()
{
	_name = "Goomba";
	_health = 16;
	_missRate = 0.3f;
	_moves.push_back(new Charge());
	_moves.push_back(new Bite());
}