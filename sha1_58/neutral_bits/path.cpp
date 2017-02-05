#include "classes.h"

DifferentialPath::DifferentialPath(const message &m1, const message &m2){
	vector<int> tmp(32, 0);
	for (int i = 0; i <= 58; i++){
		for (int j = 0; j < 32; j++){
			tmp[j] = int((m2.a[i] >> j) & 1) - int((m1.a[i] >> j) & 1);
			//if (tmp[j]>0)
			//	cout << dec << i << " " << j + 1 << endl;
			//if (tmp[j]<0)
			//	cout << dec << i << " " << -(j + 1) << endl;
		}
		path.push_back(tmp);
	}
	//	cout << hex << m1.a[i] - m2.a[i] << endl;
}


int DifferentialPath::check(const message &m1, const message &m2)const{
	vector<int> tmp(32, 0);
	for (int i = 0; i <= 58; i++){
		for (int j = 0; j < 32; j++){
			tmp[j] = int((m2.a[i] >> j) & 1) - int((m1.a[i] >> j) & 1);
			if (tmp[j] != path[i][j])
				return i-1;
		}
	}
	return 58;
}