#include <cstring>
#include <iostream>
#include "Anahash.h"

// Create a Anahash object with hash table of size 'htSize'.  If
// 'htSize' is greater than HT_SIZE_LIMIT or less than 1, throw a
// range_error exception.
Anahash::Anahash( int htSize ){
  if (htSize < 1 || htSize > (int)HT_SIZE_LIMIT){
    throw std::range_error("This is not a valid size");
  }
  m_htSize = htSize;
  m_ht = new set<string>[m_htSize];
}

// Copy constructor
Anahash::Anahash( const Anahash& rhs ){
  //std::set<string>::iterator it;
  m_htSize = rhs.m_htSize;
  m_ht = new set<string>[m_htSize];
  for (int i = 0; i < m_htSize; i++){
    if (!rhs.m_ht[i].empty()){
      m_ht[i] = rhs.m_ht[i];
    }
  }
}

// Assignment operator
Anahash& Anahash::operator=( const Anahash& rhs ){
  if (this != &rhs){
    m_htSize = rhs.m_htSize;
    delete [] m_ht;
    m_ht = new set<string>[m_htSize];
    for (int i = 0; i < m_htSize; i++){
      if (!rhs.m_ht[i].empty()){
	m_ht[i] = rhs.m_ht[i];
      }
    }
  }
  return *this;
}


// Destructor
Anahash::~Anahash(){
  delete [] m_ht;
}


//function that makes elements in a char array uppercase  
void Anahash::makeUpper(char Arr[], int size){
  for (int i = 0; i < size; i++){
   Arr[i] = toupper(Arr[i]);
  }
}

// Insert 'line' into hash table.  Return true if a new entry is
// created, false if the line is already in the table.
bool Anahash::insert( string line ){
  //hash modded by the array size 
  int strInd = anaHash(line)%m_htSize;
  int insEnd = strInd;
  int varCheck = 0;

  //if the hash index is empty then insert the line
  while (strInd < m_htSize){
    if (m_ht[strInd].empty()){
      m_ht[strInd].insert(line);
      return true;
    }
    //if we linear prob and go through the whole table without inserting
    if (varCheck == 1 && strInd == insEnd){
      return false;
    }
    //set up iterator to get the first item of a set and a copy of line
    auto strFir = m_ht[strInd].begin();
    string lineComp = *strFir;
    string lineCopy = line;
    //get rid of the whitespace in the set comparison
    for(int i=0; lineComp[i]; i++){
      if(lineComp[i] == ' '){
	lineComp.erase(i,1);
      }
    }
    //get rid of whitspace in the line copy
    for(int i=0; lineCopy[i]; i++){
      if(lineCopy[i] == ' '){
        lineCopy.erase(i,1);
      }
    }
    //get the size and create a char array
    int compSize = lineComp.length()+1;
    int copySize = lineCopy.length()+1;
    char charLineComp[compSize];
    char charLineCopy[copySize];

    //turn the strings into char arrays
    strcpy(charLineComp, lineComp.c_str());
    strcpy(charLineCopy, lineCopy.c_str());

    //make each char in the char array into uppercase
    makeUpper(charLineComp, compSize);
    makeUpper(charLineCopy, copySize);

    //get the strings back from the char array
    lineComp = charLineComp;
    lineCopy = charLineCopy;

    //sort the letters of the string
    sort(lineComp.begin(),lineComp.end());
    sort(lineCopy.begin(),lineCopy.end());

    //check if both strings are the same and insert if they are
    if (lineCopy == lineComp){
      int setBefSize = m_ht[strInd].size();
      m_ht[strInd].insert(line);
      //checks if size of set changed and if it did something was inserted
      //if not the it was a duplicate
      if ((int)m_ht[strInd].size() > setBefSize){
	return true;
      }else{
	return false;
      }
      //linear prob and go to next index if not equal
    }else if (strInd < m_htSize){
      strInd++;
      //goes to the start of the array if the end is reached
    }else if (strInd == m_htSize-1){
      strInd = 0;
      varCheck = 1;
    }
  }
  return false;
 
}

