#include <iostream>
#include <fstream>
#include <string> 

using namespace std;


bool podzielnosc(long long liczba) {
    string s = to_string(liczba);
    if (s.length() % 2 != 0) {
        return false;
    }
    int polowa = s.length() / 2;
    string czesc1 = s.substr(0, polowa); 
    string czesc2 = s.substr(polowa);    
    if (czesc1 == czesc2) {
        return true; 
    } else {
        return false;
    }
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
            if (podzielnosc(i)) {
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