//
//  main.cpp
//  JohnnyyGames
//
//  Created by Jonathan Garcia on 1/17/18.
//  Copyright © 2018 Jonathan Garcia. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "BattleSimulator.h"

using namespace std;

int main(){
    //you can encapsulate the whole main code into the try code and use it to catch an error
    //in the UNFIXABLE problem in doing the lifepoints adjusments suring a player match
    try {
        code();
    } catch (string str) {
        cout << str << endl;
        return 1;
    }
    
    int choice;
    
    do {
        printMenu();
        choice = getChoice();
        menuChoices(choice);
    }
    while (choice != 6);
    
    return 0;
}

