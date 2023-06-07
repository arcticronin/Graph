#ifndef amgraph_H
#define amgraph_H

#include <ostream> // std::ostream
#include <cassert> 
#include <iterator> // std::forward_iterator_tag
#include <cstddef>  // std::ptrdiff_t

/**
  @file amgraph.h
  @brief Dichiarazione della classe amgraph
*/

/**
  @brief Classe amgraph

  Classe che vuole rappresentare un grafo dinamico di tipo T 
  tramite array di nodi e matrice booleana di adiacenza.

  Nomenclatura:
    - Arc e Node (come da consegna) per gli oggetti di alto livello
      e le funzioni pubbliche
    - Edge e Vertex per gli oggetti di basso livello e funzioni private
    
  esempio:
    - Edge è interpretato come il collegamento tra gli indici dei
        nodi rappresentato come un numero booleano
    - Arc invece rappresenta il collegamento tra due oggetti Nodi
    - Vertex è usato nelle funzioni private

*/
template <typename T>
class amgraph {

public:
  
  typedef T value_type;
  typedef unsigned int size_type; 
 
  /**
    @brief Costruttore di default

    COSTRUTTORE DI DEFAULT:
    Il costruttore di default serve a inizializzare un grafo vuoto

    @post _vertices = nullptr
    @post _size = 0
    @post _adjacencyMatrix = nullptr
  */
  amgraph() : _vertices(nullptr), _size(0), _adjacencyMatrix(nullptr) { // Initialization list
 
  
  #ifndef NDEBUG
  std::cout << "amgraph::amgraph()" << std::endl;
  #endif
}

  /**
    @brief Distruttore

    2° METODO FONDAMENTALE: DISTRUTTORE
    Distruttore della classe. Il distruttore deve rimuovere tutte 
    le risorse usate dalla classe. 
    Dealloca matrice di adiacenza e array di tipo T dei vertici
  */

  ~amgraph()  {
  for (int i = 0; i < _size; ++i) {
            delete[] _adjacencyMatrix[i];
        }
  delete[] _adjacencyMatrix;
  delete[] _vertices;
  _adjacencyMatrix = nullptr;
  _vertices = nullptr;
  _size = 0;

  #ifndef NDEBUG
  std::cout << "amgraph::~amgraph()"<< std::endl;
  #endif
}

  /**
    @brief Copy Constructor

    3° METODO FONDAMENTALE: COPY CONSTRUCTOR
    Costruttore di copia. Serve a creare un oggetto come copia di un 
    altro oggetto. I due oggetti devono essere indipendenti.

    @param other amgraph sorgente da copiare
    
    @post _vertices != nullptr
    @post _size = other._size
    @post _adjacencyMatrix != nullptr
  */
  amgraph(const amgraph &other) : _vertices(nullptr), _size(0), _adjacencyMatrix(nullptr) {
  _vertices = new value_type[other._size];
  _size = other._size;
  try {
    for(size_type i=0; i<_size; ++i)
      _vertices[i] = other._vertices[i];

  }
  catch(...) {
    delete[] _vertices;
    _vertices = nullptr;
    _size =0;
    throw;
  }
  _adjacencyMatrix = new bool*[_size];
  for (int i = 0; i < _size; ++i) {
            _adjacencyMatrix[i] = new bool[_size];
            for (int j = 0; j < _size; ++j) {
                _adjacencyMatrix[i][j] = other._adjacencyMatrix[i][j];
            }
        }
  #ifndef NDEBUG
  std::cout << "amgraph::amgraph(const amgraph&)"<< std::endl;
  #endif
}

  /**
    @brief Operatore di assegnamento

    4° METODO FONDAMENTALE: OPERATORE ASSEGNAMENTO
    L'operatore di assegnamento serve a copiare il contenuto di un oggetto
    in un altro oggetto dello stesso tipo. I due oggetti devono essere
    indipendenti.

    @param other amgraph sorgenete da copiare

    @return un reference all'oggetto corrente

    @post _amgraph != nullptr
    @post _size = other._size 
    @post _adjacencyMatrix != nullptr
  */
  amgraph& operator=(const amgraph &other){
  if (this != &other) {

    amgraph tmp(other);

    this->swap(tmp);
  }

  #ifndef NDEBUG
  std::cout << "amgraph::operator=(const amgraph &)" << std::endl;
  #endif

  return *this;
}

