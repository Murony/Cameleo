#include "graph.h"

#define MASK 0xffffffff
#define R 22

using namespace std;

unsigned round_function(unsigned b, unsigned c, unsigned d, int round){
	if (round < 20) {
		return (b & c) | (~b & d);
	}
	else if (round >= 20 && round < 40) {
		return b ^ c ^ d;
	}
	else if (round >= 40 && round < 60) {
		return (b & c) | (b & d) | (c & d);
	}
	else {
		return b ^ c ^ d;
	}
}

unsigned key(int round){
	if (round < 20) {
		return 0x5A827999;
	}
	else if (round >= 20 && round < 40) {
		return 0x6ED9EBA1;
	}
	else if (round >= 40 && round < 60) {
		return 0x8F1BBCDC;
	}
	else {
		return 0xCA62C1D6;
	}
}

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
	//int equal(message m);
};

message::message(vector<unsigned> In){
	W = vector<unsigned>(80, 0);
	a = vector<unsigned>(81, 0);
	b = vector<unsigned>(81, 0);
	c = vector<unsigned>(81, 0);
	d = vector<unsigned>(81, 0);
	e = vector<unsigned>(81, 0);
	a[0] = 0x67452301;
	b[0] = 0xEFCDAB89;
	c[0] = 0x98BADCFE;
	d[0] = 0x10325476;
	e[0] = 0xC3D2E1F0;
	W = In;
	for (int i = 16; i<80; i++){
		W[i] = (W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16]);
		//W[i] = ((W[i] << 1) | (W[i] >> (32 - 1)));
	}
	for (int i = 0; i < 80; i++){
		unsigned f = round_function(b[i], c[i], d[i], i);
		a[i + 1] = (e[i] + ((a[i] << 5) | (a[i] >> (32 - 5))) + f + W[i] + key(i))&MASK;
		b[i + 1] = a[i];
		c[i + 1] = ((b[i] << 30) | (b[i] >> 2))&MASK;
		d[i + 1] = c[i];
		e[i + 1] = d[i];
	}
}

message::message(vector<unsigned> In, int max_round){
	W = vector<unsigned>(80, 0);
	a = vector<unsigned>(81, 0);
	b = vector<unsigned>(81, 0);
	c = vector<unsigned>(81, 0);
	d = vector<unsigned>(81, 0);
	e = vector<unsigned>(81, 0);
	a[0] = 0x67452301;
	b[0] = 0xEFCDAB89;
	c[0] = 0x98BADCFE;
	d[0] = 0x10325476;
	e[0] = 0xC3D2E1F0;
	W = In;
	for (int i = 16; i<max_round; i++){
		W[i] = (W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16]);
		//W[i] = ((W[i] << 1) | (W[i] >> (32 - 1)));
	}
	for (int i = 0; i < max_round; i++){
		unsigned f = round_function(b[i], c[i], d[i], i);
		a[i + 1] = (e[i] + ((a[i] << 5) | (a[i] >> (32 - 5))) + f + W[i] + key(i))&MASK;
		b[i + 1] = a[i];
		c[i + 1] = ((b[i] << 30) | (b[i] >> 2))&MASK;
		d[i + 1] = c[i];
		e[i + 1] = d[i];
	}
}

struct message_cupple{
	message m1;
	message m2;
public:
	message_cupple(vector<unsigned> In1, vector<unsigned> In2, int r){
		m1 = message(In1,r);
		m2 = message(In2,r);
	}
	message_cupple(){}
};

class difference{
public:
	vector<unsigned> dif;
	difference(message m1, message m2){
		dif = vector<unsigned>(81, 0);
		for (int i = 0; i <= 80; i++){
			dif[i] = m1.a[i] ^ m2.a[i];
			//cout << hex << dif[i] << " ";
		}
		//cout << endl;
	}
	int equal(const message m1, const message m2, int r)const;
	int equal(const message_cupple cup, int r)const;
};

int difference::equal(const message m1, const message m2, int r)const{
	for (int i = 0; i <= r; i++){
		if ((m1.a[i] ^ m2.a[i]) != dif[i])
			return i;
	}
	return r;
}

int difference::equal(const message_cupple cup, int r)const{
	return equal(cup.m1, cup.m2,r);
}

vector<unsigned> xor_vec(vector<unsigned> a, vector<unsigned> b){
	vector<unsigned> c(81, 0);
	for (unsigned i = 0; i < min(a.size(), b.size()); i++){
		c[i] = a[i] ^ b[i];
	}
	return c;
}

vector<unsigned> xor_vec(vector<unsigned> a, vector<unsigned> b, vector<unsigned> d){
	vector<unsigned> c(81, 0);
	for (unsigned i = 0; i < min(a.size(), min(b.size(), d.size())); i++){
		c[i] = a[i] ^ b[i] ^ d[i];
	}
	return c;
}

void show_number(vector<unsigned> v){
	int k = 0;
	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 32; j++){
			if ((v[i] & (1 << j)) != 0)
				cout << dec << k << " ";
			k++;
		}
	}
	cout << endl;
}

