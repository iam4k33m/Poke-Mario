#include "PlayerMoveSelector.h"
#include "Fighter.h"
#include "Move.h"
#include<iostream>
PlayerMoveSelector::PlayerMoveSelector()
{
	_moveID = 0;
}
PlayerMoveSelector::~PlayerMoveSelector() = default;
//Function to decide the player move, and to return the text buffer after attacking
std::string PlayerMoveSelector::PlayerAttack(Fighter* target)
{
	//Keep track of whether the player has made a selection or not
	bool selectionMade = false;
	//Until they make a selection, keep doing this
	while (!selectionMade)
	{
		//Loop over the players moves
		for (uint32 i = 0; i < _player->GetMoves().size(); i++)
		{
			//Print the move names
			std::cout << _player->GetMoves()[i]->GetName() + " / ";
		}
		//print context text
		std::cout << "\n What will " << _player->GetName() << " Do? \n";
		//Get input
		std::getline(std::cin, _inputBuffer);
		//Loop over the player's moves again
		for (uint32 i = 0; i < _player->GetMoves().size(); i++)
		{
			//Check each name, see if equal
			if (_inputBuffer.compare(_player->GetMoves()[i]->GetName()) == 0)
			{
				//If it is set the moveid to it's id
				_moveID = i;
				//And we can finish here
				selectionMade = true;
			}
		}
		if(!selectionMade)
		{
			std::cout << _player->GetName() << " doesn't know " << _inputBuffer << "...\n";
		}
	}
	//Attack, and return the output.
	return _player->Attack(_moveID, *target);
}

Fighter *PlayerMoveSelector::GetPlayer() const
{
    return _player;
}

void PlayerMoveSelector::SetPlayer(Fighter *player)
{
    _player = player;
}
