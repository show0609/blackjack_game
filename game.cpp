#include "game.h"

Game::Game():decki(0),deckj(0){
    setPlayer();
    setCard();
    shuffle();
}

// set players
void Game::setPlayer(){
    int bankroll,i=0;
    string name,type,input;

    // get the number of players and check the format is correct or not
    cout << "Please enter the number of player: ";
    cin >> input;
    while(!isNonNegInt(input)){
        cout << "Please enter a non-negative integer: ";
        cin >> input;
    }
    playerNum=stoi(input);
    
    // get information of players and set up
    while(i<playerNum){
        
        cout << "Please enter the information of player " << i+1 << endl;

        // get the type of player and check the format is correct or not
        cout << "Type (H or M or R): ";
        cin >> type;
        while(type != "M" && type != "H" && type != "R"){
            cout << "Please enter the correct format (H or M or R): ";
            cin >> type;
        }

        // get name
        cout << "Name: ";
        cin >> name;

        // get bankroll and check the format is correct or not (integer) 
        cout << "Bankroll: ";
        cin >> input;
        while(!isInt(input)){
            cout << "Please enter an integer: ";
            cin >> input;
        }
        bankroll=stoi(input);

        // create object and add to vector
        if(type == "H"){
            players.push_back(new Human(name,bankroll));
        }
        else if(type == "M"){
            players.push_back(new Meek(name,bankroll));
        }
        else if(type == "R"){
            players.push_back(new Random(name,bankroll));
        }
        i++;
    }
    cout << endl;
    
    // add dealer to players
    players.push_back(new Dealer());
}

// create cards
void Game::setCard(){
    deckNum=(playerNum+4)/4;
    deck=new Deck[deckNum];
    for(int i=0; i<deckNum; i++){
        for(int j=0; j<52; j++){
            deck[i][j].set((j/4)+1,j%4);
        }
    }
}

// shuffle
void Game::shuffle(){
    Card test;
    srand(time(NULL));
    for(int i=0; i<deckNum; i++){
        for(int j=0; j<52; j++){
            int x=rand()%deckNum;
            int y=rand()%52;
            deck[i][j].swap(deck[x][y]);
        }
    }
}

void Game::drawCard(Player *&player){
    player->drawCard(deck[decki][deckj]);
    deckj++;
    if(deckj == 52){
        decki++;
        deckj=0;
    }
}

// run the game
void Game::run(){
    
    // init: clear cards, point, cntA 
    for(Player *player : players){
        player->init();
    }

    // run out of cards
    int remainCardNum=(deckNum-1-decki)*52 + 51-deckj;
    if(remainCardNum < (playerNum+1)*5){
        shuffle();
        decki=deckj=0;
    }

    setBet();
    startCard();
    turn();
    result();
    standing();
}

void Game::setBet(){
    // information
    cout << "Okay, time for betting!" << endl;
    cout << "--------------------------------" << endl;

    // set bet
    for(Player *player : players){
        player->straBet();
    }

    // print bet for every player (no dealer)
    for(int i=0; i<playerNum; i++){
        // not join 
        if(players[i]->getBet() == 0){
            cout << players[i]->getName() << " doesn't join this round" << endl;
        }
        // join
        else{
            cout << players[i]->getName() << " bets $" << players[i]->getBet() << endl;
        }
    }

    cout << endl;
}

void Game::startCard(){
    // information
    cout << "The initial starting cards are:" << endl;
    cout << "--------------------------------" << endl;
    
    for(Player *player : players){
        
        // not join 
        if(player->getBet() == 0){
            continue;
        }
        // give two cards (one face down and one face up)
        for(int i=0; i<2; i++){
            drawCard(player);
        }
        cout << player->getName() << "'s current hand: [??][";
        cout << (player->getCard(1)).toString() << "]" << endl;
    }
    cout << endl;
}

void Game::turn(){
    for(Player *player : players){

        // not join 
        if(player->getBet() == 0){
            continue;
        }

        int cardNum=2;
        
        // information
        cout << player->getName() << "'s turn:" << endl;
        cout << "--------------------------------" << endl;

        while(1){

            // print current card
            cout << player->getName() << "'s current hand:";
            for(int j=0; j<cardNum; j++){
                cout << "[" + (player->getCard(j)).toString() + "]";                
            }
            
            // print possible point
            int *point=player->getPoint();
            cout << " (" << point[0];
            for(int i=1; i<5; i++){
                if(point[i] != 0){
                    cout << " or " << point[i];
                }
            }
            cout << " point)" << endl;

            // bust (end the turn / exit the loop)
            if(point[0] > 21){
                cout << player->getName() << " busted at " << point[0] << " !" << endl;
                player->setResult(0);
                break;
            }

            // 5-card (end the turn / exit the loop)
            if(cardNum == 5){
               cout << player->getName() << " collect five cards!" << endl;
                player->setResult(22);
                break;
            }
            
            // draw
            if(player->straDraw()){
                cout << player->getName() << " chooses to draw." << endl;
                drawCard(player);
                cardNum++;
            }
            // stay (end the turn / exit the loop)
            else{
                cout << player->getName() << " chooses to stay." << endl;

                // largest number ( <= 21 )
                for(int i=0; i<5; i++){
                    if(point[i] <= 21 && point[i] != 0){
                        player->setResult(point[i]);
                    }
                }
                break;
            }
        }
        cout << endl;
    }
}

void Game::result(){
    int moneyPlayer,moneyDealer;  // new bankroll of player and dealer
    bool win;

    // information
    cout << "Let's see how it turned out:" << endl;
    cout << "--------------------------------" << endl;

    // print the result
    for(int i=0; i<playerNum; i++){
        
        // not join 
        if(players[i]->getBet() == 0){
            continue;
        }

        // win (index playerNum is dealer)
        if(players[i]->getResult() > players[playerNum]->getResult()){
            cout << "Yowzah! " << players[i]->getName() << " wins $" << players[i]->getBet() << endl;
            
            // new bankroll
            moneyPlayer=players[i]->getBankroll() + players[i]->getBet();
            moneyDealer=players[playerNum]->getBankroll() - players[i]->getBet();

            win=true;
        }

        // lose and tie
        else{
            cout << "Ouch! " << players[i]->getName() << " loses $" << players[i]->getBet() << endl;
            
            // new bankroll
            moneyPlayer=players[i]->getBankroll() - players[i]->getBet();
            moneyDealer=players[playerNum]->getBankroll() + players[i]->getBet();
                                    
            win=false;

        }

        // update bankroll
        players[i]->setBankroll(moneyPlayer);
        players[playerNum]->setBankroll(moneyDealer);

        // if the player is meek need to set win and bust
        if((typeid(*players[i]) == typeid(Meek))){
            if(players[i]->getResult() == 0){  // bust
                static_cast<Meek*>(players[i])->update(win,1);  
            }
            else{
                static_cast<Meek*>(players[i])->update(win,0);  
            }
        }
    }
    cout << endl;
}

void Game::standing(){
    //information
    cout << "The standings so far:" << endl;
    cout << "--------------------------------" << endl;

    // print bankroll
    for(Player *player : players){
        cout << player->getName() << " $" << player->getBankroll() << endl;
    }
    cout << endl;
}
