//
// Created by S17118281 on 25/09/2019.
//

#ifndef UNTITLED_GRAB_H
#define UNTITLED_GRAB_H
#include "Move.h"
class Grab : public Move
        {
        public:
            Grab();
            virtual void Evaluate(Fighter* user, Fighter* target)override;
        };
#endif //UNTITLED_GRAB_H
