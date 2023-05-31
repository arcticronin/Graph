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

  Classe che vuole rappresentare un grafo dinamico di tipo T.
*/
template <typename T>
class amgraph {

public:
  
  typedef T value_type; ///< Tipo del dato dell'array
  typedef unsigned int size_type; ///< Tipo del dato size
 
  /**
    @brief Costruttore di default

    COSTRUTTORE DI DEFAULT:
    Il costruttore di default serve a inizializzare un grafo vuoto

    @post _vertices = nullptr
    @post _size = 0
  */
  amgraph() : _vertices(nullptr), _size(0), _adjacencyMatrix(nullptr) { // Initialization list
 
  
  #ifndef NDEBUG
  std::cout << "amgraph::amgraph()" << std::endl;
  #endif
}

  /**
    @brief Costruttore secondario

    Costruttore secondario che serve a costruire un amgraph alla 
    dimensione data. Le celle della matrice sono inizializzate a false.

    @param sz dimensione dell'array da creare

    @post _vertices != nullptr
    @post _size = sz 
  */
  explicit amgraph(size_type sz) : _vertices(nullptr), _size(0), _adjacencyMatrix(nullptr) {
  // stato coerente

  // try catch
  _vertices = new value_type[sz];
  //for (int i = 0; i < _size; ++i){
  //  _vertices[i] = 0;
  //}
  // end try
  
  _size = sz;

  _adjacencyMatrix = new bool*[_size];
  for (int i = 0; i < _size; ++i) {
            _adjacencyMatrix[i] = new bool[_size];
            for (int j = 0; j < _size; ++j) {
                _adjacencyMatrix[i][j] = false;
            }
        }

  #ifndef NDEBUG
  std::cout << "amgraph::amgraph(size_type)" << std::endl;
  #endif
}

  /**
    @brief Costruttore secondario

    Costruttore secondario che serve a costruire un amgraph alla 
    dimensione data e con le celle dell'array inizializzate al valore
    passato.

    @param sz dimensione dell'array da creare
    @param value valore da usare per inizializzare le celle dell'array

    @post _vertices != nullptr
    @post _size = sz 
  */
  amgraph(size_type sz, const value_type &value) : _vertices(nullptr), _size(0), _adjacencyMatrix(nullptr) {

  _vertices = new value_type[sz];
  _size = sz;
  
  _adjacencyMatrix = new bool*[_size];
  for (int i = 0; i < _size; ++i) {
            _adjacencyMatrix[i] = new bool[_size];
            for (int j = 0; j < _size; ++j) {
                _adjacencyMatrix[i][j] = false;
            }
        }


  try {
    for(unsigned int i=0; i<_size; ++i)
      _vertices[i] = value;
  }
  catch(...) {
    delete[] _vertices;
    _vertices = nullptr;
    _size =0;
    
    //todo remove adjacencymatrix

    throw; // rilancio dell'eccezione !!
  }

  #ifndef NDEBUG
  std::cout << "amgraph::amgraph(size_type, value_type)" << std::endl;
  #endif
}

  /**
    @brief Distruttore

    2° METODO FONDAMENTALE: DISTRUTTORE
    Distruttore della classe. Il distruttore deve rimuovere tutte 
    le risorse usate dalla classe. In questo caso l'array allocato 
    sullo heap deve essere deallocato.
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
    @brief Accesso alla dimensione dell'array (stile C++)

    Metodo per ottenere la dimensione dell'array dinamico

    @return dimensione dell'array dinamico
  */
  size_type size(void) const{
    return _size;
  }

  /**
    @brief Accesso ai dati in lettura (stile Java)

    Metodo getter per leggere il valore index-esimo dell'array

    @param index indice della cella dell'array da leggere

    @return valore della cella index-esima

    @pre index < size()
  */
  value_type get_value(size_type index) const {
    assert(index<_size);

    return _vertices[index];
  }

  /**
    @brief Accesso ai dati in scrittura (stile Java)

    Metodo setter per scrivere un valore nella cella index-esima dell'array

    @param index indice della cella dell'array da scrivere
    @param value valore da scrivere nella cella

    @pre index < size()
  */  
  void set_value(unsigned int index, const value_type &value){
  assert(index<_size);

  _vertices[index] = value;
}

