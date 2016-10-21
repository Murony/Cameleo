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

#define MASK 0xffffffff
#define R 23

using namespace std;

void generate_list(list<vector<unsigned>> &neutral_bits_set, set<int> &neutral_bits);

vector<unsigned> xor_vec(const vector<unsigned> &a, const vector<unsigned> &b);

vector<unsigned> xor_vec(const vector<unsigned> &a, const vector<unsigned> &b, const vector<unsigned> &c);

vector<unsigned> xor_vec(vector<unsigned> a, const vector<int> &v1, const vector<int> &v2);

vector<unsigned> xor_vec(vector<unsigned> a, int b, int c, int d, int e, int f);

void show_number(const vector<unsigned> &v);

class message{
	vector<unsigned int> b;
	vector<unsigned int> c;
	vector<unsigned int> d;
	vector<unsigned int> e;
public:
	vector<unsigned int> W;
	vector<unsigned int> a;
	message(const vector<unsigned> &in);
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
	int equal(const message &m1, const message &m2, int r)const;
	int equal(const message_cupple &cup, int r)const;
	void print(const message& m1, const message& m2, int r)const;
};

int check(vector<vector<int>> &a, set <int> &K, set <int> &P);

void extend(vector<vector<int>> &a, list<set<int>> &REZULT, set <int> candidates, set <int> not, set <int> M);

void kerbosh(vector<vector<int>> &a, int SIZE, set<int> &clique);

class adj_matrix{
public:
	vector<vector<int>> adj;
	adj_matrix(int size){
		adj.resize(size);
		for (unsigned i = 0; i < adj.size(); i++){
			adj[i] = vector<int>(size, 0);
		}
	}
	void fill(const list<vector<int>> &new_neutral_bits_set, const message &M1, const message &M2, const difference &D);
	void show(const list<vector<int>> &new_neutral_bits_set, const message &M1, const message &M2, const difference &D);
	void edges();
};

void show_clique(const set<int> &clique, const list<vector<int>> &new_neutral_bits_set, list<vector<int>> &sfinal_set);

vector<int> convert_vector(const vector<unsigned> &v);