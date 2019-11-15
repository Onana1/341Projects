// CMSC 341, Spring 2019
// Project 5: Finding anagrams by hashing
// Driver program

#include "Anahash.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
  Anahash aH(5);
  aH.insert("The dog is gone");
  aH.insert("The Dog Is gone");
  aH.dump();
  return 0;
}
