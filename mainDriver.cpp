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

//void placeRooms

// generate map (Need to look into how to do so)
void phase1(){
    // creates map
    Map mainMap;
    // create random ints
    for(int i = 0; i < 6; i++){
    int xRoom = rand() % 12, yRoom = rand() % 12;
    mainMap.addRoom(xRoom,yRoom);
    /*int xNPC = rand() % 12, yNPC = rand() % 12;
    mainMap.addNPC(xNPC,yNPC);*/
    }
    // displays map
    mainMap.displayMap();
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
    party mainParty;
    mainParty.addPlayer(partyLeader);
    mainParty.addPlayer(member1);
    mainParty.addPlayer(member2);
    mainParty.addPlayer(member3);
    mainParty.addPlayer(member4);
    mainParty.partyInventory_.addGold(100);
    Sorcerer s("Sorcerer", 6);
    cout << "Between the 5 of you, you have 100 gold pieces.\nYou will need to spend the some of your money on the following items:\n" << endl;
    cout << "- INGREDIENTS. To make food, you have to cook raw ingredients." << endl <<
    "- COOKWARE. If you want to cook, you have to have cookware first." << endl << 
    "- WEAPONS. You'll want at least one weapon per party member to fend off monsters." << endl << 
    "- ARMOR. Armor increases the chances of surviving a monster attack.\n" << endl <<
    "You can spend all of your money here before you start your journey, or you can save some to spend on merchants along the way." << endl << 
    "But beware, some of the merchants in this dungeon are shady characters, and they won't always give you a fair price...\n" << endl;
    //merchantMenu(mainParty);
    /*vector<player> players = mainParty.getPlayers();
    for(int i = 0; i < 5; i++){
        cout << players.at(i).isUserPlayer << endl;
    }*/
}

void phase2(){

}

int main(){
    //Sorcerer s("Sorcerer", 6);
    phase1();
    /*while(s.getAnger() != 100){
        phase2();
    }*/
    return 0;
}

/*
could make invalid input outputs more fun
"Welcome to the store, since it's your first time in let me give you some important information...
You will see other vendors out there and while we all cary similar good, are prices may not be so similar."
will print thank you even if cancelled could make bool or leave it
clean up responses and add parts that use type in response

get map to print properly
make player set randomly
use rng to make it put rooms and npcs randomly
make sure it excluses spaces already taken
*/
