#include<iostream>
#include<string>
#include<fstream>

int main() {
	std::ifstream infile;
	infile.open("DANE.txt");
	if(infile.is_open()){
		std::string bank;
		int luk1,luk2,luk3;
		int lenght;
		int licznik;
		int wynik = 0;
		while (infile >> bank){
			lenght = bank.size();
			luk1 = std::stoi(bank.substr(0,1));
			luk2 = 0;
			licznik = 1;
			while(licznik < lenght){
				luk3 = std::stoi(bank.substr(licznik,1));
				if(luk3 > luk1 && licznik != lenght - 1) {
					luk1 = luk3;
					luk2 = 0;
				} else { if(luk3 > luk2){
					luk2 = luk3;
				}}
				std::cout << luk1 << luk2 << "\n";
				licznik++;
			}
//			std::cout << luk1 << luk2 << "\n";;
			luk3 = luk1*10 + luk2;
			wynik += luk3;
		}
		std::cout << wynik;
	}else{
		std::cout << "nie otwarlo sie";
	}
	return 0;
}
