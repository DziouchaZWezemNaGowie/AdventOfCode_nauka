#include<iostream>
#include<fstream>
#include<string>

int main() {
    std::ifstream infile; 
	infile.open("DANE.txt");
    if(infile.is_open()){
        long long id_min,id_max;
        int lenght;
        long long wynik = 0;
        std::string first_part,second_part;
        std::string id_string, id_string_min, id_string_max;
        int liczba_znakow;
        int ilosc_czesci,zgad_czesci;
        int zgodnosc = 0;
        while(getline(infile, id_string_min, '-') && getline(infile, id_string_max, ',')){
			id_min = std::stoll(id_string_min);
            id_max = std::stoll(id_string_max);
			while (id_min <= id_max) {
            std::string id_string = std::to_string(id_min);
            lenght = id_string.size();
            liczba_znakow = 1;
            while(liczba_znakow <= lenght/2){
            	first_part = id_string.substr(0, liczba_znakow);
            	second_part = id_string.substr(liczba_znakow, liczba_znakow);
            	ilosc_czesci = 1;
            	zgad_czesci = 1;
            	if(first_part == second_part) {
            		while (second_part != "."){
            			if (first_part == second_part){
            				zgad_czesci++;
						}
					first_part = second_part;
            		ilosc_czesci++;
            		if(liczba_znakow*ilosc_czesci < lenght){
            		second_part = id_string.substr(liczba_znakow*ilosc_czesci, liczba_znakow);
            		}else{
            			second_part = ".";
					}
            		}
            		if (zgad_czesci == ilosc_czesci && second_part=="."){
            			wynik = wynik + id_min;
            			zgodnosc++;
            			std::cout << id_min << zgodnosc << "|";
					}
				}
				if (zgodnosc==1){
					liczba_znakow = 100;
					zgodnosc--;
				}
				liczba_znakow++;
			}
            id_min++;
            }
        }
         std::cout << wynik;
    }else{
        std::cout << "nie otwarlo sie";
    }
    return 0;
}
