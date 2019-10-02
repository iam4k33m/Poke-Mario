#ifndef POWERSHELL
#define POWERSHELL
#include "Move.h"
class PowerShell : public Move
{
public:
	PowerShell();
	~PowerShell();
	virtual void Evaluate(Fighter* user, Fighter* target)override;
};
#endif
