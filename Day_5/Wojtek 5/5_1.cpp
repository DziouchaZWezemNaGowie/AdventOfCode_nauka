#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
int main(){
	ifstream infile;
	infile.open("DANE.txt");
	if (infile.is_open()){
		vector<string> zasieg;
		vector<string> ids;
		string l, z;
		long long zmin, zmax, id;
		int wynik = 0;
		while (infile >> l){
			if (l.find('-') != string::npos){
				zasieg.push_back(l);
			}else{
				ids.push_back(l);
			}
		}
		for (int iid=0; iid < ids.size(); iid++){
			id = stoll(ids.at(iid));
			for (int iz=0; iz < zasieg.size(); iz++){
				z = zasieg.at(iz);
				zmin = stoll(z.substr(0,z.find('-')));
				zmax = stoll(z.substr(z.find('-')+1,z.size()-z.find('-')));
				if (id >= zmin && id <= zmax){
					wynik++;
					iz = zasieg.size();
				}
			}
		}
		cout << wynik;
	}else{
		cout << "nieotwarlosie";
	}
	return 0;
}
