//
// Created by S17118281 on 25/09/2019.
//
#include <iostream>
#include "Fighter.h"
#include "Move.h"
#include "Helpers.h"
#include<sstream>
#include <map>
std::string FighterStatusNamePastTense[] = { "Healthy", "Grabbed", "Paralyzed", "Poisoned", "Burned","Frozen" , "Crushed", "Confused" };
std::string FighterStatusNamePresentTense[] = { "Health", "Grab", "Paralysis", "Poisoning", "Burn" ,"Hypothermia" , "Crushing", "Confusion" };
std::map<FighterStatus, float> statusDamage;

std::map<FighterStatus, std::string> statusDamageText;
std::map<FighterStatus, std::string> statusSkipTurnText;
std::map<FighterStatus, float> statusSkipTurn;
void InitializeStatusDamage()
{
#pragma region Damage
	//region Damage

	statusDamage.insert(std::make_pair(FighterStatus::Healthy, 0.0f));
	statusDamage.insert(std::make_pair(FighterStatus::Grabbed, 1.0f));
	statusDamage.insert(std::make_pair(FighterStatus::Paralyzed, 0.0f));
	statusDamage.insert(std::make_pair(FighterStatus::Poisoned, 6.0f));
	statusDamage.insert(std::make_pair(FighterStatus::Burned, 4.0f));
	statusDamage.insert(std::make_pair(FighterStatus::Frozen, 6.0f));
	statusDamage.insert(std::make_pair(FighterStatus::Crushed, 7.0f));
	statusDamage.insert(std::make_pair(FighterStatus::Confused, 3.0f));
	//endregion
#pragma endregion
#pragma region DamageText
	statusDamageText.insert(std::make_pair(FighterStatus::Healthy, " Felt good in it's "));
	statusDamageText.insert(std::make_pair(FighterStatus::Grabbed, " Hurt itself trying to get free from "));
	statusDamageText.insert(std::make_pair(FighterStatus::Paralyzed, " Somehow got hurt in it's "));
	statusDamageText.insert(std::make_pair(FighterStatus::Confused, " thrashed about and hurt itself in "));
#pragma endregion
#pragma region SkipTurn
	statusSkipTurn.insert(std::make_pair(FighterStatus::Healthy, 0.0f));
	statusSkipTurn.insert(std::make_pair(FighterStatus::Grabbed, 0.25f));
	statusSkipTurn.insert(std::make_pair(FighterStatus::Paralyzed, 0.9f));
	statusSkipTurn.insert(std::make_pair(FighterStatus::Poisoned, 0.0f));
	statusSkipTurn.insert(std::make_pair(FighterStatus::Burned, 0.25f));
	statusSkipTurn.insert(std::make_pair(FighterStatus::Frozen, 0.8f));
	statusSkipTurn.insert(std::make_pair(FighterStatus::Crushed, 0.7f));
	statusSkipTurn.insert(std::make_pair(FighterStatus::Confused, 0.5f));
#pragma endregion
#pragma region SkipTurnText
	statusSkipTurnText.insert(std::make_pair(FighterStatus::Healthy, " somehow didn't "));
	statusSkipTurnText.insert(std::make_pair(FighterStatus::Confused, " and forgot to "));
	statusSkipTurnText.insert(std::make_pair(FighterStatus::Grabbed, " and missed it's chance to "));
#pragma endregion
}
Fighter::Fighter()
{
    //Set the name to a valid string so C++ doesn't cry.
    _name = "Undefined";
    //Set values to safe defaults
    _status = FighterStatus::Healthy;
    _statusClock = 0;
    _health = 0;
    _attack = 1.0f;
    _defense = 1.0f;
    _speed = 1.0f;
    _missRate = 0.0f;
	_missedTurn = false;
	_dirtyBuffer = false;
}
Fighter::~Fighter() = default;
//region Getters and Setters

void Fighter::SetName(const std::string& name)
{
    _name = name;
}
const std::string& Fighter::GetName()
{
    return _name;
}

uint32 Fighter::GetHealth() const
{
    return _health;
}

void Fighter::SetHealth(uint32 health)
{
    _health = health;
}

float Fighter::GetAttack() const
{
    return _attack;
}

void Fighter::SetAttack(float attack) 
{	
	OnStatChange(_attack, attack, "Attack");
    _attack = attack;
}

float Fighter::GetDefense() const
{

    return _defense;
}

void Fighter::SetDefense(float defense)
{
	OnStatChange(_defense, defense, "Defense");
    _defense = defense;
}

float Fighter::GetSpeed() const
{
    return _speed;
}

void Fighter::SetSpeed(float speed)
{
	OnStatChange(_speed, speed, "Speed");
    _speed = speed;
}

float Fighter::GetMissRate() const {
    return _missRate;
}

void Fighter::SetMissRate(float missRate)
{
	if (missRate < _missRate)
	{ 
		_moveCache += _name + "'s Accuracy rose!\n";
		_dirtyBuffer = true;
	}
	if (missRate > _missRate)
	{
		_moveCache += _name + "'s Accuracy fell!\n";
		_dirtyBuffer = true;
	}
    _missRate = missRate;
	
}

