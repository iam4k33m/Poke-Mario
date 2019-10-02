#include "Goomba.h"
Goomba::Goomba()
{
	_name = "Goomba";
	_health = 24;
	_missRate = 0.01f;
	_moves.push_back(new Charge());
	_moves.push_back(new Bite());
}