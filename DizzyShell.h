#ifndef DizzyShell_h__
#define DizzyShell_h__
#include "Move.h"

class DizzyShell : public Move
{
public:
	DizzyShell();
	virtual void Evaluate(Fighter* user, Fighter* target)override;
};

#endif // DizzyShell_h__
