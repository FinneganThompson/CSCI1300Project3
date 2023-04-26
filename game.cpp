#include "game.h"


/*
Algorithm prints out everything that is in the party's inventory 
Accepts the party's inventory object 
Create vectors for the cookware, weapons, and treasure, of their respective types
Create ints to hold the amount of each type of cookware, weapons, and treasure respectively 
Loop through each vector and count the number of each type for cookware, weapons, and treasure respectively
*/

void printInventory(inventory partyInventory){
    // creates a vector to hold the cookware in the party's inventory
    vector<cookware> partyCookware = partyInventory.cookwareAvailible();
    // creates ints to hold the number of each individual type of cookware
    int pots = 0, fryingPans = 0, cauldrons = 0;
    // loops through the vector to count the number of each type of cookware
    for(int i = 0; i < partyCookware.size(); i++){
        if(partyCookware.at(i).getType() == "Ceramic pot"){
            pots++;
        }
        else if(partyCookware.at(i).getType() == "Frying pan"){
            fryingPans++;
        }
        else{
            cauldrons++;
        }
    }
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
    // creates a vector to hold the treasure in the party's inventory
    vector<treasure> partyTreasure = partyInventory.treasureAvailible();
    // creates ints to hold the number of each individual type of treasure
    int rings = 0, necklaces = 0, bracelets = 0, circlets = 0, goblets = 0;
    // loops through the vector to count the number of each type of treasure
    for(int i = 0; i < partyTreasure.size(); i++){
        if(partyTreasure.at(i).getType() == "Silver ring"){
            rings++;
        }
        else if(partyTreasure.at(i).getType() == "Ruby necklace"){
            necklaces++;
        }
        else if(partyTreasure.at(i).getType() == "Emerald bracelet"){
            bracelets++;
        }
        else if(partyTreasure.at(i).getType() == "Diamond circlet"){
            circlets++;
        }
        else{
            goblets++;
        }
    }
    // prints out the whole inventory, including the counts for each item in the inventory
    cout << "+-------------+\n| INVENTORY   |\n+-------------+" << endl <<
    "| Gold        | " << partyInventory.goldAvalible() << endl << 
    // edit so that we get weight 
    "| Ingredients | " << partyInventory.totalIngredientsAvliable() << " kg" << endl << 
    "| Cookware    | P: " << pots << " | F: " << fryingPans << " | C: " << cauldrons << endl <<
    "| Weapons     | C: " << clubs << " | S: " << spears << " | R: " << rapiers << " | B: " << batAxes << " | L: " << longSwords << endl <<
    "| Armor       | " << partyInventory.armorAvalible() << endl << 
    "| Treasures   | R: " << partyTreasure.at(0).getQuantity() << " | N: " << partyTreasure.at(1).getQuantity() << " | B: " << partyTreasure.at(2).getQuantity() << 
    " | C: " << partyTreasure.at(3).getQuantity() << " | G: " << partyTreasure.at(4).getQuantity() << endl;
}

