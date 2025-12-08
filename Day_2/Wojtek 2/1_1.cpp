#include<iostream>
#include<fstream>
#include<string>

int main() {
    std::ifstream infile; 
	infile.open("DANE.txt");
    if(infile.is_open()){
        long long id_min,id_max;
        int id_reversed;
        int lenght;
        long long wynik = 0;
        std::string first_half,second_half;
        std::string id_string, id_string_min, id_string_max;
        while(getline(infile, id_string_min, '-') && getline(infile, id_string_max, ',')){
			id_min = std::stoll(id_string_min);
            id_max = std::stoll(id_string_max);
			while (id_min <= id_max) {
            std::string id_string = std::to_string(id_min);
            lenght = id_string.size();
            if(lenght%2 == 0){
            first_half = id_string.substr(0, lenght / 2);
            second_half = id_string.substr(lenght / 2, lenght / 2);
            if (first_half == second_half) {
                wynik = wynik + id_min;
                std::cout << id_min << std::endl;
            }
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
