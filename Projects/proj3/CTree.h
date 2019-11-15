// File: CTree.h
//
// CMSC 341 Spring 2019
//
// Header file for Tree class
//

#include <iostream>
using namespace std;

#ifndef _CTREE_H_
#define _CTREE_H_

class Node {
 public:
  Node(int data);

  //Node(const Node& other);
  //void copyTree(Node* myNode, Node* otherNode);
  ~Node();

  //const Node& operator=(const Node& rhs);

  int getData();

  void setData(int data);

  Node *getLeft();

  Node *getRight();

  void setLeft(Node *left);

  void setRight(Node *right);
  Node* rebalance(Node* Node);
  int treeToArray(Node* Node, int Arr[], int num);
  Node* arrayToTree(int Arr[], int Begin, int End);
  bool find(int data);

  void insert(int data);

  Node* deleteNode(int data, Node* parent);

  void inorderTraversal();

  bool locate(const char *position, int& key);

  int minData();

 private:
  int m_data;
  Node *m_left;
  Node *m_right;
  int m_height;
  int m_size;
};

class CTree {

public:
  // Default tree constructor
  CTree();

  void copyTree(Node *myNode, Node *otherNode);
  
  // Tree copy constructor
  CTree(const CTree& other);

  // Tree destructor
  ~CTree();

  // Tree assignment operator
  const CTree& operator= (const CTree& rhs);

  // Insert function that adds an item to the Tree with a certain signature
  void insert(int key);

  // Remove function that finds and removes an item with a given key
  bool remove(int key);

  // Find function that returns whether the item is in the tree
  bool find(int key);

  // Function that rebalances a subtree of the Tree
  void rebalance();

  // Function that perfroms in order walk of the tree at each node
  // returns the key:height:size of each node
  void inorder();

  // Returns if there is a node in a given position and stores the item
  // in the reference
  bool locate(const char *position, int& key);

private:
  //CTree *m_Tree;
  Node *m_root;
  //int m_height;
  //int m_size;

};

/*  
class Node {
 public:
  Node(int data);

  Node(const Node& other);
  
  ~Node();
  
  const Node& operator=(const Node& rhs);
    
  int getData();

  void setData(int data);

  Node *getLeft();
  
  Node *getRight();

  void setLeft(Node *left);

  void setRight(Node *right);
  int changeSize();
  void changeHeight();
  //int findHeight(Node* Node);

  bool find(int data);

  void insert(int data);

  Node* deleteNode(int data, Node* parent);
  
  void inorderTraversal();
  
  bool locate(const char *position, int& key);

  int minData();
  //void preorderTraversal();
  //void postorderTraversal();
  
 private:
  int m_data;
  Node *m_left;
  Node *m_right;
  int m_height;
  int m_size;
};
*/
#endif
