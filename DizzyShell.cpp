#include "DizzyShell.h"
#include "Fighter.h"

DizzyShell::DizzyShell()
{
	_name = "Dizzy Shell";
	_damage = 4;
	_type = MoveType::Defensive;
}
void DizzyShell::Evaluate(Fighter* user, Fighter* target)
{
	Move::Evaluate(user, target);
	if(target->GetStatus() == FighterStatus::Healthy)
	{
		target->SetStatus(FighterStatus::Confused);
		target->SetStatusClock(2);
	}
}