//
//  BSImplementation.cpp
//  JohnnyyGames
//
//  Created by Jonathan Garcia on 1/17/18.
//  Copyright © 2018 Jonathan Garcia. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <stack>
#include <sstream>
#include "BattleSimulator.h"

using namespace std;

//custructor to create a new Player object
//the string passed will be the name of the player
//the integer passed will be the number of lifepoints that the player stars with
Player::Player(string g, int l){
    playerName = g;
    lifepoints = l;
}

//used to obtain the name of a player
string Player::getPlayerName() const {
    return playerName;
}

//used to obtain the lifepoints of a player
int Player::getLifepoints() const {
    return lifepoints;
}

//set the lifepoints equal to the number passed in the parameter
//this will be used to set lifepoints equal to zero when they become negative
void Player::setLifepoints(int l){
    lifepoints = l;
}

//this function will serve to increase or decrease lifepoints during the match
//the symbol determines whether it will be an increase or decrease
//the integer will determine how many lifepoints to increase or decrease by
void Player::adjustLifepoints(char symbol, int changeInLifepoints){
    if (symbol == '+')                  //'+' will increase lifepoints
        lifepoints+= changeInLifepoints;
    else if (symbol == '-')             //'-' will decrease lifepoints
        lifepoints -= changeInLifepoints;
    else
        cout << "ERROR" << endl;
}

//the overloaded = operator will allow objects to be set equal to each other
//this function will e useful to determine the winner of the match
Player& Player::operator =(const Player& obj){
    playerName = obj.playerName;    //copy the name of the player into a new object
    lifepoints = obj.lifepoints;    //copy the number of lifepoints into a new object
    return *this;
}

//the overloaded << operator will allow the user to use
//"cout" to output the contents of the object.

ostream& operator <<(ostream& out, const Player& obj){
    out << obj.playerName << setw(10) << obj.lifepoints << endl;
    
    return out;
}

//prints out a message with the name of the winner of the match.
void printWinnerMessage(const Player& obj){
    cout << obj.getPlayerName() << " Wins!" << endl;
    cout << endl;
}

//print the possible actions that can be conducted by the program.
void printMenu(){
    
    cout << "1: New Game " << setw(50) << "2: Check Wins/Losses" << endl;
    cout << "3: Add New Player" << setw(57) << "4: Delete a Player From the List" << endl;
    cout << "5: View List of Players" << setw(34) <<  "6: Quit Program" << endl;
    
}

//the menu of possible actions will be displayed to the user.
void menuChoices(int choice){
    switch(choice){
        case 1:
            try{
                newGame();
                break;
            } catch (string str){
                cout << "***********************WARNING***********************" << endl;
                cout << str << endl;
                cout << "***********************WARNING***********************" << endl;
                cout << endl;
                break;
            }
        case 2: winsAndLosses();
            break;
        case 3: addNewPlayerToRoster();
            break;
        case 4: deletePlayerFromRoster();
            break;
        case 5: printPlayerList();
            break;
        case 6: cout << "*************************" << endl;
                cout << "   THANKS FOR PLAYING!   " << endl;
                cout << "*************************" << endl;
                cout << endl;
                cin.get();
            exit(0); //exit from main and not a function. maybe throw exit and have main catch it?
            
    }
}

//check for duplicates throw error if already exists
void addNewPlayerToRoster(){
    cout << "******************************" << endl;
    cout << "   CREATING A NEW CHARACTER    " << endl;
    cout << "******************************" << endl;
    cout << endl;
    
    string player;
    int wins = 0, losses = 0;
    bool checkListForPlayer;
    
    //code a part to state that success of a new character creation
    cout << "Enter new player: ";
    getline(cin, player);
    
    checkListForPlayer = playerExists(player);
    if (checkListForPlayer == true){
        cout << "This player already exists" << endl;
        cout << endl;
        return;
    }
    
    ofstream outfile("playerlist.txt", ios::app);
    outfile << endl;
    outfile << player << "  " << wins << "  " << losses;
    outfile.close();
    
    cout << player << " has successfully been added to the roster " << endl;
    cout << endl;
}

//will return the winner of the match
Player getWinner(const Player& playerOne, const Player& playerTwo){
    Player winner;
    
    if (playerOne.getLifepoints() <= 0)
        winner = playerTwo;
    else
        winner = playerOne;
    
    return winner;
}