// Search for 'line' in the hash table.  Return true if found, false
// otherwise.
bool Anahash::search( string line ){
  int strInd = anaHash(line)%m_htSize;
  int insEnd = strInd;
  int varCheck = 0;
  
  //if the hash index is empty then insert the line is not in the table
   while (strInd < m_htSize){
    if (m_ht[strInd].empty()){
      return false;
    }
    //if we linear prob and go through the whole table without finding the line
    if (varCheck == 1 && strInd == insEnd){
      return false;
    }
    //set up iterator to get the first item of a set and a copy of line
    auto strFir = m_ht[strInd].begin();
    string lineComp = *strFir;
    string lineCopy = line;
    
    //get rid of the whitespace in the set comparison
    for(int i=0; lineComp[i]; i++){
      if(lineComp[i] == ' '){
        lineComp.erase(i,1);
      }
    }
    //get rid of the whitespace in the line copy
    for(int i=0; lineCopy[i]; i++){
      if(lineCopy[i] == ' '){
        lineCopy.erase(i,1);
      }
    }
    
    //get the size and create a char array
    int compSize = lineComp.length()+1;
    int copySize = lineCopy.length()+1;
    char charLineComp[compSize];
    char charLineCopy[copySize];

    //makes the contents of the char array the strings
    strcpy(charLineComp, lineComp.c_str());
    strcpy(charLineCopy, lineCopy.c_str());

    //make the contents in the string uppercase
    makeUpper(charLineComp, compSize);
    makeUpper(charLineCopy, copySize);

    //make the strings the contents of the char array
    lineComp = charLineComp;
    lineCopy = charLineCopy;

    //sort the letters of the string
    sort(lineComp.begin(),lineComp.end());
    sort(lineCopy.begin(),lineCopy.end());

    //checks if the 2 strings are the same then
    if (lineCopy == lineComp){
      //checks if the string is in the set and returns the count
      if(m_ht[strInd].count(line) != 0){
	return true;
      }
      //increments the index 
    }else if (strInd < m_htSize){
      strInd++;
      //sets the index to the beginning to go through the whole table
    }else if (strInd == m_htSize-1){
      strInd = 0;
      varCheck = 1;
    }
   }
   //return false if the loop is exited incorrectly
   return false;
}

// If 'line' is in the the hash table, return its set of anagrams,
// including 'line'.  If 'line' is not in the hash table, return an
// emtpy set of strings.
set<string> Anahash::getAnagrams( string line ){
  set<string> emptySet;
  int strInd = anaHash(line)%m_htSize;
  int insEnd = strInd;
  int varCheck = 0;
  //if the hash index is empty the return an empty set
   while (strInd < m_htSize){
    if (m_ht[strInd].empty()){
      return emptySet;
    }
    //if you loop through the who table without finding return empty set
    if (varCheck == 1 && strInd == insEnd){
      return emptySet;
    }
    //same as other functions above get rid
    //of white space, make string uppercase, and sort string
    auto strFir = m_ht[strInd].begin();
    string lineComp = *strFir;
    string lineCopy = line;
    
    for(int i=0; lineComp[i]; i++){
      if(lineComp[i] == ' '){
        lineComp.erase(i,1);
      }
    }
    for(int i=0; lineCopy[i]; i++){
      if(lineCopy[i] == ' '){
        lineCopy.erase(i,1);
      }
    }
    int compSize = lineComp.length()+1;
    int copySize = lineCopy.length()+1;
    char charLineComp[compSize];
    char charLineCopy[copySize];

    strcpy(charLineComp, lineComp.c_str());
    strcpy(charLineCopy, lineCopy.c_str());

    makeUpper(charLineComp, compSize);
    makeUpper(charLineCopy, copySize);

    lineComp = charLineComp;
    lineCopy = charLineCopy;
    sort(lineComp.begin(),lineComp.end());
    sort(lineCopy.begin(),lineCopy.end());

    //checks if the line is in the table 
    if (lineCopy == lineComp){
      if(m_ht[strInd].count(line) != 0){
	//returns the entire set
        return m_ht[strInd];
      }
      //increments the table index
    }else if (strInd < m_htSize){
      strInd++;
      //loops to the beginning of the table
    }else if (strInd == m_htSize-1){
      strInd = 0;
      varCheck = 1;
    }
   }
   //return empty set if all the
   return emptySet;
   
}

// Dump all non-empty lists from the hash table.  Print the hash
// value in hexadecimal and the strings in the list.
void Anahash::dump(){
  //create a set iterator
  std::set<string>::iterator it;
  for (int i = 0; i < m_htSize; i++){
    //checks if the set is not empty
    if (!m_ht[i].empty()){
      cout << hex << i << endl;
      //outputs the contents of a set
      for (it=m_ht[i].begin(); it!=m_ht[i].end(); ++it)
	cout << "  " <<  *it << endl;
    }
  }
}

 
// Hash function
unsigned int Anahash::anaHash( string line ){
  int hashNum = 0;
  //get rid of whitespace
  for(int i=0; line[i]; i++){
      if(line[i] == ' '){
        line.erase(i,1);
      }
  }
  //go through every letter inthe string and make it lower case then get the ascii value
  //and adjust it with functions
  for (int i = 0; i < (int)line.size(); i++){
    hashNum += ((((((((((int)tolower(line[i])) * 3) << 2)/7) ^ 31)+ 3) * 5) >>
		 1)^41); 
  }
  return (unsigned int)hashNum;
}
