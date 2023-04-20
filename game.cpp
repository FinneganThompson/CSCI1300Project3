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
        if(partyCookware.at(i).getType() == 'P'){
            pots++;
        }
        else if(partyCookware.at(i).getType() == 'F'){
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
        if(partyWeapons.at(i).type = 'C'){
            clubs++;
        }
        else if(partyWeapons.at(i).type == 'S'){
            spears++;
        }
        else if(partyWeapons.at(i).type == 'R'){
            rapiers++;
        }
        else if(partyWeapons.at(i).type == 'B'){
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
        if(partyTreasure.at(i).type == 'R'){
            rings++;
        }
        else if(partyTreasure.at(i).type == 'N'){
            necklaces++;
        }
        else if(partyTreasure.at(i).type == 'B'){
            bracelets++;
        }
        else if(partyTreasure.at(i).type == 'C'){
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
    "| Treasures   | R: " << rings << " | N: " << necklaces << " | B: " << bracelets << " | C: " << circlets << " | G: " << goblets << 
    endl << endl;
}
