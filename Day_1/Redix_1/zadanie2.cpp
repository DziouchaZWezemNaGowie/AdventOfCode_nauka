#include <iostream>
#include <vector>
#include <fstream> 

using namespace std; 

int main() {
    ifstream dane("dane.txt"); // plik z danymi
if (!dane.good()) {
        cout << "Dane sie nie wczytaly" << endl;
        return 1;
    } else {  // <--- Tutaj dodalem klamerke przed else
        cout << "dane sie wczytaly" << endl;
    }
    int pozycja = 50; //zgodnie z trescia zadania zaczynamy od 50
    int ilosc_zer = 0; 
    char kierunek; 
    int wartosc;
while (dane >> kierunek >> wartosc) {
        for (int i = 0; i < wartosc; i++) {  //tykanie 
            
            if (kierunek == 'R') { 
                pozycja++;  //przesuwamy w prawo
                if (pozycja == 100) {
                    pozycja = 0; // wskakujemy na 0 od konca
                }
            }
            else if (kierunek == 'L') { 
                pozycja--; // Przesuwamy w lewo
                if (pozycja < 0) {
                    pozycja = 99; // wskakujemy na 0 od poczatku
                }
            }

        
            if (pozycja == 0) {
                ilosc_zer++;
            }
        }
    }

    cout << "Wynik: " << ilosc_zer << endl;

    return 0;
}