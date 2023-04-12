#include "npc.h"

    // no default constructor 
    // parameterized constructor
    Monster :: Monster(string inputName, int inputLevel){
        string name = inputName;
        int level = inputLevel;
    }
    string Monster :: getName(){
        return name;
    }
    void Monster :: setName(string inputName){
        name = inputName;
    }
    int Monster :: getLevel(){
        return level;
    }
    void Monster :: setLevel(int inputLevel){
        level = inputLevel;
    }

    // no default constructor 
    // parameterized constructor
    Sorcerer :: Sorcerer(string inputName, int inputLevel){
        string name = inputName;
        int level = inputLevel;
        int anger = 0;
    }
    string Sorcerer :: getName(){
        return name;
    }
    void Sorcerer :: setName(string inputName){
        name = inputName;
    }
    int Sorcerer :: getLevel(){
        return level;
    }
    void Sorcerer :: setLevel(int inputLevel){
        level = inputLevel;
    }
    int Sorcerer :: getAnger(){
        return anger;
    }
    void Sorcerer :: increaseAnger(){
        anger += 1;
    }
