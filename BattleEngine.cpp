#include "BattleEngine.h"
#include "Fighter.h"
#include <vector>
#include <iostream>
#include <thread>
#include "PlayerMoveSelector.h"
#include "CPUMoveSelector.h"

template <class T> T Derive()
{
	return new T();
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
}

void BattleEngine::SetB(Fighter *b)
{
    BattleEngine::b = b;
}

void BattleEngine::ProcessTurn()
{
	a->Update();
	b->Update();
	if(a->GetSpeed() >= b->GetSpeed())
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
	/*for (uint32 i = 0; i < secondBuffer->size(); i++)
	{
		std::cout << secondBuffer->at(i) + '\n';
		std::this_thread::sleep_for(std::chrono::milliseconds((uint32)(secondsTowait * 1000)));
	}*/
}

void BattleEngine::RandomGenB()
{
	if(constructors.size() > 0)
	{
		uint32 target = (uint32)(RandomFloat()*constructors.size() - 1);
		std::function<Fighter*()> constructor = constructors.at(target);
		
		b = constructor();
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