const std::vector<Move*> &Fighter::GetMoves() const
{
    return _moves;
}

void Fighter::SetMoves(const std::vector<Move*> &moves)
{
    _moves = moves;
}

FighterStatus Fighter::GetStatus() const
{
    return _status;
}

void Fighter::SetStatus(FighterStatus status)
{
	OnStatusChange(status);
    _status = status;
}

uint32 Fighter::GetStatusClock() const
{
    return _statusClock;
}

void Fighter::SetStatusClock(uint32 statusClock)
{
    _statusClock = statusClock;
}

//endregion
//region Battle stuff
std::string Fighter::Attack(uint32 move, Fighter& target)
{
	if(!_missedTurn)
	{
		if (move < _moves.size())
		{
			_moveCache += _name + " used " + _moves[move]->GetName() + "!\n";
			float missChance = _moves[move]->GetMissRate() * _missRate;
			if (RandomFloat() >= missChance)
			{
				_moves[move]->Evaluate(this, &target);

			}
			else
			{
				_moveCache += "The Attack missed...\n";
			}
			_dirtyBuffer = true;
		}
	}
   
	return _moveCache;
}
void Fighter::OnStatusStay()
{
	if(statusDamage[_status] != 0)
	{
		std::string damageText;
		if(statusDamageText.find(_status) != statusDamageText.end())
		{
			damageText = statusDamageText[_status];
		}
		else
		{
			damageText = " was hurt by it's ";
		}
		_moveCache += _name  + damageText + FighterStatusNamePresentTense[static_cast<int>(_status)] + "\n" ;
		if(_health > statusDamage[_status])
		{
			_health -= statusDamage[_status];
		}
		else
		{
			_health = 0;
		}
		if(RandomFloat() < statusSkipTurn[_status])
		{
			std::string skipTurn;
			if (statusSkipTurnText.find(_status) != statusSkipTurnText.end())
			{
				skipTurn = statusSkipTurnText[_status];
			}
			else
			{
				skipTurn = " and didn't ";
			}
			_moveCache += _name + " is " + FighterStatusNamePastTense[static_cast<int>(_status)] + skipTurn + "attack.\n";
			_missedTurn = true;
		}
		if (_statusClock == 0)
		{
			_moveCache += _name + "'s " + FighterStatusNamePastTense[static_cast<int>(_status)] + " wore off\n";
			_status = FighterStatus::Healthy;

		}
		--_statusClock;
		_dirtyBuffer = true;
	}
}
//Checker for stat changes, call in set.
void Fighter::OnStatChange(float assigned, float old, const std::string& name)
{
	if(assigned < old)
	{
		_moveCache += _name + "'s " + name + " rose!\n";
	}
	if(assigned > old)
	{
		_moveCache += _name + "'s " + name + " fell!\n";
	}
}

//Update
void Fighter::Update()
{
	_dirtyBuffer = true;
	_missedTurn = false;
	
	_moveCache = "";

	OnStatusStay();
}
//Call before writing new status
void Fighter::OnStatusChange(FighterStatus status)
{
	std::string statusName;
	if (static_cast<int>(_status) < sizeof(FighterStatusNamePresentTense) / sizeof(FighterStatusNamePresentTense[0]))
	{
		statusName = FighterStatusNamePastTense[static_cast<int>(_status)];
	}
	else
	{
		statusName = "Peculiar Ache";
	}
	switch(status)
	{
		
		
		case FighterStatus::Healthy:
			_moveCache += _name + "'s " + FighterStatusNamePresentTense[static_cast<int>(_status)] + " wore off.\n";
			break;
		default:
			if (static_cast<int>(status) < sizeof(FighterStatusNamePastTense) / sizeof(FighterStatusNamePastTense[0]))
			{
				statusName = FighterStatusNamePastTense[static_cast<int>(status)];
			}
			else
			{
				statusName = "given a Peculiar Ache";
			}
			_moveCache += _name + " was " + statusName + "!\n";
			break;

	}
	_dirtyBuffer = true;
}
//Take a hit
void Fighter::TakeHit(float damage)
{
	
    //Check if defense is greater than zero - we don't want div by zero errors here, nor any other shenanigans
    if( _defense > 0 )
    {
        //If we are okay, divide damage by defense, which is usually 1.0f
        damage /= _defense;
    }
    //After this, if damage is less than, or equal to health
    if(damage <= _health)
    {
        //Turn it to an int and deal the damage
        _health -= static_cast<uint32>(damage);
    }
    //But, if we get more damage than health
    else
    {
        //Just set health to zero, preventing underflow
        _health = 0;
    }
	
}

	std::vector < std::string>*  Fighter::GetBufferLine()
	{
		if(_dirtyBuffer)
		{
			_lineBuffer.clear();
			//Stringstream, for splitting
			std::stringstream stream(_moveCache);
			std::string item;
			while(std::getline(stream, item, '\n'))
			{
				_lineBuffer.push_back(item);
			}
		}
		_dirtyBuffer = false;
		return &_lineBuffer;

	}
    const std::string &Fighter::GetMoveCache() const
    {
        return _moveCache;
    }

//endregion

	