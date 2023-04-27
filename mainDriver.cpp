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


void phase1(party &mainParty){
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
Algorithm prints out a status update, to be used at the start of every turn
Accepts a party object and a sorcerer object
Print out the number of rooms cleared, keys found, and the anger level of the sorcerer
Print the inventory by calling the print inventory function
Print out the fullness of the player and all party members
*/

void statusUpdate(party mainParty, Sorcerer gameSorcerer){
    // prints out the rooms cleared, keys found, and sorcerer anger
    cout << "+-------------+\n| STATUS      |\n+-------------+\n| Rooms Cleared: " << mainParty.getRoomsCleared() << " | Keys: " << mainParty.getKeysFound() << 
    " | Anger Level: " << gameSorcerer.getAnger() << endl;
    // calls print inventory to print the inventory
    printInventory(mainParty.partyInventory_);
    mainParty.printFullness();
    // maybe add check here for starvation/ if too few members
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

void normalSpace(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer){
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
            cout << "Oh! You've chosen to try your luck with a monster.\n" << endl; 
            vector<Monster> monsters;
            readInMonsters(monsters, "monsters.txt");
            fightMonster(monsters, mainParty);
            // lose health 50%
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

void roomSpace(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer){
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
            if(mainParty.getKeysFound() > 0){ // get into room with key
                cout << "You got in the room using a key, inside you see a monster.\n" << endl; 
                vector<Monster> monsters;
                readInMonsters(monsters, "monsters.txt");
                // check if player wins the fight
                if(fightMonster(monsters, mainParty) == true){ // win
                    endOfTurnMisfortune(mainParty, 60, true); // 60%
                }
                else{ // loss
                    mainParty.loseKey(); 
                    endOfTurnMisfortune(mainParty, 40, true); // 40%
                }
                    // lose health
            }
            else{ // no key
                //check if player wins boulder, parchment, sheers 
                if(doorPuzzle() == true){ // win
                    cout << "Dispite not having a key, you got in the room. Inside you see a monster.\n" << endl; 
                    vector<Monster> monsters;
                    readInMonsters(monsters, "monsters.txt");
                    fightMonster(monsters, mainParty);
                    // check if player wins the fight
                    if(fightMonster(monsters, mainParty) == true){ // win
                        endOfTurnMisfortune(mainParty, 40, false); // 40%
                    }
                    else{ // loss
                        mainParty.loseKey();
                        endOfTurnMisfortune(mainParty, 40, false); // 40%
                    }
                    // lose health
                }
                else{ // loss
                    RNG random;
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

void npcSpace(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer){
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
                cout << "Not too clever I see. Say hello to my friend. HAHAHA!\n" << endl;
                vector<Monster> monsters;
                readInMonsters(monsters, "monsters.txt");
                fightMonster(monsters, mainParty);
                // lose health  
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
            break;
        }
    }
}



void phase2(Sorcerer &gameSorcerer, Map &mainMap, party &mainParty){
    statusUpdate(mainParty,gameSorcerer);
    mainMap.displayMap();
    cout << endl;
    if(mainMap.isRoomLocation(mainMap.getPlayerRow(),mainMap.getPlayerCol()) == true){
        cout << "room\n" << endl;
        roomSpace(mainMap, mainParty, gameSorcerer);
    }
    else if(mainMap.isNPCLocation(mainMap.getPlayerRow(),mainMap.getPlayerCol()) == true){
        cout << "npc\n" << endl;
        npcSpace(mainMap, mainParty, gameSorcerer);
    }
    else if(mainMap.isDungeonExit(mainMap.getPlayerRow(),mainMap.getPlayerCol())){
        cout << "exit\n" << endl;
    }
    else{
        normalSpace(mainMap, mainParty, gameSorcerer);
    }
}

int main(){
    party mainParty;
    // creates map
    Map mainMap;
    srand(time(NULL));
    int xNPC, yNPC;
    for(int i = 0; i < 6; i++){
    int xRoom = rand() % 12, yRoom = rand() % 12;
    mainMap.addRoom(xRoom,yRoom);
    xNPC = rand() % 12, yNPC = rand() % 12;
    mainMap.addNPC(xNPC,yNPC);
    }
    Sorcerer gameSorcerer("Sorcerer", 6);
    phase1(mainParty);
    char leave = 'n';
    while(leave == 'n'){
        phase2(gameSorcerer, mainMap, mainParty);
        cout << "leave\n" << endl;
        cin >> leave;
        cout << endl;
    }
    /*
    while(s.getAnger() != 100 || giveUp || dies (loseGame(different types))){
        phase2(gameSorcerer, mainMap, mainParty);
    }
    for(int i = 0; i < 3; i++){
        phase2(gameSorcerer, mainMap, mainParty);
    }*/
    return 0;
}

/*
could make invalid input outputs more fun
"Welcome to the store, since it's your first time in let me give you some important information...
You will see other vendors out there and while we all cary similar good, are prices may not be so similar."
will print thank you even if cancelled could make bool or leave it
clean up responses and add parts that use type in response

check for starvation/ too few members in the status update
check anger for each phase 2


could be good to make weapons an array rather than vector, or sort


sometimes "nothing turned up" doesn't print from investigation 
for end game, only prints first party member and leader
also prints out the treasure but not quantity so it looks like they have all that treasure
spaces explored is not tracking


score = numPlayersLeft*100 (include player if they do not die) + roomsCleared*200 + treasure(each iteam * cost for each*10) + spacesExplored*2 + 
monstersDefeated (should we use level)*40 (exclude sorcerer) + didDefeatSorcerer
score = 500 + 1000 + __ + 288 + __ + 1000
print monsters defeated
    level 1: 
    level 2:
    etc


*/
