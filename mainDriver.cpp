/*
* mainDriver.cpp
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
*
*/

#include "game.h"
#include "move.h"
#include <cassert>

/* phase 1
Map should generate randomly 
Enter names of player and party members (each has 50 fullness points, bellow 0 means death)
Start with 100 gold 
game ends when sorcer gets 100 anger 
Get merchnat menu
*/

/* phase 2
Display status update 
Display map 
Display action menu (type depends on turn type)

*/

// to run: g++ mainDriver.cpp item.cpp Monster.cpp Sorcerer.cpp party.cpp Map.cpp game.cpp RNG.cpp puzzles.cpp move.cpp

/**/

void beforeEntry(party &mainParty){
    //print scoreboard
    // creates the player objects for the party
    player partyLeader, member1, member2, member3, member4;
    partyLeader.isUserPlayer = true;
    cout << "Please enter names for you and your party:" << endl;
    cout << "Your name: ";
    cin >> partyLeader.name;
    cout << "Names for 4 more party members:" << endl;
    cin >> member1.name >> member2.name >> member3.name >> member4.name;
    cout << endl;
    partyLeader.hunger = 50;
    member1.hunger = 50;
    member2.hunger = 50;
    member3.hunger = 50;
    member4.hunger = 50;
    mainParty.addPlayer(partyLeader);
    mainParty.addPlayer(member1);
    mainParty.addPlayer(member2);
    mainParty.addPlayer(member3);
    mainParty.addPlayer(member4);
    mainParty.partyInventory_.addGold(100);
    cout << "Between the 5 of you, you have 100 gold pieces.\nYou will need to spend the some of your money on the following items:\n" << endl;
    cout << "- INGREDIENTS. To make food, you have to cook raw ingredients." << endl <<
    "- COOKWARE. If you want to cook, you have to have cookware first." << endl << 
    "- WEAPONS. You'll want at least one weapon per party member to fend off monsters." << endl << 
    "- ARMOR. Armor increases the chances of surviving a monster attack.\n" << endl <<
    "You can spend all of your money here before you start your journey, or you can save some to spend on merchants along the way." << endl << 
    "But beware, some of the merchants in this dungeon are shady characters, and they won't always give you a fair price...\n" << endl;
    merchantMenu(mainParty);
}


/**/

void inDungeon(Sorcerer &gameSorcerer, Map &mainMap, party &mainParty){
    vector<Monster> monsters;
    readInMonsters(monsters, "monsters.txt");
    bool gameOver = false;
    while(gameOver == false){
        vector<player> starvingPlayers = mainParty.starvingPlayers();
        if(starvingPlayers.size() > 0){
            cout << "It may be a good idea to cook soon, your party has some players that are on the brink of starving:\n" << endl;
            for(int i = 0; i < starvingPlayers.size(); i++){
                cout << "\t" << starvingPlayers.at(i).name << endl;
            }
            cout << endl;
        }
        statusUpdate(mainParty,gameSorcerer);
        mainMap.displayMap();
        cout << endl;
        if(mainMap.isRoomLocation(mainMap.getPlayerRow(),mainMap.getPlayerCol()) == true){ // room space
            roomSpace(mainMap, mainParty, gameSorcerer, gameOver, monsters);
        }
        else if(mainMap.isNPCLocation(mainMap.getPlayerRow(),mainMap.getPlayerCol()) == true){ // NPC space
            npcSpace(mainMap, mainParty, gameSorcerer, gameOver, monsters);
        }
        else if(mainMap.isDungeonExit(mainMap.getPlayerRow(),mainMap.getPlayerCol())){ // exit space
            if(mainParty.getRoomsCleared() == 5){
                mainParty.winGame();
                gameOver = true;
            }
            int spaceChoice = -1;
            vector<string> moveOptions= {"Move","Give up"};
            char proceed = 'n';
            cout << "You have made it to the exit... However, you cannot leave without defeating all the monsters and the Sorcerer." << endl;
            while(proceed == 'n'){
                cout << "Would you like to:\n1. " << moveOptions.at(0) << endl << "2. " << moveOptions.at(1) << "?\n" << endl;
                cin >> spaceChoice;
                cout << endl;
                if(spaceChoice != 1 && spaceChoice != 2){
                    cout << "I am not sure what you mean, please only pick one of the choices.\n" << endl;
                }
                else{
                    proceed = 'l';
                    while(proceed != 'y' && proceed != 'n'){
                        cout << "Are you sure you'd like to " << moveOptions.at(spaceChoice-1) << "? (y/n)\n" << endl;
                        cin >> proceed;
                        cout << endl;
                        if(proceed != 'y' && proceed != 'n'){
                            cout << "What was that? I couldn't understand you, please only answer y or n.\n" << endl;
                        }
                    }
                }
            }
           
            switch(spaceChoice){
                case 1:{ // move
                    move(mainMap, mainParty, gameSorcerer);
                }
                case 2:{ // give up
                    mainParty.loseGame(0);
                    gameOver = true;
                }
            }
        }
        else{ // normal space
            normalSpace(mainMap, mainParty, gameSorcerer,gameOver, monsters);
        }
        mainParty.incrementTurn();
        if(mainParty.getPlayers().size() < 2){
            mainParty.loseGame(1);
            gameOver = true;
        }
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
    beforeEntry(mainParty);
    inDungeon(gameSorcerer, mainMap, mainParty);
    return 0;
}

/*
monster from room appeared again ~

said that the monsters were all gone but then one showed up and was one i had beaten, monster showed up again

can't beat sorcerer

score = numPlayersLeft*100 (include player if they do not die) + roomsCleared*200 + treasure(each iteam * cost for each*10) + spacesExplored*2 + 
monstersDefeated (should we use level)*40 (exclude sorcerer) + didDefeatSorcerer - (turns elapsed) - sorcerer anger
score = 500 + 1000 + __ + 288 + __ + 1000 - __ - 100
print monsters defeated
    level 1: 
    level 2:
    etc


*/