//will return the loser of the match
Player getLoser(const Player& playerOne, const Player& playerTwo){
    Player loser;
    
    if (playerOne.getLifepoints() <= 0)
        loser = playerOne;
    else
        loser = playerTwo;
    
    return loser;
}

//will start up a new gamw between two players
void newGame(){
    if (!checkRoster()){
        throw string ("Roster does not have enough players to starts a duel. \nMinimum players required: 2");
        return;
    }
    
    //print out a message indicating the start of the match
    cout << "**********************************" << endl;
    cout << "   A NEW GAME IS ABOUT TO BEGIN    " << endl;
    cout << "**********************************" << endl;
    cout << endl;

    int changeInLifepoints;
    char symbol;
    Player playerOne, playerTwo;
    Player winner, loser;
    
    //create a variable named player number to see
    //how many players to input in case of more than
    //2 players playing

    playerOne = createPlayer(1);
    playerTwo = createPlayer(2);
    
    //displays a warning if both player 1 and player 2 are the same player
    if(playerOne.getPlayerName() == playerTwo.getPlayerName()){
        cout << endl;
        cout << "***********************WARNING***********************" << endl;
        cout << "   PLAYER 1 AND PLAYER 2 CANNOT BE THE SAME PLAYER   " << endl;
        cout << "***********************WARNING***********************" << endl;
        cout << endl;
        return;
    }
    
    //diceRoll is called to determine who goes first and who goes second
    diceRoll (playerOne, playerTwo);
    
    //play through the match, adjusting each player's lifepoints until there is a winner and a loser
    while (true) {
        cout << playerOne.getPlayerName() << ": ";
        cin >> symbol >> changeInLifepoints;
        playerOne.adjustLifepoints(symbol,changeInLifepoints);
        if (playerOne.getLifepoints() < 1)
            zeroLifepoints(playerOne);
        cout << "Lifepoints: " << playerOne.getLifepoints() << endl;
        cout << endl;
        if (playerOne.getLifepoints() == 0)
            break;
        
        cout << playerTwo.getPlayerName() << ": ";
        cin >> symbol >> changeInLifepoints;
        playerTwo.adjustLifepoints(symbol,changeInLifepoints);
        if (playerTwo.getLifepoints() < 1)
            zeroLifepoints(playerTwo);
        cout << "Lifepoints: " << playerTwo.getLifepoints() << endl;
        cout << endl;
        if (playerTwo.getLifepoints() == 0)
            break;
    }
    
    //determine winner and loser
    winner = getWinner(playerOne, playerTwo);
    loser = getLoser(playerOne, playerTwo);
    
    //print a message stating who the winner is
    printWinnerMessage(winner);
    
    //add a win and a lose to the respective players
    addWin(winner);
    addLoss(loser);
}

//prepares a player from the roster to duel in a match
Player createPlayer(int playerNumber){
    string nameOfPlayer;
    bool inRoster;
    cout << "Player" << playerNumber << ": ";
    getline(cin, nameOfPlayer);
    
    //checks if the player is registered in the roster
    inRoster = playerIsInRoster(nameOfPlayer);
    
    //if they are not, then a registered player must be entered
    while(inRoster == false){
        cout << nameOfPlayer << " is not in the roster." << endl;
        cout << "Please enter a name that is currently in the player roster: ";
        getline(cin, nameOfPlayer);
        inRoster = playerIsInRoster(nameOfPlayer);
    }
    
    //player from the roster is created and given 8000 lifepoints
    Player newPlayer(nameOfPlayer, 8000);
    
    return newPlayer;
}

//print the roster of players
void printPlayerList(){
    cout << "*******************" << endl;
    cout << "   PLAYER ROSTER   " << endl;
    cout << "*******************" << endl;
    
    string nameOfPlayer;
    
    //open the file from where we will get the player roster
    ifstream myfile;
    myfile.open("playerlist.txt");
    
    //display each player in the roster
    while(!myfile.eof()){
        getline(myfile, nameOfPlayer);
        cout << nameOfPlayer << endl;
    }
    
    //close the file that contains the player roster
    myfile.close();
    
    cout << endl;
}

