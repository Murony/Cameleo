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
	//*
	for (auto v = neutral_bits.begin(); v != neutral_bits.end(); v++){
		for (auto q = next(v); q != neutral_bits.end(); q++){
			const message_cupple tmp(xor_vec(M1.W, *v, *q, -1, -1, -1), xor_vec(M2.W, *v, *q, -1, -1, -1), R);
			if (D.equal(tmp, R) == R){
				vector<int> init(5,-1);
				init[0] = *v;
				init[1] = *q;
				new_neutral_bits_set.push_back(init);
			}
		}
	}
	//*/
	//*
	for (auto v = neutral_bits.begin(); v != neutral_bits.end(); v++){
		cout << r++ << " ";
		for (auto q = next(v); q != neutral_bits.end(); q++){
			for (auto w = next(q); w != neutral_bits.end(); w++){
				const message_cupple tmp(xor_vec(M1.W, *v, *q, *w, -1, -1), xor_vec(M2.W, *v, *q, *w, -1, -1), R);
				if (D.equal(tmp, R) == R){
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

	//getchar();
	//return;

	//cout << dec << D.equal(M1, M2) << endl;

	list<vector<unsigned>> neutral_bits_set;
	list<vector<int>> new_neutral_bits_set;
	list<vector<int>> final_set;
	set<int> neutral_bits;

	generate_list(neutral_bits_set, neutral_bits);

	cout << dec << endl << "size " << neutral_bits_set.size() << endl;

	construct_neutral_set(neutral_bits, neutral_bits_set, new_neutral_bits_set, M1, M2, D);

	cout << dec << endl << "new size " << new_neutral_bits_set.size() << endl;

	//for (auto it = new_neutral_bits_set.begin(); it != new_neutral_bits_set.end(); it++) { show_number(*it); }

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



//adj_matrix check_m(new_neutral_bits_set.size());
//check_m.show(final_neutral_bits_set, M1, M2, D);

//cout << dec << endl << "final_size " << final_neutral_bits_set.size() << endl;
//for (auto it = new_neutral_bits_set.begin(); it != new_neutral_bits_set.end(); it++) { show_number(*it);}

/*list<set<int>> clique = kerbosh(adj.adj,adj.adj[1].size());

	cout << endl;
	auto it = clique.begin();
	//for ( it != clique.end(); it++){//{ cout << *it << " "; }
		for (auto q = it->begin(); q != it->end(); q++){ cout << *q << " "; }
		cout << endl;
	//}
	
	cout << endl <<"clique size "<<clique.begin()->size()<<endl;

	int w = 0;
	for (auto q = it->begin(); q != it->end(); q++){
		w = 0;
		for (auto t = new_neutral_bits_set.begin(); t != new_neutral_bits_set.end(); t++){
			if (w == *q){
				//final_neutral_bits_set.push_back(*t);
				show_number(*t);
			}
			w++;
		}
	}*/

/*int r = 0;
	for (auto v = neutral_bits_set.begin(); v != neutral_bits_set.end(); v++){
		for (auto q = next(v); q != neutral_bits_set.end(); q++){
			const message_cupple tmp(xor_vec(*v, *q, M1.W), xor_vec(*v, *q, M2.W), R);
			if (D.equal(tmp, R) == R){
				new_neutral_bits_set.push_back(xor_vec(*v, *q));
				//cout << r++;
			}
		}
	}

	for (auto v = neutral_bits_set.begin(); v != neutral_bits_set.end(); v++){
		for (auto q = next(v); q != neutral_bits_set.end(); q++){
			for (auto w = next(q); w != neutral_bits_set.end(); w++){
				const message_cupple tmp(xor_vec(*v, *q, *w, M1.W), xor_vec(*v, *q, *w, M2.W), R);
				if (D.equal(tmp, R) == R){
					new_neutral_bits_set.push_back(xor_vec(*v, *q, *w));
					cout << r++ <<" ";
				}
			}
		}
	}*/







/*
for_each(neutral_bits_set.begin(), neutral_bits_set.end(),
[M1, M2, D, &new_neutral_bits_set](vector<unsigned> v){
const message_cupple tmp(xor_vec(v, M1.W), xor_vec(v, M2.W), R);
//for (auto it = v.begin(); it != v.end(); it++){ cout << hex << *it << " "; } cout << endl;
if (D.equal(tmp,R) == R){
new_neutral_bits_set.push_back(v);
}
});
*/


//auto it = new_neutral_bits_set.begin();
//copy(it->begin(), it->end(), ostream_iterator<unsigned>(cout, " "));
//cout << dec << endl << new_neutral_bits_set.size();
//show_number(*it);



/*for (auto it = neutral_bits_set.begin(); it != neutral_bits_set.end(); it++) {
vector<unsigned> tmp(80, 0);
tmp = W1;
for (int i = 0; i < 16; i++){
tmp[i] ^= (*it)[i];
}
message temp_m(tmp);
copy(temp_m.W.begin(), temp_m.W.end(), ostream_iterator<unsigned>(cout, " "));
}*/


/*
copy(it->begin(),it->end(), ostream_iterator<unsigned>(cout, " "));
cout << endl;


fopen_s(&f,"m1.txt","r");
vector<unsigned int> mes1(128,0);
for (int i = 0; i < 128; i++){
fscanf_s(f, "%x ", &mes1[i]);
}
fclose(f);
fopen_s(&f, "m2.txt", "r");
vector<unsigned int> mes2(128, 0);
for (int i = 0; i < 128; i++){
fscanf_s(f, "%x ", &mes2[i]);
}
fclose(f);*/


/*for (int i = 16; i<80; i++){
W1[i] = (W1[i - 3] ^ W1[i - 8] ^ W1[i - 14] ^ W1[i - 16]);
//W1[i] = ((W1[i] << 1) | (W1[i] >> (32 - 1)));
}
for (int i = 16; i<80; i++){
W2[i] = (W2[i - 3] ^ W2[i - 8] ^ W2[i - 14] ^ W2[i - 16]);
//cout << hex << W2[i] << " ";
}
for (int i = 0; i < 80; i++){
dif[i] = W1[i] ^ W2[i];
if (i % 20 == 0)
cout << endl;
cout << hex << dif[i] << " ";
}
cout << endl;
vector<unsigned int> a1(81, 0);
vector<unsigned int> b1(81, 0);
vector<unsigned int> c1(81, 0);
vector<unsigned int> d1(81, 0);
vector<unsigned int> e1(81, 0);
vector<unsigned int> a2(81, 0);
vector<unsigned int> b2(81, 0);
vector<unsigned int> c2(81, 0);
vector<unsigned int> d2(81, 0);
vector<unsigned int> e2(81, 0);
a1[0] = 0x67452301;
b1[0] = 0xEFCDAB89;
c1[0] = 0x98BADCFE;
d1[0] = 0x10325476;
e1[0] = 0xC3D2E1F0;
a2[0] = 0x67452301;
b2[0] = 0xEFCDAB89;
c2[0] = 0x98BADCFE;
d2[0] = 0x10325476;
e2[0] = 0xC3D2E1F0;
for (int i = 0; i < 80; i++){
unsigned f = round_function(b1[i], c1[i], d1[i], i);//b1[i] ^ c1[i] ^ d1[i];
a1[i + 1] = (e1[i] + ((a1[i] << 5) | (a1[i] >> (32 - 5))) + f + W1[i] + key(i))&MASK;
b1[i + 1] = a1[i];
c1[i + 1] = ((b1[i] << 30) | (b1[i] >> 2));
d1[i + 1] = c1[i];
e1[i + 1] = d1[i];
}
cout << endl;
for (int i = 0; i < 80; i++){
unsigned f = round_function(b2[i], c2[i], d2[i], i); // f = b2[i] ^ c2[i] ^ d2[i];
a2[i + 1] = (e2[i] + ((a2[i] << 5) | (a2[i] >> (32 - 5))) + f + W2[i] + key(i)) &MASK;
b2[i + 1] = a2[i];
c2[i + 1] = ((b2[i] << 30) | (b2[i] >> 2));
d2[i + 1] = c2[i];
e2[i + 1] = d2[i];
if (i % 20 == 0)
cout << endl;
cout << hex << (a1[i+1] ^ a2[i+1]) << " ";
}*/