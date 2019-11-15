// File: BaselineGraph.cpp
//
// CMSC 341 Spring 2019

// Nana Owusu

// Method implementation for Baseline::Graph class
//

#include <iostream>
#include "BaselineGraph.h"

namespace Baseline {
  
  //Baseline::Graph implementations go here
  Graph::Graph(int n){
    if (n < 1){
      throw std::out_of_range("The amount of vertices has to be more than 0");
    }
    m_numVert = n;
    //m_nz.reserve(n);
    //m_ci.reserve(n);
    //m_re.reserve(n+1);
    m_re.assign(n+1,0);
    m_numEdge = 0;
  }
  
  //return number of vertices
  int Graph::numVert(){
    return m_numVert;
  }
  
  // return number of edges
  int Graph::numEdge(){
    return m_numEdge;
  }
  
  // add edge between u and v with weight x
  void Graph::addEdge(int u, int v, int x){
    if (u < 0 || v < 0){
      throw std::out_of_range("This is not in the range");
    }
    if (u > m_numVert - 1 || v > m_numVert - 1){
      throw std::out_of_range("This is not in the range");
    }
    if (u == v){
      throw std::out_of_range("You cannot make a self edge");
    }
    int intFor = 0;
    //case for it the graph is empty
    //adding in u,v
    if (m_numEdge == 0){
      m_nz.push_back(x);
      m_ci.push_back(v);
      for(unsigned int i = u+1; i < m_re.size(); i++){
	m_re[i]++;
      }
      m_numEdge++; 
    }else if (m_re[u] == m_re[u+1]){
      if (u > v && m_re[u] == m_re[m_numVert]){
	m_nz.push_back(x);
	m_ci.push_back(v);
      }else{
	m_nz.insert(m_nz.begin()+m_re[u],x);
	m_ci.insert(m_ci.begin()+m_re[u],v);
      }
      for(unsigned int i = u+1; i < m_re.size(); i++){
	m_re[i]++;
      }
      m_numEdge++;
    }else if (m_re[u] != m_re[u+1]){
      for(unsigned int i = m_re[u]; i < unsigned(m_re[u+1]); i++){
	//checks if this edge exist and replaces the weight
	intFor = i;
	if (m_ci[i] == v){
	  m_nz[i] = x;
	}else{
	  if (v < m_ci[i]){
	    m_ci.insert(m_ci.begin()+intFor,v);
	    m_nz.insert(m_nz.begin()+intFor,x);
	    i = m_re[u+1];
	    for(unsigned int p = u+1; p < m_re.size(); p++){
	      m_re[p]++;
	    }
	    m_numEdge++;
	  }
	  else if(intFor+1 == m_re[m_numVert]){
	    m_nz.push_back(x);
	    m_ci.push_back(v);
	    i = m_re[u+1];
	    for(unsigned int p = u+1; p < m_re.size(); p++){
              m_re[p]++;
            }
            m_numEdge++;
	  }
	  else if(intFor+1 == m_re[u+1]){
	    m_ci.insert(m_ci.begin()+intFor+1,v);
	    m_nz.insert(m_nz.begin()+intFor+1,x);
	    for(unsigned int p = u+1; p < m_re.size(); p++){
	      m_re[p]++;
	    }
	    m_numEdge++;
	  }
	}
      }
    }
    //adding in v,u
    if (m_re[v] == m_re[v+1]){
      if (v > u && m_re[v] == m_re[m_numVert]){
	m_nz.push_back(x);
	m_ci.push_back(u);
      }else{
	m_nz.insert(m_nz.begin()+m_re[v],x);
	m_ci.insert(m_ci.begin()+m_re[v],u);
      }
      for(unsigned int i = v+1; i < m_re.size(); i++){
	m_re[i]++;
      }
    }else if (m_re[v] != m_re[v+1]){
      for(unsigned int i = m_re[v]; i < unsigned(m_re[v+1]); i++){
	//checks if this edge exist and replaces the weight
	intFor = i;
	if (m_ci[i] == u){
          m_nz[i] = x;
        }else{
	  if (u < m_ci[i]){
	    m_ci.insert(m_ci.begin()+intFor,u);
	    m_nz.insert(m_nz.begin()+intFor,x);
	    i = m_re[v+1];
	    for(unsigned int p = v+1; p < m_re.size(); p++){
	      m_re[p]++;
	    }
	    m_numEdge++;
	  }
	  else if(intFor+1 == m_re[m_numVert]){
            m_nz.push_back(x);
            m_ci.push_back(u);
            i = m_re[v+1];
            for(unsigned int p = u+1; p < m_re.size(); p++){
              m_re[p]++;
            }
            m_numEdge++;
	  }
	  else if(intFor+1 == m_re[v+1]){
	    m_ci.insert(m_ci.begin()+intFor+1,u);
	    m_nz.insert(m_nz.begin()+intFor+1,x);
	    for(unsigned int p = v+1; p < m_re.size(); p++){
	      m_re[p]++;
	    }
	  }
	}
      }
    }
  }
  
