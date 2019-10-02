//
// Created by S17118281 on 25/09/2019.
//

#ifndef UNTITLED_MOVE_H
#define UNTITLED_MOVE_H
#include "Typedefs.h"
#include <string>
class Fighter;
//Move types. Normal moves usually lack a buff / debuff
//Defensive moves increase user defense/decrease enemy attack
//Offensive moves increase user attack/decrease enemy defense
enum class MoveType
        {
            Normal,
            Defensive,
            Offensive,
        };

class Move
        {
        protected:
            //Raw damage to deal, an integer
            uint32 _damage;
            //Damage to receive for using this move
            uint32 _knockBack;
            //Miss rate
            float _missRate;
            //Type of move
            MoveType _type;
            //Name of move
            std::string _name;

        public:
            //Constructor
            Move();
            //Destructor
            virtual ~Move();
            virtual void Evaluate(Fighter* user, Fighter* target);

    uint32 GetDamage() const;

    void SetDamage(uint32 damage);

    uint32 GetKnockBack() const;

    void SetKnockBack(uint32 knockBack);

    const std::string& GetName() const;

    float GetMissRate() const;

    void SetMissRate(float missRate);

    MoveType GetType();
};
#endif //UNTITLED_MOVE_H
