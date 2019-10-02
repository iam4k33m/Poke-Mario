#ifndef CPUMOVESELECT
#define CPUMOVESELECT
#include "Typedefs.h"
#include "Fighter.h"
#include "Helpers.h"
class CPUMoveSelector
{
private:
	Fighter* _player;
	uint32 _moveID;
	uint32 _startingHealth;
	float _worryPortion;
	float _panicPortion;
public:
	CPUMoveSelector();
	~CPUMoveSelector();
	std::string PlayerAttack(Fighter* target);

    Fighter *GetPlayer() const;

    void SetPlayer(Fighter *player);

    float GetWorryPortion() const;

    void SetWorryPortion(float worryPortion);

    float GetPanicPortion() const;

    void SetPanicPortion(float panicPortion);
};
#endif
