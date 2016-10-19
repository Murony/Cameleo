#include "classes.h"

vector<unsigned> xor_vec(const vector<unsigned> &a, const vector<unsigned> &b){
	vector<unsigned> c(81, 0);
	for (unsigned i = 0; i < min(a.size(), b.size()); i++){
		c[i] = a[i] ^ b[i];
	}
	return c;
}

vector<unsigned> xor_vec(const vector<unsigned> &a, const vector<unsigned> &b, const vector<unsigned> &d){
	vector<unsigned> c(81, 0);
	for (unsigned i = 0; i < min(a.size(), min(b.size(), d.size())); i++){
		c[i] = a[i] ^ b[i] ^ d[i];
	}
	return c;
}

vector<unsigned> xor_vec(const vector<unsigned> &a, const vector<unsigned> &b, const vector<unsigned> &d, const vector<unsigned> &e){
	vector<unsigned> c(81, 0);
	for (unsigned i = 0; i < min(a.size(), min(b.size(), min(d.size(), e.size()))); i++){
		c[i] = a[i] ^ b[i] ^ d[i] ^ e[i];
	}
	return c;
}

vector<unsigned> xor_vec(vector<unsigned> a, const vector<int> &vec){
	for (int i = 0; i < 5; i++){
		if (vec[i] != -1)
			a[vec[i] / 32] ^= 1 << (vec[i] % 32);
	}
	return a;
}

vector<unsigned> xor_vec(vector<unsigned> a, const vector<int> &v1, const vector<int> &v2){
	for (int i = 0; i < 5; i++){
		if (v1[i] != -1)
			a[v1[i] / 32] ^= 1 << (v1[i] % 32);
	}
	for (int i = 0; i < 5; i++){
		if (v2[i] != -1)
			a[v2[i] / 32] ^= 1 << (v2[i] % 32);
	}
	return a;
}

vector<unsigned> xor_vec(vector<unsigned> a, int b, int c, int d, int e, int f){
	if (b != -1)
		a[b / 32] ^= 1 << (b % 32);
	if (c != -1)
		a[c / 32] ^= 1 << (c % 32);
	if (d != -1)
		a[d / 32] ^= 1 << (d % 32);
	if (e != -1)
		a[e / 32] ^= 1 << (e % 32);
	if (f != -1)
		a[f / 32] ^= 1 << (f % 32);
	return a;
}

void show_number(const vector<int> &v, ofstream &fout){
	for (int i = 0; i < 5; i++){
		if (v[i] != -1){
			cout << v[i] << " ";
			fout << v[i] << " ";
		}
	}
	cout << endl;
	fout << endl;
}

vector<int> convert_vector(const vector<unsigned> &v){
	int k = 0;
	vector<int> neutral_set(5,-1);
	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 32; j++){
			if ((v[i] & (1 << j)) != 0){
				neutral_set[k]= i * 32 + j;
				k++;
			}
		}
	}
	return neutral_set;
}

void show_clique(const set<int> &clique, const list<vector<int>> &new_neutral_bits_set, list<vector<int>> &final_set){
	int w = 0;
	ofstream fout("nbits.txt");
	for (auto q = clique.begin(); q != clique.end(); q++){
		w = 0;
		for (auto t = new_neutral_bits_set.begin(); t != new_neutral_bits_set.end(); t++){
			if (w == *q){
				final_set.push_back(*t);
				show_number(*t, fout);
			}
			w++;
		}
	}
	fout.close();
}

void generate_list(list<vector<unsigned>> &neutral_bits_set, set<int> &neutral_bits){
	for (int i = 0; i < 512; i++){
		vector<unsigned> neutral_bit_vec(16, 0);
		neutral_bit_vec[i / 32] ^= 1 << (i % 32);
		neutral_bits_set.push_back(neutral_bit_vec);
		neutral_bits.insert(i);
	}
}