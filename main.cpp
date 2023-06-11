/**
@file main.cpp
@brief test d'uso della classe Amgraph<int>
**/
#include <iostream>
#include <fstream>
#include "amgraph.h" 
#include <cassert>   
#include <functional> // just for fun (tionals)
#include <vector>

auto test_int() -> int{

  Amgraph<int> graph;

  graph.add_Node(1);
  graph.add_Node(2);
  graph.add_Node(3);

  graph.add_Arc(1, 2);
  graph.add_Arc(2, 3);
  try {
    graph.add_Arc(1, 4);
  }
  catch (std::invalid_argument){
    std::cout<<"Exception correctly caugth"<< std::endl;
  }

  assert(graph.exists(1));
  assert(!graph.exists(4));

  // raising exceptions
  try{
  assert(!graph.connected(5, 3));
  }
  catch(std::invalid_argument){
    std::cout<<"Exception correctly caugth"<< std::endl;
    }
  assert(graph.connected(2, 3));

  // Print the graph
  std::cout << "graph for test_int:";//<< std::endl << graph << std::endl;
  graph.print();
  return 0;
  
}

auto test_string() -> int{

  Amgraph<std::string> graph;

  graph.add_Node("A");
  graph.add_Node("B");
  graph.add_Node("C");

  graph.add_Arc("A", "B");
  graph.add_Arc("B", "C");

  assert(graph.exists("A"));
  assert(!graph.exists("D"));
  
  graph.connected("B", "C");
  std::cout << "graph for test_string:"<< std::endl; //<< graph << std::endl;
  graph.print();
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

auto test_persona() -> int{
  
  Amgraph<Persona> graph;

  // Create person objects
  Persona person1{"Adalberto", 19};
  Persona person2{"Susanna", 24};
  Persona person3{"Charlie", 21};

  // Add nodes
  graph.add_Node(person1);
  graph.add_Node(person2);
  graph.add_Node(person3);

  // Add arcs
  graph.add_Arc(person1, person2);
  graph.add_Arc(person2, person3);

  // Check if nodes and arcs exist
  assert(graph.exists(person1));
  assert(!graph.exists(Persona{"Dave", 40}));
  assert(graph.connected(person2, person3));
  
  // Print the matrix for this graph
  std::cout << "graph for test_persona"; //<< graph << std::endl;
  graph.print();

  // Test the const forward iterator
  std::cout << "Iterating over the Graph using a const forward iterator:" << std::endl;
  for (const auto& person : graph) {
        std::cout << "Name: " << person.nome << ", Age: " << person.eta << std::endl;
    }
  return 0;
}




int test_3() { 
  Amgraph<int> amg1;
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

  Amgraph<int>::const_iterator it = amg1.begin();
  Amgraph<int>::const_iterator ite = amg1.end();
  
  Amgraph<int> amg2;
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

void stress_test1 (int max_nodes){
    Amgraph<int> graph;
    for (int i = 1; i <= max_nodes; ++i) {
        graph.add_Node(i);
        std::cout << "Trying: " << i << "/" << max_nodes << " (" << (i * 100 / max_nodes) << "%)";
        std::cout.flush();
        std::cout << "\r";
    }
    std::cout << std::endl;
}

void stress_test2(int max_nodes) {
    Amgraph<std::vector<int>> graph; 
    for (int i = 1; i <= max_nodes; ++i) {
        std::vector<int> node_vector;
        for (int j = 1; j <= 1000; ++j) {
            node_vector.push_back(i * j); 
            //riempi i vettori, dovranno essere diversi
        }
        graph.add_Node(node_vector); 
        std::cout << "Trying: " << i << "/" << max_nodes
                  << " (" << (i * 100 / max_nodes) << "%)";
        std::cout.flush();
        std::cout << "\r";
    }
    std::cout << std::endl;
}

template <typename T>
void stress_test3(int max_nodes){
    Amgraph<T> graph;
    for (int i = 1; i <= max_nodes; ++i) {
        graph.add_Node(T());
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

struct Useless_data{
  int* cose;
  Useless_data(){
    cose = new int[1];
    cose[0] = 1;
  };
  bool operator ==(const Useless_data& d) const{
    return false;
  };
  bool operator= (const Useless_data& other){
    cose[0] = *other.cose;
    return this;
  };
  ~Useless_data(){
    delete[] cose;
  }
};

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

  //stress_tests
  stress_test1(1000);
  stress_test2(1000);
  stress_test3<Useless_data>(1000);
  std::cout << "All test were successful" << std::endl;
  return 0;
}