  // print out data structure for debugging
  void Graph::dump(){
    std::cout << "Number of Vertices: " << m_numVert << std::endl;
    std::cout << "Number of Edges: " << m_numEdge << std::endl;
    
    std::cout << "m_nz: " << "";
    for(unsigned int i = 0; i < m_nz.size(); i++)
      {
	std::cout << m_nz[i] << " ";
      }
    std::cout << std::endl;
    
    std::cout << "m_ci: " << "";
    for(unsigned int i = 0; i <m_ci.size(); i++)
      {
	std::cout << m_ci[i] << " ";
      }
    std::cout << std::endl;
    
    std::cout << "m_re: " << "";
    for(unsigned int i = 0; i < m_re.size(); i++)
      {
	std::cout << m_re[i] << " ";
      }
    std::cout << std::endl;
  }
  
  // Edge Iterator constructor; indx can be used to
  // set m_indx for begin and end iterators.
  Graph::EgIterator::EgIterator(Graph *Gptr, int indx){
    m_Gptr = Gptr;
    m_indx = 0;
    m_row = 0;

    if ( m_Gptr != nullptr ) {

      if (indx < 0 || indx > m_Gptr->m_numEdge)
	throw std::out_of_range("EgIterator(): indx out-of-range");
      
      m_indx = indx;
      
      // Find the row corresponding to indx
      if (m_Gptr->m_numEdge > 0) 
	for (m_row = 0; m_row < m_Gptr->m_numVert; m_row++)
	  if ( (m_Gptr->m_re[m_row] <= m_indx) &&
	       (m_indx < m_Gptr->m_re[m_row + 1]) )
	    break;
    }
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
    if ( m_indx == m_Gptr->m_numEdge ) return;

    int numEdge = m_Gptr->m_numEdge;
    
    do {
      m_indx++;
      while ( (m_indx < numEdge) && (m_indx >= m_Gptr->m_re[m_row + 1]) )
	m_row++;
    } while ( (m_indx < numEdge) && (m_row > m_Gptr->m_ci[m_indx]) );
  }

  // return edge at iterator location
  std::tuple<int,int,int> Graph::EgIterator::operator*(){
    if (m_indx > (m_Gptr->m_numEdge) * 2 || m_indx < 0){
      throw std::out_of_range("The iterator has reached its end");
    }
    return std::make_tuple(m_row, m_Gptr->m_ci[m_indx], m_Gptr->m_nz[m_indx]);
  }
  
  // Make an initial edge Iterator
  Graph::EgIterator Graph::egBegin(){
    return EgIterator(this, 0);
  }
  
  // Make an end iterator for edge iterator
  Graph::EgIterator Graph::egEnd(){
    return EgIterator(this, m_numEdge);
  }
  
  //Constructor for the neighbor iterator
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
}

