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
    while (dane >> kierunek >> wartosc) { //okreslamy jaki format maja dane w pliku
        if (kierunek == 'R') { //obrot w prawo
            pozycja = pozycja + wartosc;
            while (pozycja >= 100) {
                pozycja = pozycja - 100; // jezeli pozycja przekroczy 100, odedjmujemy 100 od pozycji
            }
        }
        else if (kierunek == 'L') {  // obrot w lewo
            pozycja = pozycja - wartosc;
           while (pozycja < 0) {
                pozycja = pozycja + 100;
            }
        }
        if (pozycja == 0) { // kazde 0 dodaje +1 do zmiennej lcznik_zer
            ilosc_zer++;
        }
    }

    cout << "Wynik: " << ilosc_zer << endl;

    return 0;
}