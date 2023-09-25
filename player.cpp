#include "player.h"

// constructor
Player::Player(string name,int bankroll):name(name),bankroll(bankroll){
    init();
}

Human::Human(string name,int bankroll):Player(name,bankroll){}

Meek::Meek(string name,int bankroll):Player(name,bankroll){
    win=bust=0;
    bet=2;
}

Random::Random(string name,int bankroll):Player(name,bankroll){
    srand(time(NULL));
}

Dealer::Dealer():Player("Dealer",10000){
    bet=-1;  // doesn't need bet 
}

// set function
void Player::setResult(int state){
    result=state;
}

void Player::setBankroll(int money){
    bankroll=money;
}

// get function
int Player::getBet(){
    return bet;
}

int Player::getResult(){
    return result;
}

int Player::getBankroll(){
    return bankroll;
}

int *Player::getPoint(){
    return point;
}

string Player::getName(){
    return name;
}

Card Player::getCard(int i){
    return cards[i];
}

// back to the original state (clear)
void Player::init(){
    cards.clear();
    for(int i=0; i<10; i++){
        point[i]=0;
    }
    cntA=0;
}

// draw a new card (add to cards) and compute point
void Player::drawCard(Card &card){
    // add to cards
    cards.push_back(card);
    point[0] += card.getValue();
    if(card.getValue() == 1){
        cntA += 1;
    }
    // compute point
    for(int i=1; i<=cntA; i++){
        point[i]=point[i-1]+10;
    }
}

// strategy for how much to bet
void Human::straBet(){
    string input;
    cout << name << ", how much would you like to bet? ";
    cin >> input;
    while(!isNonNegInt(input)){
        cout << "Please enter a non-negative integer: ";
        cin >> input;
    }
    bet=stoi(input);
}

void Meek::straBet(){
    // first bust (back to $2)
    if(bust == 1){
        bet = 2;
        bust++;
    }
    // win 3 rounds in a row (double the bet)
    if(win == 3){
        bet *= 2;
        win=0;
    }
}

void Random::straBet(){
    // if bankroll is less than 2, bet should be zero
    if(bankroll < 2){
        bet=0;
    }
    // between $1 and half of bankroll
    else{
        bet=rand()%(bankroll/2)+1;
    }
}

void Dealer::straBet(){
    // nothing
}

// strategy for draw(return true) or not(return false)
bool Human::straDraw(){
    string input;
    cout << "Would you like to draw another card (Y or N): ";
    cin >> input;
    while(input != "Y" && input != "N"){
        cout << "Please enter Y or N: ";
        cin >> input;
    }
    if(input == "Y"){
        return true;
    }
    return false;
}

bool Meek::straDraw(){
    // have seven club: draw
    for(Card card : cards){
        if(card.toString() == "7C"){
            return true;
        }
    }
    // even: draw
    if(point[0]%2 == 0){
        return true;
    }
    // odd: stay
    return false;
}

bool Random::straDraw(){
    int prob=rand()%10;

    // 0~9: 100%
    if(point[0] <= 9){
        return true;
    }
    // 10~12: 80%
    else if(point[0] <= 12){
        if(prob < 8){
            return true;
        }
    }
    // 13~15: 70%
    else if(point[0] <= 15){
        if(prob < 7){
            return true;
        }
    }
    // 16~18: 50%
    else if(point[0] <= 18){
        if(prob < 5){
            return true;
        }
    }
    // 19~: 0%
    return false;
}

bool Dealer::straDraw(){
    if(point[0] <= 16){
        return true;
    }
    return false;
}

// update win and bust (Meek)
void Meek::update(bool win,bool bust){
    if(win){
        this->win++;
    }
    else{
        this->win=0;
    }

    if(bust){
        this->bust++;
    }
}

// check the input string is integer or not
bool isInt(string input){
    int len=input.length();
    if(input[0] != '-' && !isdigit(input[0])){
        return false;
    }
    return isNonNegInt(input.substr(1,len));
}

// check the input string is non-negative integer or not
bool isNonNegInt(string input){
    int len=input.length();
    for(int i=0; i<len; i++){
        if(!isdigit(input[i])){
            return false;
        }
    }
    return true;
}
