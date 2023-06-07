/**
@file main.cpp
@brief test d'uso della classe amgraph<int>
**/
#include <iostream>
#include <fstream>
#include "amgraph.h" 
#include <cassert>   
#include <functional> // just for fun
#include <vector>

int test_int(){

  amgraph<int> graph;

  graph.add_Node(1);
  graph.add_Node(2);
  graph.add_Node(3);

  graph.add_Arc(1, 2);
  graph.add_Arc(2, 3);

  assert(graph.exists(1));
  assert(!graph.exists(4));
  assert(graph.connected(2, 3));
  assert(!graph.connected(5, 3));

  // Print the graph
  std::cout << "graph for test_int:"<< std::endl << graph << std::endl;

  return 0;
  
}

int test_string(){

  amgraph<std::string> graph;

  graph.add_Node("A");
  graph.add_Node("B");
  graph.add_Node("C");

  graph.add_Arc("A", "B");
  graph.add_Arc("B", "C");

  std::cout << "Node A exists: " << graph.exists("A") << std::endl;
  std::cout << "Node D exists: " << graph.exists("D") << std::endl;
  std::cout << "Nodes B and C are connected: " 
    << graph.connected("B", "C") << std::endl;

  std::cout << "graph for test_string:"<< std::endl << graph << std::endl;

  return 0;
}

struct Persona {
  std::string nome;
  int eta;

  // operatore di comparison
  bool operator==(const Persona& other) const {
    return nome == other.nome && eta == other.eta;
  }

  bool operator!=(const Persona& other) const {
    return !(*this == other);
  }
};

std::ostream& operator<<(std::ostream& os, const Persona& person) {
  os << "Name: " << person.nome << ", Age: " << person.eta;
  return os;
}

int test_persona(){
  
  amgraph<Persona> graph;

  // Create person objects
  Persona person1{"Alice", 25};
  Persona person2{"Bob", 30};
  Persona person3{"Charlie", 35};

  // Add nodes
  graph.add_Node(person1);
  graph.add_Node(person2);
  graph.add_Node(person3);

  // Add arcs
  graph.add_Arc(person1, person2);
  graph.add_Arc(person2, person3);

  // Check if nodes and arcs exist
  std::cout << "Node person1 exists: " << graph.exists(person1) << std::endl;
  std::cout << "Node person4 exists: " << graph.exists(Persona{"Dave", 40}) << std::endl;
  std::cout << "Nodes person2 and person3 are connected: " << graph.connected(person2, person3) << std::endl;

  // Print the graph
  std::cout << "graph for test_persona"<< graph << std::endl;
  // Test the const forward iterator
  std::cout << "Iterating over the Graph using a const forward iterator:" << std::endl;
  for (const auto& person : graph) {
        std::cout << "Name: " << person.nome << ", Age: " << person.eta << std::endl;
    }
  return 0;
}




int test_3() { 
  amgraph<int> amg1;
  amg1.print();
  amg1.add_Node(1);
  amg1.add_Node(2);
  amg1.add_Node(3);
  amg1.add_Arc(1,1);
  amg1.add_Arc(2,1);
  amg1.add_Arc(1,3);
  amg1.add_Arc(3,3);
  
  assert(amg1.connected(1,2));
  assert(!amg1.connected(3,2));

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

void test_memory_limit (int max_nodes){
    amgraph<int> graph;
    for (int i = 1; i <= max_nodes; ++i) {
        graph.add_Node(i);
        std::cout << "Trying: " << i << "/" << max_nodes << " (" << (i * 100 / max_nodes) << "%)";
        std::cout.flush();
        std::cout << "\r";
    }
    std::cout << std::endl;
}

// empty implementation of the output stream for cstructure to test
// std::ostream& operator<<(std::ostream& os, const std::vector<int> obj) {
//     return os;
// }

// void test_memory_limit_2(int max_nodes) {
//     amgraph<std::vector<int>> graph; // Use std::vector<int> as the data structure type
    
//     for (int i = 1; i <= max_nodes; ++i) {
//         graph.add_Node(std::vector<int>(100)); 
//         // Create a new std::vector<int> with 100 elements and add it to the graph
//         std::cout << "Trying: " << i << "/" << max_nodes 
//                   << " (" << (i * 100 / max_nodes) << "%)";
//         std::cout.flush();
//         std::cout << "\r";
//     }

//     std::cout << std::endl;
// }



int main(int argc, char *argv[]){
  
  
  std::vector<std::pair<std::function<void()>, std::string>> testFunctions = {
    {test_int, "test con graph<int"},
    {test_string, "test con graph<std::string>"},
    {test_persona, "test graph<Persona>"},
    {test_3, "add nodes on graph<int> "}
  };

  for (const auto& testFunction : testFunctions) {
    std::cout << "Executing " << testFunction.second << std::endl;
    testFunction.first();
  }

  // breaking test
  test_memory_limit(1000);
  //test_memory_limit_2(1000);

  std::cout << "All test were successful" << std::endl;
  return 0;
}