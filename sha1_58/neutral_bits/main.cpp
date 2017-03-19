#include "set_constructor.h"

void brute_force(const vector<vector<int>> &final_set, const message &M1, const message &M2, const difference &D, const DifferentialPath &P){
	ofstream found_i("found_i.txt");
	
	map<unsigned, unsigned> power;
	for (int i = 0; i < 40; i++)
		power[pow(2, i)] = i;

	long long min_power = 732055732;// pow(2, 28);		//	121164		169436		20930652
	long long max_power = 732055732 + 1;// pow(2, 33);
	
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
	
	omp_set_num_threads(7);
	#pragma omp parallel for
	for (long long i = min_power; i < max_power; i++){
		tmp1[omp_get_thread_num()] = M1;
		tmp2[omp_get_thread_num()] = M2;
		int k = 0;
		for (long long j = 1; j <= i; j *= 2){
			if ((i&j) != 0){
				xor(tmp1[omp_get_thread_num()].W, final_set[k]);
				xor(tmp2[omp_get_thread_num()].W, final_set[k]);
			}
			k++;
		}
		//D.modify(tmp1[omp_get_thread_num()], tmp2[omp_get_thread_num()]);
		tmp1[omp_get_thread_num()].modify(tmp1[omp_get_thread_num()].W,64);
		tmp2[omp_get_thread_num()].modify(tmp2[omp_get_thread_num()].W,64);
		if (P.check(tmp1[omp_get_thread_num()], tmp2[omp_get_thread_num()]) >= 60){
				#pragma omp critical
				{
					cout << "i=" << dec << i << " " << P.check(tmp1[omp_get_thread_num()], tmp2[omp_get_thread_num()]) << endl;
					found_i << "i=" << dec << i << " " << P.check(tmp1[omp_get_thread_num()], tmp2[omp_get_thread_num()]) << endl;
				}
			//print_results(tmp1[omp_get_thread_num()], tmp2[omp_get_thread_num()], M1, M2, 64);
			//print_results_full(tmp1[omp_get_thread_num()], tmp2[omp_get_thread_num()], M1, M2);
			//print_results_two_blocks(M1, M2, 64);
			//D.print(80);
			//D.print(tmp1[omp_get_thread_num()], M1, 16);

			//print_results(tmp1[omp_get_thread_num()], tmp2[omp_get_thread_num()], M1, M2, 35);

			/*cout << (M1.a[0] + M1.a[40]) << " " << (M2.a[0] + M2.a[40]) << endl;
			cout << (M1.b[0] + M1.b[40]) << " " << (M2.b[0] + M2.b[40]) << endl;
			cout << (M1.c[0] + M1.c[40]) << " " << (M2.c[0] + M2.c[40]) << endl;
			cout << (M1.d[0] + M1.d[40]) << " " << (M2.d[0] + M2.d[40]) << endl;
			cout << (M1.e[0] + M1.e[40]) << " " << (M2.e[0] + M2.e[40]) << endl;*/
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

	fopen_s(&f, "m1_64_first.txt", "r");
	for (int i = 0; i < 16; i++){
		fscanf_s(f, "%x ", &W1[i]);
	}
	fclose(f);
	fopen_s(&f, "m2_64_first.txt", "r");
	for (int i = 0; i < 16; i++){
		fscanf_s(f, "%x ", &W2[i]);
	}
	fclose(f);

	message M1(W1);
	message M2(W2);
	difference D(M1, M2);

	D.print(M1, M2, 64);

	fopen_s(&f, "m1_64_second.txt", "r");
	for (int i = 0; i < 16; i++){
		fscanf_s(f, "%x ", &W1[i]);
	}
	fclose(f);
	fopen_s(&f, "m2_64_second.txt", "r");
	for (int i = 0; i < 16; i++){
		fscanf_s(f, "%x ", &W2[i]);
	}
	fclose(f);

	unsigned last_m1 = M1.a[63];
	unsigned last_m2 = M2.a[63];

	M1.SetIV(64);
	M1.modify(W1, 64);

	M2.SetIV(64);
	M2.modify(W2, 64);

	D.print(M1, M2, 64);

	cout << endl << last_m1 + M1.a[63] << endl;
	cout << endl << last_m2 + M2.a[63] << endl;


	DifferentialPath P;
	cout << endl << dec << P.check(M1, M2) << endl;

	//M1.modify(xor_vec(M1.W, 393, 423, 463, -1, -1), 64);
	//M2.modify(xor_vec(M2.W, 393, 423, 463, -1, -1), 64);

	//M1.modify(xor_vec(M1.W, 393, 392, 457, 425, -1), 64);
	//M2.modify(xor_vec(M2.W, 393, 392, 457, 425, -1), 64);

	//456
	
	//M1.modify(xor_vec(M1.W, 452, 458, 494, -1, -1), 64);
	//M2.modify(xor_vec(M2.W, 452, 458, 494, -1, -1), 64);

	/*
	M1.modify(xor_vec(M1.W, 425, 489, 501, -1, -1), 64);	//	425, 486, 489 501
	M2.modify(xor_vec(M2.W, 425, 489, 501, -1, -1), 64);

	M1.modify(xor_vec(M1.W, 430, 504, -1, -1, -1), 64);	
	M2.modify(xor_vec(M2.W, 430, 504, -1, -1, -1), 64);	//486
	*/

	ofstream changes("good_changes.txt");
	findPairTree(M1, M2, D, P, 20, changes, 1);
	
	//find_best_pair(M1, M2, D, P);
	return;

	vector<vector<int>> final_set;

	int just_read_from_file = 0;
	if (just_read_from_file){
		read_clique(final_set);
		cout << dec << "final set size:" << final_set.size() << endl;

		seconds = time(NULL);

		brute_force(final_set, M1, M2, D, P);

		cout << dec << time(NULL) - seconds << endl;
	}
	else{
		constructor(M1, M2, D, P);
	}

	//D.print(M1, M2, 58);
	//print_results(M1,M2, M1, M2, 16);



	//print_results_two_blocks(M1,M2);

	//*
	
	//find_best_pair(M1, M2, D, P);

	//cout << "===DONE===" << endl;
	//return;
	//*/



	getchar();
};



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


/*
fopen_s(&f, "m1_40_block2.txt", "r");
for (int i = 0; i < 16; i++){
fscanf_s(f, "%x ", &W1[i]);
}
fclose(f);
fopen_s(&f, "m2_40_block2.txt", "r");
for (int i = 0; i < 16; i++){
fscanf_s(f, "%x ", &W2[i]);
}
fclose(f);

M1.SetIV(40);
M1.modify(W1, 40);

M2.SetIV(40);
M2.modify(W2, 40);

D.print(M1, M2, 40);
D.print(40);

*/