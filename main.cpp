/**
@file main.cpp
@brief test d'uso della classe amgraph<int>
**/

// NOTA

#include <iostream>
#include <fstream>
#include "amgraph.h" // amgraph<int>
#include <cassert>   // assert

int main(int argc, char *argv[])
{ 
  amgraph<int> amg1;
  amg1.print();
  amg1.add_Node(1);
  amg1.add_Node(2);
  amg1.add_Node(3);
  amg1.add_Arc(1,1);
  amg1.add_Arc(2,1);
  amg1.add_Arc(1,3);
  amg1.add_Arc(3,3);
  amg1.print();
  //int r = 2;
  //std::cout << std::endl << "Removing  = "  << r << std::endl;
  //std::cout << std::endl << "Index  = "  << amg1.getVertexIndex(r) << std::endl;
  //amg1.remove_Node(r);
  //amg1.print();
  assert(amg1.connected(1,2));
  assert(!amg1.connected(3,2));
  
  //std::cout << std::endl << "cout  = "  << std::endl << amg1 << std::endl;

  amgraph<int>::const_iterator it = amg1.begin();
  amgraph<int>::const_iterator ite = amg1.end();
  
  amgraph<int> amg2;
  amg2.print();
  amg2.add_Node(9);
  amg2.add_Node(8);
  amg2.add_Node(7);
  amg2.add_Arc(9,9);
  
  amg2.add_Nodes(it,ite);
  amg2.print();
  //std::cout << std::endl << "Iteratorzzzz" << std::endl;
  //for (; it!=ite; ++it){
  //  std::cout<< *it << std::endl;
  //}
  

  return 0;
}

struct utente {
  std::string nome;
  std::string cognome;

  utente(const std::string &n, const std::string &c) : 
    nome(n), cognome(c) {}
};
  