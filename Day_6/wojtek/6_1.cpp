#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
int main() {
	ifstream infile;
	infile.open("DANE.txt");
	if (infile.is_open()){
		vector<int> liczby;
		vector<string> znaki;
		string liczba;
		int y;
		string znak;
		long long wynik = 0;
		long long mwynik;
		while(infile >> liczba){
			if(liczba.find('+') == string::npos && liczba.find('*') == string::npos){
				liczby.push_back(stoi(liczba));
			}else{
				znaki.push_back(liczba);
			}
		}
		for(int i = 0; i<znaki.size(); i++){
			znak = znaki.at(i)[0];
			if (znak == "*"){
				mwynik = 1;
			}else{
				mwynik = 0;
			}
			for (int i2 = 0; i2 < liczby.size(); i2 += znaki.size()){
				y = liczby.at(i2 + i);
				if (znak == "+"){
					mwynik += y;
				}else{
					mwynik = mwynik * y;
				}
			}
			wynik += mwynik;	
		}
		cout << wynik;
	}else{
		cout << "nie otwarlo sie";
	}
	return 0;
}
