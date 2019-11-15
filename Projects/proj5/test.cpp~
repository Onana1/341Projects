// CMSC 341, Spring 2019
// Project 5: Finding anagrams by hashing
// Driver program

#include "Anahash.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

  cout << "ok" << endl;
  Anahash aH( 1 << 16 );  // Table of size 2^16

  // Read the sample data an insert into the hash table.

  string fileName = "anagrams_single.txt";
  ifstream inFp( fileName );

  if ( inFp.is_open() ) {
    string line;
    while ( getline( inFp, line ) ) {
      if ( line.size() > 0 ) {
	aH.insert( line );
      }
    }
    inFp.close();
  } else {
    cerr << "File " << fileName << " could not be opened\n";
  }

  /*
  //use search to see if wired is in the table
  if (aH.search("wired")){
    cout << "wired is in the table" << endl;
  }else{
    cout << "wired is not in the table" << endl << endl;
  }

  
  // Use getAnagrams to retrieve the anagrams of "wired".

  cout << "wired:\n";
  auto ana = aH.getAnagrams("wired");
  for (auto itr = ana.begin(); itr != ana.end(); itr++)
    cout << "   " << *itr << endl;
  cout << endl;

  // Dump the contents of the hash table.

  cout << "Full dump of table:\n";
  aH.dump();

  //test copy constructor
  Anahash *aH2 = new Anahash(aH);
  cout << "Dump using copy constructor" << endl;
  aH2->dump();
  //cout << "Collisions: " << aH2->strCol << endl;

  //test assignment operator
  Anahash aH3(3);
  aH3 = *aH2;
  cout << "Dump using assignment operator" << endl;
  aH3.dump();
  // cout << "Collisions: " << aH3.strCol << endl;

  //delete copy and dump the original
  delete aH2;
  */
  cout << "Dump of orig after deleted copy" << endl;
  aH.dump();
  //cout << "Collisions: " << aH.strCol << endl;

  return 0;
}
  
  