//deletes a player from the roster
void deletePlayerFromRoster(){
    cout << "*********************" << endl;
    cout << "   DELETING PLAYER   " << endl;
    cout << "*********************" << endl;
    cout << endl;
    
    //if the roster is empty, display a warning sign
    if(checkRosterEmpty()){
        cout << "*********WARNING*********" << endl;
        cout << "   THE ROSTER IS EMPTY   " << endl;
        cout << "*********WARNING*********" << endl;
        cout << endl;
        return;
    }

    string playerName, playerToDelete;
    string certainty;
    stack<string> namesOfCurrentPlayers, bottomToTop;
    stack<int> winsAndLosses, bottomToTop2;
    int wins, losses;
    
    //user enters the name of the player they would like to delete
    cout << "Please enter the name of the player that you would";
    cout << " like to delete or \"return\" to return to the main menu: ";
    getline(cin, playerToDelete);
    
    //if the user types "return" they will return to the main menu
    if(playerToDelete == "return")
        return;
    
    //continue asking for a valid player name until
    //one is entered or the user enters "return"
    while(!playerExists(playerToDelete)){
        cout << playerToDelete << " is not on the roster." << endl;
        cout << "Enter a valid name or \"return\" to return to the main menu: ";
        getline(cin, playerToDelete);
        if(playerToDelete == "return")
            return;
    }
    
    //a warning message to the user is displayed
    cout << "*************WARNING*************" << endl;
    cout << playerToDelete << " will be permanently deleted!" << endl;
    cout << "*************WARNING*************" << endl;
    
    //asks for certainty on deleting the player
    cout << "Would you like to contiue?" << endl;
    cout<< "(y): yes" << setw(15) << "(n): no" << endl;
    getline(cin, certainty);

    //continue asking until a valid answer, "y" or "n", is given
    while (certainty != "y" && certainty != "n"){
        cout << "Please enter a valid answer (y) or (n): ";
        getline(cin, certainty);
    }
    
    //if the user decides NOT to delete the player,
    //they are taken back to the main menu
    if (certainty == "n")
        return;
    
    //otherwise, adjust the player roster
    //the deleted player will no longer be in the roster
    ifstream infile;
    ofstream outfile;
    infile.open("playerlist.txt");                  //the file to read the roster from
    outfile.open("tempfile.txt");                   //the file to write the new roster to
    while (!infile.eof()) {
        infile >> playerName >> wins >> losses;     //read the player name, wins, and losses,
        if (playerName != playerToDelete){
            namesOfCurrentPlayers.push(playerName); //add the player names to the namesOfPlayers stack
            winsAndLosses.push(wins);               //wins will be added to the winsAndLosses stack
            winsAndLosses.push(losses);             //losses will also be added to the winsAndLosses stack
        }                                           //winsAndLosses alternates: p1-wins,p1-losses,p2-wins...
    }

    //if there is only one name in the roster then the new roster is a blank file
    if(namesOfCurrentPlayers.empty() && winsAndLosses.empty()){
        remove("playerlist.txt");
        rename("tempfile.txt", "playerlist.txt");
        
        cout << playerToDelete << " has been removed from the roster." << endl;
        cout << endl;
        
        return;
    }
    
    //otherwise, reverse the stacks to maintain the same roster order
    while(!namesOfCurrentPlayers.empty() && !winsAndLosses.empty()){
        bottomToTop.push(namesOfCurrentPlayers.top());
        namesOfCurrentPlayers.pop();
        bottomToTop2.push(winsAndLosses.top());
        winsAndLosses.pop();
        bottomToTop2.push(winsAndLosses.top());
        winsAndLosses.pop();
    }
    
    //write the new roster to the file
    for(int i = bottomToTop.size(); i > 1; i--) {
        outfile << bottomToTop.top() << "   " << bottomToTop2.top() << "    ";
        bottomToTop2.pop();
        outfile << bottomToTop2.top();
        bottomToTop2.pop();
        bottomToTop.pop();
        outfile << endl;
    }
    
    //write the last player to the new roster file
    outfile << bottomToTop.top() << "   " << bottomToTop2.top() << "    ";
    bottomToTop2.pop();
    outfile << bottomToTop2.top();
    bottomToTop2.pop();
    bottomToTop.pop();
    
    //close both files
    //the one that was read from and the one that was written to
    infile.close();
    outfile.close();
    
    //delete the old roster and rename the new one
    remove("playerlist.txt");
    rename("tempfile.txt", "playerlist.txt");
    
    //let the user know that the deletion was a success
    cout << playerToDelete << " has been removed from the roster." << endl;
    cout << endl;
}

