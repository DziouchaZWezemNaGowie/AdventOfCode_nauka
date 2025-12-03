#include<iostream>
#include<fstream>
#include<string>
#include<cmath>

int main()
 {
    std::ifstream infile;
    infile.open("DANE_1.txt");
    if(infile.is_open()) 
    {
        std::string read;
        int licz=50;
        int wynik=0;
        char r = 'R';
        int liczba;
        int lenght;
        std::string str_z_liczba;
        int size;
        while (infile >> read )
        {
			size = read.size();
            lenght = size - 1;
            str_z_liczba = read.substr(1,lenght);
            liczba = std::stoi(str_z_liczba);        //wyciagam liczbe
            auto right = read.find(r);              //szukam r
            if (right == std::string::npos) {            //sprawdzam czy nie znalazlo r
				if(licz == 0) {
            	wynik--;
            	std::cout << wynik << "l";
            }
				licz = licz - liczba;
            }else{
                licz = licz + liczba;
            }
            while(licz > 99){
            	if(licz != 100){
            		wynik++;
				}
            	licz = licz - 100;
            	std::cout << wynik << ",";
			}
			while(licz < 0) {
				wynik++;
				licz = licz + 100;
				std::cout << wynik << ".";
			}
            if(licz == 0) {
            	wynik++;
                std::cout << wynik << ";;";
            }
        }
        std::cout << wynik;
    }else{
        std::cout << "nie otwarlo sie";
    }
    return 0;
}
