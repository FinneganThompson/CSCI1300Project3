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
    vector<player> partyMembers = mainParty.getPlayers();
    cout << "+-------------+\n| PARTY       |\n+-------------+" << endl;
    // maybe add check here for starvation/ if too few members
    // loop through all the party members and print out their fullness
    for(int i = 0; i < partyMembers.size(); i++){
        cout << "| " << partyMembers.at(i).name << " | Fullness: " << partyMembers.at(i).hunger << endl;
    }
    cout << "+-------------+\n" << endl;
}


//move funtion
void move(Map &mainMap, party &mainParty){
    RNG random;
    char moveChoice;
    bool okayMove = false;
    while(okayMove == false){
        cout << "Where would you like to go? (w to go up, s to go down, a to go left, and d to go right)\n" << endl;
        cin >> moveChoice;
        cout << endl;
        if(mainMap.move(moveChoice) != false){ 
            okayMove = true;
        }
        else{
            cout << "Ouch, looks like you've walked into a wall. Maybe try going a different direction or use lowercase input.\n" << endl;
        }
    }
    for(int i = 0; i < mainParty.getPlayers().size(); i++){
        if(random.doesActionOccur(20) == true){
            // need to sort out what to do if it will kill
            mainParty.removeHunger(i,1);
        }
    }
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

void cookAndEat(party &mainParty){
    cout << "In order to cook a meal, you must have at least 5kg of ingredients and can only cook in 5kg increments." << endl <<
    "For each 5kg of ingredients cooked, your whole party will gain back 1 fullness point.\n" << endl;
    if(mainParty.partyInventory_.totalIngredientsAvliable() < 5){
        cout << "Unfortunately it looks like you don't have enough ingredients for a meal, better hope you find a merchant!\n"<< endl;
    }
    else{
        RNG random;
        int quantity = mainParty.partyInventory_.totalIngredientsAvliable() + 1;
        while(quantity > mainParty.partyInventory_.totalIngredientsAvliable()){
            cout << "How much would you like to cook?\n" << endl;
            cin >> quantity;
            cout << endl;
            if(quantity > mainParty.partyInventory_.totalIngredientsAvliable()){
                cout << "You don't have enough ingredients for that.\n" << endl;
            }
            else{
                
                /*
                ask what they would like to cook with
                find index of first instance
                see if cookware breaks
                if it does break erase it from the vector (print message)
                if it does not, increase fullness (print message)
                after either display the fullness levels of each party member, as well as the remaining number of kg of food.
                */
                // use tp lower
                //if())
                //mainParty.partyInventory_.useCookware();
                cout << "What would you like to cook with?\n" << endl;
                //cin >> 
            }
        }

    }
}

void normalSpace(Map &mainMap, party &mainParty){
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
            if(spaceChoice == 2 && mainMap.isExplored(mainMap.getPlayerRow(),mainMap.getPlayerCol()) == true){
                cout << "This space has been explored, please pick another option.\n" << endl;
                proceed = 'n';
            }
        }
    }
    switch (spaceChoice){
        case 1:{// move
            move(mainMap, mainParty);
            break;
        }
        case 2:{// investigate 
            mainParty.investigate();
            mainMap.exploreSpace(mainMap.getPlayerRow(),mainMap.getPlayerCol());
            break;
        }
        case 3:{// pick a fight
            break;
        }
        case 4:{// cook and eat
            //mainParty.cookAndEat();
            break;
        }
        case 5:{// give up
            //mainParty.loseGame(0);
            break;
        }
    }
}

void roomSpace(){

}

void npcSpace(){

}



void phase2(Sorcerer &gameSorcerer, Map &mainMap, party &mainParty){
    statusUpdate(mainParty,gameSorcerer);
    mainMap.displayMap();
    cout << endl;
    if(mainMap.isRoomLocation(mainMap.getPlayerRow(),mainMap.getPlayerCol()) == true){
        roomSpace();
    }
    else if(mainMap.isNPCLocation(mainMap.getPlayerRow(),mainMap.getPlayerCol()) == true){
        npcSpace();
    }
    else if(mainMap.isDungeonExit(mainMap.getPlayerRow(),mainMap.getPlayerCol())){
        cout << "exit\n" << endl;
    }
    else{
        normalSpace(mainMap, mainParty);
    }
    gameSorcerer.increaseAnger();
}

int main(){
    /*party mainParty;
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
    while(s.getAnger() != 100 || giveUp || dies (loseGame(different types))){
        phase2(gameSorcerer, mainMap, mainParty);
    }
    for(int i = 0; i < 3; i++){
        phase2(gameSorcerer, mainMap, mainParty);
    }
    */
    RNG random;
    cout << random.randIntOnRange(1,3) << endl;
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
*/