//the dice roll will determine who goes first and who goes second
void diceRoll (Player& playerOne, Player& playerTwo){
    string guessOne, guessTwo;
    srand(time(NULL));
    int roll = rand() % 6 + 1;  //generates a random number between 1 and 6
    string firstOrSecond;
    int numGuessOne = 0;
    int numGuessTwo = 0;
    
    do{
        cout << playerOne.getPlayerName() << " pick a number: ";
        getline(cin,guessOne);
        while(guessOne.length() > 1 || (guessOne != "1" && guessOne != "2" && guessOne != "3" && guessOne != "4" && guessOne != "5" && guessOne != "6")){
            cout << playerOne.getPlayerName() << " pick a valid number (1-6): ";
            getline(cin, guessOne);
        }
        stringstream numOne(guessOne);
        numOne >> numGuessOne;          //turns the string version of the dice guess into and int for player 1
        
        cout << playerTwo.getPlayerName() << " pick another number: ";
        getline(cin, guessTwo);
        while(guessTwo.length() > 1 || (guessTwo != "1" && guessTwo != "2" && guessTwo != "3" && guessTwo != "4" && guessTwo != "5" && guessTwo != "6")){
            cout << playerTwo.getPlayerName() << " pick a valid number (1-6): ";
            getline(cin, guessTwo);
        }
        while (guessTwo == guessOne){
            cout << "Pick another number: ";
            getline(cin, guessTwo);
            while(guessTwo.length() > 1 || (guessTwo != "1" && guessTwo != "2" && guessTwo != "3" && guessTwo != "4" && guessTwo != "5" && guessTwo != "6")){
                cout << playerOne.getPlayerName() << " pick a valid number (1-6): ";
                getline(cin, guessOne);
            }
        }
        stringstream numTwo(guessTwo);
        numTwo >> numGuessTwo;          //turns the string version of the dice guess into and int for player 2
        
    } while (numGuessOne != roll && numGuessTwo != roll);
    
    //if player 1 correctly guesses the dice roll, allow them to pick if they want to go first or second
    if (numGuessOne == roll){
        do{
            cout << playerOne.getPlayerName() << ", would you like to go first or second" << endl;
            getline(cin, firstOrSecond);
            if (firstOrSecond == "second"){                     //if player 1 wants to go second, then
                switchPlayerPositions(playerOne, playerTwo);    //switch the positions of the two players
                break;
            }
            else if (firstOrSecond == "first")                  //else continue as normal
                break;
            //if neither "first" nor "second" is entered, then ask for a valid choice
            else if (firstOrSecond != "first" || firstOrSecond != "second")
                cout << "Please type \"first\" to go first and \"second\" to go second" << endl;
        } while (firstOrSecond != "first" || firstOrSecond != "second");    //continue while choice is invalid
    }
    
    //if player 2 correctly guesses the dice roll, allow them to pick if they want to go first or second
    else if (numGuessTwo == roll){
        do{
            cout << playerTwo.getPlayerName() << ", would you like to go first or second" << endl;
            getline(cin, firstOrSecond);
            if (firstOrSecond == "first"){                      //if player 2 wants to go second, then
                switchPlayerPositions(playerOne, playerTwo);    //switch the positions of the two players
                return;
            }
            else if (firstOrSecond == "second")                 //else continue as normal
                break;
            //if neither "first" nor "second" is entered, then ask for a valid choice
            else if (firstOrSecond != "first" || firstOrSecond != "second")
                cout << "Please type \"first\" to go first and \"second\" to go second" << endl;
        } while (firstOrSecond != "first" || firstOrSecond != "second");    //continue while choice is invalid
    }
    
}

//switches the positions of the players. player 1 becomes player 2 and vise versa
void switchPlayerPositions(Player& playerOne, Player& playerTwo){
    Player tempPlayer = playerOne;
    playerOne = playerTwo;
    playerTwo = tempPlayer;
}

//if lifepoints drop below 0 then set them to 0
void zeroLifepoints(Player& playerOne){
    if (playerOne.getLifepoints() <= 0)
        playerOne.setLifepoints(0);
}

//checks if the player passed in the parameter exists in the player roster
bool playerExists(string newPlayer){
    string playerName;
    int wins, losses;
    
    ifstream myfile;
    myfile.open("playerlist.txt");
    
    while (myfile >> playerName >> wins >> losses)
        if (newPlayer == playerName)    //if one of the players in the roster matches the
            return true;                //name passed in the parameter, then return true
        
    myfile.close();
    return false;                       //if the name is not in the roster, then return false
}

