#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream dane("dane.txt"); 
    if (!dane.good()) {
        cout << " Nie mozna otworzyc danych" << endl;
        return 1;
    }

    long long suma = 0;
    string linia;

    while (dane >> linia) {
        
        int max_napiecie = -1; 
        int dlugosc = linia.length();


        for (int i = 0; i < dlugosc - 1; i++) {
        
            for (int j = i + 1; j < dlugosc; j++) {
                
              
                int pierwsza = linia[i] - '0'; 
                int druga = linia[j] - '0';

             
                int liczba = pierwsza * 10 + druga;

             
                if (liczba > max_napiecie) {
                    max_napiecie = liczba;
                }
            }
        }

       
        suma += max_napiecie;
    }

    cout << "Całkowite Napięcie:  " << suma << endl;

    return 0;
}