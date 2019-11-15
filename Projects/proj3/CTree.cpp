// File: CTree.cpp
//
// CMSC 341 Spring 2019
//
// cpp file for the Tree
//

#include "CTree.h"
using namespace std;

CTree::CTree(){
  m_root = NULL;
}

void CTree::copyTree(Node *myNode, Node *otherNode){
  if (otherNode == NULL){
    myNode = NULL;
  }else{
    myNode = new Node(0);
    myNode->setData(otherNode->getData());

    copyTree(myNode->getLeft(), otherNode->getLeft());
    copyTree(myNode->getRight(), otherNode->getRight());
  }
}

CTree::CTree(const CTree& other) {
  // m_root = other.m_root;
  if (other.m_root == NULL){
    m_root = NULL;
  }else{
    copyTree(m_root, other.m_root);
  }
}

CTree::~CTree(){
  delete m_root;
}

const CTree& CTree::operator=(const CTree& rhs){
  if (this != &rhs){
    //m_root = rhs.m_root;
    copyTree(m_root, rhs.m_root);
  }
  return *this;
}

void CTree::insert (int key){
  if(m_root == NULL) {
    Node *newNode = new Node(key);
    m_root = newNode;
  } else {
    m_root->insert(key);
  }
  //check rebalance doesn't work
  //rebalance();
}

bool CTree::remove(int key){
  bool nodeRem = false;
  if(m_root == NULL){
    return false;
  }else{
    if (m_root->getData() == key){
      Node tempRoot(0);
      tempRoot.setLeft(m_root);
      Node* delNode = m_root->deleteNode(key, &tempRoot);
      m_root = tempRoot.getLeft();
      if (delNode != NULL){
	delete delNode;
	nodeRem = true;
      }
    }else{
      Node* delNode = m_root->deleteNode(key, NULL);
      if (delNode != NULL){
	delete delNode;
	nodeRem = true;
      }
      
    }
    if (nodeRem == true){
    return true;
    }else{
      return false;
    }
  }
}

bool CTree::find(int key){
  if (m_root->getData() == key){
    return true;
  }else{
    return m_root->find(key);
  }
}

void CTree::rebalance(){
  Node* newNode;
  newNode = m_root->rebalance(m_root);
  return; 
}

void CTree::inorder(){
  if(m_root != NULL) {
    m_root->inorderTraversal();
    cout << endl;
  }else{
    cout << "Tree is empty" << endl;
  }
}

bool CTree::locate(const char *position, int& key){
  if (m_root == NULL){
    return false;
  }else if (position[0] == '\0'){
    key = m_root->getData();
    return true;
  }else{
    return m_root->locate(position, key);
  }
}

Node::Node(int data){
  m_data = data;
  m_left = NULL;
  m_right = NULL;
  m_height = 0;
  m_size = 1;
}
/*
void Node::copyTree(Node* myNode, Node* otherNode){
  if (otherNode == NULL){
    myNode = NULL;
  }else{
    myNode = new Node(0);
    myNode->m_data = otherNode->m_data;

    copyTree(myNode->m_left, otherNode->m_left);
    copyTree(myNode->m_right, otherNode->m_right);
  }
}
*/
/*
Node::Node(const Node& other){
  m_left = nullptr;
  m_right = nullptr;
  m_data = other.m_data;
  
  if (other.m_left != nullptr){
    m_left = new Node(*other.m_left);
  }
   if (other.m_right != nullptr){
    m_right = new Node(*other.m_right);
  }
}
*/

Node::~Node(){
  if(m_left != NULL) {
      delete m_left;
    }

    if(m_right != NULL) {
      delete m_right;
    }

    cout << "Deleting " << m_data << endl;
}

/*
const Node& Node::operator=(const Node& rhs){
  m_data = rhs.m_data;

  Node* newLeft = m_left;
  Node* newRight = m_right;
  
  m_left = new Node(*rhs.m_left);
  m_right = new Node(*rhs.m_right);
  
  delete newLeft;
  delete newRight;
  
  m_left = nullptr;
  m_right = nullptr;
  m_data = rhs.m_data;

  if (rhs.m_left != nullptr){
    m_left = new Node(*rhs.m_left);
  }
  if (rhs.m_right != nullptr){
    m_right = new Node(*rhs.m_right);
  }
  
  return *this;
}
*/

int Node::getData(){
  return m_data;
}

void Node::setData(int data){
  m_data = data;
}

Node* Node::getLeft(){
  return m_left;
}

Node* Node::getRight(){
  return m_right;
}

void Node::setLeft(Node *left){
  m_left = left;
}

void Node::setRight(Node *right){
  m_right = right;
}

/*void Node::changeSize(Node* Node, int s){
  if (Node == NULL){
    return;
  }
  if (Node->m_right != NULL){
    s++;
  }
  if (Node->m_left != NULL){
    s++;
  }
  Node->m_size = s;
  //changeSize(Node->m_left) + 1 + changeSize(Node->m_right));
  changeSize(Node->m_left, s);
  changeSize(Node->m_right, s);
}
void Node::changeHeight(Node* Node, int h){
  if (Node == NULL){
    //h++;
    //Node->m_height = h;
    return;
  }
 h++;
  Node->m_height = h;
  changeHeight(Node->m_left, h);
  changeHeight(Node->m_right, h);
  
  changeHeight(Node->m_left, h);
  h++;
  Node->m_height = h;
  changeHeight(Node->m_right, h);
  h++;
  //h++;
  //Node->m_height = h;
  //Node->m_height = h;
  //h++;
}
	        
int Node::findHeight(Node* Node){
  if (node == NULL){
    return 0;
  }else{
    int lHeight = AdHeight(Node->m_left);
    int rHeight = AdHeight(Node->m_right);

    if (lHeight > rHeight){
      return(lHeight + 1);
    }else{
      return(rHeight + 1);
    }
  }
}
*/

