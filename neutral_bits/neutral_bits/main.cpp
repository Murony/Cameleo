#include "set_constructor.h"

void brute_force(const vector<vector<int>> &final_set, const message &M1, const message &M2, const difference &D){
	ofstream found_i("found_i.txt");
	
	map<unsigned, unsigned> power;
	for (int i = 0; i < 40; i++)
		power[pow(2, i)] = i;

	int min_power = pow(2, 27);
	int max_power = pow(2, 28);
	
	message tmp1[16];
	message tmp2[16];
	
	for (int i = 0; i < 16; i++){
		tmp1[i] = message(M1.W);
		tmp2[i] = message(M2.W);
	}
	
	omp_set_num_threads(16);
	#pragma omp parallel for
	for (int i = min_power; i < max_power; i++){
		tmp1[omp_get_thread_num()].W = M1.W;
		tmp2[omp_get_thread_num()].W = M2.W;
		int k = 0;
		for (int j = 1; j <= i; j *= 2){
			if ((i&j) != 0){
				//cout << dec << i << " " << j << " " << (i&j) << endl;
				xor(tmp1[omp_get_thread_num()].W, final_set[k]);
				xor(tmp2[omp_get_thread_num()].W, final_set[k]);
			}
			k++;
		}
		if (D.modify(tmp1[omp_get_thread_num()], tmp2[omp_get_thread_num()]) > 55){
			cout << "i=" << dec << i << " " << D.equal(tmp1[omp_get_thread_num()], tmp2[omp_get_thread_num()], 80) << endl; //<< " " << tmp1[omp_get_thread_num()].a[49]  
			found_i << "i=" << dec << i << " " << D.equal(tmp1[omp_get_thread_num()], tmp2[omp_get_thread_num()], 80) << endl;
			//D.print(35);
			//D.print(tmp_m1, tmp_m2, 35);
		}
	}
	cout << endl << "Brute Force done: ";
	found_i.close();
}

void main(){
	time_t seconds = time(NULL);
	time_t all = time(NULL);
	FILE* f;
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


	/*message tmp_m1(M1.W);
	message tmp_m2(M2.W);
	tmp_m1.modify(xor_vec(M1.W, 456, 493, -1, -1, -1), R);
	tmp_m2.modify(xor_vec(M2.W, 456, 493, -1, -1, -1), R);
	D.print(tmp_m1, tmp_m2, R);
	cout << dec << D.equal(tmp_m1, tmp_m2, R);*/

	/*
	vector<int> v1 = { 456, 493, -1, -1, -1 };
	vector<int> v2 = { 388, -1, -1, -1, -1 };
	vector<int> v3 = { -1, -1, -1, -1, -1 };
	D.print(M1, M2, R);
	//D.print(message(xor_vec(M1.W, v1, v2)), message(xor_vec(M2.W,v1,v2)), R);
	//D.print(message(xor_vec(M1.W, v1, v3)), message(xor_vec(M2.W, v1, v3)), R);
	getchar();
	return;//*/

	vector<vector<int>> final_set;

	int just_read_from_file = 1;
	if (just_read_from_file){
		final_set = vector<vector<int>>(40, { -1, -1, -1, -1, -1 });
		read_clique(final_set);
		cout << "final set size:" << final_set.size() << endl;

		seconds = time(NULL);
		brute_force(final_set, M1, M2, D);
		cout << dec << time(NULL) - seconds << endl;
	}
	else{
		constructor(M1,M2,D);
	}

	getchar();
};



