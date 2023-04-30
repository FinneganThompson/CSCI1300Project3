/*
* move.cpp
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
* to run: g++ mainDriver.cpp item.cpp Monster.cpp Sorcerer.cpp party.cpp Map.cpp game.cpp RNG.cpp puzzles.cpp move.cpp
* 
* implementations of all move.h functions
*/


#include "move.h"





/*
Algorithm enacts what should happen when the party is on a normal space
Accepts the map, party, and sorcerer objects along with a bool holding whether or not the game ends and the vector of monsters
Print out all the options for what the party can do 
Validate their input
Check that their choice is what the want to do
Do whatever their choice was
*/

void normalSpace(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer, bool &gameOver, vector<Monster> &monsters){
    // vector of all the space options
    vector<string> turnOptions = {"Move to a different space","Investigate the space you are on","Pick a fight with a monster",
    "Cook and eat","Give up on your adventure"};
    int spaceChoice;
    char proceed = 'n';
    // to stay in while the user is unhappy with their choice
    while(proceed == 'n'){
        cout << "You are on a normal space, here are your options:" << endl;
        // print out the turn options
        for(int i = 0; i < turnOptions.size(); i++){
            cout << i+1 << ". " << turnOptions.at(i) << "." << endl;
        }
        cout << endl;
        cin >> spaceChoice;
        cout << endl;
        // validate the input
        if(spaceChoice < 1 || spaceChoice > 5){
            cout << "Please only enter an integer between 1-5.\n" << endl;
        }
        else{
            // resets so that the input can be validated
            proceed = 'l';
            // to stay in until the user gives valid input
            while(proceed != 'n' && proceed != 'y'){
                cout << "Are you sure you'd like to " << turnOptions.at(spaceChoice-1) << "? (y/n)\n" << endl;
                cin >> proceed;
                cout << endl;
                // to print for invalid input
                if(proceed != 'n' && proceed != 'y'){
                    cout << "What kind of an answer is that? I only understand y or n.\n" << endl; 
                }
            }
            // if they want to investigate the space, check if the space has been explored and will send the user back to select something else
            if(spaceChoice == 2 && mainMap.isExplored(mainMap.getPlayerRow(),mainMap.getPlayerCol()) == true && proceed != 'n'){
                cout << "This space has been explored, please pick another option.\n" << endl;
                proceed = 'n';
            }
        }
    }
    // cases for each input the user has selected
    switch (spaceChoice){
        case 1:{// move
            move(mainMap, mainParty, gameSorcerer);
            break;
        }
        case 2:{// investigate 
            investigate(mainParty, gameOver, monsters);
            // marks the space as explored
            mainMap.exploreSpace(mainMap.getPlayerRow(),mainMap.getPlayerCol());
            endOfTurnMisfortune(mainParty, 40, false, gameOver); // 40%
            break;
        }
        case 3:{ // pick a fight
            RNG random;
            cout << "Oh! You've chosen to try your luck with a monster.\n" << endl; 
            fightMonster(monsters, mainParty, false, gameOver);
            // determines if the party loses fullness points after fighting 
            if(random.doesActionOccur(50) == true){
                for(int i = 0; i < mainParty.getPlayers().size(); i++){
                    mainParty.removeHunger(i,1);
                }
                cout << "You all became tired from exploring, -1 hunger.\n" << endl;
            }
            endOfTurnMisfortune(mainParty, 40, false, gameOver); // 40%
            break;
        }
        case 4:{// cook and eat
            // makes sure that the party has enough ingredients to cook
            if(mainParty.partyInventory_.totalIngredientsAvliable() < 5){
                cout << "You do not have enough ingredients to cook.\n" << endl;
                break;
            }
            mainParty.cookAndEat();
            endOfTurnMisfortune(mainParty, 40, false, gameOver); // 40%
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
Algorithm enacts what should happen when the party is on a room space
Accepts the map, party, and sorcerer objects along with a bool holding whether or not the game ends and the vector of monsters
Print out all the options for what the party can do 
Validate their input
Check that their choice is what the want to do
Do whatever their choice was
*/

void roomSpace(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer, bool &gameOver, vector<Monster> &monsters){
    // the turn options
    vector<string> turnOptions = {"Move to a different space","Open the room door","Give up on your adventure"};
    int spaceChoice;
    char proceed = 'n';
    // to stay in until the user is happy with their choice 
    while(proceed == 'n'){
        cout << "You happen across a door to a room, here are your options:" << endl;
        // print all turn options
        for(int i = 0; i < turnOptions.size(); i++){
            cout << i+1 << ". " << turnOptions.at(i) << "." << endl;
        }
        cout << endl;
        cin >> spaceChoice;
        cout << endl;
        // validates the user input
        if(spaceChoice < 1 || spaceChoice > 3){
            cout << "Please only enter an integer between 1-3.\n" << endl;
        }
        else{ // if the user enters valid input
            // resets value so that the input can be validated
            proceed = 'l';
            // stay in until user gives valid input
            while(proceed != 'n' && proceed != 'y'){
                cout << "Are you sure you'd like to " << turnOptions.at(spaceChoice-1) << "? (y/n)\n" << endl;
                cin >> proceed;
                cout << endl;
                // output if the user gives invalid input
                if(proceed != 'n' && proceed != 'y'){
                    cout << "What kind of an answer is that? I only understand y or n.\n" << endl; 
                }
            }
        }
    }
    switch(spaceChoice){
        case 1:{//move
            move(mainMap, mainParty, gameSorcerer);
            break;
        }
        case 2:{//open door
            // for random number generation
            RNG random;
            // determines if the party has a ket to use
            if(mainParty.getKeysFound() > 0){ // get into room with key
                // check to see if the party has beaten all rooms but the sorcerer's
                if(mainParty.getRoomsCleared() == 4)
                {
                    cout << "You got in the room using a key. Inside you see the Sorcerer.\n";
                    fightSorcerer(mainParty, mainMap, gameSorcerer, monsters);
                    // these will only happen if the sorcerer battle was won
		            endOfTurnMisfortune(mainParty, 60, true, gameOver); // 60%
                    mainParty.increaseRoomsCleared();
                    mainMap.removeRoom(mainMap.getPlayerRow(),mainMap.getPlayerCol());
                    break;
                }
                // only for if the party cannot yet face the sorcerer
                cout << "You got in the room using a key, inside you see a monster.\n" << endl; 
                // check if player wins the fight
                if(fightMonster(monsters, mainParty, true, gameOver) == true){ // win
                    mainParty.loseKey();
                    endOfTurnMisfortune(mainParty, 60, true, gameOver); // 60%
                    mainParty.increaseRoomsCleared();
                    mainMap.removeRoom(mainMap.getPlayerRow(),mainMap.getPlayerCol());
                }
                else{ // loses fight
                    mainParty.loseKey(); 
                    endOfTurnMisfortune(mainParty, 40, true, gameOver); // 40%
                }
                // check if the platers lose fullness points
                if(random.doesActionOccur(50) == true){
                    for(int i = 0; i < mainParty.getPlayers().size(); i++){
                        mainParty.removeHunger(i,1);
                    }
                    cout << "You all became tired from fighting, -1 hunger.\n" << endl;
                }
            }
            else{ // no key
                //check if player wins boulder, parchment, sheers 
                if(doorPuzzle() == true){ // win
                    // check to see if the party has beaten all rooms but the sorcerer's
                    if(mainParty.getRoomsCleared() == 4)
                    {
                        cout << "You got in without a key. Inside you see the Sorcerer.\n";
                        fightSorcerer(mainParty, mainMap, gameSorcerer, monsters);
			            endOfTurnMisfortune(mainParty, 60, true, gameOver); // 60%
                    	mainParty.increaseRoomsCleared();
                   	    mainMap.removeRoom(mainMap.getPlayerRow(),mainMap.getPlayerCol());
                        break;
                    }
                    // only for if the party cannot yet face the sorcerer
                    cout << "Dispite not having a key, you got in the room. Inside you see a monster.\n" << endl; 
                    bool monsterFightResult = fightMonster(monsters, mainParty, false, gameOver);
                    // check if player wins the fight
                    if(monsterFightResult == true){ // win
                        endOfTurnMisfortune(mainParty, 40, false, gameOver); // 40%
                        mainParty.increaseRoomsCleared();
                        mainMap.removeRoom(mainMap.getPlayerRow(),mainMap.getPlayerCol());
                    }
                    else{ // loses fight
                        endOfTurnMisfortune(mainParty, 40, false, gameOver); // 40%
                    }
                    // check if party loses fullness points
                    if(random.doesActionOccur(50) == true){
                        for(int i = 0; i < mainParty.getPlayers().size(); i++){
                            mainParty.removeHunger(i,1);
                        }
                        cout << "You all became tired from fighting, -1 hunger.\n" << endl;
                    }
                }
                else{ // loses game to door
                    string playerName = mainParty.getPlayers().at(random.randIntOnRange(1,mainParty.getPlayers().size()-1)).name;
                    mainParty.killPlayerNoMessage(playerName);
                    cout << "Having failed to beat me, say goodbye to " << playerName << 
                    ", they were unable to escape my trap along with the rest of you.\n" << endl;
                    endOfTurnMisfortune(mainParty, 40, false, gameOver);
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
Algorithm enacts what should happen when the party is on an NPC space
Accepts the map, party, and sorcerer objects along with a bool holding whether or not the game ends and the vector of monsters
Print out all the options for what the party can do 
Validate their input
Check that their choice is what the want to do
Do whatever their choice was
*/

void npcSpace(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer, bool &gameOver, vector<Monster> &monsters){
    // the turn options for NPC spaces
    vector<string> turnOptions = {"Move to a different space","Speak to the NPC","Give up on your adventure"};
    int spaceChoice;
    char proceed = 'n';
    // to stay in unless the user is happy with their choice
    while(proceed == 'n'){
        cout << "You have run into an NPC, here are your options:" << endl;
        // prints turn options
        for(int i = 0; i < turnOptions.size(); i++){
            cout << i+1 << ". " << turnOptions.at(i) << "." << endl;
        }
        cout << endl;
        cin >> spaceChoice;
        cout << endl;
        // validates user choice
        if(spaceChoice < 1 || spaceChoice > 3){
            cout << "Please only enter an integer between 1-3.\n" << endl;
        }
        else{ // if input is valid
            // reset variable so that the proceed input can be validated
            proceed = 'l';
            // to stay in until the user enters valid input
            while(proceed != 'n' && proceed != 'y'){
                cout << "Are you sure you'd like to " << turnOptions.at(spaceChoice-1) << "? (y/n)\n" << endl;
                cin >> proceed;
                cout << endl;
                // to be out put if the user enters invalid input
                if(proceed != 'n' && proceed != 'y'){
                    cout << "What kind of an answer is that? I only understand y or n.\n" << endl; 
                }
            }
        }
    }
    switch(spaceChoice){
        case 1:{//move
            move(mainMap, mainParty, gameSorcerer);
            break;
        }
        case 2:{//speak to NPC
            // spaces becomes normal and explored 
            bool doesNPCPuzzle = NPCPuzzle();
            // if the user passes the riddles
            if(doesNPCPuzzle == true){
                cout << "Congratulations on completing my riddle, allow me to offer my services!\n" << endl;
                merchantMenu(mainParty);
            }
            // if the user fails the riddles
            else if(doesNPCPuzzle == false){
                // for random number generation
                RNG random;
                cout << "Not too clever I see. Say hello to my friend. HAHAHA!\n" << endl;
                fightMonster(monsters, mainParty, false, gameOver);
                // determine if the party loses fullness points
                if(random.doesActionOccur(50) == true){
                    for(int i = 0; i < mainParty.getPlayers().size(); i++){
                        mainParty.removeHunger(i,1);
                    }
                    cout << "You all became tired from exploring, -1 hunger.\n" << endl;
                }  
            }
            // if the NPC doesn't have any riddles
            else{
                cout << "You may not have completed my riddle but since I couldn't find them, I shall still offer my services.\n" << endl;
                merchantMenu(mainParty);
            }
            mainMap.removeNPC(mainMap.getPlayerRow(),mainMap.getPlayerCol());
            endOfTurnMisfortune(mainParty, 40, false, gameOver); // 40%
            break;
        }
        case 3:{//give up
            mainParty.loseGame(0);
            gameOver = true;
            break;
        }
    }
}
