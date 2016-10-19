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

vector<unsigned> xor_vec(vector<unsigned> a, vector<unsigned> b);

vector<unsigned> xor_vec(vector<unsigned> a, vector<unsigned> b, vector<unsigned> d);

vector<unsigned> xor_vec(vector<unsigned> a, int b, int c, int d, int e, int f);

vector<unsigned> xor_vec(vector<unsigned> a, vector<int> vec);

vector<unsigned> xor_vec(vector<unsigned> a, vector<int> v1, vector<int> v2);

void show_number(vector<unsigned> v);

class message{
	vector<unsigned int> b;
	vector<unsigned int> c;
	vector<unsigned int> d;
	vector<unsigned int> e;
public:
	vector<unsigned int> W;
	vector<unsigned int> a;
	message(vector<unsigned> in);
	message(vector<unsigned> in, int max_round);
	message(){}
};

struct message_cupple{
	message m1;
	message m2;
public:
	message_cupple(vector<unsigned> In1, vector<unsigned> In2, int r){
		m1 = message(In1, r);
		m2 = message(In2, r);
	}
	message_cupple(){}
};

class difference{
public:
	vector<unsigned> dif;
	difference(message m1, message m2);
	int equal(const message m1, const message m2, int r)const;
	int equal(const message_cupple cup, int r)const;
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
	void fill(list<vector<int>> new_neutral_bits_set, message M1, message M2, difference D);
	void show(list<vector<int>> new_neutral_bits_set, message M1, message M2, difference D);
	void edges();
};

void show_clique(const set<int> clique, const list<vector<int>> new_neutral_bits_set, list<vector<int>> final_set);

vector<int> convert_vector(const vector<unsigned> &v);


//void rec_kerbosch(set<int> M, G, K, P){}

/*list<set<int>> kerbosh(vector<vector<int>> &a, int SIZE)
{
set <int> M, G, K, P;
list<set<int> > REZULT;
for (int i = 0; i<SIZE; i++)
{
K.insert(i);
}
int v, Count = 0, cnt = 0;
int Stack1[10000];
set<int> Stack2[10000];
set<int>::iterator theIterator;
theIterator = K.begin();
while (((K.size() != 0) || (M.size() != 0)) && REZULT.size()<3)
{
//cout << Count << " ";
if (K.size() != 0)
{
theIterator = K.begin();
v = *theIterator;
Stack2[++Count] = M;
Stack2[++Count] = K;
Stack2[++Count] = P;
Stack1[++cnt] = v;
M.insert(v);
for (int i = 0; i<SIZE; i++)
{
if (!a[v][i])
{
theIterator = K.find(i);
if (theIterator != K.end())
{
K.erase(theIterator);
}
theIterator = P.find(i);
if (theIterator != P.end())
{
P.erase(theIterator);
}
}
}
theIterator = K.find(v);
if (theIterator != K.end())
{
K.erase(theIterator);
}
}
else
{
if (P.size() == 0)
{
REZULT.push_back(M);
cout << M.size() <<" ";
}
v = Stack1[cnt--];
P = Stack2[Count--];
K = Stack2[Count--];
M = Stack2[Count--];
theIterator = K.find(v);
if (theIterator != K.end())
{
K.erase(theIterator);
}
P.insert(v);
}
}
set<int> REZ = *REZULT.begin();
int k = REZULT.begin()->size();
for (auto it = REZULT.begin(); it != REZULT.end(); it++){
if (it->size() >= k)
REZ = *it;
}
return REZULT;
}*/

/*for (int i = 0; i < 512; i++){
for (int j = i + 1; j < 512; j++){
vector<unsigned> neutral_bit_vec(16, 0);
neutral_bit_vec[i / 32] ^= 1 << (i % 32);
neutral_bit_vec[j / 32] ^= 1 << (j % 32);
neutral_bits_set.push_back(neutral_bit_vec);
}
}
for (int i = 0; i < 512; i++){
for (int j = i + 1; j < 512; j++){
for (int k = j + 1; k < 512; k++){
vector<unsigned> neutral_bit_vec(16, 0);
neutral_bit_vec[i / 32] ^= 1 << (i % 32);
neutral_bit_vec[j / 32] ^= 1 << (j % 32);
neutral_bit_vec[k / 32] ^= 1 << (k % 32);
neutral_bits_set.push_back(neutral_bit_vec);
}
}
}
for (int i = 0; i < 512; i++){
for (int j = i + 1; j < 512; j++){
for (int k = j + 1; k < 512; k++){
for (int w = k + 1; w < 512; w++){
vector<unsigned> neutral_bit_vec(16, 0);
neutral_bit_vec[i / 32] ^= 1 << (i % 32);
neutral_bit_vec[j / 32] ^= 1 << (j % 32);
neutral_bit_vec[k / 32] ^= 1 << (k % 32);
neutral_bit_vec[w / 32] ^= 1 << (w % 32);
neutral_bits_set.push_back(neutral_bit_vec);
}
}
}
}*/
