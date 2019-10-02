#ifndef CHARGE
#define CHARGE
#include "Move.h"
#include "Fighter.h"
class Charge : public Move
{
public:
	Charge();
	virtual void Evaluate(Fighter* user, Fighter* target)override;
};

#endif // CHARGE
