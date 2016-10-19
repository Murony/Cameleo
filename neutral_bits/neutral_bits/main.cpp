#include "classes.h"
#include <ctime>

void construct_neutral_set(set<int> &neutral_bits, list<vector<unsigned>>  &neutral_bits_set, list<vector<int>>  &new_neutral_bits_set, const message &M1, const message &M2, const difference &D){
	int r = 0;
	for (auto v = neutral_bits_set.begin(); v != neutral_bits_set.end();){
		const message_cupple tmp(xor_vec(*v, M1.W), xor_vec(*v, M2.W), R);
		if (D.equal(tmp, R) == R){
			new_neutral_bits_set.push_back(convert_vector(*v));
			v = neutral_bits_set.erase(v);
			neutral_bits.erase(r);
		}
		else{
			v++;
		}
		r++;
	}
	time_t seconds = time(NULL);
	//*
	message tmp_m1(M1.W);
	message tmp_m2(M1.W);
	for (auto v = neutral_bits.begin(); v != neutral_bits.end(); v++){
		for (auto q = next(v); q != neutral_bits.end(); q++){
			tmp_m1.modify(xor_vec(M1.W, *v, *q, -1, -1, -1), R);
			tmp_m2.modify(xor_vec(M2.W, *v, *q, -1, -1, -1), R);
			if (D.equal(tmp_m1, tmp_m2, R) == R){
				vector<int> init(5,-1);
				init[0] = *v;
				init[1] = *q;
				new_neutral_bits_set.push_back(init);
			}
		}
	}
	seconds = time(NULL) - seconds;
	cout << "pairs time: " << seconds << endl;
	//*/
	//*
	seconds = time(NULL);
	for (auto v = neutral_bits.begin(); v != neutral_bits.end(); v++){
		cout << time(NULL)-seconds<<" ";
		for (auto q = next(v); q != neutral_bits.end(); q++){
			for (auto w = next(q); w != neutral_bits.end(); w++){
				tmp_m1.modify(xor_vec(M1.W, *v, *q, *w, -1, -1), R);
				tmp_m2.modify(xor_vec(M2.W, *v, *q, *w, -1, -1), R);
				if (D.equal(tmp_m1, tmp_m2, R) == R){
					vector<int> init(5, -1);
					init[0] = *v;
					init[1] = *q;
					init[2] = *w;
					new_neutral_bits_set.push_back(init);
				}
			}
		}
	}//*/
}

void main(){
	time_t seconds = time(NULL);
	FILE* f;
	vector<unsigned int> dif(128, 0);
	vector<unsigned int> W1(80, 0);
	vector<unsigned int> W2(80, 0);
	fopen_s(&f, "m1_start.txt", "r");
	for (int i = 0; i < 16; i++){
		fscanf_s(f, "%x ", &W1[i]);
	}
	fclose(f);
	fopen_s(&f, "m2_start.txt", "r");
	for (int i = 0; i < 16; i++){
		fscanf_s(f, "%x ", &W2[i]);
	}
	fclose(f);

	message M1(W1);
	message M2(W2);
	difference D(M1, M2);
	//cout << dec << D.equal(M1, M2) << endl;

	list<vector<unsigned>> neutral_bits_set;
	list<vector<int>> new_neutral_bits_set;
	list<vector<int>> final_set;
	set<int> neutral_bits;

	generate_list(neutral_bits_set, neutral_bits);

	cout << dec << endl << "size " << neutral_bits_set.size() << endl;

	construct_neutral_set(neutral_bits, neutral_bits_set, new_neutral_bits_set, M1, M2, D);

	cout << dec << endl << "new size " << new_neutral_bits_set.size() << endl;

	adj_matrix adj(new_neutral_bits_set.size());
	adj.fill(new_neutral_bits_set, M1, M2, D);

	//adj.edges();

	cout << "filled" << endl;

	set<int> clique;
	kerbosh(adj.adj, adj.adj[1].size(), clique);

	cout << endl;
	for (auto q = clique.begin(); q != clique.end(); q++){ cout << *q << " "; }
	cout << endl;
	
	cout << endl <<"clique size "<<clique.size()<<endl;

	show_clique(clique, new_neutral_bits_set, final_set);

	seconds = time(NULL) - seconds;
	cout <<"time: "<< seconds;
	getchar();
};
