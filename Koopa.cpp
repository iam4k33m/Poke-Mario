#include "Koopa.h"
Koopa::Koopa()
{
	_name = "Koopa";
	_health = 24;
	_missRate = 0.35f;
	_moves.push_back(new ShellToss());
	_moves.push_back(new PowerShell());
	_moves.push_back(new DizzyShell());
} 