  /**
    @brief Getter/Setter della cella index-esima (stile C++)

    Metodo che permette di leggere e/o scrivere la cella
    index-esima dell'array

    @param index della cella da leggere/scrivere

    @return reference alla cella index-esima 

    @pre index < size()
  */
  value_type &value(size_type index) { 
  assert(index<_size);

  return _vertices[index];
}

  /**
    @brief Getter della cella index-esima (stile C++)

    Metodo che permette di leggere la cella
    index-esima dell'array. Il metodo si può usare
    solo su istanze costanti della classe.

    @param index della cella da leggere

    @return reference alla cella index-esima 

    @pre index < size()
  */
  const value_type &value(size_type index) const { 
  assert(index<_size);

  return _vertices[index];
}

  /**
    @brief Getter/Setter della cella index-esima (stile op[])

    Metodo che permette di leggere e/o scrivere la cella
    index-esima dell'array

    @param index della cella da leggere/scrivere

    @return reference alla cella index-esima 

    @pre index < size()
  */
  value_type &operator[](size_type index) { 
  assert(index<_size);

  return _vertices[index];
}

  /**
    @brief Getter della cella index-esima (stile op[])

    Metodo che permette di leggere la cella
    index-esima dell'array. Il metodo si può usare
    solo su istanze costanti della classe.

    @param index della cella da leggere

    @return reference alla cella index-esima 

    @pre index < size()
  */
  const value_type &operator[](size_type index) const { 
  assert(index<_size);

  return _vertices[index];
}


  /**
    @brief Metodo swap per la classe amgraph

    Funzione che scambia il contenuto di due amgraph

    @param other il amgraph con cui scambiare il contenuto
  */
  void swap(amgraph &other) {
    std::swap(_vertices, other._vertices);
    std::swap(_size, other._size); 
    std::swap(_adjacencyMatrix, other._adjacencyMatrix);
  }

  /**
    @brief ridefinizione operatore di stream

    Ridefinizione dell'operatore di stream per scrivere un
    amgraph su uno stream di output

    @param os stream di output (operando di sinistra)
    @param db amgraph da scrivere (operando di destra)

    @return reference allo stream di output
  */
  // Diamo accesso alla funzione globale, esterna alla classe, alle
  // parti private della classe
  friend std::ostream& operator<<(std::ostream &os, const amgraph<T> &db) {
    os << db._size << ' ';
    for(typename amgraph<T>::size_type i = 0; i < db.size() ; i++)
      os << db[i] << ' ';
  
    return os;
  }

/*
  // Versione "veloce" dell'iteratore di tipo random
  // Dato che noi abbiamo un puntatore ai dati di un array 
  // e un puntatore è anche un iteratore random, possiamo
  // usare typedef per mappare le classi iteratore ai rispettivi puntatori   
  typedef value_type *iterator;

  iterator begin() {
    return _vertices;
  }

  iterator end() {
    return _vertices + _size;
  }

  typedef const value_type *const_iterator;

  const_iterator begin() const {
    return _vertices;
  }

  const_iterator end() const {
    return _vertices + _size;
  }

*/

  // Implementazione completa di ietartori di tipo random.
  // Come si vedrà, i metodi sono solo dei wrapper a delle
  // operazioni tra puntatori.

  class const_iterator; // forward declaration

  class iterator {
    //  
  public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef T                        value_type;
    typedef ptrdiff_t                difference_type;
    typedef T*                       pointer;
    typedef T&                       reference;

  
    iterator() {
      ptr = nullptr;
    }
    
    iterator(const iterator &other) {
      ptr = other.ptr;
    }

    iterator& operator=(const iterator &other) {
      ptr = other.ptr;
      return *this;
    }

    ~iterator() { }

    // Ritorna il dato riferito dall'iteratore (dereferenziamento)
    reference operator*() const {
      return *ptr;
    }

    // Ritorna il puntatore al dato riferito dall'iteratore
    pointer operator->() const {
      return ptr;
    }

    // Operatore di accesso random
    reference operator[](int index) {
      return ptr[index];
    }
    
    // Operatore di iterazione post-incremento
    iterator operator++(int) {
      iterator old(*this);
      ++ptr;
      return  old;
    }

    // Operatore di iterazione pre-incremento
    iterator &operator++() {
      ++ptr;
      return *this;
    }

    // Operatore di iterazione post-decremento
    iterator operator--(int) {
      iterator old(*this);
      --ptr;
      return old;
    }

