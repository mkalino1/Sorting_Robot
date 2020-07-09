//
// Mateusz Kalinowski
// Program wybierający plan pracy dźwigu porządkującego kulki w trzech kolorach
//

#ifndef AAL_PROJEKT_LIST_ALGORYTHM_H
#define AAL_PROJEKT_LIST_ALGORYTHM_H

#include <map>
#include <vector>
#include <algorithm>
#include "utilities.h"

using namespace std;

struct lista{
    int start;
    int koniec;
};

bool czy_nie_wystepuje_kolor_w_listach(vector<char> &dane, vector<lista> &listy, char c);
bool inicjalizuj(vector<char> &dane, vector<lista> &listy, char &COLOR, map<char, char> &next_color);
int wybierz_ruch_dla_modulo_0(vector<char> &dane, vector<lista> &listy, char &COLOR);
int wybierz_ruch_dla_modulo_1(vector<char> &dane, vector<lista> &listy, char &COLOR);
int wybierz_ruch_dla_modulo_2(vector<char> &dane, vector<lista> &listy, char &COLOR);
void wydzielaj_listy(vector<char> &dane, vector<lista> &listy, int index, char &COLOR, map<char, char> &next_color);
void zaktualizuj_indeksy_list(vector<char> &dane, vector<lista> &listy, int wybor);
void rozdziel_ostatnia_liste(vector<char> &dane, vector<lista> &listy, char &COLOR, map<char, char> &next_color);
vector<int> list_algorythm(vector<char> &dane);

#endif //AAL_PROJEKT_LIST_ALGORYTHM_H
