//
// Created by S17118281 on 25/09/2019.
//
#include "Mario.h"
#include "Jump.h"
#include "Kick.h"
#include "Ground Pound.h"
#include "Grab.h"
Mario::Mario() : Fighter()
{
    _name = "Mario";
    _health = 32;
    _missRate = 0.01f;
    _moves.push_back(new Jump());
    _moves.push_back(new Grab());
    _moves.push_back(new Kick());
    _moves.push_back(new GroundPound());

}
