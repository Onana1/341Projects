// File: Graph.cpp
//
// CMSC 341 Spring 2019
//
// Cpp file for Graph class
//
// Nana Owusu

#include <iostream>
#include "Graph.h"
using namespace std;


//constructor for the graph
Graph::Graph(int n){
  if (n < 1){
    throw out_of_range("The amount of vertices has to be more than 0");
  }
  m_numVert = n;
  m_nz = new int[n]();
  m_ci = new int[n]();
  m_re = new int[n+1]();  
  m_numEdge = 0;
  m_cap = n;
    
}

// Graph copy constructor
Graph::Graph(const Graph& G){
  m_cap = G.m_cap;
  m_numVert = G.m_numVert;
  m_numEdge = G.m_numEdge;
  m_nz = new int[m_cap]();
  m_ci = new int[m_cap]();
  m_re = new int[m_cap]();

  for (int i = 0;  i<G.m_cap; i++)
    {
      m_nz[i] = G.m_nz[i];
    }
  delete []G.m_nz;
  
  for (int i = 0;  i<G.m_cap; i++)
    {
      m_re[i] = G.m_re[i];
    }
  delete []G.m_re;
  
  for (int i = 0;  i<G.m_cap; i++)
    {
      m_ci[i] = G.m_ci[i];
    }
  delete []G.m_ci;


}

// Graph destructor
Graph::~Graph(){
  delete [] m_nz;
  delete [] m_re;
  delete [] m_ci;
  m_nz = NULL;
  m_re = NULL;
  m_ci = NULL;
    
}

 // Graph assignment operator
const Graph& Graph::operator= (const Graph& rhs){
  if ( this != &rhs ){
     m_cap = rhs.m_cap;
     m_numVert = rhs.m_numVert;
     m_numEdge = rhs.m_numEdge;
     m_nz = new int[m_cap]();
     m_ci = new int[m_cap]();
     m_re = new int[m_cap]();
     
     for (int i = 0;  i<rhs.m_cap; i++)
       {
	 m_nz[i] = rhs.m_nz[i];
       }
     delete []rhs.m_nz;

     
     for (int i = 0;  i<rhs.m_cap; i++)
       {
	 m_re[i] = rhs.m_re[i];
       }
     delete []rhs.m_nz;
     
     for (int i = 0;  i<rhs.m_cap; i++)
       {
	 m_ci[i] = rhs.m_ci[i];
       }
     delete []rhs.m_nz;
  }
  return *this;
}
// return number of vertices
int Graph::numVert(){
  return m_numVert;
}

// return number of edges
int Graph::numEdge(){
  return m_numEdge/2;
}