//displays the wins and losses of a single player
void winsAndLosses(){
    cout << "*******************" << endl;
    cout << "   WINS / LOSSES   " << endl;
    cout << "*******************" << endl;
    cout << endl;
    
    //if the roster is empty, then a warning is displayed stating that the roster is empty
    if(checkRosterEmpty()){
        cout << "*********WARNING*********" << endl;
        cout << "   THE ROSTER IS EMPTY   " << endl;
        cout << "*********WARNING*********" << endl;
        cout << endl;
        return;
    }
    
    string playerName,tempPlayerName;
    int wins, losses;
    bool inRoster;
    
    //player is asked which player's wins and losses they would like to view
    cout << "What player's wins and losses would you like to view";
    cout << " or enter \"return\" to return to the main menu: ";
    getline(cin, playerName);
    if (playerName == "return"){    //if they type "return" then the player is returned to the main menu
        cout << endl;
        return;
    }
    
    //checks if the player is in the roster
    inRoster = playerIsInRoster(playerName);
    
    //if the player is not in the roster then ask for a valid
    //player or to type "return" to return to the main menu
    while(inRoster == false){
        cout << playerName << " is not in the roster." << endl;
        cout << "Please enter a name that is currently in the player";
        cout << " roster or enter \"return\" to return to main menu: ";
        getline(cin, playerName);
        if (playerName == "return"){    //if they type "return" then the player is returned to the main menu
            cout << endl;
            return;
        }
        //checks if the new player is in the roster
        inRoster = playerIsInRoster(playerName);
    }
    
    //search the roster for the player and display the player's name, wins, and losses
    ifstream infile;
    infile.open("playerlist.txt");
    while (!infile.eof()){
        infile >> tempPlayerName >> wins >> losses;
        if (tempPlayerName == playerName){
            cout << endl;
            cout << playerName << endl << "Wins: " << wins << endl <<"Losses: " << losses << endl;
            cout << endl;
            return;
        }
    }
}

void addWin(const Player& player){
    string playerName;
    stack<string> namesOfCurrentPlayers, bottomToTop;
    stack<int> winsAndLosses, bottomToTop2;
    int wins, losses;
    
    ifstream infile;
    ofstream outfile;
    infile.open("playerlist.txt");
    outfile.open("tempfile.txt");
    
    while (!infile.eof()) {
        infile >> playerName >> wins >> losses;
        if (playerName != player.getPlayerName()){
            namesOfCurrentPlayers.push(playerName);
            winsAndLosses.push(wins);
            winsAndLosses.push(losses);
        }
        else if (playerName == player.getPlayerName() /*&& !playerName.empty()*/){
            namesOfCurrentPlayers.push(playerName);
            winsAndLosses.push(wins+1);
            winsAndLosses.push(losses);
        }
    }
    
    while (!namesOfCurrentPlayers.empty() && !winsAndLosses.empty()){
        bottomToTop.push(namesOfCurrentPlayers.top());
        namesOfCurrentPlayers.pop();
        bottomToTop2.push(winsAndLosses.top());
        winsAndLosses.pop();
        bottomToTop2.push(winsAndLosses.top());
        winsAndLosses.pop();
    }
    
    for (int i = bottomToTop.size(); i > 1; i--) {
        outfile << bottomToTop.top() << "   " << bottomToTop2.top() << "    ";
        bottomToTop2.pop();
        outfile << bottomToTop2.top();
        bottomToTop2.pop();
        bottomToTop.pop();
        outfile << endl;
    }
    
    outfile << bottomToTop.top() << "   " << bottomToTop2.top() << "    ";
    bottomToTop2.pop();
    outfile << bottomToTop2.top();
    bottomToTop2.pop();
    bottomToTop.pop();
    
    infile.close();
    outfile.close();
    
    remove("playerlist.txt");
    rename("tempfile.txt", "playerlist.txt");
}

