#include "classes.h"

unsigned round_function(unsigned b, unsigned c, unsigned d, int round){
	if (round < 20) {
		return (b & c) | (~b & d);
	}
	else if (round >= 20 && round < 40) {
		return b ^ c ^ d;
	}
	else if (round >= 40 && round < 60) {
		return (b & c) | (b & d) | (c & d);
	}
	else {
		return b ^ c ^ d;
	}
}

unsigned key(int round){
	if (round < 20) {
		return 0x5A827999;
	}
	else if (round >= 20 && round < 40) {
		return 0x6ED9EBA1;
	}
	else if (round >= 40 && round < 60) {
		return 0x8F1BBCDC;
	}
	else {
		return 0xCA62C1D6;
	}
}

message::message(vector<unsigned> In){
	W = vector<unsigned>(80, 0);
	a = vector<unsigned>(81, 0);
	b = vector<unsigned>(81, 0);
	c = vector<unsigned>(81, 0);
	d = vector<unsigned>(81, 0);
	e = vector<unsigned>(81, 0);
	a[0] = 0x67452301;
	b[0] = 0xEFCDAB89;
	c[0] = 0x98BADCFE;
	d[0] = 0x10325476;
	e[0] = 0xC3D2E1F0;
	W = In;
	for (int i = 16; i<80; i++){
		W[i] = (W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16]);
		//W[i] = ((W[i] << 1) | (W[i] >> (32 - 1)));
	}
	for (int i = 0; i < 80; i++){
		unsigned f = round_function(b[i], c[i], d[i], i);
		a[i + 1] = (e[i] + ((a[i] << 5) | (a[i] >> (32 - 5))) + f + W[i] + key(i))&MASK;
		b[i + 1] = a[i];
		c[i + 1] = ((b[i] << 30) | (b[i] >> 2))&MASK;
		d[i + 1] = c[i];
		e[i + 1] = d[i];
	}
}

message::message(vector<unsigned> In, int max_round){
	W = vector<unsigned>(80, 0);
	a = vector<unsigned>(81, 0);
	b = vector<unsigned>(81, 0);
	c = vector<unsigned>(81, 0);
	d = vector<unsigned>(81, 0);
	e = vector<unsigned>(81, 0);
	a[0] = 0x67452301;
	b[0] = 0xEFCDAB89;
	c[0] = 0x98BADCFE;
	d[0] = 0x10325476;
	e[0] = 0xC3D2E1F0;
	W = In;
	for (int i = 16; i <= max_round; i++){
		W[i] = (W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16]);
		//W[i] = ((W[i] << 1) | (W[i] >> (32 - 1)));
	}
	for (int i = 0; i <= max_round; i++){
		unsigned f = round_function(b[i], c[i], d[i], i);
		a[i + 1] = (e[i] + ((a[i] << 5) | (a[i] >> (32 - 5))) + f + W[i] + key(i))&MASK;
		b[i + 1] = a[i];
		c[i + 1] = ((b[i] << 30) | (b[i] >> 2))&MASK;
		d[i + 1] = c[i];
		e[i + 1] = d[i];
	}
}

difference::difference(message m1, message m2){
	dif = vector<unsigned>(81, 0);
	/*for (int i = 0; i <= 23; i++){
	dif[i] = m1.a[i] ^ m2.a[i];
	cout << hex << dif[i] << " ";
	}
	cout << endl;*/
	for (int i = 0; i < 16; i++){
		dif[i] = m1.W[i] ^ m2.W[i];
		//cout << hex << dif[i] << " ";
	}
	//cout << endl;
	vector<unsigned> W = vector<unsigned>(80, 0);
	vector<unsigned> a = vector<unsigned>(81, 0);
	vector<unsigned> b = vector<unsigned>(81, 0);
	vector<unsigned> c = vector<unsigned>(81, 0);
	vector<unsigned> d = vector<unsigned>(81, 0);
	vector<unsigned> e = vector<unsigned>(81, 0);
	W = dif;
	for (int i = 16; i<80; i++){
		W[i] = (W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16]);
		//W[i] = ((W[i] << 1) | (W[i] >> (32 - 1)));
	}
	for (int i = 0; i < 80; i++){
		unsigned f = b[i] ^ c[i] ^ d[i];
		a[i + 1] = (e[i] ^ ((a[i] << 5) | (a[i] >> (32 - 5))) ^ f ^ W[i])&MASK;
		b[i + 1] = a[i];
		c[i + 1] = ((b[i] << 30) | (b[i] >> 2))&MASK;
		d[i + 1] = c[i];
		e[i + 1] = d[i];
	}
	dif = a;
	for (int i = 0; i < 81; i++){
		//cout << hex << dif[i] << " ";
	}
	//cout << endl;
}

int difference::equal(const message m1, const message m2, int r)const{
	for (int i = 1; i < r; i++){
		if ((m1.a[i] ^ m2.a[i]) != dif[i])
			return i;
	}
	return r;
}

int difference::equal(const message_cupple cup, int r)const{
	return equal(cup.m1, cup.m2, r);
}















/*	void edges(Graph &g){
		for (unsigned i = 0; i < adj[1].size(); i++){
			g.addNode(i);
		}
		for (unsigned i = 0; i < adj[1].size(); i++){
			for (unsigned j = 0; j < adj[1].size(); j++){
				if (adj[i][j] != 0){
					g.addEdge(i, j);
					cout << i << " " << j << endl;
				}
			}
		}
		cout << endl;
		}*/