#include "Charge.h"

Charge::Charge()
{
	_name = "Charge";
	_damage = 4;
	_type = MoveType::Offensive;
}
void Charge::Evaluate(Fighter* user, Fighter* target)
{
	user->SetSpeed(user->GetSpeed() * 1.1f);
	Move::Evaluate(user, target);
}