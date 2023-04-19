/*
* mainDriver.cpp
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
*
*/

#include "item.h"
#include "Monster.h"
#include "Sorcerer.h"
#include "party.h"
#include "Map.h"
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

// to run: g++ mainDriver.cpp item.cpp Monster.cpp Sorcerer.cpp party.cpp Map.cpp

/*
+-------------+
| INVENTORY   |
+-------------+
| Gold        | 100
| Ingredients | 0 kg
| Cookware    | P: 0 | F: 0 | C: 0
| Weapons     | C: 0 | S: 0 | R: 0 | B: 0 | L: 0
| Armor       | 0
| Treasures   | R: 0 | N: 0 | B: 0 | C: 0 | G: 0
*/


void printInventory(party mainParty){
    inventory partyInventory = mainParty.partyInventory_;
    vector<cookware> partyCookware = partyInventory.cookwareAailible();
    cookware pot('P');
    cookware fryingPan('F');
    cookware cauldron('C');
    for(int i = 0; i < partyCookware.size(); i++){
        if(partyCookware[i] == 'P'){
            
        }
    }
    cout << "+-------------+\n| INVENTORY   |\n+-------------+" << endl <<
    "| Gold        | " << partyInventory.goldAvalible() << endl << 
    "| Ingredients | " << partyInventory.totalIngredientsAvliable() << endl << 
    "| Cookware    | " << partyCookware.
    
}



void merchantMenu()
{
    cout << "If you're looking to get supplies, you've come to the right place." << endl <<
    "I would be happy to part with some of my wares...for the proper price!" << endl;
    //call inventory function
    int menuChoice = 0;
    cin >> menuChoice;
    while(menuChoice != 6){
        switch (menuChoice){
            case 1:{ // ingredients 
                
                break;
            }
            case 2:{ // cookware
                break;
            }
            case 3:{ // weapons
                break;
            }
            case 4:{ // armor
                break;
            }
            case 5:{ // sell
                break;
            }
            case 6:{ // leave
                break;
            }
            default:{
                break;
            }
        }
    }
}




// generate map (Need to look into how to do so)
void phase1(){
    // creates and displays map
    Map mainMap;
    mainMap.displayMap();
    // creates the player objects for the party
    player partyLeader, member1, member2, member3, member4;
    // 
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
    cout << "Between the 5 of you, you have 100 gold pieces.\nYou will need to spend the some of your money on the following items:" << endl;
    cout << "- INGREDIENTS. To make food, you have to cook raw ingredients." << endl <<
    "- COOKWARE. If you want to cook, you have to have cookware first." << endl << 
    "- WEAPONS. You'll want at least one weapon per party member to fend off monsters." << endl << 
    "- ARMOR. Armor increases the chances of surviving a monster attack." << endl <<
    "You can spend all of your money here before you start your journey, or you can save some to spend on merchants along the way." << endl << 
    "But beware, some of the merchants in this dungeon are shady characters, and they won't always give you a fair price..." << endl;
    
    //merchant menu
    /*vector<player> players = mainParty.getPlayers();
    for(int i = 0; i < 5; i++){
        cout << players.at(i).isUserPlayer << endl;
    }*/
}

void phase2(){

}

int main(){
    phase1();
    return 0;
}
