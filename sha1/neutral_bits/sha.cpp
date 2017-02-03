#include "classes.h"

#define sha1 1

inline
unsigned round_function(unsigned b, unsigned c, unsigned d, int round){
	if (round < 20) {
		return (b & c) | (~b & d);
	}
	else if ((round >= 20) && (round < 40)) {
		return b ^ c ^ d;
	}
	else if ((round >= 40) && (round < 60)) {
		return (b & c) | (b & d) | (c & d);
	}
	else {
		return b ^ c ^ d;
	}
}

inline
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

message::message(const message &M){
	W = vector<unsigned>(80, 0);
	a = vector<unsigned>(81, 0);
	b = vector<unsigned>(81, 0);
	c = vector<unsigned>(81, 0);
	d = vector<unsigned>(81, 0);
	e = vector<unsigned>(81, 0);
	a[0] = M.a[0];
	b[0] = M.b[0];
	c[0] = M.c[0];
	d[0] = M.d[0];
	e[0] = M.e[0];

	W = M.W;
	for (int i = 16; i<80; i++){
		W[i] = (W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16]);
		if (sha1)
			W[i] = ((W[i] << 1) | (W[i] >> (32 - 1)))&MASK;
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

message::message(const vector<unsigned> &In){
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

	/*a[0] = 0x37970DFF;
	b[0] = 0x5E912289;
	c[0] = 0xC78B3705;
	d[0] = 0x923B82E9;
	e[0] = 0xCC36E948;*/

	W = In;
	for (int i = 16; i<80; i++){
		W[i] = (W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16]);
		if (sha1)
			W[i] = ((W[i] << 1) | (W[i] >> (32 - 1)))&MASK;
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

message::message(const vector<unsigned> &In, char n)
	:a(vector<unsigned>(81, 0)), W(vector<unsigned>(80, 0)), b(vector<unsigned>(81, 0)), c(vector<unsigned>(81, 0)), d(vector<unsigned>(81, 0)), e(vector<unsigned>(81, 0)){
	a[0] = 0x67452301;
	b[0] = 0xEFCDAB89;
	c[0] = 0x98BADCFE;
	d[0] = 0x10325476;
	e[0] = 0xC3D2E1F0;

	/*a[0] = 0x37970DFF;
	b[0] = 0x5E912289;
	c[0] = 0xC78B3705;
	d[0] = 0x923B82E9;
	e[0] = 0xCC36E948;*/
	W = In;
	for (int i = 16; i<80; i++){
		W[i] = (W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16]);
		if (sha1)
			W[i] = ((W[i] << 1) | (W[i] >> (32 - 1)))&MASK;
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

message::message(const vector<unsigned> &In, int max_round){
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

	/*a[0] = 0x37970DFF;
	b[0] = 0x5E912289;
	c[0] = 0xC78B3705;
	d[0] = 0x923B82E9;
	e[0] = 0xCC36E948;*/
	W = In;
	for (int i = 16; i <= max_round; i++){
		W[i] = (W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16]);
		if (sha1)
			W[i] = ((W[i] << 1) | (W[i] >> (32 - 1)))&MASK;
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

void message::SetIV(int round){
	a[0] = (a[0] + a[round]) & MASK;
	b[0] = (b[0] + b[round]) & MASK;
	c[0] = (c[0] + c[round]) & MASK;
	d[0] = (d[0] + d[round]) & MASK;
	e[0] = (e[0] + e[round]) & MASK;
}

void message::modify(const vector<unsigned> &In, int max_round){
	W = In;
	for (int i = 16; i <= max_round; i++){
		W[i] = (W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16]);
		if (sha1)
			W[i] = ((W[i] << 1) | (W[i] >> (32 - 1)))&MASK;
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


int difference::modify(message& m1, message& m2)const{
	unsigned f;
	int k = 0;
	for (int i = 0; i < 66; i++){
		if ((m1.a[i] ^ m2.a[i]) == dif[i])
			k = i;

		if (i>15){
			m1.W[i] = (m1.W[i - 3] ^ m1.W[i - 8] ^ m1.W[i - 14] ^ m1.W[i - 16]);
			if (sha1)
				m1.W[i] = ((m1.W[i] << 1) | (m1.W[i] >> (32 - 1)))&MASK;
			m2.W[i] = (m2.W[i - 3] ^ m2.W[i - 8] ^ m2.W[i - 14] ^ m2.W[i - 16]);
			if (sha1)
				m2.W[i] = ((m2.W[i] << 1) | (m2.W[i] >> (32 - 1)))&MASK;
		}

		f = round_function(m1.b[i], m1.c[i], m1.d[i], i);
		m1.a[i + 1] = (m1.e[i] + ((m1.a[i] << 5) | (m1.a[i] >> (32 - 5))) + f + m1.W[i] + key(i))&MASK;
		m1.b[i + 1] = m1.a[i];
		m1.c[i + 1] = ((m1.b[i] << 30) | (m1.b[i] >> 2))&MASK;
		m1.d[i + 1] = m1.c[i];
		m1.e[i + 1] = m1.d[i];

		f = round_function(m2.b[i], m2.c[i], m2.d[i], i);
		m2.a[i + 1] = (m2.e[i] + ((m2.a[i] << 5) | (m2.a[i] >> (32 - 5))) + f + m2.W[i] + key(i))&MASK;
		m2.b[i + 1] = m2.a[i];
		m2.c[i + 1] = ((m2.b[i] << 30) | (m2.b[i] >> 2))&MASK;
		m2.d[i + 1] = m2.c[i];
		m2.e[i + 1] = m2.d[i];
	}
	return k;
}

int difference::modify_full(message& m1, message& m2)const{
	unsigned f;
	int k = 0;
	for (int i = 0; i < 80; i++){
		if ((m1.a[i] ^ m2.a[i]) != dif[i])
			k = i - 1;

		if (i>15){
			m1.W[i] = (m1.W[i - 3] ^ m1.W[i - 8] ^ m1.W[i - 14] ^ m1.W[i - 16]);
			if (sha1)
				m1.W[i] = ((m1.W[i] << 1) | (m1.W[i] >> (32 - 1)))&MASK;
			m2.W[i] = (m2.W[i - 3] ^ m2.W[i - 8] ^ m2.W[i - 14] ^ m2.W[i - 16]);
			if (sha1)
				m2.W[i] = ((m2.W[i] << 1) | (m2.W[i] >> (32 - 1)))&MASK;
		}

		f = round_function(m1.b[i], m1.c[i], m1.d[i], i);
		m1.a[i + 1] = (m1.e[i] + ((m1.a[i] << 5) | (m1.a[i] >> (32 - 5))) + f + m1.W[i] + key(i))&MASK;
		m1.b[i + 1] = m1.a[i];
		m1.c[i + 1] = ((m1.b[i] << 30) | (m1.b[i] >> 2))&MASK;
		m1.d[i + 1] = m1.c[i];
		m1.e[i + 1] = m1.d[i];

		f = round_function(m2.b[i], m2.c[i], m2.d[i], i);
		m2.a[i + 1] = (m2.e[i] + ((m2.a[i] << 5) | (m2.a[i] >> (32 - 5))) + f + m2.W[i] + key(i))&MASK;
		m2.b[i + 1] = m2.a[i];
		m2.c[i + 1] = ((m2.b[i] << 30) | (m2.b[i] >> 2))&MASK;
		m2.d[i + 1] = m2.c[i];
		m2.e[i + 1] = m2.d[i];
	}
	return k;
}

difference::difference(const message &m1, const message &m2){
	dif = vector<unsigned>(81, 0);
	/*for (int i = 0; i <= 30; i++){
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
		if (sha1)
			W[i] = ((W[i] << 1) | (W[i] >> (32 - 1)))&MASK;
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

int difference::equal(const message& m1, const message& m2, int r)const{
	int k = 0;
	for (int i = 1; i <= r; i++){
		if ((m1.a[i] ^ m2.a[i]) == dif[i])
			k=i;
	}
	return k;
}

void difference::print(int r)const{
	cout << endl;
	for (int i = 0; i <= r; i++){
		cout << hex << dif[i] << " ";
	}
	cout << endl;
}

void difference::print(const message& m1, const message& m2, int r)const{
	for (int i = 0; i < 16; i++){
		//cout << hex << (m1.W[i]) << " ";
	}
	cout << endl;
	for (int i = 0; i <= r; i++){
		cout << hex << (m1.a[i] ^ m2.a[i])<<" ";
		//if ((m1.a[i] ^ m2.a[i]) != 0)
		//	cout << "Here it is";
	}
	cout << endl;
}

int difference::equal(const message_cupple& cup, int r)const{
	return equal(cup.m1, cup.m2, r);
}