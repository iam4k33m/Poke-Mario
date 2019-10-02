//
// Created by S17118281 on 25/09/2019.
//
#include "Ground Pound.h"
#include "Fighter.h"
GroundPound::GroundPound() : Move()
{
    _name = "Ground Pound";
    _damage = 12;
	_type = MoveType::Offensive;
}
void GroundPound::Evaluate(Fighter *user, Fighter *target)
{
	Move::Evaluate(user, target);
    if(target->GetStatus() == FighterStatus::Healthy)
    {
        target->SetStatus(FighterStatus::Crushed );
        target->SetStatusClock( 2 );
    }
}
