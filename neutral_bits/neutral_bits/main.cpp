#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <iterator>
#include <algorithm>
#include <map>
#include <stack>
#include <tuple>
#include "classes.h"

void main(){
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
	list<vector<unsigned>> new_neutral_bits_set;
	list<vector<unsigned>> final_neutral_bits_set;

	generste_list(neutral_bits_set);

	cout << dec << endl << "size " << neutral_bits_set.size() << endl;

	for_each(neutral_bits_set.begin(), neutral_bits_set.end(), 
		[M1, M2, D, &new_neutral_bits_set](vector<unsigned> v){
			const message_cupple tmp(xor_vec(v, M1.W), xor_vec(v, M2.W), R);
			if (D.equal(tmp,R) == R){
				new_neutral_bits_set.push_back(v);
			}
		});

	cout << dec << endl << "new size " << new_neutral_bits_set.size() << endl;

	adj_matrix adj(new_neutral_bits_set.size());

	adj.fill(new_neutral_bits_set, M1, M2, D);
	//Graph g = Graph();
	//adj.edges(g);

	cout << "filled" << endl;

	list<set<int>> clique = kerbosh(adj.adj,adj.adj[1].size());

	cout << endl;
	auto it = clique.begin();
	//for ( it != clique.end(); it++){//{ cout << *it << " "; }
		for (auto q = it->begin(); q != it->end(); q++){ cout << *q << " "; }
		cout << endl;
	//}
	
	cout << endl <<"clique size "<<clique.begin()->size();

	//cout << dec << endl << "final_size " << final_neutral_bits_set.size() << endl;
	//for (auto it = new_neutral_bits_set.begin(); it != new_neutral_bits_set.end(); it++) { show_number(*it);}

	getchar();
};





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