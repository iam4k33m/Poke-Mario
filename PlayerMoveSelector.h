#ifndef PLAYERMOVESELECT
#define PLAYERMOVESELECT
#include "Typedefs.h"
#include <string>
class Fighter;
class PlayerMoveSelector
{
private:
	std::string _inputBuffer;
	Fighter* _player;
	uint32 _moveID;
	
public:
	PlayerMoveSelector();
	~PlayerMoveSelector();
	std::string PlayerAttack(Fighter* target);

    Fighter *GetPlayer() const;

    void SetPlayer(Fighter *player);
};
#endif
