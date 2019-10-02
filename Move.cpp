//
// Created by S17118281 on 25/09/2019.
//
#include "Fighter.h"
#include "Move.h"
Move::Move()
{
    _damage = 0;
    _knockBack = 0;
    _type = MoveType::Normal;
    _missRate = 0;
}
Move::~Move() = default;
void Move::Evaluate(Fighter* user, Fighter* target)
{
	
    //Damage to deal
    float damageToDeal = _damage;
    //Multiply by fighter damage
    damageToDeal *= user->GetAttack();
    //Attack the target
    target->TakeHit(damageToDeal);
}

uint32 Move::GetDamage() const
{
    return _damage;
}

void Move::SetDamage(uint32 damage)
{
    _damage = damage;
}

uint32 Move::GetKnockBack() const
{
    return _knockBack;
}

void Move::SetKnockBack(uint32 knockBack)
{
    _knockBack = knockBack;

}

const std::string& Move::GetName() const
{
    return _name;
}

float Move::GetMissRate() const {
    return _missRate;
}

void Move::SetMissRate(float missRate) {
    _missRate = missRate;
}

MoveType Move::GetType() 
{
    return _type;
}
