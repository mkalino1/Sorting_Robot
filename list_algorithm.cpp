//
// Mateusz Kalinowski
// Program wybierający plan pracy dźwigu porządkującego kulki w trzech kolorach
//

#include "list_algorithm.h"



bool czy_nie_wystepuje_kolor_w_listach(vector<char> &dane, vector<lista> &listy, char c) {
    for (auto lista:listy) {
        for (int i = lista.start; i <= lista.koniec; i++) {
            if (dane[i] == c)
                return false;
        }
    }
    return true;
}

void wydzielaj_listy(vector<char> &dane, vector<lista> &listy, int index, char &COLOR, map<char, char> &next_color){
    bool szukaj_kolejnej_listy = true;
    lista l;
    l.start = index;
    while(szukaj_kolejnej_listy){
        if(index == dane.size()){
            l.koniec = l.start-1;
            szukaj_kolejnej_listy = false;
            listy.push_back(l);
        }
        else if(index >= dane.size()-3){
            l.koniec = dane.size()-1;
            szukaj_kolejnej_listy = false;
            listy.push_back(l);
        }
        else if(dane[index+3] == COLOR){
            l.koniec = index + 2;
            listy.push_back(l);
            while(index+3 < dane.size() && dane[index+3] == COLOR)
                index++;
            if(COLOR != 'n' && czy_nie_wystepuje_kolor_w_listach(dane, listy, COLOR) &&
                    czy_nie_wystepuje_od_tego_indeksu_kolor(dane, COLOR, index + 3))
                COLOR = next_color[COLOR];
            while(index+3 < dane.size() && dane[index+3] == COLOR)
                index++;
            l.start = index + 3;

        }
        index+=3;
    }
}

bool inicjalizuj(vector<char> &dane, vector<lista> &listy, char &COLOR, map<char, char> &next_color){
    int index = oblicz_liczbe_dopasowanych_kulek_na_poczatku(dane);

    if(index == dane.size())
        return true;

    wydzielaj_listy(dane, listy, index, COLOR, next_color);
    return false;
}

int wybierz_ruch_dla_modulo_0(vector<char> &dane, vector<lista> &listy, char &COLOR){
    vector<int> tiers = {-1, -1, -1, -1};

    for(auto lista: listy){
        for(int index = lista.start; index<lista.koniec-1; index++) {
            if(index == dane.size()-3)
                continue;
            string s = "";
            for (int i = 0; i < 3; i++) {
                (dane[index + i] == COLOR) ? s += 'X' : s += '*';
            }
            if (s == "XXX") {
                return index;
            }
            else if (s == "XX*"){
                if (tiers[0] == -1) tiers[0] = index;
            }
            else if (s == "X**" || s == "X*X") {
                if (tiers[1] == -1) tiers[1] = index;
            }
            else if (s == "*X*" || s == "*XX" || (s == "**X" && !(index == dane.size()-4 && index >= listy.back().start))) {
                if (tiers[2] == -1) tiers[2] = index;
            }
            else
            if(tiers[3] == -1) tiers[3] = index;
        }
    }

    for(int i = 0; i<4; i++){
        if(tiers[i] != -1)
            return tiers[i];
    }
}

int wybierz_ruch_dla_modulo_1(vector<char> &dane, vector<lista> &listy, char &COLOR){
    vector<int> tiers = {-1, -1};
    for(auto lista: listy){
        for(int index = lista.start; index<lista.koniec-1; index++) {
            if(index == dane.size()-3)
                continue;
            string s = "";
            for (int i = 0; i < 3; i++) {
                (dane[index + i] == COLOR) ? s += 'X' : s += '*';
            }
            if (s == "**X" || s == "*XX" || s == "XXX") {
                return index;
            }
            else if (s == "X*X" || s == "XX*" || s == "*X*" || s == "X**") {
                if (tiers[0] == -1) tiers[0] = index;
            }
            else
            if(tiers[1] == -1) tiers[1] = index;
        }
    }
    for(int i = 0; i<2; i++){
        if(tiers[i] != -1)
            return tiers[i];
    }
}


