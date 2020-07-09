//
// Mateusz Kalinowski
// Program wybierający plan pracy dźwigu porządkującego kulki w trzech kolorach
//

#include "naive_algorithm.h"


vector<int> naive_algorythm(vector<char> &dane){

    //funkcja pomocnicza porownujaca stany na potrzeby definiowania prawidlowej kolejnosci w kolejce priotytetowej
    auto cmp = [](stan_naive left, stan_naive right) {
        if(left.ilosc_dopasowanych == right.ilosc_dopasowanych)
            return left.poprzednie_ruchy.size() > right.poprzednie_ruchy.size();
        return (left.ilosc_dopasowanych) < (right.ilosc_dopasowanych);
    };

    priority_queue<stan_naive, vector<stan_naive>, decltype(cmp)> kolejka(cmp);

    stan_naive stan_poczatkowy;

    // Inicjalizowanie wszystkich wartosci stanu poczatkowego
    stan_poczatkowy.aktualne_polozenia_kulek = dane;
    stan_poczatkowy.ilosc_kulek_c = 0;
    stan_poczatkowy.ilosc_kulek_z = 0;
    stan_poczatkowy.ilosc_uporzadkowanych_kulek_c = 0;
    stan_poczatkowy.ilosc_uporzadkowanych_kulek_z = 0;
    for (auto kulka: dane) {
        if (kulka == 'c') stan_poczatkowy.ilosc_kulek_c++;
        else if (kulka == 'z') stan_poczatkowy.ilosc_kulek_z++;
    }
    stan_poczatkowy.ilosc_dopasowanych = oblicz_liczbe_dopasowanych_kulek_na_poczatku(dane);
    for(int i=0; i<stan_poczatkowy.ilosc_dopasowanych; i++){
        if(stan_poczatkowy.aktualne_polozenia_kulek[i] == 'c')
            stan_poczatkowy.ilosc_uporzadkowanych_kulek_c++;
        else if(stan_poczatkowy.aktualne_polozenia_kulek[i] == 'z')
            stan_poczatkowy.ilosc_uporzadkowanych_kulek_z++;
    }
    //Dodaj do kolejki stan poczatkowy
    kolejka.push(stan_poczatkowy);

    //W petli pobiera najlepiej rokujacy stan i rozwija go w stany potomne z odpowiednimi priorytetami
    while(true){
        stan_naive aktualnie_przetwarzany = kolejka.top();
        kolejka.pop();

        //Warunek stopu
        if(aktualnie_przetwarzany.ilosc_dopasowanych == dane.size()) {
            dane = aktualnie_przetwarzany.aktualne_polozenia_kulek;
            return aktualnie_przetwarzany.poprzednie_ruchy;
        }

        //Rozwin pobrany stan w stany potomne i dodaj je do kolejki tak aby zachowana byla odpowiednia kolejnosc
        for(int i=aktualnie_przetwarzany.ilosc_dopasowanych; i<dane.size()-3; i++){
            stan_naive stan_potomny = aktualnie_przetwarzany;
            stan_potomny.poprzednie_ruchy.push_back(i);
            move(stan_potomny.aktualne_polozenia_kulek, i);

            //Sprawdz czy stan potomny jest lepszy i o ile. Jesli jest to zaktualizuj jego ilosc_dopasowanych
            while (stan_potomny.ilosc_dopasowanych != dane.size() && stan_potomny.aktualne_polozenia_kulek[stan_potomny.ilosc_dopasowanych] == 'c') {
                stan_potomny.ilosc_dopasowanych++;
                stan_potomny.ilosc_uporzadkowanych_kulek_c++;
            }
            while (stan_potomny.ilosc_dopasowanych != dane.size() && stan_potomny.aktualne_polozenia_kulek[stan_potomny.ilosc_dopasowanych] == 'z'
                   && stan_potomny.ilosc_kulek_c == stan_potomny.ilosc_uporzadkowanych_kulek_c) {
                stan_potomny.ilosc_dopasowanych++;
                stan_potomny.ilosc_uporzadkowanych_kulek_z++;
            }
            if(stan_potomny.ilosc_dopasowanych != dane.size()
               && stan_potomny.ilosc_kulek_c == stan_potomny.ilosc_uporzadkowanych_kulek_c
               && stan_potomny.ilosc_kulek_z == stan_potomny.ilosc_uporzadkowanych_kulek_z) {
                stan_potomny.ilosc_dopasowanych = dane.size();
            }

            // Dodaj tak przetworzony stan do kolejki
            kolejka.push(stan_potomny);
        }
    }
}
