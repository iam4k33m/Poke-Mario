//
// Created by S17118281 on 25/09/2019.
//

#ifndef UNTITLED_GROUND_POUND_H
#define UNTITLED_GROUND_POUND_H
#include "Move.h"

class GroundPound : public Move
        {
        public:
            GroundPound();
            virtual void Evaluate(Fighter* user, Fighter* target)override;
        };
#endif //UNTITLED_GROUND_POUND_H
