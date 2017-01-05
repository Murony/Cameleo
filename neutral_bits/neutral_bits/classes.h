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
#define R 22
#define CLIQUE_SIZE 30

using namespace std;

vector<unsigned> xor_vec(const vector<unsigned> &a, const vector<unsigned> &b);

vector<unsigned> xor_vec(const vector<unsigned> &a, const vector<unsigned> &b, const vector<unsigned> &c);

vector<unsigned> xor_vec(vector<unsigned> a, const vector<int> &v1, const vector<int> &v2);

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
	message(){}
	void modify(const vector<unsigned> &In, int max_round);
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
};

int check(vector<vector<char>> &a, set <int> &K, set <int> &P);

void extend(vector<vector<char>> &a, list<set<int>> &REZULT, set <int> candidates, set <int> not, set <int> M);

void kerbosh(vector<vector<char>> &a, int SIZE, set<int> &clique, vector<vector<int>> &neutral_vectors);

class adj_matrix{
public:
	vector<vector<char>> adj;
	adj_matrix(int size){
		adj.resize(size);
		for (unsigned i = 0; i < size; i++){
			adj[i] = vector<char>(size, 0);
		}
	}
	void fill(const list<vector<int>> &new_neutral_bits_set, const message &M1, const message &M2, const difference &D);
	void show(const list<vector<int>> &new_neutral_bits_set, const message &M1, const message &M2, const difference &D);
	void fill(const vector<vector<int>> &new_neutral_bits_set, const message &M1, const message &M2, const difference &D);
	void edges();
};

void show_clique(const set<int> &clique, const vector<vector<int>> &new_neutral_bits_set, vector<vector<int>> &final_set);

vector<int> convert_vector(const vector<unsigned> &v);

void print_results(const message &m1, const message &m2, const message &start_m1, const message &start_m2, int r);