// add edge between u and v with weight x
void Graph::addEdge(int u, int v, int x){
  // cout << "this is the EDGE" << m_numEdge << endl;
  if (u < 0 || v < 0){
    throw out_of_range("This is not in the range");
      }
  if (u > m_numVert - 1 || v > m_numVert - 1){
    throw out_of_range("This is not in the range");
      }
  if (u == v){
    throw out_of_range("You cannot make a self edge");
      }
  //check if row is filled
  if (m_numEdge == m_cap){
    int *temp = new int[2 * m_cap]();
    int *tempc = new int[2 * m_cap]();
    for (int i = 0; i < m_cap; i++){
      temp[i] = m_nz[i];
    }
    delete [] m_nz;
    m_nz = temp;

    for (int i = 0; i < m_cap; i++){
      tempc[i] = m_ci[i];
    }
    delete [] m_ci;
    m_ci = tempc;
    m_cap = m_cap * 2;
  }

  int runAddIn = 0;
  //check if something is already in that uv spot
  if (m_numEdge > 0){
    if (m_re[u] != m_re[u+1]){
      for (int i = m_re[u]; i < m_re[u+1]; i++){
	if (m_ci[i] == v){
	  m_nz[i] = x;
	  runAddIn = 1;
	}
      }
    }
    if (m_re[v] != m_re[v+1]){
      for (int i = m_re[v]; i < m_re[v+1]; i++){
	if (m_ci[i] == u){
	  m_nz[i] = x;
	  runAddIn = 1;
	}
      }
    }
  }
  
  
  if (u != v && runAddIn == 0){
    //adding(u,v)
    //makes open space to input item if row is empty
    /*if (m_re[u] == m_re[u+1]){
      for (int t = m_numEdge; t > m_re[u]; t--){
          m_ci[t] = m_ci[t-1];
          m_nz[t] = m_nz[t-1];
      }
       m_ci[m_re[u]] = 0;
       m_nz[m_re[u]] = 0;
       }*/
    //shifts re for new edge getting added
    for(int i = u+1; i<=m_numVert; i++){
      m_re[i] = m_re[i] + 1;
    }
    //indexes through row
    for (int i = m_re[u]; i < m_re[u+1]; i++){
      //if the item is less than the index move everything right of insertion
      //and insert
      if (v <= m_ci[i] && m_re[u] != m_re[u+1]){
        for (int p = m_numEdge; p >= i; p--){
          m_ci[p] = m_ci[p-1];
          m_nz[p] = m_nz[p-1];
        }
        m_ci[i] = v;
        m_nz[i] = x;
        m_numEdge = m_numEdge + 1;
        m_re[m_numVert] = m_numEdge;
        i = m_re[m_numVert];
      }
      //if the insert nz index is empty from moving it earlier, insert the item
      else if (m_nz[i] == 0){
        m_ci[i] = v;
        m_nz[i] = x;
        m_numEdge = m_numEdge + 1;
        m_re[m_numVert] = m_numEdge;
      }
      //if the item is more than the everything in that row
      //move everything right of insertion point and insert
      else if(v >= m_ci[i] && m_re[u] != m_re[u+1] && i+1 == m_re[u+1] - 1){
        for (int g = m_numEdge; g > i+1 ; g--){
          m_ci[g] = m_ci[g-1];
          m_nz[g] = m_nz[g-1];
        }
        m_ci[i+1] = v;
        m_nz[i+1] = x;
        m_numEdge = m_numEdge + 1;
        m_re[m_numVert] = m_numEdge;
	i = m_re[m_numVert];
      }
    }
    //checking if graph is full and if make new graph with double cap
    if (m_numEdge == m_numVert){
      int *temp = new int[2 * m_cap]();
      int *tempc = new int[2 * m_cap]();
      for (int i = 0; i < m_cap; i++){
	temp[i] = m_nz[i];
      }
      delete [] m_nz;
      m_nz = temp;
      
      for (int i = 0; i < m_cap; i++){
	tempc[i] = m_ci[i];
      }
      delete [] m_ci;
      m_ci = tempc;
      m_cap = m_cap * 2;
    }
    //adding (v,u)
    //makes open space to input item if row is empty 
    if (m_re[v] == m_re[v+1]){
      for (int t = m_numEdge; t > m_re[v]; t--){
          m_ci[t] = m_ci[t-1];
          m_nz[t] = m_nz[t-1];
      }
       m_ci[m_re[v]] = 0;
       m_nz[m_re[v]] = 0;
    }
    //shifts re for new Edge getting added
    for(int i = v+1; i<=m_numVert; i++){
      m_re[i] = m_re[i] + 1;
    }
    for (int i = m_re[v]; i < m_re[v+1]; i++){
      //if the item is less than the index move everything right of insertion
      //and insert
      if (u <= m_ci[i] && m_re[v] != m_re[v+1]){
        for (int p = m_numEdge; p > i; p--){
          m_ci[p] = m_ci[p-1];
          m_nz[p] = m_nz[p-1];
        }
        m_ci[i] = u;
        m_nz[i] = x;
        m_numEdge = m_numEdge + 1;
	m_re[m_numVert] = m_numEdge;
	i = m_re[m_numVert];
      }
      //if the insert nz index is empty from moving it earlier, insert the item
      else if (m_nz[i] == 0){
        m_ci[i] = u;
        m_nz[i] = x;
        m_numEdge = m_numEdge + 1;
        m_re[m_numVert] = m_numEdge;
      }
      //if the item is more than the everything in that row
      //move everything right of insertion point and insert
      else if(u >= m_ci[i] && m_re[v] != m_re[v+1] && i+1 == m_re[v+1] - 1){
	for (int g = m_numEdge; g > i+1 ; g--){
          m_ci[g] = m_ci[g-1];
          m_nz[g] = m_nz[g-1];
        }
        m_ci[i+1] = u;
        m_nz[i+1] = x;
        m_numEdge = m_numEdge + 1;
        m_re[m_numVert] = m_numEdge;
	i = m_re[m_numVert];
      }
    }
  }
}

