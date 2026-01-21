#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
int main() {
	ifstream infile;
	infile.open("DANE.txt");
	if (infile.is_open()){
		vector<string> liczby;
		string znaki;
		string liczba;
		int lenght;
		int czy, x, y;
		string znak;
		long long wynik = 0;
		long long mwynik;
		while(getline(infile, liczba, '\n')){
			if(liczba.find('+') == string::npos && liczba.find('*') == string::npos){
			liczby.push_back(liczba);
			}else{
				znaki = liczba;
			}
		}
		lenght = liczby[0].length();
		for(int i = 0; i < znaki.length(); i++){
			znak = znaki[i];
			if (znak == "*" || znak == "+"){
				if(znak == "*"){
					mwynik = 1;
				}else{
					mwynik = 0;
				}
				czy = 0;
				for(int j = 0;czy < liczby.size(); j++){
					czy = 0;
					x = 0;
					for(int k = 0; k < liczby.size(); k++){
						if (liczby[k][i+j] != ' '){
							liczba = liczby[k][i+j];
							y = stoi(liczba);
							x = x * 10 + y;
							
						}else{
						czy++;
						}
					}
					if(znak == "*" && x != 0){
						mwynik = mwynik * x;
					}else if(x != 0){
						mwynik += x;
					}
					if (j == liczby.size() - 1)
					czy = liczby.size();
				}
				cout << mwynik << endl;
				wynik += mwynik;
			}
		}
		cout << wynik;
	}else{
		cout << "nie otwarlo sie";
	}
	return 0;
}