/*
Algorithm is an interactive menu to allow a user to buy or sell items 
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
                        // creates the cost 
                        cost = quantity+(quantity*costChange);
                        // checks to make sure that the party has enough gold to spend
                        if(mainParty.partyInventory_.spendGold(cost) == false){
                            cout << "You do not have enough gold for this quantity of this item.\n" << endl;
                        }
                        else{
                            cout << "You want to buy " << quantity << " kg of ingredients for " << cost << " Gold? (y/n)\n" << endl;
                            cin >> buy;
                            cout << endl;
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
                                cost = (quantity*cook.getCost())+(quantity*cook.getCost()*costChange);
                                // checks to make sure that the party has enough gold to spend
                                if(mainParty.partyInventory_.spendGold(cost) == false){
                                    cout << "You do not have enough gold for this quantity of this item.\n" << endl;
                                }
                                else{
                                    cout << "You want to buy " << quantity << " "<< cook.getType() << "(s) for " << cost << " Gold? (y/n)\n" << endl;
                                    cin >> buy;
                                    cout << endl;
                                    // only if they want to proceed with purchase
                                    if(buy != 'n'){
                                        mainParty.partyInventory_.addGold(-cost);
                                        for(int i = 0; i < quantity; i++){
                                            mainParty.partyInventory_.addCookware(cook);
                                        }
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
                                cout << "I can't give you " << quantity << "weapons, please ask for a real amount.\n" << endl;
                            }
                            // assuming user has not wanted to exit and input is valid
                            else if(quantity != 0){
                                cost = (quantity*wep.getCost())+(quantity*wep.getCost()*costChange);
                                // checks to make sure that the party has enough gold to spend
                                if(mainParty.partyInventory_.spendGold(cost) == false){
                                    cout << "You do not have enough gold for this quantity of this item.\n" << endl;
                                }
                                else {
                                    cout << "You want to buy " << quantity << " (+" << wep.getMod() << ") " << wep.getType() << 
                                    "(s) for " << cost << " Gold? (y/n)\n" << endl;
                                    cin >> buy;
                                    cout << endl;
                                    // only if they want to proceed with purchase
                                    if(buy != 'n'){
                                        mainParty.partyInventory_.addGold(-cost);
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
                while(quantity != 0){
                    cout << "How many suits of armor can I get you? (Enter a positive integer, or 0 to cancel)\n" << endl;
                    cin >> quantity;
                    cout << endl;
                    // if there is an invalid amount 
                    if(quantity < 0){
                        cout << "Well now, I'm not sure I can give you " << quantity << " armor, my boss might get upset.\n" << endl;
                    }
                    else if(quantity != 0){
                        // calculates the cost of the quantity
                        cost = (quantity*5)+(quantity*5*costChange);
                        // checks to make sure that the party has enough gold to spend
                        if(mainParty.partyInventory_.spendGold(cost) == false){
                            cout << "You do not have enough gold for this quantity of this item.\n" << endl;
                        }
                        else{
                            cout << "You want to buy " << quantity << " suit(s) of armor for " << cost << 
                            " Gold? (y/n)\n" << endl;
                            cin >> buy;
                            cout << endl;
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
                                else if(quantity != 0){
                                    cost = (quantity*treas.getPrice());
                                    cout << "You want to sell " << quantity << " " << treas.getType() << "(s) for " << cost << " Gold? (y/n)\n" << endl;
                                    // buy is used but really it is to sell
                                    cin >> buy;
                                    cout << endl;
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
            default:{
                cout << "Please only enter an integer between 1-6. What can I get for you?\n" << endl;
                break;
            }
        }
    }
}

bool endOfTurnMisfortune(party &mainParty, bool wasLastActionExitRoomOpenedWithKey)
{
    RNG randomGenerator;
    bool doesMisfortuneHappen = randomGenerator.doesActionOccur(40); // 40% chance of action ocurring
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
                    random.randIntOnRange(1,3);
                /*vector<cookware> cookwareVect = mainParty.partyInventory_.cookwareAvailible(); // Get our cookware
                if (mainParty.partyInventory_.removeCookware(1) == true) // Remove one cookware if we can
                {
                    string cookwareTypeRemovedString = cookwareVect.at((cookwareVect.size() - 1)).getType(); // Get the type of the cookware we removed
                    char cookwareTypeRemovedChar = cookwareTypeRemovedString[0];
                    string cookwareType;
                    switch(cookwareTypeRemovedChar) // Change our type char to a string
                    {
                        case 'P':
                            cookwareType = "Pot";
                            break;
                        case 'F':
                            cookwareType = "Frying Pan";
                            break;
                        case 'C':
                            cookwareType = "Cauldron";
                            break;

                    }*/
                    //cout << "OH NO! Your team was robbed by dungeon bandits!" << '\n' << "You lost 1 " << cookwareType << "." << endl;
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
            //mainParty.killPlayerOfHunger(playerNameToRemove);
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
        //mainParty.killPlayerNoMessage(playerToBeLeftBehind.name); // Kill the player w/o a death message
        // Print the left behind message
        cout << "OH NO! Your teammate " << playerToBeLeftBehind.name << " is trapped in the previous room and is unable to get through. You must continue without them."
        << '\n' <<  "Your party size has reduced to " << tempPlayers.size()-1 << " members." << endl;
        return true;
    }

    return false; // Should never occur

}

