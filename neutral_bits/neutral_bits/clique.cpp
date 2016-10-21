#include "classes.h"

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
			return 0;
		}
	}
	return 1;
}

void extend(vector<vector<int>> &a, list<set<int>> &REZULT, set <int> candidates, set <int> not, set <int> M){
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
			if (REZULT.size()%100==0)
				cout << M.size() << " ";
			if (M.size()>20)
				cout <<"here m size->"<< M.size() << " ";
		}
		else{
			if (REZULT.size() < 10000000){
				extend(a, REZULT, K, P, M);
			}
			else{
				//cout << "stop ";
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
	}
}

void kerbosh(vector<vector<int>> &a, int SIZE, set<int> &clique)
{
	set <int> M, K, P;
	list<set<int> > REZULT;
	for (int i = 0; i < SIZE; i++)
	{
		K.insert(i);
	}
	extend(a, REZULT, K, P, M);
	set<int> REZ = *REZULT.begin();
	unsigned k = REZULT.begin()->size();
	for (auto it = REZULT.begin(); it != REZULT.end(); it++){
		if (it->size() > k){
			REZ = *it;
			k = it->size();
		}
	}
	clique = REZ;
	return;
}

void adj_matrix::fill(const list<vector<int>> &new_neutral_bits_set, const message &M1, const message &M2, const difference &D){
	int z = 0, x = 0;
	message tmp_m1(M1.W);
	message tmp_m2(M1.W);
	for (auto it = new_neutral_bits_set.begin(); it != new_neutral_bits_set.end(); it++) {
		x = 0;
		for (auto q = new_neutral_bits_set.begin(); q != new_neutral_bits_set.end(); q++) {
			tmp_m1.modify(xor_vec(M1.W, *it, *q), R);
			tmp_m2.modify(xor_vec(M2.W, *it, *q), R);
			if (D.equal(tmp_m1, tmp_m2, R) == R){
				adj[z][x] = 1;
			}
			x++;
		}
		z++;
		if ((z + 1) % 100 == 0)
			cout << z << " ";
	}
}

void adj_matrix::edges(){
	for (unsigned i = 0; i < adj[1].size(); i++){
		for (unsigned j = 0; j < adj[1].size(); j++){
			if (adj[i][j] != 0){
				cout << i << " " << j << endl;
			}
		}
	}
	cout << endl;
}

void adj_matrix::show(const list<vector<int>> &new_neutral_bits_set, const message &M1, const message &M2, const difference &D){
	int z = 0, x = 0;
	for (auto it = new_neutral_bits_set.begin(); it != new_neutral_bits_set.end(); it++) {
		x = 0;
		for (auto q = new_neutral_bits_set.begin(); q != new_neutral_bits_set.end(); q++) {
			const message_cupple tmp(xor_vec(M1.W, *it, *q), xor_vec(M2.W, *it, *q), R);
			if (D.equal(tmp, R) == R){
				adj[z][x] = 1;
			}
			cout << adj[z][x] << " ";
			x++;
		}
		cout << endl;
		z++;
	}
}