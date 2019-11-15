// File: Driver.cpp
//
// CMSC 341 Spring 2019
//
// Driver that has test for the program
//

#include <iostream>
using namespace std ;

#include "CTree.h"

int main() {

   CTree T ;

   //insertion
   T.insert(70) ;
   T.inorder() ; cout << endl ;

   T.insert(30) ;
   T.inorder() ; cout << endl ;

   T.insert(110) ;

   T.inorder() ; cout << endl ;

   cout << "\n\n***** Insert 40 *****\n" ;
   T.insert(40) ;
   T.inorder() ; cout << endl ;

   cout << "\n\n***** Insert 20 *****\n" ;
   T.insert(20) ;
   T.inorder() ; cout << endl ;
   
   
   cout << "Original T1:         " ;
   T.inorder() ; cout << endl ;
   
   // Use copy constructor
   CTree *Tptr = new CTree(T) ;

   cout << "Copied T1:           " ;
   Tptr->inorder() ; cout << endl; 
   
   CTree T2 ;

   T2.insert(50) ;
   T2.insert(25) ; T2.insert(75) ;

   T2 = *Tptr ;
   cout << "Second copy:         " ;
   T2.inorder() ; cout << endl ; 

   cout << "Delete first copy...\n" ;
   delete Tptr ;

   cout << "Recheck original:    " ;
   T.inorder() ; cout << endl ;
   cout << "Recheck second copy: " ;
   T2.inorder() ; cout << endl ; 
  
   //Locate Function
   int key = 9999 ;
   bool ans ;
   const char *str ;

   ans = T.locate(str="", key=-1) ;
   cout << str << ": " << ans << " " << key << endl ;

   ans = T.locate(str="LL", key=-1) ;
   cout << str << ": " << ans << " " << key << endl;
   
   //Remove function
   int n ;

   n = 20 ; cout << "removing " << n << endl ; T.remove(n) ;
   T.inorder() ; cout << endl ; 
   
   //Find function
   int b;
   b = 3  ;
   cout << "Find " << b << endl ;
   if ( T.find(b) == true ) {
     cout << T.find(b) << endl;
     cout << "found = " << b << endl ;
   } else {
     cout << "did not find = " << b << endl ;
   }
   cout << endl ;
   
}

