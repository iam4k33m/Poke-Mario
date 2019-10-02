#include "PowerShell.h"
#include "Fighter.h"
PowerShell::PowerShell()
{
	_name = "Power Shell";
	_damage = 8;
}
PowerShell::~PowerShell() = default;
//This move decreases defense of the target and is overriding evaluate() to do this
void PowerShell::Evaluate(Fighter* user, Fighter* target)
{
	Move::Evaluate(user, target);
	target->SetDefense(target->GetDefense()*0.8f);
}
