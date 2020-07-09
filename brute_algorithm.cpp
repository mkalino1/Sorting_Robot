//
// Mateusz Kalinowski
// Program wybierający plan pracy dźwigu porządkującego kulki w trzech kolorach
//

#include "brute_algorithm.h"


bool is_solved(vector<char> &dane){
    int index = 0;
    while (index != dane.size() && dane[index] == 'c') index ++;
    while (index != dane.size() && dane[index] == 'z') index ++;
    while (index != dane.size() && dane[index] == 'n') index ++;
    if(index == dane.size())
        return true;
    return false;
}


vector<int> brute_algorythm(vector<char> &dane){
    queue<stan_brute> stany;

    //Dodaj do kolejki stan poczatkowy
    stan_brute stan_poczatkowy;
    stan_poczatkowy.aktualne_polozenia = dane;
    stany.push(stan_poczatkowy);

    //w petli pobiera kolejny stan i rozwija go w stany potomne likwidujac jednoczesnie stany-rodzice
    while(true){
        stan_brute tmp = stany.front();
        stany.pop();

        //Warunek stopu
        if(is_solved(tmp.aktualne_polozenia)) {
            dane = tmp.aktualne_polozenia;
            return tmp.poprzednie_ruchy;
        }
        //Rozwin pobrany stan w stany potomne
        for(int i=0; i<dane.size()-3; i++){
            stan_brute kopia = tmp;
            kopia.poprzednie_ruchy.push_back(i);
            move(kopia.aktualne_polozenia, i);
            stany.push(kopia);
        }
    }
}