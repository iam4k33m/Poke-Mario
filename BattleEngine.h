#ifndef BATTLEENGINE
#define BATTLEENGINE
class Fighter;
class PlayerMoveSelector;
class CPUMoveSelector;
#include <vector>
#include <functional>
#include "Typedefs.h"
//A battle engine - this handles setup and execution of the battle loop
class BattleEngine
{
private:
	//Fighters A and B
	 Fighter* a;
	 Fighter* b;
	 //Flags for if they are cpu controlled
	 bool aIsCPU;
	 bool bIsCPU;
	 //Time to delay text lines
	 float secondsTowait;
	 //Vector of move selectors
	 std::vector<PlayerMoveSelector*> playerInputs;
	 std::vector<CPUMoveSelector*> cpuInputs;
	 //String buffers
	 std::vector < std::string>* firstBuffer;
	 std::vector < std::string>* secondBuffer;
	 //Functions to register a fighter, these are internal access only
	 void RegisterA(Fighter* fighter);
	 void RegisterB(Fighter* fighter);
	 //Functions to process fighter attacks, internal only, also.
	 void ProcessA();
	 void ProcessB();
	 
	 
public:
	//Constructor and destructor
	BattleEngine();
	~BattleEngine();
	//Process and output game, this is in the game loop
	void ProcessTurn();
	void OutputTurn();
	//Randomly generate A and B, for encounters
	void RandomGenA();
	void RandomGenB();
	//Check if we have a winner - 0, is no, 1, is a, and 2 is b
	uint32 CheckWin(); 

    Fighter *GetA() const;

    Fighter *GetB() const;

    std::vector<PlayerMoveSelector *> &GetPlayerInputs();

    std::vector<CPUMoveSelector *> &GetCpuInputs();

    void SetA(Fighter *a);

    void SetB(Fighter *b);

    bool GetAIsCpu() const;

    void SetAIsCpu(bool aIsCpu);

    bool GetBIsCpu() const;

    void SetBIsCpu(bool bIsCpu);

    float GetSecondsTowait() const;

    void SetSecondsTowait(float secondsTowait);


};
#endif
