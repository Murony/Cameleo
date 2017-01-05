#include "set_constructor.h"

void brute_force(const vector<vector<int>> &final_set, const message &M1, const message &M2, const difference &D){
	ofstream found_i("found_i.txt");
	
	map<unsigned, unsigned> power;
	for (int i = 0; i < 40; i++)
		power[pow(2, i)] = i;

	long long min_power = pow(2, 0); //52833389152; //pow(2, 27); //24832
	long long max_power = pow(2, 22); //52833389152 + 1; //pow(2, 36);
	
	message tmp1[16];
	message tmp2[16];

	int parity[16][512];
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 512; j++)
			parity[i][j] = 0;
	
	for (int i = 0; i < 16; i++){
		tmp1[i] = message(M1.W);
		tmp2[i] = message(M2.W);
	}
	
	omp_set_num_threads(16);
	#pragma omp parallel for
	for (long long i = min_power; i < max_power; i++){
		tmp1[omp_get_thread_num()].W = M1.W;
		tmp2[omp_get_thread_num()].W = M2.W;
		int k = 0;
		for (long long j = 1; j <= i; j *= 2){
			if ((i&j) != 0){
				//cout << k << " ";
				//cout << dec << i << " " << j << " " << (i&j) << endl;
				xor(tmp1[omp_get_thread_num()].W, final_set[k]);
				xor(tmp2[omp_get_thread_num()].W, final_set[k]);
				//cout << final_set[k][0] << " " << final_set[k][1] << " " << final_set[k][2] << " " << final_set[k][3] << endl;
				for (int q = 0; q < 4; q++){
					if (final_set[k][q]!=-1)
						parity[omp_get_thread_num()][final_set[k][q]] ^= 1;
				}
			}
			k++;
		}
		bool trivial = 1;
		for (int q = 0; q < 512; q++){
			if (parity[omp_get_thread_num()][q] != 0){
				trivial = 0;
				parity[omp_get_thread_num()][q] = 0;
			}
		}
		if (!trivial){
			if (D.modify(tmp1[omp_get_thread_num()], tmp2[omp_get_thread_num()]) >= 50){
				#pragma omp critical
				{
					cout << "i=" << dec << i << " " << D.equal(tmp1[omp_get_thread_num()], tmp2[omp_get_thread_num()], 80) << endl; //<< " " << tmp1[omp_get_thread_num()].a[49]  
					found_i << "i=" << dec << i << " " << D.equal(tmp1[omp_get_thread_num()], tmp2[omp_get_thread_num()], 80) << endl;
				}
			//print_results(tmp1[omp_get_thread_num()], tmp2[omp_get_thread_num()], M1, M2, 65);
			//D.print(80);
			//D.print(tmp1[omp_get_thread_num()], M1, 16);
			}
		}
		//else{
		//	cout << "trivial" << endl;
		//}
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

	fopen_s(&f, "m1_16.txt", "r");
	//fopen_s(&f, "m1_second.txt", "r");
	//fopen_s(&f, "m1_start.txt", "r");
	for (int i = 0; i < 16; i++){
		fscanf_s(f, "%x ", &W1[i]);
	}
	fclose(f);
	fopen_s(&f, "m2_16.txt", "r");
	//fopen_s(&f, "m2_second.txt", "r");
	//fopen_s(&f, "m2_start.txt", "r");
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

	int just_read_from_file = 0;
	if (just_read_from_file){
		//final_set = vector<vector<int>>(40, { -1, -1, -1, -1, -1 });
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



