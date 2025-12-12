#include <iostream>
#include <fstream>
#include <string> 

using namespace std;
bool zleid(long long liczba) {
    string s = to_string(liczba);
    int dlugosc = s.length();
    for (int d = 1; d <= dlugosc / 2; d++) {
        if (dlugosc % d == 0) {      
            string czesc = s.substr(0, d);      
            string proba = "";
            int ile_powtorzen = dlugosc / d;
            
            for (int k = 0; k < ile_powtorzen; k++) {
                proba += czesc;
            }

            if (proba == s) {
                return true; 
            }
        }
    }
    return false; 
}
int main() {
    ifstream dane("dane.txt"); 
    if (!dane.good()) {
        cout << "Nie można otworzyć pliku z danymi." << endl;
        return 1;
    }
    long long suma = 0; 
    long long start, koniec;
    char myslnik, przecinek;

    while (dane >> start >> myslnik >> koniec) {
        for (long long i = start; i <= koniec; i++) {
            if (zleid(i)) {
                suma += i;
            }
        }
        if (dane.peek() == ',') {
            dane >> przecinek; 
        }
    }
    cout << "Suma złych id: " << suma << endl;

    return 0;
}