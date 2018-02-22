//
//  BattleSimulator.cpp
//  JohnnyyGames
//
//  Created by Jonathan Garcia on 1/17/18.
//  Copyright © 2018 Jonathan Garcia. All rights reserved.
//

#ifndef BATTLESIMULATOR_H
#define BATTLESIMULATOR_H

#include <string>
#include <iomanip>


using namespace std;

//Player objects will each contain a name and a certain number of lifepoints
//By default, the name will be "CPU" and the lifepoints will be 8000
class Player{
private:
    string playerName;
    int lifepoints;
    
public:
    //constructor to create a new Player object
    Player(string g = " CPU" , int l = 8000);
    //return the name of the gamer
    string getPlayerName() const;
    //return the amount of lifepoints
    int getLifepoints() const;
    //set the amount of lifepoints to the given parameter
    void setLifepoints(int l);
    //add or subtract lifepoints
    // it takes a '+' or '-' symbol along with the amount of lipoints to increase or decrease
    void adjustLifepoints (char s, int l);
    //allows objects to be assigned to one another
    Player& operator =(const Player& obj);
    //<< operator to display the gamer object
    friend ostream& operator <<(ostream& out, const Player& p);
    
};

//print a message with the name of the winner
void printWinnerMessage(const Player& one);

//print the menu of available actions
void printMenu();

//takes an int parameter to determine what action to take
void menuChoices(int choice);

// add a new player to the roster
void addNewPlayerToRoster();

//takes two player objects as parameters to determine the winner of the match
Player getWinner(const Player& playerOne, const Player& playerTwo);

//takes two player objects as parameters to determine the loser of the match
Player getLoser(const Player& playerOne, const Player& playerTwo);

//conduct battle mode
void newGame();

//will create the players with the integer passed in the parameter
//for example: "Player1" or "Player2"
Player createPlayer(int playerNumber); // pass it an int 1 to show "player 1"

//prints the list of current players on file
void printPlayerList();

//delete a player from the current file
void deletePlayerFromRoster();

//roll a dice and ask players to guess what number is rolled in order
//to determine who goes first and who goes second
void diceRoll (Player& playerOne, Player& playerTwo);

//switch the positions of the players if Player2 decides to go first
void switchPlayerPositions(Player& playerOne, Player& playerTwo);

//make lifepoints equal to 0 if they become less than 1
//this is good for when lifepoints become neagtive
void zeroLifepoints(Player& playerOne);

/*checks the current list of players to see if the player
 the user is trying to add already exists within the list*/
bool playerExists(string playerToDelete);

//displays the number of wins and losses
void winsAndLosses();

//record a win for the winning player
void addWin(const Player& player);

//record a loss for the losing player
void addLoss(const Player& player);

//determines if the player passed in the parameter is
//currently in the roster of player
bool playerIsInRoster(string player);

//this function will require the user to enter the code
//to begin the program. If they get three incorrect tries,
//then the program will terminate
void code();

//checks that the roster has enough players to start a game
bool checkRoster();

//checks if the roster is empty
bool checkRosterEmpty();

//get the player's choice in regards to the menu
int getChoice();

#endif
