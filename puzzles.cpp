/*
* puzzles.cpp
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
*
* implementaitons of puzzles used in the game
*/

#include "puzzles.h"



//Splits a string at a given seperator an puts it into an array
int split(string inputString, char seperator, string peiceArray[], int peiceArraySize)
{   
    int lastSeperatorLocation = 0;
    int seperatorsFound = 0;

    if (inputString.length() == 0) // Empty strings retunrn 0 by project spec
    {
        return 0;
    }

    for (int i = 0; i < inputString.length()+1; i++) //Iterate through all elements in the string
    {
        if (((inputString[i]  == seperator) && peiceArraySize > seperatorsFound) || i == inputString.length() ) // If we encounter the seperator and still have room in our array we will evaluate the following
        {

            peiceArray[seperatorsFound] = inputString.substr(lastSeperatorLocation,(i-lastSeperatorLocation)); // Setting the next avalible location in the array to the string before the found seperator
            lastSeperatorLocation = i+1; // We do not include the seperator in our new array, so we set the location one higher than actual
            seperatorsFound++;
        }

        else if (peiceArraySize <= seperatorsFound) // If the array is too small retunrn -1
        {
            return -1;
        }
    }

    if (lastSeperatorLocation == 0) // If there are no seperators all the whole string goes into the array
    {
        peiceArray[0] = inputString;
        return 1;
    }
    


    return seperatorsFound;

}

int NPCPuzzle()
{
    RNG randomGenerator = RNG();
    ifstream puzzleFile; 
    puzzleFile.open("riddles.txt");

    vector<string> riddles;
    vector<string> answers; 

    if(!puzzleFile.is_open())
    {
        cout << "I seem to have lost my riddles... That just makes it easier for you!" << endl;
        return -1;
    }

    while (!puzzleFile.eof()) // Read in all riddles from the file
    {
        string tempLine;
        string tempArr[2]; 
        getline(puzzleFile, tempLine);
        
        int splitLineReturn = split(tempLine, '~', tempArr, 2); // Split each line into riddle and answer

        if (splitLineReturn == 2) 
        {
            riddles.push_back(tempArr[0]);
            answers.push_back(tempArr[1]);
        }
    }

    puzzleFile.close(); 

    int puzzleIndex = randomGenerator.randIntOnRange(0, riddles.size()-1); // Randomly select a ridd;e
    string puzzleAnswer = answers.at(puzzleIndex); // Find its answer

    string userInput; 

    // Main riddle statement
    cout << "Answer my riddle and you may trade with me, or give up (G) and suffer the price..." << endl;
    cout << riddles.at(puzzleIndex) << endl;


    // Take user input untill the player gives up or gets it right
    while (true)
    {
        cin >> userInput; 

        if (userInput == "G") return false; // G gives up
        else if (userInput == puzzleAnswer)
        {
            return true;
        }
        else
        {
            cout << "Not quite, try again:" << endl;
        }
    }

    return false; // This should never be encountered... 

}

bool doorPuzzle()
{
    RNG randomGenerator = RNG();
    const int BOULDER = 0; // Numerical representaions of the three choices
    const int PARCHMENT = 1;
    const int SHEARS = 2;

    int numberOfTries = 0;

    cout << "You try to open a door without a key? How foolish." <<
    endl << "Beat me in a game of Boulder, Parchement, Shears, and I might take pity on you" <<
    endl << "But if you are thrice defeated... Let's just say it won't be pretty." << endl << endl; 

    while (numberOfTries < 3)
    {
        char userInput;
        int userNumInput;

        cout << "Your choice. Boulder (B), Parchment (P), or Shears (S)?" << endl;
        cin >> userInput; cout << endl << endl;
        

        // Convert user's choice to an int:
        switch (userInput)
        {
            case 'B':
                userNumInput = 0;
                break;
            case 'P':
                userNumInput = 1;
                break;
            case 'S':
                userNumInput = 2;
                break;
            default: // If the user inputs a bad value make them try again
                cout << "What is this nonsense!?! Are you trying to mock me?" << endl << endl;
                continue;
        }

        int doorsNumChoice = randomGenerator.randIntOnRange(0,2);
        
        int result = (userNumInput - doorsNumChoice);
        switch(result)
        {
            case 0: // A tie
                cout << "It looks like I've picked the same as you... Let's try this again." << endl << endl;
                continue;
            case -1: // The user picked a losing item
                numberOfTries++;
                if (userNumInput == 1)
                    cout << "You've chosen poorly... Shears beat Parchment!" << endl;
                else if (userNumInput == 0)
                    cout << "You've chosen poorly... Parchment beats Boulder!" << endl;
                if (numberOfTries < 1)
                    cout << "You only have " << 3-numberOfTries << " tries left. Maybe try and pick something better next time, okay?" << endl << endl;
                else if (numberOfTries == 2)
                    cout << "You only have 1 try left. Maybe try and pick something better next time, okay?" << endl << endl;
                continue;
            case 2: // User picks shears, door picks rock
                numberOfTries++;
                cout << "You've chosen poorly... Boulder beat Shears!" << endl;
                if (numberOfTries < 1)
                    cout << "You only have " << 3-numberOfTries << " tries left. Maybe try and pick something better next time, okay?" << endl << endl;
                else if (numberOfTries == 2)
                    cout << "You only have 1 try left. Maybe try and pick something better next time, okay?" << endl << endl;
                continue;
            default:
                cout << "You've beaten me! As a reward for your luck (it certainly wasn't skill), I shall let you pass through this door." << endl;
                return true;
        }


    }
    cout << "You challenged me and lost -- now pay the price!" << endl;
    return false;

}
