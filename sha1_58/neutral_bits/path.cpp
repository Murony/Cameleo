#include "classes.h"

DifferentialPath::DifferentialPath(){
	ifstream found_i("found_i.txt");
	vector<char> tmp(32, 0);
	char q;
	FILE* f;
	fopen_s(&f, "diff.txt", "r");
	for (int j = 0; j < 65; j++){
		for (int i = 31; i >= 0; i--){
			fscanf_s(f, "%c", &tmp[i]);
			cout << tmp[i];
		}
		fscanf_s(f, "%c", &q);
		path.push_back(tmp);
		cout << endl;
	}
	fclose(f);
	fopen_s(&f, "diff_w.txt", "r");
	for (int j = 0; j < 64; j++){
		for (int i = 31; i >= 0; i--){
			fscanf_s(f, "%c", &tmp[i]);
			cout << tmp[i];
		}
		fscanf_s(f, "%c", &q);
		path_w.push_back(tmp);
		cout << endl;
	}
	fclose(f);
}

char letter(int a, int b, int c){
	//cout << a << b << c << endl;
	if (a == 1)
		return 'u';
	if (a == -1)
		return 'n';
	if (a == 0)
		if (b == 0){
			return '0';
		}
		else{
			return '1';
		}
}

bool compareLetters(char a, char b){
	if (a == b)
		return true;
	if ((a == 'u' || a == 'n') && (b == 'x'))
		return true;
	if ((a == '0' || a == '1') && (b == '-'))
		return true;
	return false;
}

int DifferentialPath::check(const message &m1, const message &m2)const{
	vector<char> tmp(32, 0);
	int k[65];
	for (int i = 0; i <= 64; i++){
		k[i] = 0;
		for (int j = 0; j < 32; j++){
			tmp[j] = letter(int((m1.a[i] >> j) & 1) - int((m2.a[i] >> j) & 1), int((m1.a[i] >> j) & 1), int((m2.a[i] >> j) & 1));
			//cout << endl << tmp[j] << path[i][j] << endl << compareLetters(tmp[j], path[i][j]) << endl;
			if (!compareLetters(tmp[j], path[i][j]))
				k[i]++;
			//tmp[j] = letter(int((m1.W[i] >> j) & 1) - int((m2.W[i] >> j) & 1), int((m1.W[i] >> j) & 1), int((m2.W[i] >> j) & 1));
			//if (!compareLetters(tmp[j], path_w[i][j]))
				//return i-1;
		}
		if (k[i] > 5)
			return i - 1;
	}
	return 64;
}


bool DifferentialPath::checkBit(int bit)const{
	if (path_w[bit / 32][bit % 32] == '-'){
		return true;
	}
	else{
		return false;
	}
}