void generste_list(list<vector<unsigned>> &neutral_bits_set){
	for (int i = 0; i < 512;  i++){
		vector<unsigned> neutral_bit_vec(16, 0);
		neutral_bit_vec[i / 32] ^= 1 << (i % 32);
		neutral_bits_set.push_back(neutral_bit_vec);
		//for (int j = i + 1; j < i+2; j++){
			//vector<unsigned> neutral_bit_vec(16, 0);
			//neutral_bit_vec[i / 32] ^= 1 << (i % 32);
			//neutral_bit_vec[j / 32] ^= 1 << (j % 32);
			//neutral_bits_set.push_back(neutral_bit_vec);
			//cout << i%32 << " " << j%32 << endl;
			/*for (int k = j + 1; k < 512; k++){
			neutral_bit_vec[k / 32] ^= 1 << (k % 32);
			neutral_bits_set.push_back(neutral_bit_vec);
			for (int w = k + 1; w < 512; w++){
			neutral_bit_vec[w / 32] ^= 1 << (w % 32);
			neutral_bits_set.push_back(neutral_bit_vec);
			}
			}*/
		//}
	}
	for (int i = 0; i < 512; i++){
		for (int j = i + 1; j < 512; j++){
			vector<unsigned> neutral_bit_vec(16, 0);
			neutral_bit_vec[i / 32] ^= 1 << (i % 32);
			neutral_bit_vec[j / 32] ^= 1 << (j % 32);
			neutral_bits_set.push_back(neutral_bit_vec);
		}
	}
}

class adj_matrix{
public:
	vector<vector<int>> adj;
	adj_matrix(int size){
		adj.resize(size);
		for (unsigned i = 0; i < adj.size(); i++){
			adj[i] = vector<int>(size, 0);
		}
	}
	void fill(list<vector<unsigned>> new_neutral_bits_set, message M1, message M2, difference D){
		int z = 0, x = 0;
		for (auto it = new_neutral_bits_set.begin(); it != new_neutral_bits_set.end(); it++) {
			//if (z % 100 == 0)
				//cout << z <<" "<<x<<endl;
			x = 0;
			for (auto q = new_neutral_bits_set.begin(); q != new_neutral_bits_set.end(); q++) {
				const message_cupple tmp(xor_vec(*it, *q, M1.W), xor_vec(*it, *q, M2.W), R);
				if (D.equal(tmp, R) == R){
					adj[z][x] = 1;
				}
				x++;
			}
			z++;
		}
	}
	void edges(Graph &g){
		for (unsigned i = 0; i < adj[1].size(); i++){
			g.addNode(i);
		}
		for (unsigned i = 0; i < adj[1].size(); i++){
			for (unsigned j = i+1; j < adj[1].size(); j++){
				if (adj[i][j] != 0){
					g.addEdge(i, j);
					cout << i << " " << j << endl;
				}
			}
		}
		cout << endl;
	}
};


int check(vector<vector<int>> &a, set <int> &K, set <int> &P){
	if (P.size() == 0)
		return 1;
	bool connected;
	for (auto v = P.begin(); v != P.end(); v++) {
		connected = true;
		for (auto i = K.begin(); i != K.end(); i++)
			if (!a[*v][*i])
				connected = false;
		if (connected){
			//cout << "check failed";
			return 0;
		}
	}
	return 1;
}

void extend(vector<vector<int>> &a, list<set<int>> &REZULT, set <int> candidates, set <int> not, set <int> M){
	//cout << "!";
	//set <int> M;
	set <int> K, P;
	int v, SIZE = a[1].size();
	auto theIterator = candidates.begin();
	while ((candidates.size() != 0) && check(a, candidates, not)){
		K.clear();
		P.clear();
		for (auto it = not.begin(); it != not.end(); it++) { P.insert(*it); }
		for (auto it = candidates.begin(); it != candidates.end(); it++) { K.insert(*it); }
		v = *candidates.begin();
		M.insert(v);
		for (int i = 0; i < SIZE; i++)
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
		if ((P.size() == 0) && (K.size() == 0))
		{
			REZULT.push_back(M);
			cout << M.size() << " ";
		}
		else{
			/*cout << "K ";
			for (auto it = K.begin(); it != K.end(); it++) { cout << *it << " "; }
			cout << endl << "M ";
			for (auto it = M.begin(); it != M.end(); it++) { cout << *it << " "; }
			cout << endl << "P ";
			for (auto it = P.begin(); it != P.end(); it++) { cout << *it << " "; }*/
			if (REZULT.size() < 100){
				extend(a, REZULT, K, P, M);
			}
			else{
				cout << "stop ";
				break;
			}
		}
		theIterator = candidates.find(v);
		if (theIterator != candidates.end())
		{
			candidates.erase(theIterator);
		}
		theIterator = M.find(v);
		if (theIterator != M.end())
		{
			M.erase(theIterator);
		}
		not.insert(v);
		
		/*cout << "v " << v  << endl;
		cout << endl << "candidates ";
		for (auto it = candidates.begin(); it != candidates.end(); it++) { cout << *it << " "; }
		cout << endl << "not ";
		for (auto it = not.begin(); it != not.end(); it++) { cout << *it << " "; }
		cout << endl;*/
	}
}

list<set<int>> kerbosh(vector<vector<int>> &a, int SIZE)
{
	set <int> M, K, P;
	list<set<int> > REZULT;
	for (int i = 0; i < SIZE; i++)
	{
		K.insert(i);
	}
	extend(a, REZULT, K, P, M);
	set<int> REZ = *REZULT.begin();
	int k = REZULT.begin()->size();
	for (auto it = REZULT.begin(); it != REZULT.end(); it++){
		if (it->size() >= k)
			REZ = *it;
	}
	cout << endl << "kerbosh completed" << endl;
	return REZULT;
}





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