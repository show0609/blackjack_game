#ifndef CARD
#define CARD
#include <iostream>
using namespace std;

class Card{
    private:
        int rank;     // rank of card
        int value;    // value in this game
        int kind;     // spade, heart, diamond, club
        enum suit{spade, heart, diamond, club};
    public:
        void set(int rank,int kind);
        void swap(Card &x);     // swap card (shuffle)
        int getValue();         // get value
        string toString();      // turn rank and kind to string (ex:1S)
};

typedef Card Deck[52]; // a deck

#endif
