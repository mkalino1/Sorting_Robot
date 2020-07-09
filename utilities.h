//
// Mateusz Kalinowski
// Program wybierający plan pracy dźwigu porządkującego kulki w trzech kolorach
//

#ifndef AAL_PROJEKT_MOVE_H
#define AAL_PROJEKT_MOVE_H

#include <vector>
#include <map>
#include <random>
#include <chrono>

using namespace std;

vector<char> generuj_dane(int rozmiar);
void move(vector<char> &dane, int index);
int oblicz_liczbe_dopasowanych_kulek_na_poczatku(vector<char> &dane);
bool czy_nie_wystepuje_od_tego_indeksu_kolor(vector<char> &dane, char &COLOR, int index);
map <char, char> get_color_map();

#endif //AAL_PROJEKT_MOVE_H
