#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <iterator>
#include <algorithm>
#include <map>
#include <stack>
#include <tuple>
#include <fstream>
#include <omp.h>
#include <string>

#define MASK 0xffffffff
#define R 20
#define CLIQUE_SIZE 35
#define CLIQUES_COUNT 10000
#define STEP 64

using namespace std;

vector<unsigned> xor_vec(const vector<unsigned> &a, const vector<unsigned> &b);

vector<unsigned> xor_vec(const vector<unsigned> &a, const vector<unsigned> &b, const vector<unsigned> &c);

vector<unsigned> xor_vec(vector<unsigned> a, const vector<int> &v1, const vector<int> &v2);

vector<int> convert_vector_long(const vector<unsigned> &v);

inline
vector<unsigned> xor_vec(vector<unsigned> a, const vector<int> &vec){
	for (int i = 0; i < 5; i++){
		if (vec[i] != -1)
			a[vec[i] / 32] ^= 1 << (vec[i] % 32);
	}
	return a;
}

inline
void xor(vector<unsigned> &a, const vector<int> &vec){
	for (int i = 0; i < 5; i++){
		if (vec[i] != -1)
			a[vec[i] / 32] ^= 1 << (vec[i] % 32);
	}
	return;
}

vector<unsigned> xor_vec(vector<unsigned> a, int b, int c, int d, int e, int f);

void show_number(const vector<unsigned> &v);

class message{
public:
	vector<unsigned int> b;
	vector<unsigned int> c;
	vector<unsigned int> d;
	vector<unsigned int> e;
	vector<unsigned int> W;
	vector<unsigned int> a;
	message(const vector<unsigned> &in);
	message(const vector<unsigned> &in, char a);
	message(const vector<unsigned> &in, int max_round);
	message(const message &M);
	message(){}
	void modify(const vector<unsigned> &In, int max_round);
	void SetIV(int round);
};

struct message_cupple{
	message m1;
	message m2;
public:
	message_cupple(const vector<unsigned> &In1, const vector<unsigned> &In2, int r){
		m1 = message(In1, r);
		m2 = message(In2, r);
	}
	message_cupple(){}
};

class difference{
public:
	vector<unsigned> dif;
	difference(const message &m1, const message &m2);
	difference();
	int equal(const message &m1, const message &m2, int r)const;
	int equal(const message_cupple &cup, int r)const;
	void print(const message& m1, const message& m2, int r)const;
	void print(int r)const;
	int modify(message& m1, message& m2)const;
	int modify_full(message& m1, message& m2)const;
};

int check(vector<vector<char>> &a, set <int> &K, set <int> &P);

void extend(vector<vector<char>> &a, list<set<int>> &REZULT, set <int> candidates, set <int> not, set <int> M);

void kerbosh(vector<vector<char>> &a, int SIZE, set<int> &clique, vector<vector<int>> &neutral_vectors);


class DifferentialPath{
	vector<vector<char>> path;
	vector<vector<char>> path_w;
public:
	DifferentialPath();
	int check(const message &m1, const message &m2)const;
	bool checkBit(int bit)const;
};

class adj_matrix{
public:
	vector<vector<char>> adj;
	adj_matrix(int size){
		adj.resize(size);
		for (unsigned i = 0; i < size; i++){
			adj[i] = vector<char>(size, 0);
		}
	}
	void show(const list<vector<int>> &new_neutral_bits_set, const message &M1, const message &M2, const difference &D);
	void fill(const vector<vector<int>> &new_neutral_bits_set, const message &M1, const message &M2, const difference &D, const DifferentialPath &P);
	void edges();
};

void show_clique(const set<int> &clique, const vector<vector<int>> &new_neutral_bits_set, vector<vector<int>> &final_set);

vector<int> convert_vector(const vector<unsigned> &v);

void print_results(const message &m1, const message &m2, const message &start_m1, const message &start_m2, int r);

bool not_intersect(vector<int> a, vector<int> b);

void print_results_full(const message &m1, const message &m2, const message &start_m1, const message &start_m2);

void print_results_two_blocks(const message &m1, const message &m2, int last_step);

void check_differential_path(const message &m1, const message &m2);

void findPairTree(message &M1, message &M2, const difference &D, const DifferentialPath &P, int max_clique_size, ofstream& changes, int counter, message &M1_old, message &M2_old);
