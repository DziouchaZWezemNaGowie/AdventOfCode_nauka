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

    unsigned long long suma = 0;
    string linia;

    while (dane >> linia) {
        
        string wynik = "";      
        int od = 0;     
        int dlugosc = linia.length();
        int do_znalezienia = 12; 

        
        for (int k = 0; k < 12; k++) {
            
          
            char max_cyfra = -1;
            int max_index = -1;

         
            int zostawic = 11 - k;

            for (int i = od; i <= dlugosc - 1 - zostawic; i++) {

         
               if (linia[i] > max_cyfra) {
                    max_cyfra = linia[i];
                    max_index = i;
                }
            }
        
    
        wynik += max_cyfra; 
        
     
        od = max_index + 1;
            suma += stoull(wynik);
    }

    cout << "Całkowite Napięcie:  " << suma << endl;

    return 0;
}
}