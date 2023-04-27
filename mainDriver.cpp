/*
* mainDriver.cpp
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
*
*/

#include "game.h"
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

// to run: g++ mainDriver.cpp item.cpp Monster.cpp Sorcerer.cpp party.cpp Map.cpp game.cpp RNG.cpp puzzles.cpp

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

/*
for normal spaces:
	move (20% chance fullness drops 1 point)
	investigate (50% chance fullness drops 1 point unless fought monster) 
		find key
		find treasure
		find random monster
	pick a fight 
	cook and eat
	give up
*/

void normalSpace(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer, bool &gameOver, vector<Monster> &monsters){
    vector<string> turnOptions = {"Move to a different space","Investigate the space you are on","Pick a fight with a monster",
    "Cook and eat","Give up on your adventure"};
    int spaceChoice;
    char proceed = 'n';
    while(proceed == 'n'){
        cout << "You are on a normal space, here are your options:" << endl;
        for(int i = 0; i < turnOptions.size(); i++){
            cout << i+1 << ". " << turnOptions.at(i) << "." << endl;
        }
        cout << endl;
        cin >> spaceChoice;
        cout << endl;
        if(spaceChoice < 1 || spaceChoice > 5){
            cout << "Please only enter an integer between 1-5.\n" << endl;
        }
        else{
            cout << "Are you sure you'd like to " << turnOptions.at(spaceChoice-1) << "? (y/n)\n" << endl;
            cin >> proceed;
            cout << endl;
            if(spaceChoice == 2 && mainMap.isExplored(mainMap.getPlayerRow(),mainMap.getPlayerCol()) == true && proceed != 'n'){
                cout << "This space has been explored, please pick another option.\n" << endl;
                proceed = 'n';
            }
        }
    }
    switch (spaceChoice){
        case 1:{// move
            move(mainMap, mainParty, gameSorcerer);
            break;
        }
        case 2:{// investigate 
            investigate(mainParty);
            mainMap.exploreSpace(mainMap.getPlayerRow(),mainMap.getPlayerCol());
            endOfTurnMisfortune(mainParty, 40, false); // 40%
            break;
        }
        case 3:{
            RNG random;
            cout << "Oh! You've chosen to try your luck with a monster.\n" << endl; 
            fightMonster(monsters, mainParty, false);
            if(random.doesActionOccur(50) == true){
                for(int i = 0; i < mainParty.getPlayers().size(); i++){
                    mainParty.removeHunger(i,1);
                }
                cout << "You all became tired from exploring, -1 hunger.\n" << endl;
            }
            endOfTurnMisfortune(mainParty, 40, false); // 40%
            break;
        }
        case 4:{// cook and eat
            mainParty.cookAndEat();
            endOfTurnMisfortune(mainParty, 40, false); // 40%
            break;
        }
        case 5:{// give up
            mainParty.loseGame(0);
            gameOver = true;
            break;
        }
    }
}

/*
for room spaces 
	move
	open the door
		if monster is defeated 60% of misfortune 
		if does not defeat monster consequences (key is lost, 40% chance of misfortune)
	give up
    */

void roomSpace(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer, bool &gameOver, vector<Monster> monsters){
    vector<string> turnOptions = {"Move to a different space","Open the room door","Give up on your adventure"};
    int spaceChoice;
    char proceed = 'n';
    while(proceed == 'n'){
        cout << "You are on a normal space, here are your options:" << endl;
        for(int i = 0; i < turnOptions.size(); i++){
            cout << i+1 << ". " << turnOptions.at(i) << "." << endl;
        }
        cout << endl;
        cin >> spaceChoice;
        cout << endl;
        if(spaceChoice < 1 || spaceChoice > 3){
            cout << "Please only enter an integer between 1-3.\n" << endl;
        }
        else{
            cout << "Are you sure you'd like to " << turnOptions.at(spaceChoice-1) << "? (y/n)\n" << endl;
            cin >> proceed;
            cout << endl;
        }
    }
    switch(spaceChoice){
        case 1:{//move
            move(mainMap, mainParty, gameSorcerer);
            break;
        }
        case 2:{//open door
            //if(mainParty.getRoomsCleared() < 5){}
            RNG random;
            if(mainParty.getKeysFound() > 0){ // get into room with key
                cout << "You got in the room using a key, inside you see a monster.\n" << endl; 
                // check if player wins the fight
                if(fightMonster(monsters, mainParty, true) == true){ // win
                    endOfTurnMisfortune(mainParty, 60, true); // 60%
                }
                else{ // loss
                    mainParty.loseKey(); 
                    endOfTurnMisfortune(mainParty, 40, true); // 40%
                }
                if(random.doesActionOccur(50) == true){
                    for(int i = 0; i < mainParty.getPlayers().size(); i++){
                        mainParty.removeHunger(i,1);
                    }
                    cout << "You all became tired from exploring, -1 hunger.\n" << endl;
                }
            }
            else{ // no key
                //check if player wins boulder, parchment, sheers 
                if(doorPuzzle() == true){ // win
                    cout << "Dispite not having a key, you got in the room. Inside you see a monster.\n" << endl; 
                    fightMonster(monsters, mainParty, false);
                    // check if player wins the fight
                    if(fightMonster(monsters, mainParty, false) == true){ // win
                        endOfTurnMisfortune(mainParty, 40, false); // 40%
                    }
                    else{ // loss
                        mainParty.loseKey();
                        endOfTurnMisfortune(mainParty, 40, false); // 40%
                    }
                    if(random.doesActionOccur(50) == true){
                        for(int i = 0; i < mainParty.getPlayers().size(); i++){
                            mainParty.removeHunger(i,1);
                        }
                        cout << "You all became tired from exploring, -1 hunger.\n" << endl;
                    }
                }
                else{ // loss
                    // maybe make check to make sure that they are not the user
                    string playerName = mainParty.getPlayers().at(random.randIntOnRange(1,mainParty.getPlayers().size()-1)).name;
                    mainParty.killPlayerNoMessage(playerName);
                    cout << "Having failed to beat me, say goodbye to " << playerName << 
                    ", they were unable to escape my trap along with the rest of you.\n" << endl;
                    endOfTurnMisfortune(mainParty, 40, false);
                }
            }
            break;
        }
        case 3:{//give up
            mainParty.loseGame(0);
            gameOver = true;
            break;
        }
    }
}

