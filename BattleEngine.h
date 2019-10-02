#ifndef BATTLEENGINE
#define BATTLEENGINE
class Fighter;
class PlayerMoveSelector;
class CPUMoveSelector;
#include <vector>
#include <functional>
class BattleEngine
{
private:
	 Fighter* a;
	 Fighter* b;
	 bool aIsCPU;
	 bool bIsCPU;
	 float secondsTowait;
	 std::vector<PlayerMoveSelector*> playerInputs;
	 std::vector<CPUMoveSelector*> cpuInputs;
	 std::vector < std::string>* firstBuffer;
	 std::vector < std::string>* secondBuffer;
	 std::vector < std::function<Fighter*()>> constructors;
public:
	BattleEngine();
	~BattleEngine();
	void ProcessTurn();
	void OutputTurn();
	void RandomGenA();
	void RandomGenB();
	void ProcessA();
	void ProcessB();
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
