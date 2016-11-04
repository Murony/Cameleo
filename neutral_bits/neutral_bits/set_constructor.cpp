#include "set_constructor.h"

void construct_neutral_set(set<int> &neutral_bits, list<vector<unsigned>>  &neutral_bits_set, list<vector<int>>  &new_neutral_bits_set, const message &M1, const message &M2, const difference &D){
	int r = 0;
	ofstream pairs("pairs.txt");
	set<int> bad_set;
	for (auto v = neutral_bits_set.begin(); v != neutral_bits_set.end();){
		const message_cupple tmp(xor_vec(*v, M1.W), xor_vec(*v, M2.W), R);
		if (D.equal(tmp, R) == R){
			new_neutral_bits_set.push_back(convert_vector(*v));
			v = neutral_bits_set.erase(v);
			neutral_bits.erase(r);
			bad_set.insert(r);
			pairs << r << " -1 -1 -1 -1" << endl;
		}
		else{
			v++;
		}
		r++;
	}
	time_t seconds = time(NULL);

	omp_set_num_threads(16);

	//*
#pragma omp parallel for
	for (int v = 0; v < 512; v++){
		message tmp_m1(M1.W);
		message tmp_m2(M2.W);
		if (bad_set.find(v) == bad_set.end()){
			for (int q = v + 1; q != 512; q++){
				if (bad_set.find(q) == bad_set.end()){
					tmp_m1.modify(xor_vec(M1.W, v, q, -1, -1, -1), R);
					tmp_m2.modify(xor_vec(M2.W, v, q, -1, -1, -1), R);
					if (D.equal(tmp_m1, tmp_m2, R) == R){
						vector<int> init(5, -1);
						init[0] = v;
						init[1] = q;
						#pragma omp critical
						{
							pairs << v << " " << q << " -1 -1 -1" <<endl;
							new_neutral_bits_set.push_back(init);
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
			for (int q = v + 1; q != 512; q++){
				if (bad_set.find(q) == bad_set.end()){
					for (int w = q + 1; w != 512; w++){
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
									pairs << v << " " << q << " " << w << " -1 -1" << endl;
									new_neutral_bits_set.push_back(init);
								}
							}
						}
					}
				}
			}
		}
		cout << time(NULL) - t << " ";
	}
	//*/
	cout << "triplets time: " << time(NULL) - seconds << endl;

	seconds = time(NULL);

	/*
	#pragma omp parallel for
	for (int v = 400; v < 512; v++){
		message tmp_m1(M1.W);
		message tmp_m2(M2.W);
		time_t t = time(NULL);
		if (bad_set.find(v) == bad_set.end()){
			for (int q = v + 1; q != 512; q++){
				if (bad_set.find(q) == bad_set.end()){
					for (int w = q + 1; w != 512; w++){
						if (bad_set.find(w) == bad_set.end()){
							for (int y = w + 1; y != 512; y++){
								if (bad_set.find(y) == bad_set.end()){
									tmp_m1.modify(xor_vec(M1.W, v, q, w, y, -1), R);
									tmp_m2.modify(xor_vec(M2.W, v, q, w, y, -1), R);
									if (D.equal(tmp_m1, tmp_m2, R) == R){
										vector<int> init(5, -1);
										init[0] = v;
										init[1] = q;
										init[2] = w;
										init[3] = y;
										#pragma omp critical
										{
											pairs << v << " " << q << " " << w << " " << y << " -1" << endl;
											new_neutral_bits_set.push_back(init);
										}
									}
								}
							}
						}
					}
				}
			}
		}
		cout << time(NULL) - t << " ";
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
	//for (int v = 0; v < neutral_vectors.size(); v++)
	//	new_neutral_bits_set.push_back(neutral_vectors[v]);
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
	/*for (int v = 0; v < 36; v++){
		for (int i = 0; i < 5; i++)
			cout << neutral_vectors[v][i] << " ";
		cout << endl;
	}*/
	cl.close();
}

void constructor(const message &M1, const message &M2, const difference &D){
	time_t seconds = time(NULL);
	time_t all = time(NULL);

	list<vector<unsigned>> neutral_bits_set;
	list<vector<int>> new_neutral_bits_set;
	set<int> neutral_bits;
	vector<vector<int>> neutral_vectors; //(2269, { -1, -1, -1, -1, -1 });
	vector<vector<int>> final_set;

	generate_list(neutral_bits_set, neutral_bits);

	cout << dec << endl << "size " << neutral_bits_set.size() << endl;

	construct_neutral_set(neutral_bits, neutral_bits_set, new_neutral_bits_set, M1, M2, D);

	read(neutral_vectors);

	cout << dec << endl << "new size " << neutral_vectors.size() << endl;

	seconds = time(NULL);

	adj_matrix adj(neutral_vectors.size());
	//adj.fill(new_neutral_bits_set, M1, M2, D);
	adj.fill(neutral_vectors, M1, M2, D);

	//adj.edges();

	cout <<endl<< "matrix filled: " << time(NULL) - seconds << endl;
	seconds = time(NULL);

	set<int> clique;
	kerbosh(adj.adj, adj.adj[1].size(), clique);

	cout << endl << "kerbosh complited: " << time(NULL) - seconds << endl;
	seconds = time(NULL);

	//cout << endl;
	//for (auto q = clique.begin(); q != clique.end(); q++){ cout << *q << " "; }
	//cout << endl;

	cout << endl << "clique size " << clique.size() << endl;

	show_clique(clique, neutral_vectors, final_set);

	cout << "time: " << time(NULL) - all << endl;

	//adj_matrix test(final_set.size());
	//test.show(final_set, M1, M2, D);
}




//write_clique(final_set);
/*void write_clique(vector<vector<int>> clique){
ofstream cl("clique.txt");
for (auto q = clique.begin(); q != clique.end(); q++){
cl << (*q)[0] << " " << (*q)[1] << " " << (*q)[2] << " " << (*q)[3] << " " << (*q)[4] << " " << endl;
}
cl.close();
}*/

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