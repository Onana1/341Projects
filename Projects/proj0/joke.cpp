// File: joke.cpp
//
// CMSC 341 Spring 2019 Project 0
//
// Header file for knock-knock jokes
//
// Nana Owusu

#include "joke.h"
using namespace std;

//Opening statement that returns the start of the joke
string opening(){
  return "Knock Knock";
}

//Second part of the joke that returns the setup of the punchline
string setup(){
  return "Robin";
}

//Last part of the joke that returns the punchline/finish
string punchline(){
  return "Robin you, now hand over the cash.";
}