//void Node::appendTree(Node* Node){
  
Node* Node::rebalance(Node* parent){
  if (parent == NULL){
    return NULL;
  }
  if (parent->m_left != NULL && parent->m_right == NULL){
    if (parent->m_left->m_size > 2){
      int treeArr[parent->m_size];
      int index = -1;
      treeToArray(parent, treeArr, index);
      return arrayToTree(treeArr, 0, parent->m_size);
    }
  }
  else if (parent->m_left == NULL && parent->m_right != NULL){
    if (parent->m_right->m_size > 2){
      int treeArr[parent->m_size];
      int index = -1;
      treeToArray(parent, treeArr, index);
      return arrayToTree(treeArr, 0, parent->m_size);
    }
  }
  else if (((parent->m_left->m_size - parent->m_right->m_size)> 2)  ||
	   ((parent->m_right->m_size - parent->m_left->m_size) > 2)){
    int treeArr[parent->m_size];
    int index = -1;
    treeToArray(parent, treeArr, index);
    return arrayToTree(treeArr, 0, parent->m_size);
  }
  else{
    return rebalance(parent->m_left);
    return rebalance(parent->m_right);
  }
}

int Node::treeToArray(Node* Node, int Arr[], int num){
  if (Node == NULL){
    return 0;
  }
  return treeToArray(Node->m_left, Arr, num);
  num++;
  Arr[num] = Node->m_data;
  return treeToArray(Node->m_right, Arr, num);
}

Node* Node::arrayToTree(int Arr[], int Begin, int End){
  if (Begin > End){
    return NULL;
  }
  int Middle = (Begin+End)/2;
  Node* newNode = new Node(Arr[Middle]);
  newNode->m_left = arrayToTree(Arr, Begin, Middle - 1);
  newNode->m_left = arrayToTree(Arr, Middle + 1, End);
  return newNode;
}

bool Node::find(int data){
  if (data < m_data){
    if (m_left == NULL){
      return false;
    }else if (m_left->getData() == data){
      return true;
    }else{
      return m_left->find(data);
    }
  }

  if (data > m_data){
    if (m_right == NULL){
      return false;     
    }
    else if (m_right->getData() == data){
      return true;
    }else{
      return m_right->find(data);
    }
  }
}
 	
void Node::insert(int data){
  if (data != m_data){
    if (data < m_data){
      if (m_left == NULL){
	m_left = new Node(data);
	this->m_size++;
	//adjusting height
	if (this->m_right != NULL){
	  if (this->m_left->m_height > this->m_right->m_height){
	    this->m_height = m_left->m_height+1;
	  }
	}else{
	  this->m_height = m_left->m_height+1;
	}
	return;
      }else{
	m_left->insert(data);
	this->m_size++;
	//adjusting hieght
	if (this->m_left != NULL){
          if (this->m_left->m_height > this->m_right->m_height){
            this->m_height = m_left->m_height+1;
          }
        }else{
          this->m_height = m_right->m_height+1;
        }
	return;
      }
    }
    if (data > m_data){
      if(m_right == NULL){
	m_right = new Node(data);
	this->m_size++;
	if (this->m_left != NULL){
	  //adjusting height
	  if (this->m_left->m_height > this->m_right->m_height){
	    this->m_height = m_left->m_height+1;
	  }
	}else{
          this->m_height = m_right->m_height+1;
        }
	return;
      }else{
	m_right->insert(data);
	//adjusting height
	this->m_size++;
	if (this->m_right != NULL){
          if (this->m_left->m_height > this->m_right->m_height){
            this->m_height = m_left->m_height+1;
          }
        }else{
          this->m_height = m_left->m_height+1;
        }
	return;
      }
    }
  }
}

Node* Node::deleteNode(int data, Node* parent){
  if (data < m_data){
    if (m_left != NULL){
      if ((m_left->deleteNode(data, this)) != NULL){
	  m_size--;
      }
      return parent;
    }else{
      return NULL;
    }
  }else if(data > m_data){
    if (m_right != NULL){
      if ((m_right->deleteNode(data, this)) != NULL){
	m_size--;
      }
      return parent;
    }else{
      return NULL;
    }
  }else{
    //node to be deleted has 2 children
    if (m_left != NULL && m_right != NULL){
      m_data = m_right->minData();
      return m_right->deleteNode(m_data, this);
      //node to be deleted has one right child
    }else if (parent->m_left == this){
      if (m_left != NULL){
	parent->m_left = m_left;
      }else{
	parent->m_left = m_right;
      }
      return this;
      //node to be deleted has one left child
    }else if (parent->m_right == this){
      if (m_left != NULL){
        parent->m_right = m_left;
      }else{
        parent->m_right = m_right;
      }
      return this;
    }
  }
} 
    
void Node::inorderTraversal(){
  cout << "(";
  if (m_left){
    m_left->inorderTraversal();
  }
  cout << m_data << ":" << m_height << ":" << m_size;
  if(m_right) {
    m_right->inorderTraversal();
  }
  cout << ")";
}

bool Node::locate(const char *position, int& key){
  if (*position == 'L'){
    if (m_left == NULL){
      return false;
    }else{
      return m_left->locate(position+1, key);
    }
  }
  if (*position == 'R'){
    if (m_right == NULL){
      return false;
    }else{
      return m_right->locate(position+1, key);
    }
  }
  if (*position != 'L' && *position != 'R'){
    key = m_data;
    return true;
  }
  else{
    return false;
  }
}

int Node::minData(){
  if (m_left == NULL){
    return m_data;
  }else{
    return m_left->minData();
  }
}
