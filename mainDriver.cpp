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

for normal spaces:
	move (20% chance fullness drops 1 point)
	investigate (50% chance fullness drops 1 point unless fought monster) 
		find key
		find treasure
		find random monster
	pick a fight 
	cook and eat
	give up

for npc spaces
	move
	speak to npc 
		if complete puzzle can sell 
		if not complete will sommon monster 
		space changes to explored no matter what
	give up

for room spaces 
	move
	open the door
		if monster is defeated 60% of misfortune 
		if does not defeat monster consequences (key is lost, 40% chance of misfortune)
	give up
*/

// to run: g++ mainDriver.cpp item.cpp Monster.cpp Sorcerer.cpp party.cpp Map.cpp game.cpp RNG.cpp


void phase1(party &mainParty){
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

void statusUpdate(party mainParty, Sorcerer gameSorcerer){
    cout << "+-------------+\n| STATUS      |\n+-------------+\n| Rooms Cleared: " << mainParty.getRoomsCleared() << " | Keys: " << mainParty.getKeysFound() << 
    " | Anger Level: " << gameSorcerer.getAnger() << endl;
    printInventory(mainParty.partyInventory_);
    vector<player> partyMembers = mainParty.getPlayers();
    cout << "+-------------+\n| PARTY       |\n+-------------+" << endl;
    for(int i = 0; i < partyMembers.size(); i++){
        cout << "| " << partyMembers.at(i).name << " | Fullness: " << partyMembers.at(i).hunger << endl;
    }
    cout << "+-------------+\n" << endl;
}


void phase2(Sorcerer &gameSorcerer, Map &mainMap, party &mainParty){
    statusUpdate(mainParty,gameSorcerer);
    mainMap.displayMap();
    /*
    if(mainMap.isFreeSpace() == true){

    }
    else if(mainMap.isNPCLocation() == true){

    }

    gameSorcerer.increaseAnger();
    */
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
    /*while(s.getAnger() != 100 || giveUp || dies){
        phase2(gameSorcerer, mainMap, mainParty);
    }*/
    phase2(gameSorcerer, mainMap, mainParty);
    return 0;
}

/*
could make invalid input outputs more fun
"Welcome to the store, since it's your first time in let me give you some important information...
You will see other vendors out there and while we all cary similar good, are prices may not be so similar."
will print thank you even if cancelled could make bool or leave it
clean up responses and add parts that use type in response

phase 1 does not modify anything, even when adding the &
erro is either in what is being counted or in what is being returned 
works for int x but not printing the values
phase 1 does not moddify the party's gold for the new value

we know phase 1 is modifiying the party members and can modify things even if the change is from the merchant menu
*/
