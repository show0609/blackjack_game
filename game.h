#ifndef GAME
#define GAME
#include <iostream>
#include <vector>
#include <time.h>
#include <typeinfo>
#include "player.h"
#include "card.h"
using namespace std;

class Game{
    
    private:
        int playerNum;
        int deckNum;
        int decki,deckj;   // record which card was dealt
        Deck *deck;
        vector<Player*> players;
    public:
        // setting for the game
        Game();
        void setPlayer();
        void setCard();        
        void shuffle();
        void drawCard(Player *&players);

        // run the game
        void run();
        void setBet();
        void startCard();
        void turn();
        void result();
        void standing();
};

#endif
