/**
@file main.cpp
@brief test d'uso della classe amgraph<int>
**/

// NOTA

#include <iostream>
#include <fstream>
#include "amgraph.h" // amgraph<int>
#include <cassert>   // assert

void test_fondamentali_int()
{
  
  std::cout << "*** TEST METODI FONDAMENTALI ***" << std::endl;

  std::cout << "test ctor default" << std::endl;
  amgraph<int> db1;
  assert(db1.size() == 0); // verifichiamo lo stato dell'oggetto
  db1.print();

  std::cout << "test ctor secondario 1" << std::endl;
  amgraph<int> db2(5);
  assert(db2.size() == 5);
  db2.print();

  std::cout << "test ctor secondario 2" << std::endl;
  amgraph<int> db3(5, 7);

  assert(db3.size() == 5);
  for (unsigned int i = 0; i < 5; i++)
    assert(db3.getVertexName(i) == 7);

  db3.print();

  std::cout << "adding true in 1:1 " << std::endl;
  db3.addEdge(1, 1);
  db3.print();

  std::cout << "test copy constructor" << std::endl;
  amgraph<int> db4(db3);
  // ATTENZIONE: una sintassi del tipo
  //             amgraph<int> db4 = db3;
  //             EQUIVALE ALLA CHIAMATA AL COPY CONSTRUCTOR!
  db4.print();
  assert(db4.size() == db3.size());

  for (unsigned int i = 0;
       i < db4.size(); i++)
    assert(db3[i] == db4[i]);

  std::cout << "test operatore assegnamento =" << std::endl;
  db1 = db3;
  assert(db1.size() == db3.size());
  for (unsigned int i = 0; i < db1.size(); i++)
    assert(db3[i] == db1[i]);
  std::cout<< "prova stampa nome secondo vertice : " << db1[1]<<std::endl;
  }


/**
  test dei metodi d'uso per un amgraph<int> non const
*/
void test_amgraph_int()
{
  std::cout << "*** TEST METODI amgraph<int> ***" << std::endl;

  amgraph<int> db(5, 0);
  db.print();
  std::cout << "test value" << std::endl;
  db.value(1) = 100;
  assert(db.value(1) == 100);
  db.print();

  std::cout << "test set_value" << std::endl;
  db.set_value(0, 99);
  assert(db.value(0) == 99);
  db.print();

  std::cout << "test scrittura op[]" << std::endl;
  db[3] = 5;
  assert(db[3] == 5);
  db.print();

  // Se compilazione in modalita' debug da' errore
  // db[100] = 5;

  std::cout << "test lettura op[]" << std::endl;
  int a = db[3];
  assert(a == 5);
  db.print();

  // Se compilazione in modalita' debug da' errore
  // int tmp = db[8];

  std::cout << "test stampa con operator<<" << std::endl;
  std::cout << db << std::endl;
}

/**
  funzione helper per i test dei metodi d'uso per un amgraph<int> const
*/
void test_amgraph_const_helper_int(const amgraph<int> &db)
{

  // Tutti i metodi di scrittura devono dare errore
  // db[1] = 10; // errore
  // db.value(1) = 10; // errore
  // db.set_value(1,10); // errore

  // I metodi di lettura devono funzionare
  int tmp1 = db[3];
  int tmp2 = db.value(3);
  int tmp3 = db.get_value(3);

  std::cout << "test stampa con operator<<" << std::endl;
  std::cout << db << std::endl;

  // amgraph<int> db2;
  // db2.swap(db); // errore
}

/**
  test dei metodi d'uso per un amgraph<int> const
*/
void test_amgraph_const_int()
{
  amgraph<int> db(5, 0);

  test_amgraph_const_helper_int(db);
}

/**
  Esempio di come si può serializzare un oggetto su file.
*/
void serializzazione_amgraph_int()
{
  std::cout << std::endl
            << "*** PROVA DI SERIALIZZAZIONE ***" << std::endl;

  // amgraph<int> di test
  amgraph<int> src(5, 9999);

  // Usando operator<< possiamo scrivere su file il contenuto del amgraph<int>.
  // E' importante scrivere operator<< in modo tale da spedire SOLO i dati
  // e niente altro. Nel caso specifico vengono spediti nell'ordine la size
  // e gli interi dell'array.
  std::ofstream ofs;
  ofs.open("output.txt"); // il file è aperto come testo
  if (!ofs.is_open())
  {
    std::cerr << "ERRORE NELLA'APERTURA DEL FILE" << std::endl;
    return;
  }
  ofs << src << std::endl;
  ofs.close();

  // Riapriamo il file e creiamo un secondo amgraph<int> con i valori salvati
  std::ifstream ifs;
  ifs.open("output.txt");
  if (!ifs.is_open())
  {
    std::cerr << "ERRORE NELLA'APERTURA DEL FILE" << std::endl;
    return;
  }
  // Leggiamo la size
  unsigned int size;
  ifs >> size;

  // Creiamo un amgraph<int> con la dimensione letta
  amgraph<int> dst(size);

  // Leggiamo i size interi dal file direttamente nelle celle dell'array
  for (unsigned int i = 0; i < size; ++i)
    ifs >> dst[i];
  ifs.close();

  std::cout << "Contenuto del amgraph<int> src:" << std::endl;
  std::cout << src << std::endl;

  std::cout << "Contenuto del amgraph<int> dst:" << std::endl;
  std::cout << dst << std::endl;
}

void test_conversione_tipo_int()
{
  amgraph<int> d1(10);

  amgraph<int> d2;

  d2 = d1; // op assegnamento

  d2 = amgraph<int>(3); // conversione di tipo esplicita

  std::swap(d1, d2);

  amgraph<int>::size_type s; // uso dei typedef
}

void test_iteratori_int()
{
  amgraph<int> d(10);

  for (unsigned int j = 0; j < 10; ++j)
    d[j] = j;

  amgraph<int>::const_iterator cit; // iteratore in lettura

  cit = d.begin();

  assert(*cit == 100);

  // *cit = 0; // errore

  // NOTA1: gli iteratori sono come i puntatori. Possono
  //        "puntare" a delle posizioni non valide se
  //        iteriamo troppo.
  //
  // NOTA2: non dereferenziare MAI l'iteratore di fine:
  //        Non punta a dei dati utili.
}

struct utente
{
  std::string nome;
  std::string cognome;

  utente(const std::string &n, const std::string &c) : nome(n), cognome(c) {}
};

int main(int argc, char *argv[])
{


  // Test con amgraph su interi: amgraph<int>
  //test_fondamentali_int();
  // ricordarsi inizializzare col cazzo di alore zero

  test_amgraph_int();

  // test_amgraph_const_int();

  // serializzazione_amgraph_int();

  // test_conversione_tipo_int();

  // test_iteratori_int();

  // Test con amgraph su tipi custom: es. amgraph<utente>

  // Rifare tutti i test come sopra
  //
  // test_amgraph_utente();
  // ...
  return 0;
}