/*
for npc spaces
	move
	speak to npc 
		if complete puzzle can sell 
		if not complete will sommon monster 
		space changes to explored no matter what
	give up
*/

void npcSpace(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer, bool &gameOver, vector<Monster> &monsters){
    vector<string> turnOptions = {"Move to a different space","Speak to the NPC","Give up on your adventure"};
    int spaceChoice;
    char proceed = 'n';
    while(proceed == 'n'){
        cout << "You are on a normal space, here are your options:" << endl;
        for(int i = 0; i < turnOptions.size(); i++){
            cout << i+1 << ". " << turnOptions.at(i) << "." << endl;
        }
        cout << endl;
        cin >> spaceChoice;
        cout << endl;
        if(spaceChoice < 1 || spaceChoice > 3){
            cout << "Please only enter an integer between 1-3.\n" << endl;
        }
        else{
            cout << "Are you sure you'd like to " << turnOptions.at(spaceChoice-1) << "? (y/n)\n" << endl;
            cin >> proceed;
            cout << endl;
        }
    }
    switch(spaceChoice){
        case 1:{//move
            move(mainMap, mainParty, gameSorcerer);
            break;
        }
        case 2:{//speak to NPC
            // spaces becomes normal and explored 
            if(NPCPuzzle() == true){
                cout << "Congratulations on completing my riddle, allow me to offer my services!\n" << endl;
                merchantMenu(mainParty);
            }
            else if(NPCPuzzle() == false){
                RNG random;
                cout << "Not too clever I see. Say hello to my friend. HAHAHA!\n" << endl;
                fightMonster(monsters, mainParty, false);
                if(random.doesActionOccur(50) == true){
                    for(int i = 0; i < mainParty.getPlayers().size(); i++){
                        mainParty.removeHunger(i,1);
                    }
                    cout << "You all became tired from exploring, -1 hunger.\n" << endl;
                }  
            }
            else{
                cout << "You may not have completed my riddle but since I couldn't find them, I shall still offer my services.\n" << endl;
                merchantMenu(mainParty);
            }
            mainMap.exploreSpace(mainMap.getPlayerRow(),mainMap.getPlayerCol());
            endOfTurnMisfortune(mainParty, 40, false); // 40%
            break;
        }
        case 3:{//give up
            mainParty.loseGame(0);
            gameOver = true;
            break;
        }
    }
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
            cout << "room\n" << endl;
            roomSpace(mainMap, mainParty, gameSorcerer, gameOver, monsters);
        }
        else if(mainMap.isNPCLocation(mainMap.getPlayerRow(),mainMap.getPlayerCol()) == true){
            cout << "npc\n" << endl;
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
    for(int i = 0; i < 6; i++){
        srand(time(NULL));
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
sort out after sorcer is defeated, no more anger increase, no more monsters

is there a limit on weapons 

fight sorcerer is not called


sometimes "nothing turned up" doesn't print from investigation
why is The remaning players in your party are: printing twice

i have only written for if they choose to leave, if they have too few players, or if the sorcerer's anger gets to 100

score = numPlayersLeft*100 (include player if they do not die) + roomsCleared*200 + treasure(each iteam * cost for each*10) + spacesExplored*2 + 
monstersDefeated (should we use level)*40 (exclude sorcerer) + didDefeatSorcerer - (turns elapsed) - sorcerer anger
score = 500 + 1000 + __ + 288 + __ + 1000 - __ - 100
print monsters defeated
    level 1: 
    level 2:
    etc


*/
