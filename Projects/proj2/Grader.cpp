// File: Grader.cpp
//
// CMSC 341 Spring 2019

// Nana Owusu

// Method implementation for Grader class
//         

#include "Grader.h"
#include "BaselineGraph.h"
#include "Graph.h"

Grader::Grader(string name) {
  m_name = name;
}


bool Grader::testCSRExact(int numVert, vector<Edge> edgeSeq) {
  int noErr = 0;
  int theU;
  int theV;
  int theX;
  std::vector<int> nzGraph;
  std::vector<int> ciGraph;
  std::vector<int> reGraph;
  Baseline::Graph testBase(numVert);
  Graph testGraph(numVert);
  //adding Edges to the Array and Vector
  for(unsigned int i = 0; i < edgeSeq.size(); i++){
    tie(theU,theV,theX) = edgeSeq[i];
    testBase.addEdge(theU,theV,theX);
    testGraph.addEdge(theU,theV,theX);
  }
  //changing the array into a vector to compare
  for (int i = 0; i < testGraph.m_numEdge*2; i++){
    nzGraph.push_back(testGraph.m_nz[i]);
  }
  for (int i = 0; i < testGraph.m_numEdge*2; i++){
    ciGraph.push_back(testGraph.m_ci[i]);
  }
  for (int i = 0; i < testGraph.m_numVert+1; i++ ){
    reGraph.push_back(testGraph.m_re[i]);  
  }
  
  //finding the errors
  if (testBase.m_re != reGraph){
    Error reCsrEx(5, 101, "Incorrect values in m_re");
    m_errors.push(reCsrEx);
    noErr = 1;
  }
  if (testBase.m_nz != nzGraph){
    Error nzCsrEx(5, 102, "Incorrect values in m_nz");
    m_errors.push(nzCsrEx);
    noErr = 1;
  }
  if (testBase.m_ci != ciGraph){
    Error ciCsrEx(5, 103, "Incorrect values in m_ci");
    m_errors.push(ciCsrEx);
    noErr = 1;
  }
  if (noErr == 0){
    Error noCsrEx(0, 100, "No errors in testCSRExact()");
    m_errors.push(noCsrEx);
  }
    return true;
}


bool Grader::testCSRUnordered(int numVert, vector<Edge> edgeSeq) {
  int noErr = 0;
  int noReCor = 0;
  int theU;
  int theV;
  int theX;
  std::vector<int> reGraphVec;
  Baseline::Graph testBase(numVert);
  Graph testGraph(numVert);
  std::multiset<int> ciSetG;
  std::multiset<int> ciSetB;
  std::multiset<int> nzSetG;
  std::multiset<int> nzSetB;
  //adding Edges to the Array and Vector
  for(unsigned int i = 0; i < edgeSeq.size(); i++){
    tie(theU,theV,theX) = edgeSeq[i];
    testBase.addEdge(theU,theV,theX);
    testGraph.addEdge(theU,theV,theX);
  }
  //putting the graph arrays re into a vector
  for (int i = 0; i < testGraph.m_numVert+1; i++ ){
    reGraphVec.push_back(testGraph.m_re[i]);
  }
  if (testBase.m_re != reGraphVec){
    Error reCsrUn(10, 201, "Incorrect m_re; cannot perform unordered test");
    m_errors.push(reCsrUn);
    noErr = 1;
    noReCor = 1;
  }
  if (noReCor == 0){
    //put the index for the graphs into their respective sets
    for(int i = 0; i < numVert; i++){
      for(int p = testGraph.m_re[i]; p < testGraph.m_re[i+1]; p++){
	ciSetG.insert(testGraph.m_ci[p]);
	nzSetG.insert(testGraph.m_nz[p]);
      }
      for(int q = testBase.m_re[i]; q < testBase.m_re[i+1]; q++){
	ciSetB.insert(testBase.m_ci[q]);
	nzSetB.insert(testBase.m_nz[q]);
      }
      if (ciSetB != ciSetG){
        Error ciCsrUn(10, 202,"Failure of unordered test of CSR");
        m_errors.push(ciCsrUn);
	noErr = 1;
	break;
       }
      ciSetB.clear();
      ciSetG.clear();
      if (nzSetB != nzSetG){
	Error nzCsrUn(10, 202,"Failure of unordered test of CSR");
	m_errors.push(nzCsrUn);
	noErr = 1;
	break;
      }
      nzSetB.clear();
      nzSetG.clear();
    }
  }
  if (noErr == 0){
    Error noCsrUn(0, 200, "No errors in testCSRUnordered()");
    m_errors.push(noCsrUn);
  }  
  return true;
}

