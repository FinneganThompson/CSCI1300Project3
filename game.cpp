/*
* game.cpp
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
* to run: g++ mainDriver.cpp item.cpp Monster.cpp Sorcerer.cpp party.cpp Map.cpp game.cpp RNG.cpp puzzles.cpp move.cpp
* 
* implementations of all game.h functions
*/

#include "game.h"

/*
Algorithm prints out everything that is in the party's inventory 
Accepts the party's inventory object 
Create a vector for the weapons of it's respective types
Create ints to hold the amount of each type of weapons 
Loop through the vector and count the number of each type of weapons
Print out the amount of gold, ingreidents, armor, and each type of weapons, cookware, and treasure
*/

void printInventory(inventory partyInventory){
    // creates a vector to hold the weapons in the party's inventory
    vector<weapon> partyWeapons = partyInventory.weaponsAvalible();
    // creates ints to hold the number of each individual type of weapon
    int clubs = 0, spears = 0,rapiers = 0, batAxes = 0, longSwords = 0;
    // loops through the vector to count the number of each type of weapon
    for(int i = 0; i < partyWeapons.size(); i++){
        if(partyWeapons.at(i).getType() == "Club"){
            clubs++;
        }
        else if(partyWeapons.at(i).getType() == "Spear"){
            spears++;
        }
        else if(partyWeapons.at(i).getType() == "Rapier"){
            rapiers++;
        }
        else if(partyWeapons.at(i).getType() == "Battle axe"){
            batAxes++;
        }
        else{
            longSwords++;
        }
    }
    // prints out the whole inventory, including the counts for each item in the inventory
    // for treasure and cookware because the amount of each type is a part of those items we check the quantity of the item at 
    cout << "+-------------+\n| INVENTORY   |\n+-------------+" << endl <<
    "| Gold        | " << partyInventory.goldAvalible() << endl << 
    "| Ingredients | " << partyInventory.totalIngredientsAvliable() << " kg" << endl << 
    "| Cookware    | P: " << partyInventory.cookwareAvailible().at(0).getQuantity() << " | F: " << partyInventory.cookwareAvailible().at(1).getQuantity() << 
    " | C: " << partyInventory.cookwareAvailible().at(2).getQuantity() << endl <<
    "| Weapons     | C: " << clubs << " | S: " << spears << " | R: " << rapiers << " | B: " << batAxes << " | L: " << longSwords << endl <<
    "| Armor       | " << partyInventory.armorAvalible() << endl << 
    "| Treasures   | R: " << partyInventory.treasureAvailible().at(0).getQuantity() << " | N: " << partyInventory.treasureAvailible().at(1).getQuantity() << 
    " | B: " << partyInventory.treasureAvailible().at(2).getQuantity() << " | C: " << partyInventory.treasureAvailible().at(3).getQuantity() << 
    " | G: " << partyInventory.treasureAvailible().at(4).getQuantity() << endl;
}

/*
//Algorithm is an interactive menu to allow a user to buy or sell items 
Accepts a party object
Declare an inventory object to hold the party's inventory
Declare an integer to hold the value of how much the cost should change (based on how many rooms have been cleared), one to hold the main menu choice,
one to hold the quantity of items to be bought or sold, the type of item to be bought or sold, and the calculated cost of items to be bought or sold
Declare a char to hold whether or not a user would like to finalize a sale or purchase
Print out welcome message 
Enter a loop to be the menu that will continue until the user wants to exit the menu
Call the printInventory funciton 
Print out the options 
Take user input and pass it to the main menu choice int 
Enter the switch statement
(Each option)
*/

