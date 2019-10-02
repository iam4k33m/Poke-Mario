#include "CPUMoveSelector.h"
#include "Move.h"

#pragma region Get and Set
Fighter *CPUMoveSelector::GetPlayer() const
{
	return _player;
}

void CPUMoveSelector::SetPlayer(Fighter *player)
{
	_player = player;
	_startingHealth = _player->GetHealth();
}

float CPUMoveSelector::GetWorryPortion() const
{
	return _worryPortion;
}

void CPUMoveSelector::SetWorryPortion(float worryPortion)
{
	_worryPortion = worryPortion;
}

float CPUMoveSelector::GetPanicPortion() const
{
	return _panicPortion;
}

void CPUMoveSelector::SetPanicPortion(float panicPortion)
{
	_panicPortion = panicPortion;
}
#pragma endregion
CPUMoveSelector::CPUMoveSelector()
{
	_player = nullptr;
	_moveID = 0;
	_startingHealth = 0;
	_worryPortion = _panicPortion = 0.0f;
}
CPUMoveSelector::~CPUMoveSelector() = default;
std::string CPUMoveSelector::PlayerAttack(Fighter* target)
{
	bool attackSelected = false;
	float healthRatio = _player->GetHealth() / _startingHealth;
	//Worried attack logic
	if(healthRatio < _worryPortion)
	{
		if(healthRatio < _panicPortion)
		{
			for (uint32 i = 0; i < _player->GetMoves().size(); i++)
			{
				if (_player->GetMoves()[i]->GetType() == MoveType::Offensive && !attackSelected)
				{
					_moveID = i;
					attackSelected = true;
				}
			}
		}
		for(uint32 i = 0; i < _player->GetMoves().size(); i++)
		{
			if(_player->GetMoves()[i]->GetType() == MoveType::Defensive && !attackSelected)
			{
				_moveID = i;
				attackSelected = true;
			}
		}

	}
	if(!attackSelected)
	{
		_moveID = static_cast<int>(RandomFloat() * _player->GetMoves().size());
		attackSelected = true;
	}
	return _player->Attack(_moveID, *target);
}

