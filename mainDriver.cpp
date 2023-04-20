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

// to run: g++ mainDriver.cpp item.cpp Monster.cpp Sorcerer.cpp party.cpp Map.cpp

/*
takes party so that it can be passed to printInventory
*/

void merchantMenu(inventory partyInventory){
    // into message to the store
    cout << "If you're looking to get supplies, you've come to the right place." << endl <<
    "I would be happy to part with some of my wares...for the proper price!\n" << endl;
    int menuChoice = 0;
    // the exit option is 6 so anything else should keep user in the loop, invalid input does have a case as well
    while(menuChoice != 6){
        // print the inventory every iteration (this also updates and allows users to see what they have including after buying)
        printInventory(partyInventory);
        // prints all store options
        cout << "Choose one of the following:\n1. Ingredients: To make food, you have to cook raw ingredients." << endl <<
        "2. Cookware: You will need something to cook those ingredients." << endl << 
        "3. Weapons: It's dangerous to go alone, take this!" << endl << 
        "4. Armor: If you want to survive monster attacks, you will need some armor." << endl << 
        "5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands." << endl <<
        "6. Leave: Make sure you get everything you need, I'm leaving after this sale!\n" << endl;
        cin >> menuChoice;
        // all extra lines are simply formatting
        cout << endl;
        // set to -1 and l just as random choices to be place holders 
        int quantity = -1;
        char buy = 'l';
        int type = 0;
        switch (menuChoice){
            case 1:{ // ingredients 
                cout << "I recommend having at least 10 kg per person of ingredients." << endl;
                // only exits loop if cancel option is selected or if purchase goes through
                while(quantity != 0){
                    cout << "How many kg of ingredients do you need [1 Gold/kg]? (Enter a positive mulitple of 5, or 0 to cancel)\n" << endl;
                    cin >> quantity;
                    cout << endl;
                    // checks valid input
                    if(quantity % 5 != 0 && quantity < 0){
                        cout << "I can only sell in 5 kg amounts, they come in bags you see. So..." << endl;
                    }
                    // makes it so that the can only buy if the input is valid and is not the cancel input
                    else if(quantity != 0){
                        // checks to make sure that the party has enough gold to spend
                        if(partyInventory.spendGold(quantity) == false){
                            cout << "You do not have enough gold for this quantity of this item.\n" << endl;
                        }
                        else{
                            cout << "You want to buy " << quantity << " kg of ingredients for " << quantity << " Gold? (y/n)\n" << endl;
                            cin >> buy;
                            cout << endl;
                            // checks that the user actually wants to buy the item
                            if(buy != 'n'){
                                partyInventory.addGold(-quantity);
                                //add to inventory
                                //allows the loop to be exited
                                break;
                            }
                        }
                    }
                }
                cout << "Thank you for your patronage! What else can I get for you?\n" << endl;
                break;
            }
            case 2:{ // cookware
                cout << "I have a several types of cookware, which one would you like?" << endl <<
                "Each type has a different probability of breaking when used, marked with (XX%).\n" << endl;
                //checks that the user does not want to exit
                while(type != 4){
                    cout << "Choose one of the following:\n1. (25%) Ceramic Pot [2 Gold]\n2. (10%) Frying Pan [10 Gold]" << endl <<
                    "3. ( 2%) Cauldron [20 Gold]\n4. Cancel\n" << endl;
                    cin >> type;
                    cout << endl;
                    // validates input
                    if(type < 1 || type > 4){
                        cout << "Hmm... I'm not sure I have that" << endl;
                    }
                    // done as long as the user does not want to exit and has given a valid input
                    else if(type != 4){
                        // resets the quantity in case the user has selected 0 (to cancel the transaction)
                        quantity = -1;
                        while(quantity != 0){
                            cout << "How many would you like? (Enter a positive integer, or 0 to cancel)\n" << endl;
                            cin >> quantity;
                            cout << endl;
                            // validates input
                            if(quantity < 0){
                                // "I'm sorry, I dont understand, what do you want?\n"
                                cout << "I can't give you " << quantity << " cookware, please ask for a real amount.\n" << endl;
                            }
                            // assuming input is valid and not the exit input
                            else if(quantity != 0){
                                // checks to make sure that the party has enough gold to spend
                                if(partyInventory.spendGold(quantity/**cost*/) == false){
                                    cout << "You do not have enough gold for this quantity of this item.\n" << endl;
                                }
                                else{
                                    cout << "You want to buy " << quantity << " Cauldron(s) for " << quantity/**cost*/ << " Gold? (y/n)\n" << endl;
                                    cin >> buy;
                                    cout << endl;
                                    // only if they want to proceed with purchase
                                    if(buy != 'n'){
                                        partyInventory.addGold(-(quantity/**cost*/));
                                        //partyInventory.addCookware(cookware());
                                        //allows both loops to be exited
                                        type = 4;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                cout << "Thank you for your patronage! What else can I get for you?\n" << endl;
                break;
            }
            case 3:{ // weapons
                cout << "You need weapons to be able to fend off monsters, otherwise, you can only run! " <<
                "Lucky for you, I have a plentiful collection of weapons to choose from." << endl <<
                "Some of them provide you a special bonus in combat, marked by a (+X), and will maximize your chances of survival " << 
                "during an attack./nBe aware that you may only have 1 weapon per person in your party, so choose wisely!\n" << endl;
                // will only exit the loop if the exit input is given
                while(type != 6){
                    cout << "What would you like? Choose one of the following:\n1. Stone Club [2 Gold]" << endl <<
                    "2. Iron Spear [2 Gold]\n3. (+1) Mythril Rapier [5 Gold]\n4. (+2) Flaming Battle-Axe [15 Gold]" << endl <<
                    "5. (+3) Vorpal Longsword [50 Gold]\n6. Cancel\n" << endl;
                    cin >> type;
                    cout << endl;
                    // validates the type of weapon input (exit input is also allowed)
                    if(type < 1 || type > 6){
                        // "I'm sorry, I dont understand, what do you want?\n"
                        cout << "Please only enter one of the options. I only have so many kinds of weapons.\n" << endl;
                    }
                    // only excecutes if the user chose a weapon and not to exit
                    else if(type != 6){
                        quantity = -1;
                        // checks that the user did not want to cancel the transaction
                        while(quantity != 0){
                            cout << "How many would you like? (Enter a positive integer, or 0 to cancel)\n" << endl;
                            cin >> quantity;
                            cout << endl;
                            // validates input (does not include cancel input because that is already checked in the entrance to loop)
                            if(quantity < 0){
                                // "I'm sorry, I dont understand, what do you want?\n"
                                cout << "I can't give you " << quantity << "weapons, please ask for a real amount.\n" << endl;
                            }
                            // assuming user has not wanted to exit and input is valid
                            else if(quantity != 0){
                                // checks to make sure that the party has enough gold to spend
                                if(partyInventory.spendGold(quantity/**cost*/) == false){
                                    cout << "You do not have enough gold for this quantity of this item.\n" << endl;
                                }
                                else {
                                    cout << "You want to buy " << quantity << " (+1) Mythril Rapier(s) for " <<
                                    quantity/**cost*/ << " Gold? (y/n)\n" << endl;
                                    cin >> buy;
                                    cout << endl;
                                    // only if they want to proceed with purchase
                                    if(buy != 'n'){
                                        partyInventory.addGold(-(quantity/**cost*/));
                                        //partyInventory.addWeapons(weapon());
                                        //allows both loops to be exited
                                        type = 6;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                cout << "Thank you for your patronage! What else can I get for you?\n"<< endl;
                break;
            }
            case 4:{ // armor
                cout << "Armor protects you from monsters. Equipping your team with armor will increase chances of " <<
                "survival during an attack. The more armor you have, the better your chances." << endl <<
                "The catch is that you can only have 1 armor per person in your party and " <<
                "any armor beyond that will not increase your chances further.\n" << endl; 
                while(quantity != 0){
                    cout << "How many suits of armor can I get you? (Enter a positive integer, or 0 to cancel)\n" << endl;
                    cin >> quantity;
                    cout << endl;
                    if(quantity < 0){
                        cout << "Well now, I'm not sure I can give you " << quantity << " armor, my boss might get upset.\n" << endl;
                    }
                    else if(quantity != 0){
                        // checks to make sure that the party has enough gold to spend
                        if(partyInventory.spendGold(quantity) == false){
                            cout << "You do not have enough gold for this quantity of this item.\n" << endl;
                        }
                        else{
                            cout << "You want to buy " << quantity << " suit(s) of armor for " << quantity/**cost*/ << 
                            " Gold? (y/n)\n" << endl;
                            cin >> buy;
                            cout << endl;
                            if(buy != 'n'){
                                partyInventory.addGold(-(quantity/**cost*/));
                                //partyInventory.addArmor(armor());
                                // exits loop
                                break;
                            }
                        }
                    }
                }
                cout << "Thank you for your patronage! What else can I get for you?\n" << endl;
                break;
            }
            case 5:{ // sell
                cout << "Let's take a look and see what you have for me today.\n" << endl;
                if(partyInventory.treasureAvailible().size() < 1){
                    cout << "Looks like you have some exploring to do, you have no treasure stored.\n" << endl;
                    break;
                }
                
                cout << "Thank you for the treasure! Is there anything you'd like from me? For a price of course.\n" << endl;
                break;
            }
            case 6:{ // leave
                cout << "Stay safe out there! Goodbye!\n" << endl;
                break;
            }
            default:{
                cout << "Please only enter an integer between 1-6. What can I get for you?\n" << endl;
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
    cout << "Between the 5 of you, you have 100 gold pieces.\nYou will need to spend the some of your money on the following items:\n" << endl;
    cout << "- INGREDIENTS. To make food, you have to cook raw ingredients." << endl <<
    "- COOKWARE. If you want to cook, you have to have cookware first." << endl << 
    "- WEAPONS. You'll want at least one weapon per party member to fend off monsters." << endl << 
    "- ARMOR. Armor increases the chances of surviving a monster attack.\n" << endl <<
    "You can spend all of your money here before you start your journey, or you can save some to spend on merchants along the way." << endl << 
    "But beware, some of the merchants in this dungeon are shady characters, and they won't always give you a fair price...\n" << endl;
    merchantMenu(mainParty.partyInventory_);
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
get ingredients is not working because i am not adding it lmfao
can change the type of type of weapons, ie stone to wood club
could be good to chnage type of items from structs to classes
could make invalid input outputs more fun
maybe integrate setting the type and cost and all that in a class definition for the wepons and cookware and treasure 
could give background info in phase one before menu
"Welcome to the store, since it's your first time in let me give you some important information...
You will see other vendors out there and while we all cary similar good, are prices may not be so similar."
Give background info at start, how to win, how to lose, could make it a help menu that can be called
will print thank you even if cancelled could make bool or leave it
clean up responses and add parts that use type in response

change the type identifier for the cookware to be an int and match to the menu options
*/
