//
// Mateusz Kalinowski
// Program wybierający plan pracy dźwigu porządkującego kulki w trzech kolorach
//

#ifndef AAL_PROJEKT_BRUTE_ALGORYTHM_H
#define AAL_PROJEKT_BRUTE_ALGORYTHM_H

#include <vector>
#include <queue>
#include "utilities.h"

using namespace std;

struct stan_brute{
    vector<char> aktualne_polozenia;
    vector<int> poprzednie_ruchy;
};

bool is_solved(vector<char> &dane);
vector<int> brute_algorythm(vector<char> &dane);

#endif //AAL_PROJEKT_BRUTE_ALGORYTHM_H