bool Grader::testNbIterator(int numVert, vector<Edge> edgeSeq) {
  int noErr = 0;
  int theU;
  int theV;
  int theX;
  set<int> baseNb;
  set<int> graphNb;
  std::set<int>::iterator it;
  Baseline::Graph testBase(numVert);
  Graph testGraph(numVert);
  Graph::NbIterator nit;
  Baseline::Graph::NbIterator nat;
  for(unsigned int i = 0; i < edgeSeq.size(); i++){
    tie(theU,theV,theX) = edgeSeq[i];
    testBase.addEdge(theU,theV,theX);
    testGraph.addEdge(theU,theV,theX);
  }
  for(int i = 0; i < numVert; i++){
    for (nit = testGraph.nbBegin(i); nit != testGraph.nbEnd(i) ; nit++) {
      graphNb.insert(*nit);
    }
    for (nat = testBase.nbBegin(i); nat != testBase.nbEnd(i) ; nat++) {
      baseNb.insert(*nat);
    }
    if (graphNb.empty() || baseNb.empty()){
      break;
    }else{
      for(it = graphNb.begin(); it != graphNb.end(); ++it){
	if(baseNb.find(*it) == baseNb.end()){
	  Error valCsrNb(5,302, "Incorrect values from neighbor iterator");
	  m_errors.push(valCsrNb);
	  noErr = 1;
	  break;
	}
      }
      baseNb.clear();
      graphNb.clear();
    }
    baseNb.clear();
    graphNb.clear();
  }
  for(int i = 0; i < numVert; i++){
    for (nit = testGraph.nbBegin(i); nit != testGraph.nbEnd(i) ; nit++) {
      graphNb.insert(*nit);
    }
    for (nat = testBase.nbBegin(i); nat != testBase.nbEnd(i) ; nat++) {
      baseNb.insert(*nat);
    }
    if (baseNb.size() != graphNb.size()){
      Error sizeCsrNb(5,301, "Incorrect neighbor set size()");
      m_errors.push(sizeCsrNb);
      noErr = 1;
      break;
    }
    baseNb.clear();
    graphNb.clear();
  }      
  if (noErr == 0){
    Error noCsrNb(0,300, "No errors in testNbIterator()");
    m_errors.push(noCsrNb);
  }
  return true;
}

bool Grader::testEgIterator(int numVert, vector<Edge> edgeSeq) {
  int noErr = 0;
  int theU;
  int theV;
  int theX;
  Graph::EgIterator eit;
  Graph::NbIterator nit;
  std::multiset<tuple<int,int,int>>::iterator it;
  multiset<tuple<int,int,int>> baseEg;
  multiset<tuple<int,int,int>> graphEg;
  Baseline::Graph testBase(numVert);
  Baseline::Graph::EgIterator egt;
  Graph testGraph(numVert);
  
  //adding Edges to the Array and Vector
  for(unsigned int i = 0; i < edgeSeq.size(); i++){
    tie(theU,theV,theX) = edgeSeq[i];
    testBase.addEdge(theU,theV,theX);
    testGraph.addEdge(theU,theV,theX);
  }
   for (eit = testGraph.egBegin() ; eit != testGraph.egEnd() ; eit++) {
      graphEg.insert(*eit);
   }
   for (egt = testBase.egBegin() ; egt != testBase.egEnd() ; egt++) {
     baseEg.insert(*egt);
   }
   for(it = graphEg.begin(); it != graphEg.end(); ++it){
     if(baseEg.find(*it) == baseEg.end()){
       Error valCsrEg(5,302, "Incorrect values from edge iterator");
       m_errors.push(valCsrEg);
       noErr = 1;
     }
   }
   if (baseEg.size() != graphEg.size()){
     Error sizeCsrEg(5,401, "Incorrect edge set size()");
     m_errors.push(sizeCsrEg);
     noErr = 1;
   }
  
   if (noErr == 0){
     Error noCsrEg(0,400,"No errors in testEgIterator()");
     m_errors.push(noCsrEg);
   }
   return true;
}


