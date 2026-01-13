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
		vector<long long> zasiegmin;
		vector<long long> zasiegmax;
		string l, z;
		long long zmin, zmax;
		long long wynik = 0;
		while (infile >> l){
			if (l.find('-') != string::npos){
				zasieg.push_back(l);
			}
		}
		for (int iz=0; iz < zasieg.size(); iz++){
			z = zasieg.at(iz);
			zmin = stoll(z.substr(0,z.find('-')));
			zmax = stoll(z.substr(z.find('-')+1,z.size()-z.find('-')));
			for (int iz2=iz-1; iz2>=0;iz2--){
				if(zasiegmin.at(iz2) >= zmin && zasiegmax.at(iz2) <= zmax){
					wynik -= zasiegmax.at(iz2) - zasiegmin.at(iz2) + 1;
					zasiegmax.at(iz2) = 0;
					zasiegmin.at(iz2) = 0;
				}else{
				if (zmin >= zasiegmin.at(iz2) && zmin <= zasiegmax.at(iz2)){
					zmin = zasiegmax.at(iz2) + 1;
				}
				if (zmax <= zasiegmax.at(iz2) && zmax >= zasiegmin.at(iz2)){
					zmax = zasiegmin.at(iz2) - 1;
				}
				}
			}
			if (zmin <= zmax){
			zasiegmin.push_back(zmin);
			zasiegmax.push_back(zmax);
			//cout<<zmin<<"-"<<zmax<<endl;
			wynik += zmax - zmin + 1; 
			}else{
				zasiegmin.push_back(0);
				zasiegmax.push_back(0);
			}
			//cout << wynik << "\n";
		}
		for(int i = 0; i< zasiegmin.size(); i++){
				cout<<zasiegmin.at(i)<<","<<zasiegmax.at(i)<<endl;
			}
		cout << wynik;			
	}else{
		cout << "nieotwarlosie";
	}
	return 0;
}
