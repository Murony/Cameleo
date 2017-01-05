#include "set_constructor.h"

void construct_neutral_set(const message &M1, const message &M2, const difference &D){
	int r = 0;
	ofstream pairs("pairs.txt");
	set<vector<int>> bad_pairs;
	set<int> bad_set;
	for (int v = 0; v < 512; v++){
		message tmp_m1(M1.W);
		message tmp_m2(M2.W);
		tmp_m1.modify(xor_vec(M1.W, v, -1, -1, -1, -1), R);
		tmp_m2.modify(xor_vec(M2.W, v, -1, -1, -1, -1), R);
		if (D.equal(tmp_m1, tmp_m2, R) == R){
			#pragma omp critical
			{
				pairs << v << " -1 -1 -1 -1" << endl;
				bad_set.insert(v);
			}
		}
	}

	time_t seconds = time(NULL);

	omp_set_num_threads(16);

	//*
	#pragma omp parallel for
	for (int v = 0; v < 512; v++){
		message tmp_m1(M1.W);
		message tmp_m2(M2.W);
		if (bad_set.find(v) == bad_set.end()){
			for (int q = v + 1; q < 512; q++){
				if (bad_set.find(q) == bad_set.end()){
					tmp_m1.modify(xor_vec(M1.W, v, q, -1, -1, -1), R);
					tmp_m2.modify(xor_vec(M2.W, v, q, -1, -1, -1), R);
					if (D.equal(tmp_m1, tmp_m2, R) == R){
						#pragma omp critical
						{
							pairs << v << " " << q << " -1 -1 -1" <<endl;
							bad_pairs.insert(vector<int>{v,q});
						}
					}
				}
			}
		}
	}
	//*/

	cout << "pairs time: " << time(NULL) - seconds << endl;
	seconds = time(NULL);

	//*
	#pragma omp parallel for
	for (int v = 0; v < 512; v++){
		message tmp_m1(M1.W);
		message tmp_m2(M2.W);
		time_t t = time(NULL);
		if (bad_set.find(v) == bad_set.end()){
			for (int q = v + 1; q < 512; q++){
				if ((bad_set.find(q) == bad_set.end()) && (bad_pairs.find({ v, q }) == bad_pairs.end())){
					for (int w = q + 1; w < 512; w++){
						if ((bad_set.find(w) == bad_set.end()) && (bad_pairs.find({ v, w }) == bad_pairs.end()) && (bad_pairs.find({ q, w }) == bad_pairs.end())){
							tmp_m1.modify(xor_vec(M1.W, v, q, w, -1, -1), R);
							tmp_m2.modify(xor_vec(M2.W, v, q, w, -1, -1), R);
							if (D.equal(tmp_m1, tmp_m2, R) == R){
								#pragma omp critical
								{
									pairs << v << " " << q << " " << w << " -1 -1" << endl;
									bad_pairs.insert(vector<int>{v, q, w});
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
	cout << "triplets time: " << time(NULL) - seconds << endl;

	seconds = time(NULL);

	//*
	for (int v = 0; v < 512; v++){
		if (bad_set.find(v) == bad_set.end()){
			#pragma omp parallel for
			for (int q = v + 1; q < 512; q++){
				message tmp_m1(M1.W);
				message tmp_m2(M2.W);
				if ((bad_set.find(q) == bad_set.end()) && (bad_pairs.find({ v, q }) == bad_pairs.end())){
					for (int w = q + 1; w < 512; w++){
						if ((bad_set.find(w) == bad_set.end()) 
									&& (bad_pairs.find({ v, w }) == bad_pairs.end()) 
									&& (bad_pairs.find({ q, w }) == bad_pairs.end()) 
									&& (bad_pairs.find({ v, q, w }) == bad_pairs.end())){
							for (int y = w + 1; y != 512; y++){
								if ((bad_set.find(y) == bad_set.end()) 
											&& (bad_pairs.find({ v, y }) == bad_pairs.end()) 
											&& (bad_pairs.find({ q, y }) == bad_pairs.end()) 
											&& (bad_pairs.find({ w, y }) == bad_pairs.end()) 
											&& (bad_pairs.find({ v, q, y }) == bad_pairs.end())
											&& (bad_pairs.find({ v, w, y }) == bad_pairs.end())
											&& (bad_pairs.find({ q, w, y }) == bad_pairs.end())){
									tmp_m1.modify(xor_vec(M1.W, v, q, w, y, -1), R);
									tmp_m2.modify(xor_vec(M2.W, v, q, w, y, -1), R);
									if (D.equal(tmp_m1, tmp_m2, R) == R){
										#pragma omp critical
										{
											pairs << v << " " << q << " " << w << " " << y << " -1" << endl;
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
		cout << v << " ";
	}

	//*/
	cout << "quadroplets time: " << time(NULL) - seconds << endl;

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

void constructor(const message &M1, const message &M2, const difference &D){
	time_t seconds = time(NULL);
	time_t all = time(NULL);

	vector<vector<int>> neutral_vectors;
	vector<vector<int>> final_set;

	//construct_neutral_set(M1, M2, D);

	read(neutral_vectors);

	cout << dec << endl << "new size " << neutral_vectors.size() << endl;

	seconds = time(NULL);

	adj_matrix adj(neutral_vectors.size());

	adj.fill(neutral_vectors, M1, M2, D);

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