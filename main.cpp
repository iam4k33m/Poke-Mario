#include <iostream>
#include <ctime>
#include "Mario.h"
#include "Goomba.h"
#include "Move.h"
#include "PlayerMoveSelector.h"
#include "CPUMoveSelector.h"
#include "BattleEngine.h"
#include <chrono>
int main() 
{
	long int clock = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	
	srand(clock);
	InitializeStatusDamage();
    
	BattleEngine* engine = new BattleEngine();
    Mario* mario = new Mario();
	Goomba* goomba = new Goomba();
	Mario* darkMario = new Mario();
	darkMario->SetName("Totally not Bowser Jr");
	PlayerMoveSelector* playerM = new PlayerMoveSelector();
	CPUMoveSelector* enemyM = new CPUMoveSelector();
	enemyM->SetPanicPortion(0.2f);
	enemyM->SetWorryPortion(0.6f);
	playerM->SetPlayer(mario);
	enemyM->SetPlayer(goomba);
	engine->SetA(mario);
	engine->SetB(goomba);
	engine->SetAIsCpu(false);
	engine->SetBIsCpu(true);
	engine->GetPlayerInputs().push_back(playerM);
	engine->GetCpuInputs().push_back(enemyM);
	engine->SetSecondsTowait(0.2f);
	std::cout << "Wild Goomba Appeared!\nGo Mario! \ntch!\n";
    
	while (mario->GetHealth() > 0 && goomba->GetHealth() > 0)
	{
		engine->ProcessTurn();
		engine->OutputTurn();
		std::cout << "Health: " << mario->GetHealth() << '\n';
	}
	system("pause");
    
    delete mario;
	delete darkMario;
	delete playerM;
	delete goomba;
	delete enemyM;

    return 0;
}