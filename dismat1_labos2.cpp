#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

template <class T> class Queue {
 private:
   template <class X> struct QueueElement {
      T data;
      QueueElement<X> *next;
   };
   QueueElement<T> *read = nullptr;
   QueueElement<T> *write = nullptr;

 public:
   bool enqueue(T data) {
      QueueElement<T> *newel = new (nothrow) QueueElement<T>;
      if (newel == nullptr)
         return false;
      newel->next = nullptr;
      newel->data = data;
      if (write == nullptr) {
         read = newel;
      } else {
         write->next = newel;
      }
      write = newel;
      return true;
   }
   bool dequeue(T &data) {
      if (read == nullptr)
         return false;
      data = read->data;
      QueueElement<T> *tmp = read;
      read = read->next;
      if (read == nullptr)
         write = nullptr;
      delete tmp;
      return true;
   }
};

auto pocVrh = 0;

// fja za provjeravanje hamiltonosti
bool isHamiltonian(int vrh, vector<vector<int>> &matSusjedstva, int n, vector<bool> &posjecen, int brojPosj) {
    posjecen[vrh] = true;
    ++brojPosj;

    if(brojPosj == n) {
        //ako je vec posjeceno n vrhova --> moramo se jos vratiti u pocetni vrh
        if(matSusjedstva[vrh][pocVrh] == 0) { // nije dobar put 
            posjecen[vrh] = false; // vrh odznacimo->nije vise posjecen
            return false;
        } else {
            return true; // vratili smo se u pocetni vrh --> imamo hamiltonski ciklus       
        }
    }

    for (int j = 0; j < n; ++j) {
        // kamo sve mozemo ici od vrha
        if (matSusjedstva[vrh][j] == 1) {
            if(posjecen[j] == false) {
                // mozemo probati ici ovim putem jer ide u neposjeceni vrh j
                bool search = isHamiltonian(j, matSusjedstva, n, posjecen, brojPosj); // sad gledamo iz vrha j 
                if (search) {
                    return true; // pronaden dobar put --> vracamo se u main
                } else {
                    continue; // ovaj put se nije isplatio, idemo gledati za neki drugi vrh
                }
            }
        }
    }
// prosli smo sve susjede vrha i nismo iz njega mogli nigdje ici --> izloran vrh
// odznacimo vrh -<nije vise posjecen
    posjecen[vrh] = false;
    return false;
}


int main(void) {

    int n; // broj vrhova
    cout << "Unesite prirodan broj n: ";
    cin >> n;

    int k_1;
    cout << "Unesite vrijednost prirodnog broja k_1: ";
    cin >> k_1;

    int k_2;
    cout << "Unesite vrijednost prirodnog broja k_2: ";
    cin >> k_2;

    int k_3;
    cout << "Unesite vrijednost prirodnog broja k_3: ";
    cin >> k_3;

    int k_4;
    cout << "Unesite vrijednost prirodnog broja k_4: ";
    cin >> k_4;



    vector<vector<int>> matSusjedstva;
    matSusjedstva.resize(n);
    for(auto& stupac : matSusjedstva) {
        stupac.resize(n);
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(((abs((i + 1) - (j + 1))) == k_1) || ((abs((i + 1) - (j + 1))) == k_2) || ((abs((i + 1) - (j + 1))) == k_3) || ((abs((i + 1) - (j + 1))) == k_4)) {
                matSusjedstva[i][j] = 1;
            } else {
                matSusjedstva[i][j] = 0;
            }
        }
    }

/*
//ispis matrice susjedstva
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cout << matSusjedstva[i][j] << " ";
        }
        cout << endl;
    }
*/

    // provjera povezanosti grafa --> U biti BFS (Breadth First Search)

    bool prijeden[n];
    Queue<int> red;

    //oznacimo sve vrhove na pocetku kao neprijedene 
    for (int i = 0; i < n; i++) {
        prijeden[i] = false;
    }

    bool provjereni = false;
    bool prviProlaz = true;

    do {
      if(prviProlaz == true) {
         prijeden[0] = true;

         for (int j = 0; j < n; ++j) {
            if(matSusjedstva[0][j] == 1) {
               red.enqueue(j);
            }
         }
         prviProlaz = false;
      }

      else {
         int el;
         if(red.dequeue(el)) { // iz reda uzmemo jedan sljedeci vrh koji je bio prije bio susjedan i gledamo njegove susj.
            prijeden[el] = true;
            for (int j = 0; j < n; ++j) {
               if(matSusjedstva[el][j] == 1) {
                  if(prijeden[j] == 0) {
                    red.enqueue(j);
                  }
               }
            }            
         }

         else {
            provjereni = true;
         }

      }
   } while (provjereni == false);

    bool povezan = true;
    for (int i = 0; i < n; i++) {
        if(prijeden[i] == false) {
            povezan = false;
        }
    }

    if (povezan == true) {
        cout << "Graf G je povezan graf";
    }
    else {
        cout << "Graf G nije povezan graf";
    }
    cout << endl;

    vector<bool> posjecen;
    posjecen.resize(n);
    for(int i = 0; i < n; i++) {
        posjecen[i] = false;
    }

    bool hamiltonski = isHamiltonian(pocVrh, matSusjedstva, n, posjecen, 0);

    if ((n > 2) && hamiltonski) { // graf da bi imao cikljus mora imati bar 2 vrha
        cout << "Graf G je hamiltonski graf";
    }
    else {
        cout << "Graf G nije hamiltonski graf";
    }

    return 0;
}