    // Operatore di iterazione pre-decremento
    iterator &operator--() {
      --ptr;
      return *this;
    }

    // Spostamentio in avanti della posizione
    iterator operator+(int offset) {
      return iterator(ptr+offset);
    }

    // Spostamentio all'indietro della posizione
    iterator operator-(int offset) {
      return iterator(ptr-offset);
    }
    
    // Spostamentio in avanti della posizione
    iterator& operator+=(int offset) {
      ptr+=offset;
      return *this;
    }

    // Spostamentio all'indietro della posizione
    iterator& operator-=(int offset) {
      ptr-=offset;
      return *this;
    }

    // Numero di elementi tra due iteratori
    difference_type operator-(const iterator &other) {
      return ptr-other.ptr;
    }
  
    // Uguaglianza
    bool operator==(const iterator &other) const {
      return ptr == other.ptr;
    }

    // Diversita'
    bool operator!=(const iterator &other) const {
      return ptr != other.ptr;
    }

    // Confronto
    bool operator>(const iterator &other) const {
      return ptr > other.ptr;
    }
    

    bool operator>=(const iterator &other) const {
      return ptr >= other.ptr;
    }

    // Confronto
    bool operator<(const iterator &other) const {
      return ptr < other.ptr;
    }
    
    
    // Confronto
    bool operator<=(const iterator &other) const {
      return ptr <= other.ptr;
    }
    
      
    friend class const_iterator;

    // Uguaglianza
    bool operator==(const const_iterator &other) const {
      return ptr == other.ptr;
    }

    // Diversita'
    bool operator!=(const const_iterator &other) const {
      return ptr != other.ptr;
    }

    // Confronto
    bool operator>(const const_iterator &other) const {
      return ptr > other.ptr;
    }
    

    bool operator>=(const const_iterator &other) const {
      return ptr >= other.ptr;
    }

    // Confronto
    bool operator<(const const_iterator &other) const {
      return ptr < other.ptr;
    }
    
    
    // Confronto
    bool operator<=(const const_iterator &other) const {
      return ptr <= other.ptr;
    }
 
  private:
    T * ptr;

    // La classe container deve essere messa friend dell'iteratore per poter
    // usare il costruttore di inizializzazione.
    friend class amgraph; 

    // Costruttore privato di inizializzazione usato dalla classe container
    // tipicamente nei metodi begin e end
    iterator(T *p) { 
      ptr = p;
    }
    
    // !!! Eventuali altri metodi privati
    
  }; // classe iterator
  
  // Ritorna l'iteratore all'inizio della sequenza dati
  iterator begin() {
    return iterator(_vertices);
  }
  
  // Ritorna l'iteratore alla fine della sequenza dati
  iterator end() {
    return iterator(_vertices+_size);
  }
  
  class const_iterator {
    //  
  public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef T                        value_type;
    typedef ptrdiff_t                difference_type;
    typedef const T*                 pointer;
    typedef const T&                 reference;

  
    const_iterator() {
      ptr = nullptr;
    }
    
    const_iterator(const const_iterator &other) {
      ptr = other.ptr;
    }

    const_iterator& operator=(const const_iterator &other) {
      ptr = other.ptr;
      return *this;
    }

    ~const_iterator() { }

    // Ritorna il dato riferito dall'iteratore (dereferenziamento)
    reference operator*() const {
      return *ptr;
    }

    // Ritorna il puntatore al dato riferito dall'iteratore
    pointer operator->() const {
      return ptr;
    }

    // Operatore di accesso random
    reference operator[](int index) {
      return ptr[index];
    }
    
    // Operatore di iterazione post-incremento
    const_iterator operator++(int) {
      const_iterator old(*this);
      ++ptr;
      return old;
    }

    // Operatore di iterazione pre-incremento
    const_iterator &operator++() {
      ++ptr;
      return *this;
    }

    // Operatore di iterazione post-decremento
    const_iterator operator--(int) {
      const_iterator old(*this);
      --ptr;
      return old;
    }

    // Operatore di iterazione pre-decremento
    const_iterator &operator--() {
      --ptr;
      return *this;
    }

    // Spostamentio in avanti della posizione
    const_iterator operator+(int offset) {
      return const_iterator(ptr+offset);
    }

    // Spostamentio all'indietro della posizione
    const_iterator operator-(int offset) {
      return const_iterator(ptr-offset);
    }
    
