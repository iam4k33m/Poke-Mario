#include "BattleEngine.h"
#include "Fighter.h"
#include <vector>
#include <iostream>
#include <thread>
#include "PlayerMoveSelector.h"
#include "CPUMoveSelector.h"
#include "Goomba.h"
#include "Koopa.h"

static const uint32 IDcount = 2;
template <class T> T* _Derive()
{
	return new T();
}
Fighter* Derive(uint32 classType)
{
	Fighter* instance = nullptr;
	switch(classType)
	{
	case 0:
		instance = _Derive<Goomba>();
		break;
	case 1:
		instance = _Derive<Koopa>();
		break;
	default:
		instance = _Derive<Fighter>();
		instance->SetName("MissingNo");
		break;
	}
	return instance;
}



BattleEngine::BattleEngine()
{
	a = b = nullptr;
	aIsCPU = bIsCPU = false;
	secondsTowait = 0.0f;
}

Fighter *BattleEngine::GetA() const
{
    return a;
}

Fighter *BattleEngine::GetB() const
{
    return b;
}
 std::vector<PlayerMoveSelector *> &BattleEngine::GetPlayerInputs()
{
    return playerInputs;
}

std::vector<CPUMoveSelector *> &BattleEngine::GetCpuInputs()
{
    return cpuInputs;
}

void BattleEngine::SetA(Fighter *a)
{
    BattleEngine::a = a;
	RegisterA(a);
}

void BattleEngine::SetB(Fighter *b)
{
    BattleEngine::b = b;
	RegisterB(b);
}

void BattleEngine::ProcessTurn()
{
	a->Update();
	b->Update();
	
		
	if (a->GetSpeed() >= b->GetSpeed())
	{
		ProcessA();
		ProcessB();
		firstBuffer = a->GetBufferLine();
		secondBuffer = b->GetBufferLine();
	}
	else
	{
		ProcessB();
		ProcessA();
		firstBuffer = b->GetBufferLine();
		secondBuffer = a->GetBufferLine();
	}
	
	
}
void BattleEngine::OutputTurn()
{
	
	for(uint32 i = 0; i < firstBuffer->size() || i < secondBuffer->size(); i++)
	{
		if (i < firstBuffer->size())
		{
			std::cout << firstBuffer->at(i) + '\n';
			std::this_thread::sleep_for(std::chrono::milliseconds((uint32)(secondsTowait * 1000)));
		}
		if(i < secondBuffer->size())
		{
			std::cout << secondBuffer->at(i) + '\n';
			std::this_thread::sleep_for(std::chrono::milliseconds((uint32)(secondsTowait * 1000)));
		}
		
	}
	if (CheckWin() > 0)
	{
		if (CheckWin() == 1)
		{
			std::cout << b->GetName() + " Fainted!\n";
		}
		else
		{
			std::cout << a->GetName() + " Fainted!\n";
		}
	}
	
}
uint32 BattleEngine::CheckWin()
{
	uint32 result = 0;
	if(a->GetHealth() == 0)
	{
		result = 2;
	}
	if(b->GetHealth() == 0)
	{
		result = 1;
	}
	return result;
}
void BattleEngine::RandomGenB()
{
	float randomValue = RandomFloat();
	randomValue *= (IDcount - 1);
	uint32 ID = static_cast<int>(roundf(randomValue));
	b = Derive(ID);
	RegisterB(b);
}
void BattleEngine::RandomGenA()
{
	float randomValue = RandomFloat();
	randomValue *= (IDcount - 1);
	uint32 ID = static_cast<int>(randomValue);
	a = Derive(ID);
	RegisterA(a);
}
void BattleEngine::RegisterA(Fighter* fighter)
{
	if (aIsCPU)
	{
		CPUMoveSelector* selector = new CPUMoveSelector();
		selector->SetPlayer(a);
		cpuInputs.push_back(selector);
	}
	else
	{
		PlayerMoveSelector* selector = new PlayerMoveSelector();
		selector->SetPlayer(a);
		playerInputs.push_back(selector);
	}
}
void BattleEngine::RegisterB(Fighter* fighter)
{
	if (bIsCPU)
	{
		CPUMoveSelector* selector = new CPUMoveSelector();
		selector->SetPlayer(b);
		cpuInputs.push_back(selector);
	}
	else
	{
		PlayerMoveSelector* selector = new PlayerMoveSelector();
		selector->SetPlayer(b);
		playerInputs.push_back(selector);
	}
}
void BattleEngine::ProcessA()
{
	
	if(playerInputs.size() >= 2)
	{
		//If both are player controlled, a is 0;
		playerInputs[0]->PlayerAttack(b);
	}
	else if (cpuInputs.size() >= 2)
	{
		//If both are cpu controlled, a is 0;
		cpuInputs[0]->PlayerAttack(b);
	}
	else if(cpuInputs.size() == 1)
	{
		if(aIsCPU)
		{
			cpuInputs[0]->PlayerAttack(b);
		}
		else
		{
			playerInputs[0]->PlayerAttack(b);
		}
	}
}
void BattleEngine::ProcessB()
{
	if (playerInputs.size() >= 2)
	{
		//If both are player controlled, b is 1;
		playerInputs[1]->PlayerAttack(a);
	}
	else if (cpuInputs.size() >= 2)
	{
		//If both are cpu controlled, b is 1;
		cpuInputs[1]->PlayerAttack(a);
	}
	else if (cpuInputs.size() == 1)
	{
		if (bIsCPU)
		{
			cpuInputs[0]->PlayerAttack(a);
		}
		else
		{
			playerInputs[0]->PlayerAttack(a);
		}
	}
}
bool BattleEngine::GetAIsCpu() const
{
    return aIsCPU;
}

void BattleEngine::SetAIsCpu(bool aIsCpu)
{
    aIsCPU = aIsCpu;
}

bool BattleEngine::GetBIsCpu() const
{
    return bIsCPU;
}

void BattleEngine::SetBIsCpu(bool bIsCpu)
{
    bIsCPU = bIsCpu;
}

float BattleEngine::GetSecondsTowait() const {
    return secondsTowait;
}

void BattleEngine::SetSecondsTowait(float secondsTowait) {
    BattleEngine::secondsTowait = secondsTowait;
}
