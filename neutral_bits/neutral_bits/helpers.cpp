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

/*vector<unsigned> xor_vec(vector<unsigned> a, const vector<int> &vec){
	for (int i = 0; i < 5; i++){
		if (vec[i] != -1)
			a[vec[i] / 32] ^= 1 << (vec[i] % 32);
	}
	return a;
}*/

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
		fout << v[i] << " ";
	}
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

int global_count = 0;

void show_clique(const set<int> &clique, const vector<vector<int>> &new_neutral_bits_set, vector<vector<int>> &final_set){
	int w = 0;
	char str[20];
	_snprintf_s(str, 20, 20, "w_clique_%d_%d.txt", clique.size(), global_count);
	ofstream fout(str);
	for (auto q = clique.begin(); q != clique.end(); q++){
		w = 0;
		for (auto t = new_neutral_bits_set.begin(); t != new_neutral_bits_set.end(); t++){
			if (w == *q){
				//final_set.push_back(*t);
				show_number(*t, fout);
			}
			w++;
		}
	}
	fout.close();
}

void print_results(const message &m1, const message &m2, const message &start_m1, const message &start_m2, int r){
	ofstream fout("results.txt");
	cout << endl << endl << "First found message:" << endl << endl;
	fout << endl << endl << "First found message:" << endl << endl;
	for (int i = 0; i < 16; i++){
		cout << hex << m1.W[i] << " ";
		fout << hex << m1.W[i] << " ";
	}
	cout << endl << endl << "Second found message:" << endl << endl;
	fout << endl << endl << "Second found message:" << endl << endl;
	for (int i = 0; i < 16; i++){
		cout << hex << m2.W[i] << " ";
		fout << hex << m2.W[i] << " ";
	}
	cout << endl << endl << "Mask:" << endl << endl;
	fout << endl << endl << "Mask:" << endl << endl;
	for (int i = 0; i < 16; i++){
		cout << hex << (m1.W[i] ^ start_m1.W[i]) << " ";
		fout << hex << (m1.W[i] ^ start_m1.W[i]) << " ";
	}
	cout << endl << endl << dec << "Difference " << r << " steps:" << endl << endl;
	fout << endl << endl << dec << "Difference " << r << " steps:" << endl << endl;
	for (int i = 0; i <= r; i++){
		cout << hex << (m1.a[i] ^ m2.a[i]) << " ";
		fout << hex << (m1.a[i] ^ m2.a[i]) << " ";
	}
	cout << endl << endl;
	fout << endl << endl;
	fout.close();
}

void print_results_full(const message &m1, const message &m2, const message &start_m1, const message &start_m2){
	ofstream fout("results.txt");
	for (int i = 0; i < 80; i++){
		fout <<dec<< "t=" << i << " & " << hex << m1.W[i] << " & " << m2.W[i] << " & " << (m1.a[i+1] ^ m2.a[i+1]) << " \\\\ \\hline" <<endl;
	}
	fout.close();
}


bool not_intersect(vector<int> a, vector<int> b){
	for (auto i : a){
		for (auto j : b){
			if ((i == j) && (i != -1) && (j != -1)){
				return 0;
			}
		}
	}
	return 1;
}