  /**
    @brief Getter del nodo [index]
    
    Metodo che permette di leggere il Nodo/Vertice
    in posizione index dell'array. Il metodo si può usare
    solo su istanze costanti della classe.

    @param index della cella da leggere

    @return reference al Nodo/Vertice di tipo value_type in posizione index 

    @pre index < size()
  */
  const value_type &operator[](size_type index) const { 
  assert(index<_size);

  return _vertices[index];
}


  /**
    @brief Metodo swap per la classe amgraph

    Funzione che scambia il contenuto di due amgraph

    @param other amgraph con cui scambiare il contenuto
  */
  void swap(amgraph &other) {
    std::swap(_vertices, other._vertices);
    std::swap(_size, other._size); 
    std::swap(_adjacencyMatrix, other._adjacencyMatrix);
  }

  /*
    @brief ridefinizione operatore di stream

    Ridefinizione dell'operatore di stream per scrivere un
    amgraph su uno stream di output

    @param os stream di output (operando di sinistra)
    @param db amgraph da scrivere (operando di destra)

    @return reference allo stream di output
  friend std::ostream& operator<<(std::ostream &os, const amgraph<T> &amg) {
    os << "size " << amg._size << " node names:"<< std::endl;
    for(typename amgraph<T>::size_type i = 0; i < amg.getSize() ; i++)
      os << amg[i] << ' ';
    os << std::endl << "Adjacency Matrix:" << std::endl;
    for (int i = 0; i < amg._size; ++i) {
      for (int j = 0; j < amg._size; ++j)
        os << amg._adjacencyMatrix[i][j] << " ";
      os << std::endl;
    }
    return os;
  }

  */

  /**
    @brief definizione di classe const_iterator

    metodi definiti per solo operazioni di tipo Forward
    
  */

  class const_iterator;   
  class const_iterator {

  public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef T                        value_type;
    typedef ptrdiff_t                difference_type;
    typedef const T*                 pointer;
    typedef const T&                 reference;

  /**
    @brief Costruttore

    @param ptr inizializzato a nullptr per iteratore vuoto
  */  
    const_iterator() {
      ptr = nullptr;
    }
    
    const_iterator(const const_iterator &other) {
      ptr = other.ptr;
    }
  /**
    @brief Copy constructor

  
    @param other altro const_iterator
  */
    const_iterator& operator=(const const_iterator &other) {
      ptr = other.ptr;
      return *this;
    }
  /**
    @brief Distruttore

  */
    ~const_iterator() { }
  /**
    @brief Metodo dereferenziamento

    type reference definito nella classe

  */
    reference operator*() const {
      return *ptr;
    }
 /**
    @brief Metodo che ritorna il puntatore

    type pointer definito nella classe
  */
    pointer operator->() const {
      return ptr;
    }
 /**
    @brief definizione di operatore post-incremento

  */
    const_iterator operator++(int) {
      const_iterator old(*this);
      ++ptr;
      return old;
    }
 /**
    @brief definizione di operatore pre-incremento

  */
    const_iterator &operator++() {
      ++ptr;
      return *this;
    }
  /**
    @brief operatore di uguaglianza

    Necessario per fermarsi nei cicli comparando due const_iterator

  */ 
    bool operator==(const const_iterator &other) const {
      return ptr == other.ptr;
    }
 /**
    @brief operatore di disuguaglianza

    Necessario per fermarsi nei cicli comparando due const_iterator

  */
    bool operator!=(const const_iterator &other) const {
      return ptr != other.ptr;
    }

    private:
    const T *ptr;

    // La classe container deve essere messa friend dell'iteratore per poter
    // usare il costruttore di inizializzazione.
    friend class amgraph; 

