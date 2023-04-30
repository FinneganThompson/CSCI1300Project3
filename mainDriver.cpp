/*
* mainDriver.cpp
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
* to run: g++ mainDriver.cpp item.cpp Monster.cpp Sorcerer.cpp party.cpp Map.cpp game.cpp RNG.cpp puzzles.cpp move.cpp
*
* the driver file for the game, and includes the base structers for the game
*/

#include "game.h"
#include "move.h"
#include <cassert>


/*
Algorithm enacts the first part of the game
Accepts a party object
Creates all the players (make sure the leader is indicated)
Ask the user to enter the names of the players and pass them to the player objects
Set all the players hunger to 50 and add them to the party object
Set the party's gold to 100
Explain what each thing that can be purchased does
Call the merchant menu function
*/

void beforeEntry(party &mainParty){
    // creates the player objects for the party
    player partyLeader, member1, member2, member3, member4;
    // indicates that the partyLeader player is the leader
    partyLeader.isUserPlayer = true;
    // set all the party members names to the user input
    cout << "Please enter names for you and your party:" << endl;
    cout << "Your name: ";
    cin >> partyLeader.name;
    cout << "Names for 4 more party members:" << endl;
    cin >> member1.name >> member2.name >> member3.name >> member4.name;
    cout << endl;
    // set all the player's hunger to 50
    partyLeader.hunger = 50;
    member1.hunger = 50;
    member2.hunger = 50;
    member3.hunger = 50;
    member4.hunger = 50;
    // add all the player members to the party
    mainParty.addPlayer(partyLeader);
    mainParty.addPlayer(member1);
    mainParty.addPlayer(member2);
    mainParty.addPlayer(member3);
    mainParty.addPlayer(member4);
    // set the party's gold to 100
    mainParty.partyInventory_.addGold(100);
    cout << "Between the 5 of you, you have 100 gold pieces.\nYou will need to spend the some of your money on the following items:\n" << endl;
    cout << "- INGREDIENTS. To make food, you have to cook raw ingredients." << endl <<
    "- COOKWARE. If you want to cook, you have to have cookware first." << endl << 
    "- WEAPONS. You'll want at least one weapon per party member to fend off monsters." << endl << 
    "- ARMOR. Armor increases the chances of surviving a monster attack.\n" << endl <<
    "You can spend all of your money here before you start your journey, or you can save some to spend on merchants along the way." << endl << 
    "But beware, some of the merchants in this dungeon are shady characters, and they won't always give you a fair price...\n" << endl;
    // print out and do the merchant menu
    merchantMenu(mainParty);
}


/*
Algorithm enacts the turns that happen through out the game until the game is over
Accepts a sorcerer, map, and party object
Declare a vector to hold all the monsters a player can fight
Read in all the monsters to that vector
Declare a bool to hold whether or not the game is over
Enter a loop that will keep going until the game is over
Each iteration of the loop the space that the party is on is checked and depending on what type of space it is, different type of turn options will apear
*/

