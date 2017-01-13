#include "classes.h"
#include <ctime>

void construct_neutral_set(set<int> &neutral_bits, list<vector<unsigned>>  &neutral_bits_set, list<vector<int>>  &new_neutral_bits_set, const message &M1, const message &M2, const difference &D);

void read(vector<vector<int>> &neutral_vectors);

void read_clique(vector<vector<int>> &neutral_vectors);

void constructor(const message &M1, const message &M2, const difference &D);

void find_best_pair(const message &M1, const message &M2, const difference &D);
