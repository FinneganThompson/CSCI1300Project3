#include "move.h"



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

void normalSpace(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer, bool &gameOver, vector<Monster> &monsters){
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
            proceed = 'l';
            while(proceed != 'n' && proceed != 'y'){
                cout << "Are you sure you'd like to " << turnOptions.at(spaceChoice-1) << "? (y/n)\n" << endl;
                cin >> proceed;
                cout << endl;
                if(proceed != 'n' && proceed != 'y'){
                    cout << "What kind of an answer is that? I only understand y or n.\n" << endl; 
                }
            }
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
            investigate(mainParty, gameOver);
            mainMap.exploreSpace(mainMap.getPlayerRow(),mainMap.getPlayerCol());
            endOfTurnMisfortune(mainParty, 40, false, gameOver); // 40%
            break;
        }
        case 3:{
            RNG random;
            cout << "Oh! You've chosen to try your luck with a monster.\n" << endl; 
            fightMonster(monsters, mainParty, false, gameOver);
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
for room spaces 
	move
	open the door
		if monster is defeated 60% of misfortune 
		if does not defeat monster consequences (key is lost, 40% chance of misfortune)
	give up
    */

void roomSpace(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer, bool &gameOver, vector<Monster> &monsters){
    vector<string> turnOptions = {"Move to a different space","Open the room door","Give up on your adventure"};
    int spaceChoice;
    char proceed = 'n';
    while(proceed == 'n'){
        cout << "You happen across a door to a room, here are your options:" << endl;
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
            proceed = 'l';
            while(proceed != 'n' && proceed != 'y'){
                cout << "Are you sure you'd like to " << turnOptions.at(spaceChoice-1) << "? (y/n)\n" << endl;
                cin >> proceed;
                cout << endl;
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
            RNG random;
            if(mainParty.getKeysFound() > 0){ // get into room with key
                // Check for sorcerer
                if(mainParty.getRoomsCleared() == 4)
                {
                    cout << "You got in the room using a key. Inside you see the Sorcerer.\n";
                    fightSorcerer(mainParty, gameSorcerer, monsters);
                    break;
                }
            
                cout << "You got in the room using a key, inside you see a monster.\n" << endl; 
                // check if player wins the fight
                if(fightMonster(monsters, mainParty, true, gameOver) == true){ // win
                    mainParty.loseKey();
                    endOfTurnMisfortune(mainParty, 60, true, gameOver); // 60%
                    mainParty.increaseRoomsCleared();
                }
                else{ // loss
                    mainParty.loseKey(); 
                    endOfTurnMisfortune(mainParty, 40, true, gameOver); // 40%
                }
                if(random.doesActionOccur(50) == true){
                    for(int i = 0; i < mainParty.getPlayers().size(); i++){
                        mainParty.removeHunger(i,1);
                    }
                    cout << "You all became tired from exploring, -1 hunger.\n" << endl;
                }
            }
            else{ // no key
                //check if player wins boulder, parchment, sheers 
                if(doorPuzzle() == true){ // win
                    // Check for sorcerer
                    if(mainParty.getRoomsCleared() == 4)
                    {
                        cout << "You got in without a key. Inside you see the Sorcerer.\n";
                        fightSorcerer(mainParty, gameSorcerer, monsters);
                        break;
                    }
            
                    cout << "Dispite not having a key, you got in the room. Inside you see a monster.\n" << endl; 
                    fightMonster(monsters, mainParty, false, gameOver);
                    // check if player wins the fight
                    if(fightMonster(monsters, mainParty, false, gameOver) == true){ // win
                        endOfTurnMisfortune(mainParty, 40, false, gameOver); // 40%
                        mainParty.increaseRoomsCleared();

                    }
                    else{ // loss
                        mainParty.loseKey();
                        endOfTurnMisfortune(mainParty, 40, false, gameOver); // 40%
                    }
                    if(random.doesActionOccur(50) == true){
                        for(int i = 0; i < mainParty.getPlayers().size(); i++){
                            mainParty.removeHunger(i,1);
                        }
                        cout << "You all became tired from exploring, -1 hunger.\n" << endl;
                    }
                }
                else{ // loss
                    // maybe make check to make sure that they are not the user
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
for npc spaces
	move
	speak to npc 
		if complete puzzle can sell 
		if not complete will sommon monster 
		space changes to explored no matter what
	give up
*/

void npcSpace(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer, bool &gameOver, vector<Monster> &monsters){
    vector<string> turnOptions = {"Move to a different space","Speak to the NPC","Give up on your adventure"};
    int spaceChoice;
    char proceed = 'n';
    while(proceed == 'n'){
        cout << "You have run into an NPC, here are your options:" << endl;
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
            proceed = 'l';
            while(proceed != 'n' && proceed != 'y'){
                cout << "Are you sure you'd like to " << turnOptions.at(spaceChoice-1) << "? (y/n)\n" << endl;
                cin >> proceed;
                cout << endl;
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
            if(NPCPuzzle() == true){
                cout << "Congratulations on completing my riddle, allow me to offer my services!\n" << endl;
                merchantMenu(mainParty);
            }
            else if(NPCPuzzle() == false){
                RNG random;
                cout << "Not too clever I see. Say hello to my friend. HAHAHA!\n" << endl;
                fightMonster(monsters, mainParty, false, gameOver);
                if(random.doesActionOccur(50) == true){
                    for(int i = 0; i < mainParty.getPlayers().size(); i++){
                        mainParty.removeHunger(i,1);
                    }
                    cout << "You all became tired from exploring, -1 hunger.\n" << endl;
                }  
            }
            else{
                cout << "You may not have completed my riddle but since I couldn't find them, I shall still offer my services.\n" << endl;
                merchantMenu(mainParty);
            }
            mainMap.exploreSpace(mainMap.getPlayerRow(),mainMap.getPlayerCol());
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