    // Spostamentio in avanti della posizione
    const_iterator& operator+=(int offset) {
      ptr+=offset;
      return *this;
    }

    // Spostamentio all'indietro della posizione
    const_iterator& operator-=(int offset) {
      ptr-=offset;
      return *this;
    }

    // Numero di elementi tra due iteratori
    difference_type operator-(const const_iterator &other) {
      return ptr - other.ptr;
    }
  
    // Uguaglianza
    bool operator==(const const_iterator &other) const {
      return ptr == other.ptr;
    }

    // Diversita'
    bool operator!=(const const_iterator &other) const {
      return ptr != other.ptr;
    }

    // Confronto
    bool operator>(const const_iterator &other) const {
      return ptr > other.ptr;
    }
    

    bool operator>=(const const_iterator &other) const {
      return ptr >= other.ptr;
    }

    // Confronto
    bool operator<(const const_iterator &other) const {
      return ptr < other.ptr;
    }
    
    
    // Confronto
    bool operator<=(const const_iterator &other) const {
      return ptr <= other.ptr;
    }
    
    
    // Solo se serve anche iterator aggiungere le seguenti definizioni
    
    friend class iterator;

    // Uguaglianza
    bool operator==(const iterator &other) const {
      return ptr == other.ptr;
    }

    // Diversita'
    bool operator!=(const iterator &other) const {
      return ptr != other.ptr;
    }

    // Confronto
    bool operator>(const iterator &other) const {
      return ptr > other.ptr;
    }
    

    bool operator>=(const iterator &other) const {
      return ptr >= other.ptr;
    }

    // Confronto
    bool operator<(const iterator &other) const {
      return ptr < other.ptr;
    }
    
    
    // Confronto
    bool operator<=(const iterator &other) const {
      return ptr <= other.ptr;
    }

    // Costruttore di conversione iterator -> const_iterator
    const_iterator(const iterator &other) {
      ptr = other.ptr;
    }

    // Assegnamento di un iterator ad un const_iterator
    const_iterator &operator=(const iterator &other) {
      ptr = other.ptr;
      return *this;
    }

    // Solo se serve anche iterator aggiungere le precedenti definizioni
  
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
    
    // !!! Eventuali altri metodi privati
    
  }; // classe const_iterator
  
  // Ritorna l'iteratore all'inizio della sequenza dati
  const_iterator begin() const {
    return const_iterator(_vertices);
  }
  