void inDungeon(Sorcerer &gameSorcerer, Map &mainMap, party &mainParty){
    // creates and read in the monsters to the vector
    vector<Monster> monsters;
    readInMonsters(monsters, "monsters.txt");
    // holds whether or not the game is over
    bool gameOver = false;
    // loops as long as the game does not end
    while(gameOver == false){
        // check to see if any of the players are starving
        // vector hols all starving players
        vector<player> starvingPlayers = mainParty.starvingPlayers();
        // if there is at least one starving loop through all the starving party members and print out their names
        if(starvingPlayers.size() > 0){
            cout << "It may be a good idea to cook soon, your party has some players that are on the brink of starving:\n" << endl;
            for(int i = 0; i < starvingPlayers.size(); i++){
                cout << "\t" << starvingPlayers.at(i).name << endl;
            }
            cout << endl;
        }
        // print out the status update and display the map
        statusUpdate(mainParty,gameSorcerer);
        mainMap.displayMap();
        cout << endl;
        // check if the space is a room space
        if(mainMap.isRoomLocation(mainMap.getPlayerRow(),mainMap.getPlayerCol()) == true){ // room space
            roomSpace(mainMap, mainParty, gameSorcerer, gameOver, monsters);
        }
        // check if the space is a NPC space
        else if(mainMap.isNPCLocation(mainMap.getPlayerRow(),mainMap.getPlayerCol()) == true){ // NPC space
            npcSpace(mainMap, mainParty, gameSorcerer, gameOver, monsters);
        }
        // check if the space is the dungeon exit space
        else if(mainMap.isDungeonExit(mainMap.getPlayerRow(),mainMap.getPlayerCol())){ // exit space
            // check if the party has cleared all the rooms and if so wins the game and will exit 
            if(mainParty.getRoomsCleared() == 5){
                mainParty.winGame();
                gameOver = true;
                break;
            }
            // holds the user input for what they would like to do
            int spaceChoice = -1;
            // holds the options for what the user can do
            vector<string> moveOptions= {"Move","Give up"};
            // holds whether or not the user would like to proceed with the move choice
            char proceed = 'n';
            cout << "You have made it to the exit... However, you cannot leave without defeating all the monsters and the Sorcerer." << endl;
            // loop until the 
            while(proceed == 'n'){
                // print out the user's options
                cout << "Would you like to:\n1. " << moveOptions.at(0) << endl << "2. " << moveOptions.at(1) << "?\n" << endl;
                cin >> spaceChoice;
                cout << endl;
                // validate the user input
                if(spaceChoice != 1 && spaceChoice != 2){
                    cout << "I am not sure what you mean, please only pick one of the choices.\n" << endl;
                }
                else{ // if the input is valide
                    // resets the proceed variable so that the user's input can be validated
                    proceed = 'l';
                    // stay in the loop until the user enters valid input
                    while(proceed != 'y' && proceed != 'n'){
                        cout << "Are you sure you'd like to " << moveOptions.at(spaceChoice-1) << "? (y/n)\n" << endl;
                        cin >> proceed;
                        cout << endl;
                        // validate the user input
                        if(proceed != 'y' && proceed != 'n'){
                            cout << "What was that? I couldn't understand you, please only answer y or n.\n" << endl;
                        }
                    }
                }
            }
           
            switch(spaceChoice){
                case 1:{ // if the user would like to move
                    move(mainMap, mainParty, gameSorcerer);
                    break;
                }
                case 2:{ // if the user would like to give up
                    mainParty.loseGame(0);
                    gameOver = true;
                    break;
                }
            }
        }
        else{ // check if the space is a regular space
            normalSpace(mainMap, mainParty, gameSorcerer,gameOver, monsters);
        }
        // increase the count of turns that have been taken
        mainParty.incrementTurn();
        // check if just the party leader is left
        if(mainParty.getPlayers().size() < 2){
            mainParty.loseGame(1);
            gameOver = true;
        }
        // check if the sorcerers anger has reached the max
        else if(gameSorcerer.getAnger() == 100){
            mainParty.loseGame(3);
            gameOver = true;
        }
    }

}

int main(){
    // creates party
    party mainParty;
    // creates sorcerer
    Sorcerer gameSorcerer("Sorcerer", 6);
    // creates map
    Map mainMap;
    // sets the location for all the rooms and NPCs
    srand(time(NULL));
    for(int i = 0; i < 6; i++){;
        int xRoom = rand() % 12, yRoom = rand() % 12;
        mainMap.addRoom(xRoom,yRoom);
        int xNPC = rand() % 12, yNPC = rand() % 12;
        mainMap.addNPC(xNPC,yNPC);
    }
    // the first part of the game
    beforeEntry(mainParty);
    // the game
    inDungeon(gameSorcerer, mainMap, mainParty);
    return 0;
}