int wybierz_ruch_dla_modulo_2(vector<char> &dane, vector<lista> &listy, char &COLOR){
    vector<int> tiers = {-1, -1, -1};
    for(auto lista: listy){
        for(int index = lista.start; index<lista.koniec-1; index++) {
            if(index == dane.size()-3)
                continue;
            string s = "";
            for (int i = 0; i < 3; i++) {
                (dane[index + i] == COLOR) ? s += 'X' : s += '*';
            }
            if (s == "*XX" || s == "XXX") {
                return index;
            }
            else if (s == "*X*" || s == "XX*"){
                if(tiers[0] == -1) tiers[0] = index;
            }
            else if (s == "X*X" || s == "X**"|| s == "**X") {
                if (tiers[1] == -1) tiers[1] = index;
            }
            else
            if(tiers[2] == -1) tiers[2] = index;
        }
    }

    for(int i = 0; i<3; i++){
        if(tiers[i] != -1)
            return tiers[i];
    }
}


//Jesli to mozliwe rozdziela ostatnia liste na pare list
void rozdziel_ostatnia_liste(vector<char> &dane, vector<lista> &listy, char &COLOR, map<char, char> &next_color){
    int index = listy.back().start;
    listy.pop_back();

    while (index != dane.size() && dane[index] == COLOR)
        index++;
    if(index != dane.size() && COLOR != 'n' && czy_nie_wystepuje_kolor_w_listach(dane, listy, COLOR) && czy_nie_wystepuje_od_tego_indeksu_kolor(dane, COLOR, index))
        COLOR = next_color[COLOR];
    while (index != dane.size() && dane[index] == COLOR)
        index++;

    wydzielaj_listy(dane, listy, index, COLOR, next_color);

    //Oznacza to, ze kulki sa juz uporzadkowane
    if(COLOR == 'n' && listy.size() == 1)
        listy.pop_back();
}

//Po dokonaniu ruchu indeksy w listach przestaly byc aktualne, nalezy je zaktualizowac
void zaktualizuj_indeksy_list(vector<char> &dane, vector<lista> &listy, int wybor) {
    vector<int> do_skasowania;
    for(int i = 0; i<listy.size(); i++){
        if(wybor < listy[i].start) {
            listy[i].start -= 3;
            listy[i].koniec -= 3;
        }
        else if (wybor >= listy[i].start && wybor < listy[i].koniec){
            listy[i].koniec -= 3;
        }
    }
    listy.back().koniec += 3;

    //Nalezy tez usunac te listy, ktore staly sie wlasnie puste po wykonaniu ruchu
    for(int i = 0; i<listy.size(); i++){
        if((listy[i].koniec - listy[i].start)<=0) {
            do_skasowania.push_back(i);
        }
    }
    reverse(do_skasowania.begin(), do_skasowania.end());
    for(auto index: do_skasowania)
        listy.erase(listy.begin() + index);
}


vector<int> list_algorythm(vector<char> &dane) {
    vector<int> wynik_dzialania_algorytmu;
    map<char, char> next_color = get_color_map();

    char COLOR = 'c';
    vector<lista> listy;
    bool is_it_already_sorted = inicjalizuj(dane, listy, COLOR, next_color);
    if(is_it_already_sorted) return wynik_dzialania_algorytmu;

    //Petla glowna przy kazdej iteracji wybierajaca kolejny ruch dzwigu
    while(!listy.empty()){
        // SWITCH SZUKANIA WYBORU RUCHU
        int wybor = 0;
        switch((listy.back().koniec - listy.back().start + 1)%3) {
            case 0:
                wybor = wybierz_ruch_dla_modulo_0(dane, listy, COLOR);
                break;
            case 1:
                wybor = wybierz_ruch_dla_modulo_1(dane, listy, COLOR);
                break;
            case 2:
                wybor = wybierz_ruch_dla_modulo_2(dane, listy, COLOR);
                break;
        }
        //RUCH DZWIGU
        move(dane, wybor);
        wynik_dzialania_algorytmu.push_back(wybor);

        zaktualizuj_indeksy_list(dane, listy, wybor);
        rozdziel_ostatnia_liste(dane, listy, COLOR, next_color);

    }
    return wynik_dzialania_algorytmu;
}