void addLoss(const Player& player){
    string playerName;
    stack<string> namesOfCurrentPlayers, bottomToTop;
    stack<int> winsAndLosses, bottomToTop2;
    int wins, losses;
    
    ifstream infile;
    ofstream outfile;
    infile.open("playerlist.txt");
    outfile.open("tempfile.txt");
    
    while(!infile.eof()) {
        infile >> playerName >> wins >> losses;
        if (playerName != player.getPlayerName()){
            namesOfCurrentPlayers.push(playerName);
            winsAndLosses.push(wins);
            winsAndLosses.push(losses);
        }
        else if (playerName == player.getPlayerName() /*&& !playerName.empty()*/){
            namesOfCurrentPlayers.push(playerName);
            winsAndLosses.push(wins);
            winsAndLosses.push(losses+1);
        }
    }
    
    while(!namesOfCurrentPlayers.empty() && !winsAndLosses.empty()){
        bottomToTop.push(namesOfCurrentPlayers.top());
        namesOfCurrentPlayers.pop();
        bottomToTop2.push(winsAndLosses.top());
        winsAndLosses.pop();
        bottomToTop2.push(winsAndLosses.top());
        winsAndLosses.pop();
    }
    
    for(int i = bottomToTop.size(); i > 1; i--) {
        outfile << bottomToTop.top() << "   " << bottomToTop2.top() << "    ";
        bottomToTop2.pop();
        outfile << bottomToTop2.top();
        bottomToTop2.pop();
        bottomToTop.pop();
        outfile << endl;
    }
    
    outfile << bottomToTop.top() << "   " << bottomToTop2.top() << "    ";
    bottomToTop2.pop();
    outfile << bottomToTop2.top();
    bottomToTop2.pop();
    bottomToTop.pop();
    
    infile.close();
    outfile.close();
    
    remove("playerlist.txt");
    rename("tempfile.txt", "playerlist.txt");
}
//might have to make this a template function to use it with a string and a player object
bool playerIsInRoster(string player){
    string playerName;
    int wins, losses;
    ifstream myfile;
    myfile.open("playerlist.txt");
    
    while(!myfile.eof()){
        myfile >> playerName >> wins >> losses;
        if(playerName == player){
            myfile.close();
            return true;
        }
    }
    
    myfile.close();
    
    return false;
}

//asks for code
void code(){
    string code = " ";
    int tries = 0;

    //continue asking for the code if the code is not correct or if tries has not exceeded 3
    while (code != "LYOKO"){
        if (tries == 3){
            tries++;
            break;
        }
        
        tries++;
        cout << "Code: ";
        getline(cin, code);
    }
    
    //if tries exceeded three, then an exception is thrown to display a message and terminate the program
    if (tries == 4)
        throw string ("Too many incorrect tries: PROGRAM TERMINATING");
    
    cout << endl;
    cout << "*******************************" << endl;
    cout << "       WELCOME DUELISTS        " << endl;
    cout << "*******************************" << endl;
    cout << endl;
}

//check that the roster has enough players registered to start a game
bool checkRoster(){
    stack<string> roster;
    string nameOfPlayer, wins, losses;
    
    ifstream myfile;
    myfile.open("playerlist.txt");
    
    //continue addind player names to the stack until the end of the file
    while(!myfile.eof()){
        myfile >> nameOfPlayer >> wins >> losses;
        roster.push(nameOfPlayer);
    }
    
    myfile.close();
    
    //if the stack has less than two names, then false is returned, otherwise true is returned
    if (roster.size() < 2)
        return false;
    return true;
}

//check to see if the roster is empty
bool checkRosterEmpty(){
    stack<string> roster;
    string line;
    
    ifstream myfile;
    myfile.open("playerlist.txt");
    
    //continue adding player information to the stack until the end of the file is reached
    while(!myfile.eof()){
        getline(myfile, line);
        roster.push(line);
    }
    
    myfile.close();
    
    //if the top of the stack is empty, then the roster is
    //empty and true is returned, otherwise false is returned
    if (roster.top() == "")
        return true;
    return false;
}

//get the player's choice in regards to the menu
int getChoice(){
    string strChoice;
    
    cout << endl;
    cout << "Choice: ";
    getline(cin, strChoice);
    //continues to ask for a valid choice while the choice is not 1-6 or if it is longer than one character
    while (strChoice.length() > 1 || (strChoice != "1" && strChoice != "2" && strChoice != "3" && strChoice != "4" && strChoice != "5" && strChoice !="6")){
        cout << "Please enter a valid choice: ";
        getline(cin, strChoice);
    }
    
    stringstream s(strChoice);
    int choice = 0;
    s >> choice;                //turns the string for the player's choice into an int
    
    cout << endl;
    
    return choice;              //the int version of the player's choice is returned
}
