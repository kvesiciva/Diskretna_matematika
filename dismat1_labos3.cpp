#include <iostream>
#include <cmath>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

template <class T>
class Queue
{
private:
    template <class X>
    struct QueueElement
    {
        T data;
        QueueElement<X> *next;
    };
    QueueElement<T> *read = nullptr;
    QueueElement<T> *write = nullptr;

public:
    bool enqueue(T data)
    {
        QueueElement<T> *newel = new (nothrow) QueueElement<T>;
        if (newel == nullptr)
            return false;
        newel->next = nullptr;
        newel->data = data;
        if (write == nullptr)
        {
            read = newel;
        }
        else
        {
            write->next = newel;
        }
        write = newel;
        return true;
    }
    bool dequeue(T &data)
    {
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

class DSU
{                  // klasa Disjoint Set Union
    int *roditelj; // polje za upis susjednog elemenata "roditelja" od
    int *rang;     // rang svakog vrha -->koliko je udaljen od "korijena"

public:
    DSU(int n)
    {
        roditelj = new int[n];
        rang = new int[n];

        for (int i = 0; i < n; i++)
        {
            roditelj[i] = -1;
            rang[i] = 1;
        }
    }

    // nadiKorijen funkcija --> vraca element "korijen" i, cija je vrijednost roditelj[i] == -1
    int nadiKorijen(int i)
    {
        if (roditelj[i] == -1) // ako je roditelj = "korijen", vrati vrijednost roditelja
            return i;

        return roditelj[i] = nadiKorijen(roditelj[i]);
    }

    // stvoriBrid funkcija --> da se dva vrha spoje u "brid"--> postaju susjedni i onaj s vecim rangom roditelj drugom (ako su isti )
    void stvoriBrid(int x, int y)
    {
        int s1 = nadiKorijen(x);
        int s2 = nadiKorijen(y);

        if (s1 != s2)
        {
            if (rang[s1] < rang[s2])
            {
                roditelj[s1] = s2;
            }
            else if (rang[s1] > rang[s2])
            {
                roditelj[s2] = s1;
            }
            else
            {
                roditelj[s2] = s1;
                rang[s1] += 1;
            }
        }
    }
};

class Graf
{
    vector<vector<int>> listaBridova;
    int V;

public:
    Graf(int V) { this->V = V; }

    void dodajBrid(int x, int y, int tezinaBrida)
    {
        listaBridova.push_back({tezinaBrida, x, y});
    }

    void kruskalMRS(vector<vector<int>> &matRazapStabla)
    {
        // sortiramo sve bridove
        sort(listaBridova.begin(), listaBridova.end());

        // inicijaliziraj DSU
        DSU s(V);
        int rez = 0;
        // cout << "Bridovi minimalnog razapinjuceg stabla su: "
        //  << endl;
        for (auto brid : listaBridova)
        {
            int tezinaBrida = brid[0];
            int x = brid[1];
            int y = brid[2];

            // Brid cemo staviti u minimalno razapinjuce stablo ako ne zatvara ciklus
            if (s.nadiKorijen(x) != s.nadiKorijen(y))
            {
                s.stvoriBrid(x, y);
                rez += tezinaBrida;
                matRazapStabla[x][y] = tezinaBrida;
                // cout << x << " -- " << y << " == " << tezinaBrida
                //  << endl;
            }
        }
        // cout << "Iznos svih bridova u minimalnom razapinjucem stablu: " << rez;
    }
};

vector<vector<int>> tezineMRS;
vector<int> susjed;

void dfs(int vrh)
{
    for (int i = 0; i < tezineMRS.size(); ++i)
    {
        if (tezineMRS[vrh][i] > 0 && i != susjed[vrh])
        {
            susjed[i] = vrh;
            dfs(i);
        }
    }
}

vector<int> pruferovKod()
{
    int n = tezineMRS.size();
    susjed.resize(n);
    susjed[n - 1] = -1;
    dfs(n - 1);

    int ptr = -1;
    vector<int> stupanj(n);
    for (int i = 0; i < n; ++i)
    {
        stupanj[i] = 0;
        for (int j = 0; j < n; ++j)
        {
            if (tezineMRS[i][j] > 0)
            {
                stupanj[i]++;
            }
        }
        if (stupanj[i] == 1 && ptr == -1)
        {
            ptr = i;
        }
    }

    vector<int> kod(n - 2);
    int list = ptr;
    for (int i = 0; i < n - 2; i++)
    {
        int next = susjed[list];
        kod[i] = next;
        if (--stupanj[next] == 1 && next < ptr)
        {
            list = next;
        }
        else
        {
            ptr++;
            while (stupanj[ptr] != 1)
                ptr++;
            list = ptr;
        }
    }

    return kod;
}

int main(void)
{

    int n; // broj vrhova
    cout << "Unesite prirodan broj n: ";
    cin >> n;

    int a;
    cout << "Unesite prirodan broj a: ";
    cin >> a;

    int b;
    cout << "Unesite prirodan broj b: ";
    cin >> b;

    int c;
    cout << "Unesite prirodan broj c: ";
    cin >> c;

    vector<vector<int>> matSusjedstva;
    matSusjedstva.resize(n);
    for (auto &stupac : matSusjedstva)
    {
        stupac.resize(n);
    }

    vector<vector<int>> matTezina;
    matTezina.resize(n);
    for (auto &stupac : matTezina)
    {
        stupac.resize(n);
    }

    int brojnik;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            brojnik = abs((a * (i + 1)) - (b * (j + 1)));

            if ((floor(brojnik / c) != 0) && (i != j) && (i < j))
            {
                matSusjedstva[i][j] = 1;
                matTezina[i][j] = floor(brojnik / c);
            }
            else
            {
                matSusjedstva[i][j] = 0;
                matTezina[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i > j)
            {
                matTezina[i][j] = matTezina[j][i];
                matSusjedstva[i][j] = matSusjedstva[j][i];
            }
        }
    }

    // provjera povezanosti grafa --> u biti BFS (Breadth First Search)

    bool prijeden[n];
    Queue<int> red;

    // oznacimo sve vrhove na pocetku kao neprijedene
    for (int i = 0; i < n; ++i)
    {
        prijeden[i] = false;
    }

    bool provjereni = false;
    bool prviProlaz = true;

    do
    {
        if (prviProlaz == true)
        {
            prijeden[0] = true;

            for (int j = 0; j < n; ++j)
            {
                if (matSusjedstva[0][j] == 1)
                {
                    red.enqueue(j);
                }
            }
            prviProlaz = false;
        }

        else
        {
            int el;
            if (red.dequeue(el))
            { // iz reda uzmemo jedan sljedeci vrh koji je bio prije bio susjedan i gledamo njegove susjede
                prijeden[el] = true;
                for (int j = 0; j < n; ++j)
                {
                    if (matSusjedstva[el][j] == 1)
                    {
                        if (prijeden[j] == 0)
                        {
                            red.enqueue(j);
                        }
                    }
                }
            }

            else
            {
                provjereni = true;
            }
        }
    } while (provjereni == false);

    bool povezan = true;
    for (int i = 0; i < n; i++)
    {
        if (prijeden[i] == false)
        {
            povezan = false;
        }
    }

    if (povezan == true)
    {
        cout << "Graf G je povezan graf";
    }
    else
    {
        cout << "Graf G nije povezan graf";
    }
    cout << endl;

    vector<vector<int>> minRazapStablo;
    minRazapStablo.resize(n);
    for (auto &stupac : minRazapStablo)
    {
        stupac.resize(n);
    }

    if (povezan == true)
    { // ako je graf povezan trazimo najmanje razapinjuce stablo i odredujemo njegov Pruferov kod

        Graf g(n);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (matTezina[i][j] != 0)
                {
                    g.dodajBrid(i, j, matTezina[i][j]);
                }
            }
        }

        vector<vector<int>> matRazapStabla;
        matRazapStabla.resize(n);
        for (auto &stupac : matRazapStabla)
        {
            stupac.resize(n);
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                matRazapStabla[i][j] = 0;
            }
        }

        g.kruskalMRS(matRazapStabla);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                matRazapStabla[j][i] = matRazapStabla[i][j]; // da bude simetricna
            }
        }

        tezineMRS.resize(n, vector<int>(n));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                tezineMRS[i][j] = matRazapStabla[i][j];
            }
        }

        vector<int> code = pruferovKod();

        cout << "Pruferov kod minimalnog razapinjuceg stabla: ";
        for (int i : code)
        {
            cout << (i + 1) << " ";
        }
    }
    return 0;
}