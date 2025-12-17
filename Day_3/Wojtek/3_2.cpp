#include<iostream>
#include<string>
#include<fstream>

int main() {
	std::ifstream infile;
	infile.open("DANE.txt");
	if(infile.is_open()){
		std::string bank;
		std::string lukstr;
		std::string luk1str;
		int pozycja;
		long long luk3;
		int luk1,luk2;
		int lenght;
		int licznik;
		long long wynik = 0;
		while (infile >> bank){
			lukstr.erase();
			pozycja = 0;
//			std::cout << "lukasz:" << lukstr.size() << "\n";
			while (lukstr.size() < 12){
			lenght = bank.size();
			luk1 = 0;
			licznik = 0 + pozycja;
			while(licznik < lenght - 11 + lukstr.size()){
				luk2 = std::stoi(bank.substr(licznik,1));
				if(luk2 > luk1) {
					luk1 = luk2;
					pozycja = licznik + 1;
				}
//				std::cout << "l" << lukstr << "\n";
				licznik++;
			}
			std::cout << luk1 << "\n";
			luk1str = std::to_string(luk1);
			lukstr.append(luk1str);
			}
//			std::cout << luk1 << luk2 << "\n";;
			luk3 = stoll(lukstr);
//			std::cout << luk3 << "\n";
			wynik += luk3;
		}
		std::cout << wynik;
	}else{
		std::cout << "nie otwarlo sie";
	}
	return 0;
}
