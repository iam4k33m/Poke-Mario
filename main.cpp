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
	
	
	
	engine->SetAIsCpu(false);
	engine->SetBIsCpu(true);
	engine->SetA(mario);
	engine->RandomGenB();
	
	
	
	engine->SetSecondsTowait(0.2f);
	std::cout << "Wild " + engine->GetB()->GetName() + " Appeared!\nGo Mario! \ntch!\n";
	uint32 status = engine->CheckWin();
	while (status == 0)
	{
		int z = 1;
		engine->ProcessTurn();
		engine->OutputTurn();
		std::cout << "Health: " << mario->GetHealth() << '\n';
		status = engine->CheckWin();
	}
	system("pause");
    
    delete mario;
	delete darkMario;
	
	delete goomba;
	

    return 0;
}