//
// Mateusz Kalinowski
// Program wybierający plan pracy dźwigu porządkującego kulki w trzech kolorach
//

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include "list_algorythm.h"
#include "brute_algorythm.h"
#include "naive_algorythm.h"
#include "utilities.h"

using namespace std;


vector<int> wywolaj_wybrany_algorytm(string &alg_name, vector<char> &dane){
    vector<int> wynik_dzialania_wybranego_algorytmu;

    if(alg_name == "l")
        wynik_dzialania_wybranego_algorytmu = list_algorythm(dane);
    else if(alg_name == "b")
        wynik_dzialania_wybranego_algorytmu = brute_algorythm(dane);
    else if(alg_name == "n")
        wynik_dzialania_wybranego_algorytmu = naive_algorythm(dane);
    else {
        cerr << "Nie ma takiego algorytmu";
        exit(1);
    }
    return wynik_dzialania_wybranego_algorytmu;
}

void wyswietl_wynik_pojedynczego_wykonania_algorytmu(string &alg_name, vector<char> dane){
    vector<int> wynik_dzialania_wybranego_algorytmu;

    cout<<"Kulki przed posortowaniem: ";
    for (auto kulka: dane)
       cout<<kulka;
    cout<<endl;

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    wynik_dzialania_wybranego_algorytmu = wywolaj_wybrany_algorytm(alg_name, dane);

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Czas wykonywania = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << " mikrosekund" << endl;
    cout << "Liczba ruchow = " << wynik_dzialania_wybranego_algorytmu.size() << endl;
    cout << "Kroki to: ";
    for(auto krok: wynik_dzialania_wybranego_algorytmu)
        cout<<krok<<" ";
    cout<<endl;
}


void wczytuj_problemy_ze_strumienia(string &alg_nazwa){
    string string_pobrany_z_pliku;
    vector<char> dane;

    int liczba_instancji_problemu;
    cin>>liczba_instancji_problemu;

    for(int i=0; i<liczba_instancji_problemu; i++){
        cin>>string_pobrany_z_pliku;
        for(char& c : string_pobrany_z_pliku) {
            dane.push_back(c);
        }
        wyswietl_wynik_pojedynczego_wykonania_algorytmu(alg_nazwa, dane);
        dane.clear();
    }
}


void procedura_testowania(string &alg_name, int rozmiar, int ilosc_iteracji, int krok, int ilosc_powtorzen){
    for(int iteracja = 0; iteracja < ilosc_iteracji; iteracja++) {
        int sum = 0;
        vector<char> dane;
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        for (int i = 0; i < ilosc_powtorzen; i++) {
            dane = generuj_dane(rozmiar + krok * iteracja);
            sum += wywolaj_wybrany_algorytm(alg_name, dane).size();
        }
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        cout << "Sredni czas wykonywania dla rozmiaru danych ";
        cout<<rozmiar + krok*iteracja<< " = " << ((double)chrono::duration_cast<chrono::microseconds>(end - begin).count()/ilosc_powtorzen)/1000000;
        cout<< " mikrosekund" << endl;
        cout << "Srednia liczba ruchow dla rozmiaru danych ";
        cout<<rozmiar + krok*iteracja<< " = " << (double)sum/ilosc_powtorzen << endl;
        cout<<endl;
    }
}

int main(int argc, char *argv[]) {
    if(argc == 1 or argc == 2){
        cerr<<"Podaj odpowiednie argumenty!";
        cerr<<"Przewodnik po trybach programu znajduje sie w pliku readme.txt";
        return 1;
    }

    switch(stoi(argv[1])) {
        case 1: {
            if(argc != 3){
                cerr<<"Zla liczba argumentow";
                return 1;
            }
            string alg_nazwa = argv[2];
            wczytuj_problemy_ze_strumienia(alg_nazwa);
            break;
        }
        case 2: {
            if(argc != 4){
                cerr<<"Zla liczba argumentow";
                return 1;
            }
            string alg_nazwa = argv[2];
            int rozmiar_problemu = stoi(argv[3]);
            vector<char> dane = generuj_dane(rozmiar_problemu);
            wyswietl_wynik_pojedynczego_wykonania_algorytmu(alg_nazwa, dane);
            break;
        }

        case 3: {
            if(argc != 7){
                cerr<<"Zla liczba argumentow";
                return 1;
            }
            string alg_nazwa = argv[2];
            int rozmiar = stoi(argv[3]);
            int ilosc_iteracji = stoi(argv[4]);
            int krok = stoi(argv[5]);
            int ilosc_powtorzen = stoi(argv[6]);
            procedura_testowania(alg_nazwa, rozmiar, ilosc_iteracji, krok, ilosc_powtorzen);
            break;
        }

        default:
            cerr<<"Podaj prawidlowe argumenty";
            return 3;
    }

    return 0;
}