    // Costruttore privato di inizializzazione usato dalla classe container
    // tipicamente nei metodi begin e end
    const_iterator(const T*p) { 
      ptr = p; 
    }    
  }; // fine della classe const_iterator
  /**
    @brief begin

    Funzione che genera il puntatore al primo elemento

  */ 
  const_iterator begin() const {
    return const_iterator(_vertices);
  }
  /**
    @brief end
    
    Funzione che genera il puntatore successivo all'ultimo elemento

    NOTA: non dereferenzalizzarlo MAI
  */ 
  const_iterator end() const {
    return const_iterator(_vertices + _size);
  }
  /**
    @brief Funzione per aggiungere un Nodo

    I nodi aggiunti non avranno collegamenti e saranno isolati.
    Per rappresentarlo basta un value_type che rappresenta il nome, 
    l'identificativo del nodo da aggiungere.
    
    @param una regreference a un nome di un nodo di tipo value_type

  */
  void add_Node(const value_type &node){
    // check if node is present
    // use get vertex index
      if ( this->getVertexIndex(node) != -1){
        //std::cout<< "node " << node <<" already present" << std::endl;
        std::cout<< "node already present" << std::endl;
        return;
        }
    // try catch

    value_type* new_vertices = new value_type[_size + 1];
    // copy vertices
    for (int i = 0; i < _size ; ++i) {
      new_vertices[i] = _vertices[i];
      }
    new_vertices[_size] = node;

    // handle matrix
    bool** new_adjacencyMatrix = new bool*[_size + 1];
    
    for (int i = 0; i < _size + 1 ; ++i) {
      new_adjacencyMatrix[i] = new bool[_size + 1];
      }

    // copy old block
    for (int i = 0; i < _size; ++i) {
      for (int j = 0; j < _size; ++j)
          new_adjacencyMatrix[i][j] = _adjacencyMatrix[i][j];
      }

    // fill last row and last column with "false"
    for (int i = 0; i < _size + 1; ++i) {
      new_adjacencyMatrix[_size][i] = false;
      new_adjacencyMatrix[i][_size] = false;
      }

    // clean temp data
    std::swap(_vertices, new_vertices);
    delete[] new_vertices;
    std::swap(_adjacencyMatrix, new_adjacencyMatrix);
    for (int i = 0; i < _size; ++i) {
          delete[] new_adjacencyMatrix[i];
      }
    delete[] new_adjacencyMatrix;
    
    _size += 1;
    }
/**
    @brief Funzione per rimuovere un Nodo

    rimozione nodo:
    1) si controlla che il nodo sia presente
      @see getVertexIndex
      scelta implementativa: ritorno se il nodo non è presente
      come se avessi effettuato la rimozione
    2)
    
    @param una regreference a un nome di un nodo di tipo value_type

*/
  void remove_Node(const value_type &node){
    // check if node is present
    // use get vertex index
    int index = this->getVertexIndex(node);
      if ( index == -1){
        std::cout<< "node " << node <<" not present" << std::endl;
        return;
        }

    // try catch

    value_type* new_vertices = new value_type[_size - 1];

    // copy vertices
    for (int i = 0; i < index ; ++i) {
      new_vertices[i] = _vertices[i];
      }
    for (int i = index; i < _size - 1 ; ++i) {
      new_vertices[i] = _vertices[i + 1];
      }

    // handle matrix

    bool** new_adjacencyMatrix = new bool*[_size - 1];
    
    for (int i = 0; i < _size - 1 ; ++i) {
      new_adjacencyMatrix[i] = new bool[_size - 1];
      }

    // copy first block
    for (int i = 0; i < index; ++i) {
      for (int j = 0; j < index; ++j)
          new_adjacencyMatrix[i][j] = _adjacencyMatrix[i][j];
      }

     // copy fourth block
    for (int i = index; i < _size - 1; ++i) {
      for (int j = index; j < _size - 1; ++j)
          new_adjacencyMatrix[i][j] = _adjacencyMatrix[i + 1][j + 1];
      }

    // copy second block
    for (int i = 0; i < index; ++i) {
      for (int j = index; j < _size - 1; ++j)
          new_adjacencyMatrix[i][j] = _adjacencyMatrix[i][j + 1];
      }

     // copy third block
    for (int i = index; i < _size - 1; ++i) {
      for (int j = 0; j < index; ++j)
          new_adjacencyMatrix[i][j] = _adjacencyMatrix[i + 1][j];
      }
     

    // clean temp data
    std::swap(_vertices, new_vertices);
    delete[] new_vertices;
    std::swap(_adjacencyMatrix, new_adjacencyMatrix);
    for (int i = 0; i < _size; ++i) {
          delete[] new_adjacencyMatrix[i];
      }
    delete[] new_adjacencyMatrix;
    
    // size--
    _size -= 1;
    }

