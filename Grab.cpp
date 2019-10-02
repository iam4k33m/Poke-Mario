//
// Created by S17118281 on 25/09/2019.
//
#include "Grab.h"
#include "Fighter.h"
Grab::Grab()
{
    _name = "Grab";
    _type = MoveType::Offensive;
}
void Grab::Evaluate(Fighter *user, Fighter *target)
{
	Move::Evaluate(user, target);
    if(target->GetStatus() == FighterStatus::Healthy)
    {
        target->SetStatus(FighterStatus::Grabbed);
        target->SetStatusClock(1);
        
    }
	target->SetDefense(target->GetDefense()*0.8f);
}