// print out data structure for debugging
void Graph::dump(){
  cout << "Number of Vertices: " << m_numVert << endl;
  cout << "Number of Edges: " << m_numEdge/2 << endl;
  cout << "Capactiy of NZ: " << m_cap << endl;

  cout << "m_nz: " << "";
  for(int i = 0; i < m_re[m_numVert]; i++)
    { 
      cout << m_nz[i] << " ";
    }
  cout << endl;

  cout << "m_ci: " << "";
  for(int i = 0; i < m_re[m_numVert]; i++)
    {
      cout << m_ci[i] << " ";
    }
  cout << endl;
  
  cout << "m_re: " << "";
  for(int i = 0; i <= m_numVert; i++)
    {
      cout << m_re[i] << " ";
    }
  cout << endl;
}

// Edge Iterator constructor; indx can be used to
// set m_indx for begin and end iterators.
Graph::EgIterator::EgIterator(Graph *Gptr, int indx){
  m_Gptr = Gptr;
  m_indx = indx;
}

// Compare iterators; only makes sense to compare with
// end iterator
bool Graph::EgIterator::operator!=(const EgIterator& rhs){
  if(m_indx != rhs.m_indx){
    return true;
  }else{
    return false;
  }
}

// Move iterator to next printable edge
void Graph::EgIterator::operator++(int dummy){
  m_indx++;
  if (m_indx == m_Gptr->m_re[m_row + 1]){
    m_row++;
  }
  for(int i = 0; i < m_row; i++){
    if (m_Gptr->m_ci[m_indx] == i){
      m_indx++;
    }
  }
}

// return edge at iterator location
std::tuple<int,int,int> Graph::EgIterator::operator*(){
  if (m_indx == (m_Gptr->m_numEdge) * 2){ 
    throw std::out_of_range("The iterator has reached its end");
  }
  return std::make_tuple(m_row, m_Gptr->m_ci[m_indx], m_Gptr->m_nz[m_indx]);
}

// Make an initial edge Iterator
Graph::EgIterator Graph::egBegin(){
  return EgIterator(this);
}

// Make an end iterator for edge iterator
Graph::EgIterator Graph::egEnd(){
  return EgIterator(this, m_re[m_numVert]);
}

Graph::NbIterator::NbIterator(Graph *Gptr, int v, int indx){
  m_Gptr = Gptr;
  m_row = v;
  m_indx = indx;
}

// Compare iterators; only makes sense to compare with
// end iterator
bool Graph::NbIterator::operator!=(const NbIterator& rhs){
  return m_indx != rhs.m_indx;
}

// Move iterator to next neighbor
void Graph::NbIterator::operator++(int dummy){
  m_indx = m_indx + 1;
}

// Return neighbor at current iterator position
int Graph::NbIterator::operator*(){
  return m_Gptr->m_ci[m_indx];
}

// Make an initial neighbor iterator
Graph::NbIterator Graph::nbBegin(int v){
  return NbIterator(this, v, m_re[v]);
}

// Make an end neighbor iterator
Graph::NbIterator Graph::nbEnd(int v){
  return NbIterator(this, v, m_re[v+1]);
}