  void add_Arc(const value_type &node1, const value_type &node2){
    int index1 = this->getVertexIndex(node1);
    int index2 = this->getVertexIndex(node2);
    if (index1 == -1 || index2 == -1){
      std::cout << "Bad Nodes";
      return;
    } 
    if (this->hasEdge(index1,index2)){
      std::cout << "Already Linked";
      return;
    }
    this->addEdge(index1, index2);
  }

/**
    @brief Funzione per rimuovere un Arco

    Si controlla che il nodo sia presente
      @see getVertexIndex ritorna -1 se un nodo non è presente
      @see hasEdge ritorna false se non c'è collegamento tra i nodi
      scelta implementativa: ritorno senza eseguire nulla,
      la rimozione di qualcosa di non esistente la considero effettuata.
    
    @param una regreference a un nome di un nodo di tipo value_type

*/
  void remove_Arc(const value_type &node1, const value_type &node2){
    int index1 = this->getVertexIndex(node1);
    int index2 = this->getVertexIndex(node2);
    if (index1 == -1 || index2 == -1){
      std::cout << "Trying to remove an arch from non existing node" 
      << std::endl;
      return;
    }
    if (! this->hasEdge(index1,index2)){
      std::cout << "No Link existing, nothing removed" << std::endl;
      return;
    }
    this->removeEdge(index1, index2);
  }

  template<typename Iter>
    void add_Nodes(Iter start, Iter end) {
        while (start != end) {
            add_Node(*start);
            ++start;
        }
    }

  private:
  
  void addEdge(int src, int dest) {
      _adjacencyMatrix[src][dest] = true;
  }

  void removeEdge(int src, int dest) {
      _adjacencyMatrix[src][dest] = false;
  }

  bool hasEdge(int src, int dest) const{
      return _adjacencyMatrix[src][dest];
  }

  T getVertexName(int vert) const{
      return _vertices[vert];
  }

  int getVertexIndex(const value_type &node) const{
    for(int i = 0; i < _size; ++i)
      if (node == _vertices[i])
        return i;
    return -1;
  }

  public:

  bool exists(const value_type &node) const{
    return (this->getVertexIndex(node) != -1);
  }

  bool connected(const value_type &node1, const value_type &node2) const{
    int index1 = this->getVertexIndex(node1);
    int index2 = this->getVertexIndex(node2);
    if (index1 == -1 || index2 == -1){
      std::cout << "bad Nodes";
      return false;
    }
    if  (this->hasEdge(index1,index2)||
        (this->hasEdge(index2,index1)))
          return true;
    return false;
  }
  

  void print() const{
          if (_size == 0)
            std::cout << "Empty Graph" << std::endl;
          for (int i = 0; i < _size; ++i) {
              std::cout << "Vertex " << getVertexName(i) << ": ";
              for (int j = 0; j < _size; ++j) {
                  std::cout << _adjacencyMatrix[i][j] << " ";
              }
              std::cout << std::endl;
          }
      }

  size_type getSize() const{
    return _size;
  }

private:

  value_type *_vertices; ///< Puntatore al primo vertice
  size_type _size; ///< Dimensione dell'array
  bool** _adjacencyMatrix;

};
#endif