/*
* move.h
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
* to run: g++ mainDriver.cpp item.cpp Monster.cpp Sorcerer.cpp party.cpp Map.cpp game.cpp RNG.cpp puzzles.cpp move.cpp
* 
* 
*/

#include "game.h"

void normalSpace(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer, bool &gameOver, vector<Monster> &monsters);

void roomSpace(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer, bool &gameOver, vector<Monster> &monsters);

void npcSpace(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer, bool &gameOver, vector<Monster> &monsters);