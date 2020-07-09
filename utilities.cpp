//
// Mateusz Kalinowski
// Program wybierający plan pracy dźwigu porządkującego kulki w trzech kolorach
//

#include "utilities.h"

vector<char> generuj_dane(int rozmiar){
    vector<char> dane;
    vector<char> litery = {'c', 'z', 'n'};

    // Obsluga losowosci
    mt19937 eng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<> distr_litery(0, litery.size()-1);
    uniform_int_distribution<> distr_kulki(0, rozmiar-1);

    //Losuj kulki
    for(int n=0; n<rozmiar; ++n)
        dane.push_back(litery[distr_litery(eng)]);

    // Upewnij sie, ze sa 3 niebieskie kulki
    int n_count = 0;
    for (auto kulka: dane)
        if(kulka == 'n') n_count++;
    while(n_count < 3) {
        dane[distr_kulki(eng)] = 'n';
        n_count = 0;
        for (auto kulka: dane)
            if(kulka == 'n') n_count++;
    }

    return dane;
}

void move(vector<char> &dane, int index){
    vector<char> tmp;
    for(int i=0; i<3; i++)
        tmp.push_back(dane[index+i]);

    auto it = dane.begin() + index;
    dane.erase(it, it+3);

    for(auto kulka:tmp)
        dane.push_back(kulka);
}

int oblicz_liczbe_dopasowanych_kulek_na_poczatku(vector<char> &dane){
    map<char, char> next_color = get_color_map();
    char szukany_kolor = 'c';
    int c_count = 0;
    int z_count = 0;
    for (auto kulka: dane){
        if(kulka == 'c') c_count++;
        if(kulka == 'z') z_count++;
    }

    if(c_count == 0){
        szukany_kolor = next_color[szukany_kolor];
        if(z_count == 0)
            szukany_kolor = next_color[szukany_kolor];
    }

    int index = 0;
    while(index != dane.size() && dane[index] == szukany_kolor) {
        index++;
        if(index == c_count )
            szukany_kolor = next_color[szukany_kolor];
        if(index == c_count + z_count)
            return dane.size();         //wszystkie sa dopasowane

    }

    return index;
}

map <char, char> get_color_map() {
    map<char, char> next_color = {
            {'c', 'z'},
            {'z', 'n'}
    };
    return next_color;
}



bool czy_nie_wystepuje_od_tego_indeksu_kolor(vector<char> &dane, char &COLOR, int index){
    while(index<dane.size()){
        if(dane[index] == COLOR)
            return false;
        index++;
    }
    return true;
}