  // Ritorna l'iteratore alla fine della sequenza dati
  const_iterator end() const {
    return const_iterator(_vertices + _size);
  }

/*
  
  // Implementazione di un forward iterator (a scopo didattico)
  // fatta a lezione

  class const_iterator; // forward declaration

  class iterator {
    //  
  public:
    typedef std::forward_iterator_tag iterator_category;
    typedef T                         value_type;
    typedef ptrdiff_t                 difference_type;
    typedef T*                        pointer;
    typedef T&                        reference;

  
    iterator() {
      ptr = nullptr;
    }
    
    iterator(const iterator &other) {
      ptr = other.ptr;
    }

    iterator& operator=(const iterator &other) {
      ptr = other.ptr;
      return *this;
    }

    ~iterator() { }

    // Ritorna il dato riferito dall'iteratore (dereferenziamento)
    reference operator*() const {
      return *ptr;
    }

    // Ritorna il puntatore al dato riferito dall'iteratore
    pointer operator->() const {
      return ptr;
    }

    // Operatore di iterazione post-incremento
    iterator operator++(int) {
      iterator tmp(ptr);
      ++ptr;
      return tmp;
    }

    // Operatore di iterazione pre-incremento
    iterator& operator++() {
      ++ptr;
      return *this;
    }

    // Uguaglianza
    bool operator==(const iterator &other) const {
      return ptr == other.ptr;
    }

    // Diversita'
    bool operator!=(const iterator &other) const {
      return ptr != other.ptr;
    }
    
    // Solo se serve anche const_iterator aggiungere le seguenti definizioni
    friend class const_iterator;

    // Uguaglianza
    bool operator==(const const_iterator &other) const {
      return ptr == other.ptr;
    }

    // Diversita'
    bool operator!=(const const_iterator &other) const {
      return ptr != other.ptr;
    }

    // Solo se serve anche const_iterator aggiungere le precedenti definizioni

  private:
    value_type *ptr;

    // La classe container deve essere messa friend dell'iteratore per poter
    // usare il costruttore di inizializzazione.
    friend class amgraph; // !!! Da cambiare il nome!

    // Costruttore privato di inizializzazione usato dalla classe container
    // tipicamente nei metodi begin e end
    explicit iterator(T* p) { 
       ptr = p;
    }
        
  }; // classe iterator
  
  // Ritorna l'iteratore all'inizio della sequenza dati
  iterator begin() {
    return iterator(_vertices);
  }
  
  // Ritorna l'iteratore alla fine della sequenza dati
  iterator end() {
    return iterator(_vertices + _size);
  }
  
  
  
  class const_iterator {
    //  
  public:
    typedef std::forward_iterator_tag iterator_category;
    typedef T                         value_type;
    typedef ptrdiff_t                 difference_type;
    typedef const T*                  pointer;
    typedef const T&                  reference;

  
    const_iterator() {
      ptr = nullptr;
    }
    
    const_iterator(const const_iterator &other) {
      ptr = other.ptr;
    }

    const_iterator& operator=(const const_iterator &other) {
      ptr = other.ptr;
    }

    ~const_iterator() {
      
    }

    // Ritorna il dato riferito dall'iteratore (dereferenziamento)
    reference operator*() const {
      return *ptr;
    }

    // Ritorna il puntatore al dato riferito dall'iteratore
    pointer operator->() const {
      return ptr;
    }
    
    // Operatore di iterazione post-incremento
    const_iterator operator++(int) {
      const_iterator tmp(ptr);
      ++ptr;
      return tmp;
    }

    // Operatore di iterazione pre-incremento
    const_iterator& operator++() {
      ++ptr;
      return *this;
    }

    // Uguaglianza
    bool operator==(const const_iterator &other) const {
      return ptr == other.ptr;
    }
    
    // Diversita'
    bool operator!=(const const_iterator &other) const {
      return ptr != other.ptr;
    }

    // Solo se serve anche iterator aggiungere le seguenti definizioni
    
    friend class iterator;

    // Uguaglianza
    bool operator==(const iterator &other) const {
      return ptr == other.ptr;
    }

    // Diversita'
    bool operator!=(const iterator &other) const {
      return ptr != other.ptr;
    }

    // Costruttore di conversione iterator -> const_iterator
    const_iterator(const iterator &other) {
      ptr = other.ptr;
    }

    // Assegnamento di un iterator ad un const_iterator
    const_iterator &operator=(const iterator &other) {
      ptr = other.ptr;
      return *this;
    }

    // Solo se serve anche iterator aggiungere le precedenti definizioni

  private:
    const T *ptr;

    // La classe container deve essere messa friend dell'iteratore per poter
    // usare il costruttore di inizializzazione.
    friend class amgraph; // !!! Da cambiare il nome!

    // Costruttore privato di inizializzazione usato dalla classe container
    // tipicamente nei metodi begin e end
    const_iterator(const T *p) { 
      ptr = p; 
    }
    
    // !!! Eventuali altri metodi privati
    
  }; // classe const_iterator
  
  // Ritorna l'iteratore all'inizio della sequenza dati
  const_iterator begin() const {
    return const_iterator(_vertices);
  }
  
  // Ritorna l'iteratore alla fine della sequenza dati
  const_iterator end() const {
    return const_iterator(_vertices + _size);
  }
*/

  void addEdge(int src, int dest) {
      _adjacencyMatrix[src][dest] = true;
      _adjacencyMatrix[dest][src] = true;
  }

  void removeEdge(int src, int dest) {
      _adjacencyMatrix[src][dest] = false;
      _adjacencyMatrix[dest][src] = false;
  }

  bool hasEdge(int src, int dest) {
      return _adjacencyMatrix[src][dest];
  }

  void setVertexName(int vert, const T& name) {
      _vertices[vert] = name;
  }

  T getVertexName(int vert) {
      return _vertices[vert];
  }


  void print() {
          for (int i = 0; i < _size; ++i) {
              std::cout << "Vertex " << getVertexName(i) << ": ";
              for (int j = 0; j < _size; ++j) {
                  std::cout << _adjacencyMatrix[i][j] << " ";
              }
              std::cout << std::endl;
          }
      }

private:

  value_type *_vertices; ///< Puntatore all'array di interi
  size_type _size; ///< Dimensione dell'array
  bool** _adjacencyMatrix;

};






#endif