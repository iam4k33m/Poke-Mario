//
// Created by Akeem.McKenzie.ADM on 24/09/2019.
//

#ifndef UNTITLED_FIGHTER_H
#define UNTITLED_FIGHTER_H


#include "Typedefs.h"
#include <vector>
#include <string>

/*
 * Fighter class.
 * Contains basics for all fighters.
 */

void InitializeStatusDamage();
class Move;
enum class FighterStatus
{
    Healthy,
    Grabbed,
    Paralyzed,
    Poisoned,
    Burned,
    Frozen,
    Crushed,
    Confused
};


class Fighter
        {
        protected:
				//Attack on this turn?
				bool _missedTurn;
                //Name, displayed by the game
                std::string _name;
				//Attack string, space to put the "x used y! text for each move used by the fighter
				std::string _moveCache;
				std::vector < std::string> _lineBuffer;
				bool _dirtyBuffer;
                //Status
                FighterStatus _status;
                //Status duration, in turns
                uint32 _statusClock;
                //Health, if this gets to zero they faint
                uint32 _health;
                //Attack, damage is multiplied by this
                float _attack;
                //Defense, damage is divided by this
                float _defense;
                //Speed, determines who goes first
                float _speed;
                //Accuracy, determines miss rate. Moves with an accuracy of 1.0f never miss, and aren't calculated
                float _missRate;
                //Vector of attacks
                std::vector<Move*> _moves;
				//Stat change event, puts "<Name>'s <stat> rose/fell." in buffer.
				void OnStatChange(float assigned, float old, const std::string& name);
				//Status change event, puts "<Name> was <status text>!" in buffer.
				void OnStatusChange(FighterStatus _status);
				//Damage tick for status
				
        public:
            //Constructor
            Fighter();
            //Destructor
            virtual ~Fighter();
            //Getter and setter for Name
            void SetName(const std::string& name);
            const std::string& GetName();
            //Getter and setter for health
            void SetHealth(uint32 health);
            uint32 GetHealth()const;
            //Getter and setter for Attack
            void SetAttack(float attack);
            float GetAttack()const;
            //Getter and setter for defense
            void SetDefense(float defense);
            float GetDefense()const;
            //Getter and setter for speed
            void SetSpeed(float speed);
            float GetSpeed()const;
            //Getter and setter for missRate
            void SetMissRate(float missRate);
            float GetMissRate()const;
            //Getter and setter for moves
            const std::vector<Move*>& GetMoves() const;
            void SetMoves(const std::vector<Move*> &moves);

            //Use move. The ai, or player input goes through this function. If an invalid move is chosen it will not be used.
            std::string Attack(uint32 move, Fighter& target);
            //Take damage, taking stats into account
            void TakeHit(float damage);
			void OnStatusStay();
			//Update the status, clear the buffer
			void Update();
			//Get a line of buffer text
			std::vector < std::string>* GetBufferLine();

    FighterStatus GetStatus() const;

    void SetStatus(FighterStatus status);

    uint32 GetStatusClock() const;

    void SetStatusClock(uint32 statusClock);

    const std::string &GetMoveCache() const;
};

#endif //UNTITLED_FIGHTER_H
