//
// Mateusz Kalinowski
// Program wybierający plan pracy dźwigu porządkującego kulki w trzech kolorach
//

#ifndef AAL_PROJEKT_NAIVE_ALGORYTHM_H
#define AAL_PROJEKT_NAIVE_ALGORYTHM_H

#include <vector>
#include <queue>
#include "utilities.h"

using namespace std;

struct stan_naive{
    vector<char> aktualne_polozenia_kulek;
    vector<int> poprzednie_ruchy;
    int ilosc_dopasowanych;
    int ilosc_kulek_c;
    int ilosc_kulek_z;
    int ilosc_uporzadkowanych_kulek_c;
    int ilosc_uporzadkowanych_kulek_z;
};

vector<int> naive_algorythm(vector<char> &dane);


#endif //AAL_PROJEKT_NAIVE_ALGORYTHM_H
