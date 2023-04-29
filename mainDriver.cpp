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
    while(!mainMap.isDungeonExit(mainMap.getPlayerRow(),mainMap.getPlayerCol()) && gameOver == false){
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
        if(mainMap.isRoomLocation(mainMap.getPlayerRow(),mainMap.getPlayerCol()) == true){
            roomSpace(mainMap, mainParty, gameSorcerer, gameOver, monsters);
        }
        else if(mainMap.isNPCLocation(mainMap.getPlayerRow(),mainMap.getPlayerCol()) == true){
            npcSpace(mainMap, mainParty, gameSorcerer, gameOver, monsters);
        }else{
            normalSpace(mainMap, mainParty, gameSorcerer,gameOver, monsters);
        }
        mainParty.incrementTurn();
        if(mainParty.getPlayers().size() < 2){
            mainParty.loseGame(1);
            break;
        }
        else if(gameSorcerer.getAnger() == 100){
            mainParty.loseGame(3);
            break;
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
if all monsters are defeated throws an error, does not show fourth level 1

score = numPlayersLeft*100 (include player if they do not die) + roomsCleared*200 + treasure(each iteam * cost for each*10) + spacesExplored*2 + 
monstersDefeated (should we use level)*40 (exclude sorcerer) + didDefeatSorcerer - (turns elapsed) - sorcerer anger
score = 500 + 1000 + __ + 288 + __ + 1000 - __ - 100
print monsters defeated
    level 1: 
    level 2:
    etc


*/