bool Grader::testExceptions(int numVert, vector<Edge> edgeSeq) {
  int theU;
  int theV;
  int theX;
  Graph::EgIterator eit;
  Graph::NbIterator nit;
  bool exceptThrew1 = false;
  bool exceptThrew2 = false;
  bool exceptThrew3 = false;
  bool exceptThrew4 = false;
  bool exceptThrew5 = false;
  bool exceptThrew6 = false;
  Baseline::Graph testBase(numVert);
  Graph testGraph(numVert);
  //adding Edges to the Array and Vector
  for(unsigned int i = 0; i < edgeSeq.size(); i++){
    tie(theU,theV,theX) = edgeSeq[i];
    testBase.addEdge(theU,theV,theX);
    testGraph.addEdge(theU,theV,theX);
  }

  //Try-Catch for the 510s Errors 
  try{
    Graph testGraph1(0);
    if (exceptThrew1 == false){
      Error CsrNZeroNone(5,511, "Constructor with n = 0 did not throw an exception");
      m_errors.push(CsrNZeroNone);
    }
  }
  catch(const std::out_of_range&Orr){
    Error noCsrNZero(0,510,
		     "No errors in testExceptions(), construtor with n = 0");
    m_errors.push(noCsrNZero);
    exceptThrew1 = true;
  }
  catch(...){
    Error InCsrNZero(2,512, "Constructor with n = 0 threw incorrect exception");
    m_errors.push(InCsrNZero);
    exceptThrew1 = true;
  }

  //Try-Catch for the 520s Errors
  try{
    Graph testGraph2(-1);
    if (exceptThrew2 == false){
      Error CsrLessNone(5,521, "Constructor with n < 0 did not throw an exception");
      m_errors.push(CsrLessNone);
    }
  }
  catch(const std::out_of_range&Orr){
    Error noCsrLess(0,520, "No errors in testExceptions(), construtor with n < 0");
    m_errors.push(noCsrLess);
    exceptThrew2 = true;
  }
  
  catch(...){
    Error InCsrLess(2,522, "Constructor with n < 0 threw incorrect exception");
    m_errors.push(InCsrLess);
    exceptThrew2 = true;
  }

  //Try-Catch for the 530s Errors
  try{
    testGraph.addEdge(2,numVert+2,8);
    if (exceptThrew3 == false){
      Error CsrDVNone(5,531,
		      "addEdge() with bad destination vertex did not throw an exception");
      m_errors.push(CsrDVNone);
    }
  }
  catch(const std::out_of_range&Orr){
    Error noCsrDV
      (0,530,"No errors in testExceptions(),addEdge() with bad destination vertex");
    m_errors.push(noCsrDV);
    exceptThrew3 = true;
  }
  catch(...){
    Error InCsrDV(2,532,
		  "addEdge() with bad destination vertex threw incorrect exception");
    m_errors.push(InCsrDV);
    exceptThrew3 = true;
  }

  //Try-Catch for the 540s Errors
  try{
    testGraph.addEdge(-1,2,9);
    if (exceptThrew4 == false){ 
      Error CsrSVNone(5,541,"addEdge() with bad source vertex did not throw an exception");
      m_errors.push(CsrSVNone);
    }
  }
  catch(const std::out_of_range&Orr){
    Error noCsrSV(0,540,
		  "No errors in testExceptions(), add Edge() with bad source vertex");
    m_errors.push(noCsrSV);
    exceptThrew4 = true;
  }
  catch(...){
    Error InCsrSV(2,542, "addEdge() with bad source vertex threw incorrect exception");
    m_errors.push(InCsrSV);
    exceptThrew4 = true;
  }

  //Try-Catch for the 550s Errors
  try{
    nit = testGraph.nbEnd(4);
    *nit;
    if (exceptThrew5 == false){
      Error CsrNbNone(5,551, "Dereference of neighbor end iterator threw no exception");
      m_errors.push(CsrNbNone);
    }
  }
  catch(const std::out_of_range&Orr){
    Error noCsrNb(0,550,
		  "No errors in testExceptions(), dereference of neighbor end iterator");
    m_errors.push(noCsrNb);
    exceptThrew5 = true;
  }
  catch(...){
    Error InCsrNb(2,552,
		  "Dereference of neighbor end iterator threw incorrect exception");
    m_errors.push(InCsrNb);
    exceptThrew5 = true;
  }

  //Try-Catch for the 560s Errors 
  try{
    eit = testGraph.egEnd();
    *eit;
    if (exceptThrew6 == false){
      Error CsrEgNone(5 ,561, "Dereference of edge end iterator threw no exception");
      m_errors.push(CsrEgNone);
    }
  }
  catch(const std::out_of_range&Orr){
    Error noCsrEg(0,560,
		  "No errors in testExceptions(), dereference of edge end iterator");
    m_errors.push(noCsrEg);
    exceptThrew6 = true;
  }
  catch(...){
    Error InCsrEg(2,562, "Dereference of edge end iterator threw incorrect exception");
    m_errors.push(InCsrEg);
    exceptThrew6 = true;
  }
  return true;
}

void Grader::printAllErrors(){
  int deductTotal = 0;
  while (!m_errors.empty()){
    cout << m_errors.front() << endl;
    deductTotal += m_errors.front().getDeduction();
    m_errors.pop();
  }
  cout << endl;
  cout << "Total Deduction: " << deductTotal << endl;
}
  
void Grader::resetErrorQueue() {
  while (!m_errors.empty()){
    m_errors.pop();
  }
}

// Formatted output of Error object:
// deduction: (id) description
ostream& operator<<(ostream& outStream, const Error& err) {
  if (err.m_deduction > 0) {
    outStream << "-" << err.m_deduction << ": (" << err.m_id
	      << ") " << err.m_description;
  } else {
    outStream << err.m_deduction << ": (" << err.m_id
	      << ") " << err.m_description;
  }
  return outStream;
}

