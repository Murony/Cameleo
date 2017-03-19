#include "set_constructor.h"

void read(set<vector<int>> &neutral_vectors);

void construct_neutral_set(const message &M1, const message &M2, const difference &D, const DifferentialPath &P){
	int r = 0;
	set<vector<int>> bad_pairs;
	//read(bad_pairs);

	//cout << "bad set size: " << bad_pairs.size() << endl;

	ofstream pairs("pairs.txt");
	set<int> bad_set;
	for (int v = 0; v < 512; v++){
		if (P.checkBit(v)){
			message tmp_m1(M1);
			message tmp_m2(M2);
			tmp_m1.modify(xor_vec(M1.W, v, -1, -1, -1, -1), R);
			tmp_m2.modify(xor_vec(M2.W, v, -1, -1, -1, -1), R);
			if (P.check(tmp_m1, tmp_m2) >= R){
				#pragma omp critical
				{
					pairs << v << " -1 -1 -1 -1" << endl;
					bad_set.insert(v);
				}
			}
		}
	}

	time_t seconds = time(NULL);

	omp_set_num_threads(16);

	//*
	#pragma omp parallel for
	for (int v = 0; v < 512; v++){
		if (P.checkBit(v)){
			message tmp_m1(M1);
			message tmp_m2(M2);
			if (bad_set.find(v) == bad_set.end()){
				for (int q = v + 1; q < 512; q++){
					if (P.checkBit(q) && (bad_set.find(q) == bad_set.end())){
						tmp_m1.modify(xor_vec(M1.W, v, q, -1, -1, -1), R);
						tmp_m2.modify(xor_vec(M2.W, v, q, -1, -1, -1), R);
						if (P.check(tmp_m1, tmp_m2) >= R){
							#pragma omp critical
							{
								pairs << v << " " << q << " -1 -1 -1" << endl;
								//bad_pairs.insert(vector<int>{v,q});
							}
						}
					}
				}
			}
		}
	}
	//*/

	//cout << "pairs time: " << time(NULL) - seconds << endl;
	seconds = time(NULL);

	//*
	#pragma omp parallel for
	for (int v = 0; v < 512; v++){
		if (P.checkBit(v)){
			message tmp_m1(M1);
			message tmp_m2(M2);
			if (bad_set.find(v) == bad_set.end()){
				for (int q = v + 1; q < 512; q++){
					if (P.checkBit(q) && (bad_set.find(q) == bad_set.end())
						//&& (bad_pairs.find({ v, q }) == bad_pairs.end())
						){
						for (int w = q + 1; w < 512; w++){
							if (P.checkBit(w) && (bad_set.find(w) == bad_set.end())
								//&& (bad_pairs.find({ v, w }) == bad_pairs.end()) 
								//&& (bad_pairs.find({ q, w }) == bad_pairs.end())
								){
								tmp_m1.modify(xor_vec(M1.W, v, q, w, -1, -1), R);
								tmp_m2.modify(xor_vec(M2.W, v, q, w, -1, -1), R);
								if (P.check(tmp_m1, tmp_m2) >= R){
									#pragma omp critical
									{
										pairs << v << " " << q << " " << w << " -1 -1" << endl;
										//bad_pairs.insert(vector<int>{v, q, w});
									}
								}
							}
						}
					}
				}
			}
		}
		//cout << time(NULL) - t << " ";
	}
	//*/
	//cout << dec << "triplets time: " << time(NULL) - seconds << endl;

	seconds = time(NULL);

	//*
	#pragma omp parallel for
	for (int v = 0; v < 512; v++){
		if (P.checkBit(v)){
			message tmp_m1(M1);
			message tmp_m2(M2);
			if (bad_set.find(v) == bad_set.end()){
				for (int q = v + 1; q < 512; q++){
					if (P.checkBit(q) && (bad_set.find(q) == bad_set.end())){
						for (int w = q + 1; w < 512; w++){
							if (P.checkBit(w) && (bad_set.find(w) == bad_set.end())){
								for (int s = w + 1; s < 512; s++){
									if (P.checkBit(s) && (bad_set.find(s) == bad_set.end())){
										tmp_m1.modify(xor_vec(M1.W, v, q, w, s, -1), R);
										tmp_m2.modify(xor_vec(M2.W, v, q, w, s, -1), R);
										if (P.check(tmp_m1, tmp_m2) >= R){
											#pragma omp critical
											{
												pairs << v << " " << q << " " << w << " " << s << " -1" << endl;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		//cout << time(NULL) - t << " ";
	}

	//*/
	//cout << "quadroplets time: " << time(NULL) - seconds << endl;

	pairs.close();
}

void read(vector<vector<int>> &neutral_vectors){
	ifstream ipairs("pairs.txt");
	int count=-1;
	string c;
	while (!ipairs.eof())
	{
		getline(ipairs,c);
		count++;
	}
	ipairs.close();
	ipairs.open("pairs.txt");
	vector<int> init={ -1, -1, -1, -1, -1 };
	for (int v = 0; v < count; v++){
		neutral_vectors.push_back(init);
		ipairs >> neutral_vectors[v][0] >> neutral_vectors[v][1] >> neutral_vectors[v][2] >> neutral_vectors[v][3] >> neutral_vectors[v][4];
	}
	ipairs.close();
}

void read(set<vector<int>> &neutral_vectors){
	ifstream ipairs("pairs.txt");
	int count = -1;
	string c;
	while (!ipairs.eof())
	{
		getline(ipairs, c);
		count++;
	}
	ipairs.close();
	ipairs.open("pairs.txt");
	int tmp, tmp2;
	vector<int> init = { -1, -1, -1};
	for (int v = 0; v < count; v++){
		init = { -1, -1, -1 };
		ipairs >> init[0] >> init[1] >> init[2] >> tmp >> tmp2;
		if (tmp != -1){
			init.push_back(tmp);
		}
		neutral_vectors.insert(init);
	}
	ipairs.close();
}

void read_clique(vector<vector<int>> &neutral_vectors){
	ifstream cl("clique.txt");
	int count = -1;
	string c;
	while (!cl.eof())
	{
		getline(cl, c);
		count++;
	}
	cl.close();
	cl.open("clique.txt");
	vector<int> init = { -1, -1, -1, -1, -1 };
	for (int v = 0; v < count; v++){
		neutral_vectors.push_back(init);
		cl >> neutral_vectors[v][0] >> neutral_vectors[v][1] >> neutral_vectors[v][2] >> neutral_vectors[v][3] >> neutral_vectors[v][4];
	}
	cl.close();
}

void constructor(const message &M1, const message &M2, const difference &D, const DifferentialPath &P){
	time_t seconds = time(NULL);
	time_t all = time(NULL);

	vector<vector<int>> neutral_vectors;
	vector<vector<int>> final_set;

	construct_neutral_set(M1, M2, D, P);
	//return;

	read(neutral_vectors);

	cout << dec << endl << "new size " << neutral_vectors.size() << endl;

	seconds = time(NULL);

	adj_matrix adj(neutral_vectors.size());

	adj.fill(neutral_vectors, M1, M2, D, P);

	cout <<endl<< "matrix filled: " << time(NULL) - seconds << endl;
	seconds = time(NULL);

	set<int> clique;
	kerbosh(adj.adj, adj.adj[1].size(), clique, neutral_vectors);

	cout << endl << "kerbosh complited: " << time(NULL) - seconds << endl;
	seconds = time(NULL);

	cout << endl << "clique size " << clique.size() << endl;

	show_clique(clique, neutral_vectors, final_set);

	cout << "time: " << time(NULL) - all << endl;

	//adj_matrix test(final_set.size());
	//test.show(final_set, M1, M2, D);
}

void find_best_pair(message &M1, message &M2, const difference &D, const DifferentialPath &P){
	ofstream changes("good_changes.txt");
	vector<vector<int>> neutral_vectors;
	vector<vector<int>> tmp_neutral_vectors;
	vector<vector<int>> final_set;
	construct_neutral_set(M1, M2, D, P);
	read(neutral_vectors);

	set<int> clique;
	int max_clique_size = 15;
	vector<vector<int>> best_bits;

	for (auto i = neutral_vectors.begin(); i != neutral_vectors.end(); i++){
		cout << endl << (*i)[0] << " " << (*i)[1] << " " << (*i)[2] << " " << (*i)[3] << " " << (*i)[4] << endl;
		message tmp1(M1);
		message tmp2(M2);
		xor(tmp1.W, *i);
		xor(tmp2.W, *i);
		D.modify(tmp1, tmp2);
		construct_neutral_set(tmp1, tmp2, D, P);
		read(tmp_neutral_vectors);
		cout << endl << tmp_neutral_vectors.size() << endl;

		adj_matrix adj(tmp_neutral_vectors.size());
		adj.fill(tmp_neutral_vectors, tmp1, tmp2, D, P);
		kerbosh(adj.adj, adj.adj[1].size(), clique, tmp_neutral_vectors);
		cout << endl << "clique size " << clique.size() << endl;

		if (clique.size() >= max_clique_size){
			changes << "clique size " << clique.size() << endl;
			changes << (*i)[0] << " " << (*i)[1] << " " << (*i)[2] << " " << (*i)[3] << " " << (*i)[4] << endl << endl;
			max_clique_size = clique.size();

			show_clique(clique, tmp_neutral_vectors, final_set);
		}

		tmp_neutral_vectors.clear();
		clique.clear();
	}

	getchar();

	return;
}


void findPairTree(message &M1, message &M2, const difference &D, const DifferentialPath &P, int max_clique_size, ofstream& changes, int counter){
	if (counter > 10)
		return;
	vector<vector<int>> neutral_vectors;
	vector<vector<int>> tmp_neutral_vectors;
	vector<vector<int>> first_level, second_level;
	construct_neutral_set(M1, M2, D, P);
	read(neutral_vectors);
	set<int> clique;
	vector<vector<int>> best_bits;
	for (auto i = neutral_vectors.begin(); i != neutral_vectors.end(); i++){
		//cout << endl << (*i)[0] << " " << (*i)[1] << " " << (*i)[2] << " " << (*i)[3] << " " << (*i)[4] << endl;
		message tmp1(M1);
		message tmp2(M2);
		xor(tmp1.W, *i);
		xor(tmp2.W, *i);
		D.modify(tmp1, tmp2);
		construct_neutral_set(tmp1, tmp2, D, P);
		read(tmp_neutral_vectors);
		adj_matrix adj(tmp_neutral_vectors.size());
		adj.fill(tmp_neutral_vectors, tmp1, tmp2, D, P);
		kerbosh(adj.adj, adj.adj[1].size(), clique, tmp_neutral_vectors);
		if (clique.size() == max_clique_size){
			//changes << "clique size " << clique.size() << endl;
			//changes << (*i)[0] << " " << (*i)[1] << " " << (*i)[2] << " " << (*i)[3] << " " << (*i)[4] << endl << endl;
			first_level.push_back({ (*i)[0], (*i)[1], (*i)[2], (*i)[3], (*i)[4] });
		}
		if (clique.size() > max_clique_size){
			changes << "clique size " << clique.size() << endl;
			changes << (*i)[0] << " " << (*i)[1] << " " << (*i)[2] << " " << (*i)[3] << " " << (*i)[4] << endl << endl;
			max_clique_size = clique.size();
			first_level.clear();
			first_level.push_back({ (*i)[0], (*i)[1], (*i)[2], (*i)[3], (*i)[4] });
		}
		tmp_neutral_vectors.clear();
		clique.clear();
	}

	for (auto i = first_level.begin(); i != first_level.end(); i++){
		message tmp1(M1);
		message tmp2(M2);
		xor(tmp1.W, *i);
		xor(tmp2.W, *i);
		D.modify(tmp1, tmp2);
		findPairTree(tmp1, tmp2, D, P, max_clique_size, changes, ++counter);
	}

	return;
}
