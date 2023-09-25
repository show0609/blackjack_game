#include "card.h"

void Card::set(int rank,int kind){
    this->rank=rank;
    this->value=rank;
    this->kind=kind;
    if(rank > 10){
        this->value=10;
    }
}

// swap card (shuffle)
void Card::swap(Card &x){
    Card tmp=*this;
    *this=x;
    x=tmp;
}

int Card::getValue(){
    return value;
}         

// turn rank and kind to string (ex:1S)
string Card::toString(){
    string tmp=to_string(rank);
    if(kind == spade){
        tmp += 'S';
    }
    else if(kind == heart){
        tmp += 'H';
    }
    else if(kind == diamond){
        tmp += 'D';
    }
    else if(kind == club){
        tmp += 'C';
    }
    return tmp;
}
