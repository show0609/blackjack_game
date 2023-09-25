#ifndef PLAYER
#define PLAYER
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include "card.h"
using namespace std;

// base class
class Player{
    protected:
        string name;
        int bankroll;
        int bet;
        int point[10];        // possible point
        int cntA;             // count of A
        int result;           // 0: bust, 1-21: point, 22: 5-card
        vector<Card> cards;
    
    public:
        // constructor      
        Player(string name,int bankroll);

        // set function
        void setResult(int state);
        void setBankroll(int money);

        // get function
        int getBet();
        int getResult();
        int getBankroll();
        int *getPoint();
        string getName();
        Card getCard(int i);        // get the card of index i

        // other member function
        void init();                // clear cards, point, canA
        void drawCard(Card &card);  // draw a new card (add to cards) and compute point
        virtual void straBet()=0;   // strategy for how much to bet
        virtual bool straDraw()=0;  // strategy for draw(return true) or not(return false)
};

// derived class (inherited from Player)
class Human: public Player{
    public:
        Human(string name,int bankroll);
        void straBet()override;
        bool straDraw()override;
};

class Meek: public Player{
    private:
        int win;        // record win how many rounds in a row
        int bust;       // record bust how many times 
    public:
        Meek(string name,int bankroll);
        void update(bool win,bool bust);  // update win and bust
        void straBet()override;
        bool straDraw()override;
};

class Random: public Player{
    public:
        Random(string name,int bankroll);
        void straBet()override;
        bool straDraw()override;
};

class Dealer: public Player{
    public:
        Dealer();
        void straBet()override;
        bool straDraw()override;
};

bool isInt(string);
bool isNonNegInt(string);

#endif
