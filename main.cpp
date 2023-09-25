#include <iostream>
#include "game.h"

using namespace std;

int main(){

    // play game
    string state="Y";
    Game game;

    while(state == "Y"){
        
        game.run();
        
        cout << "Another round? (Y or N): ";
        cin >> state;
        while(state != "Y" && state != "N"){
            cout << "Please enter Y or N: ";
            cin >> state;
        }

        cout << endl;
    }
    return 0;
}

