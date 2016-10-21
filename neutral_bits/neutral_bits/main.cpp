#include "classes.h"
#include <omp.h>
#include <ctime>

void construct_neutral_set(set<int> &neutral_bits, list<vector<unsigned>>  &neutral_bits_set, list<vector<int>>  &new_neutral_bits_set, const message &M1, const message &M2, const difference &D){
	int r = 0;
	set<int> bad_set;
	for (auto v = neutral_bits_set.begin(); v != neutral_bits_set.end();){
		const message_cupple tmp(xor_vec(*v, M1.W), xor_vec(*v, M2.W), R);
		if (D.equal(tmp, R) == R){
			new_neutral_bits_set.push_back(convert_vector(*v));
			v = neutral_bits_set.erase(v);
			neutral_bits.erase(r);
			bad_set.insert(r);
		}
		else{
			v++;
		}
		r++;
	}
	time_t seconds = time(NULL);

	//message tmp_m1(M1.W);
	//message tmp_m2(M1.W);

	omp_set_num_threads(16);

	//*
	#pragma omp parallel for
	for (int v = 0; v < neutral_bits.size(); v++){
		message tmp_m1(M1.W);
		message tmp_m2(M1.W);
		if (bad_set.find(v) == bad_set.end()){
			for (int q = v + 1; q != neutral_bits.size(); q++){
				if (bad_set.find(q) == bad_set.end()){
					tmp_m1.modify(xor_vec(M1.W, v, q, -1, -1, -1), R);
					tmp_m2.modify(xor_vec(M2.W, v, q, -1, -1, -1), R);
					if (D.equal(tmp_m1, tmp_m2, R) == R){
						vector<int> init(5, -1);
						init[0] = v;
						init[1] = q;
						#pragma omp critical
						{
						new_neutral_bits_set.push_back(init);
						}
					}
				}

			}
		}
	}
	//*/

	cout << "pairs time: " << time(NULL)-seconds << endl;
	seconds = time(NULL);

	/*
	#pragma omp parallel for
	for (int v = 100; v < neutral_bits.size(); v++){
		message tmp_m1(M1.W);
		message tmp_m2(M1.W);
		time_t t = time(NULL);
		if (bad_set.find(v) == bad_set.end()){
			for (int q = v + 1; q != neutral_bits.size(); q++){
				if (bad_set.find(q) == bad_set.end()){
					for (int w = q + 1; w != neutral_bits.size(); w++){
						if (bad_set.find(w) == bad_set.end()){
							tmp_m1.modify(xor_vec(M1.W, v, q, w, -1, -1), R);
							tmp_m2.modify(xor_vec(M2.W, v, q, w, -1, -1), R);
							if (D.equal(tmp_m1, tmp_m2, R) == R){
								vector<int> init(5, -1);
								init[0] = v;
								init[1] = q;
								init[2] = w;
								#pragma omp critical
								{
									new_neutral_bits_set.push_back(init);
								}
							}
						}
					}
				}
			}
		}
		cout << time(NULL) - t<<" ";
	}
	//*/
	cout << "triplets time: " << time(NULL) - seconds << endl;
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
	
	/*
	vector<int> v1 = { 425, 426, -1, -1, -1 };
	vector<int> v2 = { 388, -1, -1, -1, -1 };
	vector<int> v3 = { -1, -1, -1, -1, -1 };
	D.print(M1.W, M2.W, R);
	D.print(message(xor_vec(M1.W, v1, v2)), message(xor_vec(M2.W,v1,v2)), R);
	D.print(message(xor_vec(M1.W, v1, v3)), message(xor_vec(M2.W, v1, v3)), R);
	getchar();
	return;//*/

	list<vector<unsigned>> neutral_bits_set;
	list<vector<int>> new_neutral_bits_set;
	list<vector<int>> final_set;
	set<int> neutral_bits;

	generate_list(neutral_bits_set, neutral_bits);

	cout << dec << endl << "size " << neutral_bits_set.size() << endl;

	construct_neutral_set(neutral_bits, neutral_bits_set, new_neutral_bits_set, M1, M2, D);

	cout << dec << endl << "new size " << new_neutral_bits_set.size() << endl;

	seconds = time(NULL);

	adj_matrix adj(new_neutral_bits_set.size());
	adj.fill(new_neutral_bits_set, M1, M2, D);

	//adj.edges();

	cout << "filled: " << time(NULL)- seconds << endl;
	seconds = time(NULL);

	set<int> clique;
	kerbosh(adj.adj, adj.adj[1].size(), clique);

	cout << "kerbosh complited: " << time(NULL) - seconds << endl;
	seconds = time(NULL);

	cout << endl;
	for (auto q = clique.begin(); q != clique.end(); q++){ cout << *q << " "; }
	cout << endl;
	
	cout << endl <<"clique size "<<clique.size()<<endl;

	show_clique(clique, new_neutral_bits_set, final_set);

	seconds = time(NULL) - seconds;
	cout <<"time: "<< seconds;
	getchar();
};


/*
	/*
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
	/*
	r=0;
	seconds = time(NULL);
	for (auto v = neutral_bits.begin(); v != neutral_bits.end(); v++){
		cout << (time(NULL) - seconds)/60;
		cout <<"r"<< r++ << " ";
		for (auto q = next(v); q != neutral_bits.end(); q++){
			for (auto w = next(q); w != neutral_bits.end(); w++){
				for (auto g = next(w); g != neutral_bits.end(); g++){
					tmp_m1.modify(xor_vec(M1.W, *v, *q, *w, *g, -1), R);
					tmp_m2.modify(xor_vec(M2.W, *v, *q, *w, *g, -1), R);
					if (D.equal(tmp_m1, tmp_m2, R) == R){
						vector<int> init(5, -1);
						init[0] = *v;
						init[1] = *q;
						init[2] = *w;
						init[3] = *g;
						new_neutral_bits_set.push_back(init);
					}
				}
			}
		}
	}//*/