void merchantMenu(party &mainParty){
    // create variables to hold the amount to chang the cost, menu choice, quantity, type, and cost
    // set to -1 and l just as random choices to be place holders
    int costChange = 0.25*mainParty.getRoomsCleared(), menuChoice = 0, quantity = -1, type = 0, cost = 0; 
    char buy = 'l';
    // into message to the store
    cout << "If you're looking to get supplies, you've come to the right place." << endl <<
    "I would be happy to part with some of my wares...for the proper price!\n" << endl;
    // the exit option is 6 so anything else should keep user in the loop, invalid input does have a case as well
    while(menuChoice != 6){
        // print the inventory every iteration (this also updates and allows users to see what they have including after buying)
        printInventory(mainParty.partyInventory_);
        // prints all store options
        cout << endl << "Choose one of the following:\n1. Ingredients: To make food, you have to cook raw ingredients." << endl <<
        "2. Cookware: You will need something to cook those ingredients." << endl << 
        "3. Weapons: It's dangerous to go alone, take this!" << endl << 
        "4. Armor: If you want to survive monster attacks, you will need some armor." << endl << 
        "5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands." << endl <<
        "6. Leave: Make sure you get everything you need, I'm leaving after this sale!\n" << endl;
        cin >> menuChoice;
        // all extra lines are simply formatting
        cout << endl;
        switch (menuChoice){
            case 1:{ // ingredients 
                cout << "I recommend having at least 10 kg per person of ingredients." << endl;
                // only exits loop if cancel option is selected or if purchase goes through
                quantity = -1;
                // to stay in until the user enters the exit value
                while(quantity != 0){
                    cout << "How many kg of ingredients do you need [1 Gold/kg]? (Enter a positive mulitple of 5, or 0 to cancel)\n" << endl;
                    cin >> quantity;
                    cout << endl;
                    // checks for valid input
                    if(quantity % 5 != 0 || quantity < 0){
                        cout << "I can only sell in 5 kg amounts, they come in bags you see. So..." << endl;
                    }
                    // makes it so that the can only buy if the input is valid and is not the cancel input
                    else if(quantity != 0){
                        // creates the cost of the ingredients
                        cost = quantity+(quantity*costChange);
                        // checks to make sure that the party has enough gold to spend
                        if(mainParty.partyInventory_.spendGold(cost) == false){
                            cout << "You do not have enough gold for this quantity of this item.\n" << endl;
                        }
                        else{ // if the party does have enough gold
                            // resets to validate user input
                            buy = 'l';
                            // stay in until the user enters valid input
                            while(buy != 'n' && buy != 'y'){
                                cout << "You want to buy " << quantity << " kg of ingredients for " << cost << " Gold? (y/n)\n" << endl;
                                cin >> buy;
                                cout << endl;
                                // output if the user does not give valid input
                                if(buy != 'n' && buy != 'y'){
                                    cout << "What kind of an answer is that? I only understand y or n.\n" << endl; 
                                }
                            }
                            // checks that the user actually wants to buy the item
                            if(buy != 'n'){
                                mainParty.partyInventory_.addGold(-cost);
                                mainParty.partyInventory_.addIngredients(quantity);
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
                // resets input if needed
                type = 0;
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
                        cookware cook(type);
                        // resets the quantity in case the user has selected 0 (to cancel the transaction)
                        quantity = -1;
                        // checks if the user wants to exit
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
                                // creates the cost of the cookware
                                cost = (quantity*cook.getCost())+(quantity*cook.getCost()*costChange);
                                // checks to make sure that the party has enough gold to spend
                                if(mainParty.partyInventory_.spendGold(cost) == false){
                                    cout << "You do not have enough gold for this quantity of this item.\n" << endl;
                                }
                                else{ // if there is enough gold
                                    // reseets so variable so it can be validated
                                    buy = 'l';
                                    // to stay in until the user gives valid input
                                    while(buy != 'n' && buy != 'y'){
                                        cout << "You want to buy " << quantity << " "<< cook.getType() << "(s) for " << cost << " Gold? (y/n)\n" << endl;
                                        cin >> buy;
                                        cout << endl;
                                        // output if the user input is invalid
                                        if(buy != 'n' && buy != 'y'){
                                            cout << "What kind of an answer is that? I only understand y or n.\n" << endl; 
                                        }
                                    }
                                    // only if they want to proceed with purchase
                                    if(buy != 'n'){
                                        mainParty.partyInventory_.addGold(-cost);
                                        mainParty.partyInventory_.changeCookwareQuantity(type-1,quantity);
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
                // checks to see if  the party can no longer add weapons
                if(mainParty.partyInventory_.weaponsAvalible().size() == 5){
                    cout << "You are at your limit for all the weapons you can hold.\n" << endl;
                    break;
                }
                // resets variable just in case
                type = 0;
                cout << "You need weapons to be able to fend off monsters, otherwise, you can only run! " <<
                "Lucky for you, I have a plentiful collection of weapons to choose from." << endl <<
                "Some of them provide you a special bonus in combat, marked by a (+X), and will maximize your chances of survival " << 
                "during an attack.\nBe aware that you may only have 1 weapon per person in your party, so choose wisely!\n" << endl;
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
                        weapon wep(type);
                        // resets quantity
                        quantity = -1;
                        // checks that the user did not want to cancel the transaction
                        while(quantity != 0){
                            cout << "How many would you like? (Enter a positive integer, or 0 to cancel)\n" << endl;
                            cin >> quantity;
                            cout << endl;
                            // validates input (does not include cancel input because that is already checked in the entrance to loop)
                            if(quantity < 0){
                                // "I'm sorry, I dont understand, what do you want?\n"
                                // << " " << wep << "(s)
                                cout << "I can't give you " << quantity << " weapons, please ask for a real amount.\n" << endl;
                            }
                            // assuming user has not wanted to exit and input is valid
                            else if(quantity != 0){
                                cost = (quantity*wep.getCost())+(quantity*wep.getCost()*costChange);
                                // checks to make sure that the party has enough gold to spend
                                if(mainParty.partyInventory_.spendGold(cost) == false){
                                    cout << "You do not have enough gold for this quantity of this item.\n" << endl;
                                }
                                else { // if the party has enough gold
                                    // resets variable so it can be validated
                                    buy = 'l';
                                    // stays in until the user gives valid input
                                    while(buy != 'n' && buy != 'y'){
                                        cout << "You want to buy " << quantity << " (+" << wep.getMod() << ") " << wep.getType() << 
                                        "(s) for " << cost << " Gold? (y/n)\n" << endl;
                                        cin >> buy;
                                        cout << endl;
                                        // output if input is invalid
                                        if(buy != 'n' && buy != 'y'){
                                            cout << "What kind of an answer is that? I only understand y or n.\n" << endl; 
                                        }
                                    }
                                    // only if they want to proceed with purchase
                                    if(buy != 'n'){
                                        mainParty.partyInventory_.addGold(-cost);
                                        // adds the weapons to the vector, loops in case the user wants more than one of the same type
                                        for(int i = 0; i < quantity; i++){
                                            mainParty.partyInventory_.addWeapons(wep);
                                        }
                                        // allows both loops to be exited
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
                // checks that the user does not want to exit the loop
                quantity = -1;
                while(quantity != 0){
                    cout << "How many suits of armor can I get you? (Enter a positive integer, or 0 to cancel)\n" << endl;
                    cin >> quantity;
                    cout << endl;
                    // if there is an invalid amount 
                    if(quantity < 0){
                        cout << "Well now, I'm not sure I can give you " << quantity << " armor, my boss might get upset.\n" << endl;
                    }
                    // in case the user wants to exit
                    else if(quantity != 0){
                        // calculates the cost of the quantity
                        cost = (quantity*5)+(quantity*5*costChange);
                        // checks to make sure that the party has enough gold to spend
                        if(mainParty.partyInventory_.spendGold(cost) == false){
                            cout << "You do not have enough gold for this quantity of this item.\n" << endl;
                        }
                        else{ // if the user has enough gold
                            // resets so that the variable can be validated
                            buy = 'l';
                            // stay in until the user enters valid input
                            while(buy != 'n' && buy != 'y'){
                                cout << "You want to buy " << quantity << " suit(s) of armor for " << cost << " Gold? (y/n)\n" << endl;
                                cin >> buy;
                                cout << endl;
                                // output if input is invalid
                                if(buy != 'n' && buy != 'y'){
                                    cout << "What kind of an answer is that? I only understand y or n.\n" << endl; 
                                }
                            }
                            // if they would like to complete the purchase
                            if(buy != 'n'){
                                mainParty.partyInventory_.addGold(-cost);
                                mainParty.partyInventory_.addArmor(quantity);
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
                // just in case it needs to be reset 
                type = 0;
                // create a vector to hold the party's treasure
                vector<treasure> partyTreasure = mainParty.partyInventory_.treasureAvailible();
                // bool to keep track of whether or not there is any treasure 
                bool hasTreasure = false;
                // checks if there is any treasure
                for(int i = 0; i < partyTreasure.size(); i++){
                    if(partyTreasure.at(i).getQuantity() > 0){
                        hasTreasure = true;
                        break;
                    }
                }
                // if there is no treasure
                if(hasTreasure == false){
                    cout << "Looks like you have some exploring to do, you have no treasure stored.\n" << endl;
                    break;
                }
                cout << "Ah have some treasure for me... What would you like to sell?" << endl;
                // to make sure the user does not want to exit
                while(type != 6){
                    cout << "Here is what I will pay:\n1. Silver rings [10 Gold]\n2. Ruby necklace [20 Gold]\n3. Emerald bracelet [30 Gold]" << endl <<
                    "4. Diamond circlet [40 Gold]\n5. Gem-encrusted goblet [50 Gold]\n6. Cancel" << endl <<
                    "Don't forget you can't sell something you don't have!\n" << endl;
                    cin >> type;
                    cout << endl;
                    // to validate the input
                    if(type < 1 || type > 6){
                        cout << "I haven't even heard of that one before." << endl;
                    }
                    // only done if the user does not want to exit
                    else if(type != 6){
                        // check if there is enough of the type they want
                        // type -1 to account for index offset
                        if(partyTreasure.at(type-1).getQuantity() == 0){
                            cout << "Looks like you don't have enough of those to sell." << endl;
                        }
                        else{
                            // creates the treasure objcet for the treasure type
                            treasure treas = mainParty.partyInventory_.treasureAvailible().at(type-1);
                            // to check that the user does not want change type of treasue 
                            while(quantity != 0){
                                cout << "How many would you like to sell? (Or 0 to cancel)\n" << endl;
                                cin >> quantity;
                                cout << endl;
                                // to make sure they have the amount of that type they want to sell
                                if(quantity > treas.getQuantity()){
                                    cout << "Unfortunately you do not have " << quantity << " " << treas.getType() << 
                                    "(s)\n" << endl;
                                }
                                // if user does not want to exit
                                else if(quantity != 0){
                                    // creates the price for the treasure 
                                    cost = (quantity*treas.getPrice());
                                    // resets so variable can be validated
                                    buy = 'l';
                                    // stay in until user enters valid input
                                    while(buy != 'n' && buy != 'y'){
                                        cout << "You want to sell " << quantity << " " << treas.getType() << "(s) for " << cost << " Gold? (y/n)\n" << endl;
                                        // buy is used but really it is to sell
                                        cin >> buy;
                                        cout << endl;
                                        // output if input is invalid
                                        if(buy != 'n' && buy != 'y'){
                                            cout << "What kind of an answer is that? I only understand y or n.\n" << endl; 
                                        }
                                    }
                                    // if they do want to sell for that amount
                                    if(buy != 'n'){
                                        mainParty.partyInventory_.addGold(cost);
                                        mainParty.partyInventory_.changeTreasureQuantity(type-1,(-quantity));
                                        type = 6;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                cout << "Thank you for the treasure! Is there anything you'd like from me? For a price of course.\n" << endl;
                break;
            }
            case 6:{ // leave
                cout << "Stay safe out there! Goodbye!\n" << endl;
                break;
            }
            default:{ // for invalid input 
                cout << "Please only enter an integer between 1-6. What can I get for you?\n" << endl;
                break;
            }
        }
    }
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
}


/*
Algorithm allows the party to move spaces on the map
Accept a map object and a party object
Declare a RNG object, a char to hold the move directio choice, and a bool to hold if the party's move choice is allowed
While the move is not allowed:
Ask the user where they would like to go and print the options as well
Accept the user input into the move choice
Check if the move choice is allowed using the .move function (if it is by checking you will also be moving)
If it is not allowed print out a message to inform the user
After exiting the while loop (if the party moved) loop through the party and individually determine if that player loses a fullness point
*/

void move(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer){
    // for random number generation
    RNG random;
    char moveChoice;
    bool okayMove = false;
    // checks if the move was not allowed
    while(okayMove == false){
        cout << "Where would you like to go? (w to go up, s to go down, a to go left, and d to go right)\n" << endl;
        cin >> moveChoice;
        cout << endl;
        // check if the move worked
        if(mainMap.move(moveChoice) == true){ 
            // if it did change the bool
            okayMove = true;
        }
        else{ // if move was not possible
            cout << "Ouch, looks like you've walked into a wall. Maybe try going a different direction or use lowercase input.\n" << endl;
        }
    }
    // loop through party members and determine if that player loses a fullness point and if so remove a fullness point
    for(int i = 0; i < mainParty.getPlayers().size(); i++){
        if(random.doesActionOccur(20) == true){
            // need to sort out what to do if it will kill
            mainParty.removeHunger(i,1);
        }
    }
    // if the space was not explored, increase the anger
    if(mainMap.isExplored(mainMap.getPlayerRow(),mainMap.getPlayerCol()) == false){
        gameSorcerer.increaseAnger();
    }
}

/*
Algorithm allows the party to investigate the space
Accepts the party object, the bool for if the game is over, and the vector of monsters
Declare a variable holding the the result of the investigation
Depending on what the result was enact whatever outcome, finding a key, finding treasure, incountering a monster or nothing
*/

void investigate(party &mainParty, bool &gameOver, vector<Monster> &monsters){
    // for random results
    RNG random;
    int investigationResult = random.randIntBetweenOneAndTen();
    // all cases are based on the probability of them happneing
    // finding a key 10%
    if(investigationResult == 1){ 
        mainParty.increaseKeysFound();
        cout << "What luck, you found a key!\n" << endl;
    }
    // find treasure 20%
    else if(investigationResult == 2 || investigationResult == 3){
        // you can only find treasure if you have cleared at least one room
        if(mainParty.getRoomsCleared() > 0){
            mainParty.partyInventory_.changeTreasureQuantity(mainParty.getRoomsCleared()-1,1);
            cout << "Something shiny... You found a " << mainParty.partyInventory_.treasureAvailible().at(mainParty.getRoomsCleared()-1).getType() << 
            "!\n" << endl;
        }
        else{ // if they have not cleared a room yet
            cout << "Looks like nothing turned up.\n" << endl;
        }
    }
    // encouter a monster 20%
    else if(investigationResult == 4 || investigationResult == 5){
        cout << "Uh-oh, you have encountered a monster!\n" << endl;
        fightMonster(monsters, mainParty, false, gameOver);
    }
    // nothing happening 50%
    else{ 
        cout << "Looks like nothing turned up.\n" << endl;
    }
    // determining if the party loses fullness pointed 
    if(random.doesActionOccur(50) == true){
        for(int i = 0; i < mainParty.getPlayers().size(); i++){
            mainParty.removeHunger(i,1);
        }
        cout << "You all became tired from exploring, -1 hunger.\n" << endl;
    }
    mainParty.increaseSpacesExplored();
}

// Randomly causes one of the end of turn misfortunes to the party
bool endOfTurnMisfortune(party &mainParty, int misfortuneProb, bool wasLastActionExitRoomOpenedWithKey, bool &gameOver)
{
    RNG randomGenerator;
    bool doesMisfortuneHappen = randomGenerator.doesActionOccur(misfortuneProb); // 40% chance of action ocurring
    if (!doesMisfortuneHappen) return false;    

    // Robbed misfortune
    bool isMisfortuneRobbed = randomGenerator.doesActionOccur(30);
    if (isMisfortuneRobbed)
    {
        int robbedRandomInt = randomGenerator.randIntOnRange(0,2);
        switch(robbedRandomInt)
        {
            case 0: // subtract 10 kg of ingredients, print robbed messauge
                if (mainParty.partyInventory_.totalIngredientsAvliable() >= 10){ // Only if we have sufficient ingredients can we take any away
                    mainParty.partyInventory_.addIngredients(-10);
                    cout << "OH NO! Your team was robbed by dungeon bandits!" << '\n' << "You lost 10kg of ingredients." << endl;
                    return true;
                    break;
                }
                else return false; // If we don't have ingredients, there is no misfotune
            case 1: // lose 1 armor
                if (mainParty.partyInventory_.removeArmor(1) == true){ // Make sure we have armor to remove
                    cout << "OH NO! Your team was robbed by dungeon bandits!" << '\n' << "You lost 1 armor." << endl;
                    return true;
                    break;
                }
                else return false; // If we don't have armor, there is no misfortune
            case 3: // lose 1 cookware
                if(mainParty.partyInventory_.totalCookware() > 0){
                    RNG random;
                    bool removed = false;
                    int randCookware = 0;
                    while(removed == false){
                        randCookware = random.randIntOnRange(1,3);
                        if(mainParty.partyInventory_.removeCookware(randCookware) == true){
                            removed = true;
                        }
                    }
                    cout << "OH NO! Your team was robbed by dungeon bandits!" << '\n' << "You lost 1 " << 
                    mainParty.partyInventory_.cookwareAvailible().at(randCookware).getType() << "." << endl;
                    return true;
                    break;
                }

        }


        return false;
    }
    // Broken weapon or armor misforutne
    bool isMisfortuneBrokenWeaponOrArmor = randomGenerator.doesActionOccur(10);
    if (isMisfortuneBrokenWeaponOrArmor)
    {
        bool doesArmorBreak = randomGenerator.doesActionOccur(50);
        if(doesArmorBreak && mainParty.partyInventory_.removeArmor(1) == true) // Make sure we have armor to remove
        {
            cout << "OH NO! One of your armor sets broke." << endl;
            return true;
        }
        else  // Weapon breaks
        {
            // Copy in our weapons and randomly select one to break. 
            vector<weapon> weapons = mainParty.partyInventory_.weaponsAvalible();
            int randWeapon = randomGenerator.randIntOnRange(0,(weapons.size()-1));
            // Remove the weapon but keep its information
            weapon weaponToRemove = weapons.at(randWeapon);
            mainParty.partyInventory_.removeWeapon(randWeapon);

            // Print out our misfortune statements
            string weaponName;
            char weaponToRemoveChar = weaponToRemove.getType()[0];
            switch (weaponToRemoveChar)
            {
                case 'C':
                    cout << "OH NO! Your +" << weaponToRemove.getMod() << " club broke!" << endl;
                    return true;
                    break;
                case 'S':
                    cout << "OH NO! Your +" << weaponToRemove.getMod() << " spear broke!" << endl;
                    return true;
                    break;
                case 'R':
                    cout << "OH NO! Your +" << weaponToRemove.getMod() << " rapier broke!" << endl;
                    return true;
                    break;
                case 'B':
                    cout << "OH NO! Your +" << weaponToRemove.getMod() << " battle axe broke!" << endl;
                    return true;
                    break;
                case 'L':
                    cout << "OH NO! Your +" << weaponToRemove.getMod() << " longsword broke!" << endl;
                    return true;
                    break;
            }

        }

        return false; // should never occur
    }
    // Food Posisoning Misfortune
    bool isFoodPoisoningMisfortune = randomGenerator.doesActionOccur(30); // 30% chance
    if (isFoodPoisoningMisfortune)
    {
        // Find the random player to make hungry
        int randPlayerToRemoveHungerFrom = randomGenerator.randIntOnRange(0,(mainParty.getPlayers().size()-1));
        // Try to remove hunger
        bool couldRemoveHunger = mainParty.removeHunger(randPlayerToRemoveHungerFrom, 10);
        // If removing the hunger would kill them, do so
        if (!couldRemoveHunger)
        {
            // Get the name of the player to kill
            vector<player> tempPlayers = mainParty.getPlayers();
            string playerNameToRemove = tempPlayers.at(randPlayerToRemoveHungerFrom).name;
            // Kill the player
            mainParty.killPlayerOfHunger(playerNameToRemove, gameOver);
        }
    }

    // Locked in room misfortune
    if (wasLastActionExitRoomOpenedWithKey)
    {
        // Get our players
        vector<player> tempPlayers = mainParty.getPlayers();
        player playerToBeLeftBehind;
        do
        {
            // Select a player to be left behing
            playerToBeLeftBehind = tempPlayers.at(randomGenerator.randIntOnRange(0,tempPlayers.size()-1));
        }
        while (playerToBeLeftBehind.isUserPlayer); // Make sure this player is not the party leader
        mainParty.killPlayerNoMessage(playerToBeLeftBehind.name); // Kill the player w/o a death message
        // Print the left behind message
        cout << "OH NO! Your teammate " << playerToBeLeftBehind.name << " is trapped in the previous room and is unable to get through. You must continue without them."
        << '\n' <<  "Your party size has reduced to " << tempPlayers.size()-1 << " members." << endl;
        return true;
    }

    return false; // Should never occur

}

// Read in monsters to the monsters vector from a file
bool readInMonsters(vector<Monster> &monsters, string filename)
{
    ifstream monsterFile; 
    monsterFile.open(filename);
    if(!monsterFile.is_open())
    {
        return false;
    }

    while (!monsterFile.eof()) // Read in all riddles from the file
    {
        string tempLine;
        string tempArr[2]; 
        getline(monsterFile, tempLine);

        int splitLineReturn = split(tempLine, ',', tempArr, 2); // Split each line into riddle and answer

        if (splitLineReturn == 2) 
        {
            Monster tempMonster = Monster(tempArr[0], stoi(tempArr[1])); // Add monsters to vector
            monsters.push_back(tempMonster);
        }
    }

    monsterFile.close(); 
    return true;
}

// Party fights the mosnter
bool fightMonster(vector<Monster> &monsters, party &mainParty, bool isInRoom, bool &gameOver)
{
    if (monsters.size() == 0) // No monsters left to fight
    {
        cout << '\n' << "It looks like you've killed all the monsters..." << endl;
        return true;
    }
    RNG randomGenerator; 
    int w = 0; // Variables from writeup formula
    int d = 0;
    int a = 0;
    int c = 0;

    int r1 = randomGenerator.randIntOnRange(1,6);
    int r2 = randomGenerator.randIntOnRange(1,6);

    vector<weapon> weapons = mainParty.partyInventory_.weaponsAvalible();

    for (int i=0; i<weapons.size(); i++) // Add up all the weapon modifiers
    {
        w += weapons.at(i).getMod();
    }

    bool areAllWeaponsUnique = true; // Check to see if all players have unique weapons
    for (int i=0; i<weapons.size(); i++)
    {
        for (int j=0; j<weapons.size(); j++)
        {
            if (weapons.at(i).getType() == weapons.at(j).getType())
            {
                areAllWeaponsUnique = false;
            }
        }
    }


    if (areAllWeaponsUnique) // Unique weapons modifier
    {
        d = 4;
    }

    a = mainParty.partyInventory_.armorAvalible();

    // Find the level needed for the monster
    int monsterLevelNeeded = 0;
    if (isInRoom)
    {
        monsterLevelNeeded = mainParty.getRoomsCleared() + 2;
        if (monsterLevelNeeded > 5)
        {
            monsterLevelNeeded = 5;
        }
    }
    else
    {
        monsterLevelNeeded = mainParty.getRoomsCleared()+1;
        if (monsterLevelNeeded > 5) 
        {
            monsterLevelNeeded = 5;
        }
    } 

    // Get all monsters of the correct level
    vector<Monster> monstersToFight;

    for (int j=0; j<monsters.size(); j++)
    {
        if (monsters.at(j).getLevel() == monsterLevelNeeded)
        {
            monstersToFight.push_back(monsters.at(j));
        }
    }
    // No monsters of correct level left
    //if (monstersToFight.size() == 0)
    if(monstersToFight.empty())
    {
        cout << "You've killed all the monsters that you can fight right now." << endl;
        return true;
    }
    // Randomly pic one of the monsters
    int randomMonster = randomGenerator.randIntOnRange(0, monstersToFight.size() - 1);
    Monster monsterToFight = monstersToFight.at(randomMonster);

    // Remove the monster from the array original so we don't see it again
    for (int j=0; j<monsters.size(); j++)
    {
        if (monsters.at(j).getLevel() == monsterToFight.getLevel() && monsters.at(j).getName() == monsterToFight.getName())
        {
            monsters.erase(monsters.begin() + j);
            break;
        }
    }

    c = monsterToFight.getLevel();

    // calculate the battle outcome
    double outcomeOfBattle = ((r1*w)+d)-((r2*c)/(a+0.1));
    cout << '\n' << "You have chosen to fight " << monsterToFight.getName() << ". Prepare for battle!" << endl;
    // Wait for the user to hit enter (for suspense)
    do 
    {
        cout << "(Press enter to see who wins!)\n" << endl;
        cin.get();
    } while (cin.get() != '\n' );


    // Wins battle
    if (outcomeOfBattle > 0)
    {
        int goldToCollect = c * 10; // Spoils to add to player inventory
        int ingredientsToCollect = 5 * c;
        bool isKeyDropped = randomGenerator.doesActionOccur(10);
        mainParty.partyInventory_.addIngredients(ingredientsToCollect);
        mainParty.partyInventory_.addGold(goldToCollect);
        for(int i = 0; i < monsters.size(); i++){
            if(monsters.at(i).getName() == monsterToFight.getName()){
                monsters.erase(monsters.begin() + i);
            }
        }

        if (isKeyDropped) // 10% of key being dropped
        {
            mainParty.increaseKeysFound();
            mainParty.winBattle(monsterToFight.getName(), gameOver);
            cout << "You have won the battle! You collect " << goldToCollect << " Gold Coins, "
            << ingredientsToCollect << " Kg of ingredients, and 1 key!" << endl;
            return true;
        }

        else 
        { // No key drop
            mainParty.winBattle(monsterToFight.getName(), gameOver);
            cout << "You have won the battle! You collect " << goldToCollect << " Gold Coins, and "
            << ingredientsToCollect << " Kg of ingredients!" << endl;
            return true;
        }

    }

    else 
    {  // All losing functionality handled in party class
        mainParty.loseBattle(gameOver);
        return false;
    }

}

// Party must win and complete a puzzle!
bool fightSorcerer(party &mainParty, Map &mainMap, Sorcerer &mainSorcerer, vector<Monster> &monsters)
{

    bool correctAns[2] = {false,false};

    cout << "You have chosen to fight me, the Sorcerer... but I'm not just the Sorcerer, I'm " 
    << mainSorcerer.getName() << ", master of computer science!" << endl;

    cout << "You must defeat me in a battle of wits! Answer two of my computer science questions and end my reign, or fail, and pay the price."
    << endl;

    RNG randomGenerator;
    ifstream questionFile; 
    questionFile.open("computerScienceQuestions.txt");

    vector<string> questions;
    vector<string> answers; 

    if(!questionFile.is_open())
    {
        return true;
    }

    while (!questionFile.eof()) // Read in all riddles from the file
    {
        string tempLine;
        string tempArr[2]; 
        getline(questionFile, tempLine);

        int splitLineReturn = split(tempLine, '~', tempArr, 2); // Split each line into riddle and answer

        if (splitLineReturn == 2) 
        {
            questions.push_back(tempArr[0]);
            answers.push_back(tempArr[1]);
        }
    }

    questionFile.close(); 

    for (int i=0; i<2; i++)
    {
        int questionIndex = randomGenerator.randIntOnRange(0, questions.size()-1); // Randomly select a riddle
        string answer = answers.at(questionIndex); // Find its answer

        string userInput; 

        // Main riddle statement
        cout << questions.at(questionIndex) << endl;


        // Take user input untill the player gives up or uses both tries    
        for (int j=0; j<2; j++)
        {
            cin >> userInput; 
            if (userInput == answer)
            {
                cout << "Correct. How did you know that?!?!?" << endl;
                correctAns[j] = true;
                break;
            }
            else if (j=0)
            {
                cout << "Wrong! You have one more try. " << endl;
                continue;
            }
            else
            {
                cout << "You have failed! Now face the consequences..." << endl;
                mainParty.loseGame(4);
                exit(0);
                return false;
            }
        }

    }
        // removes room space
        mainMap.removeRoom(mainMap.getPlayerRow(),mainMap.getPlayerCol());
        // Remove all monsters
        while(monsters.size() > 0)
        {
            monsters.pop_back();
        }
        cout << "You have defeated me in a battle of wits! My dungeon is now yours." << endl;
        mainSorcerer.angerNoLongerIncreases();
        return true;
}
