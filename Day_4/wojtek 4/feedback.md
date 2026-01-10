### Uwagi do rozwiązania pierwszej części zadania

Zadanie rozwiązane w sposób poprawny.

Na początek mam 3 małe uwagi:

- Kiedy potrzebujesz tylko sprawdzić, jaki jest znak w stringu, to lepiej zamiast np. `l1.substr(i,1)` jest wykorzystać fakt, że string to tablica znaków i dostać się do znaku przy pomocy nawiasów kwadratowych: `l1[i]` lub wykorzystać metodę `.at()`: `l1.at(i)`. Jest to bardziej wydajne (`substr` tworzy nowego stringa) i ma więcej sensu, stąd jak ktoś inny (lub ty z przyszłości) będzie czytać twój kod, to łatwiej mu będzie zrozumieć, o co ci chodziło.
- Bardziej czytelne od pętli `while`, która robi to, co pętla `for`, jest po prostu użycie pętli `for`. Do tego przy pętli `for` iterator jest zmienną lokalną (jego zasięg to tylko ta pętla `for`).
- Lepiej, żeby zmienne występowały tylko tam, gdzie są potrzebne, czyli nie miały za dużego zasięgu (scope). Nie zajmujesz nimi wtedy pamięci przez cały czas programu, a tylko wtedy, gdy to potrzebne, no i nie musisz pamiętać, żeby zerować ich wartości. Chodzi mi konkretnie o zmienne `i` (która wystarczy, że będzie typu `int`, a nie `long long`) oraz `paper`.

Po poprawieniu twojego kodu według tych uwag dostaniemy coś takiego:

```cpp
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main(){
    ifstream infile;
	infile.open("DANE.txt");
	if(infile.is_open()){
        string l1,l2,l3;
        int wynik=0;
        infile >> l1 >> l2;
        cout << l1;
        for(int i = 0; i<l1.size(); i++){
        	if(l1[i]=='@'){                  // pojedynczy cudzysłów, bo mamy znak
        		if (i==0){
        			wynik++;
				}else if (i==l1.size()-1){
					wynik++;
				}else{
          int paper = 0;
					if(l1[i-1]=='@'){
						paper++;
					}
					if(l1[i+1]=='@'){
						paper++;
					}
					if(l2[i-1]=='@'){
						paper++;
					}
					if(l2[i]=='@'){
						paper++;
					}
					if(l2[i+1]=='@'){
						paper++;
					}
					if (paper<4){
						wynik++;
					}
				}
			}
      // już nie trzeba zerować paper i robić i++
		}
		cout << wynik;
		while(infile >> l3){
			for(int i = 0; i<l2.size(); i++){
                int paper = 0;
            	if (l2[i]=='@'){
					if (i==0){
        				if(l1[i]=='@'){
							paper++;
						}
						if(l1[i+1]=='@'){
							paper++;
						}
						if(l2[i+1]=='@'){
							paper++;
						}
						if(l3[i]=='@'){
							paper++;
						}
						if(l3[i+1]=='@'){
							paper++;
						}
						if (paper<4){
							wynik++;
						}
					}else if (i==l1.size()-1){
						if(l1[i-1]=='@'){
							paper++;
						}
						if(l1[i]=='@'){
							paper++;
						}
						if(l2[i-1]=='@'){
							paper++;
						}
                        if(l3[i-1]=='@'){
                            paper++;
                        }
						if(l3[i]=='@'){
							paper++;
						}
						if (paper<4){
							wynik++;
						}
					}else{
						if(l1[i-1]=='@'){
							paper++;
						}
						if(l1[i]=='@'){
							paper++;
						}
						if(l1[i+1]=='@'){
							paper++;
						}
						if(l2[i-1]=='@'){
							paper++;
						}
						if(l2[i+1]=='@'){
							paper++;
						}
						if(l3[i-1]=='@'){
							paper++;
						}
						if(l3[i]=='@'){
							paper++;
						}
						if(l3[i+1]=='@'){
							paper++;
						}
						if (paper<4){
							wynik++;
							cout << "l" << i;
						}
					}
				}
			}
        	l1=l2;
        	l2=l3;
        	 cout << "|" << wynik;
		}
		for(int i = 0; i<l3.size(); i++){
			if(l3[i]=='@'){
                int paper = 0;
				if (i==0){
        			wynik++;
				}else if (i==l1.size()-1){
					wynik++;
				}else{
					if(l1[i-1]=='@'){
						paper++;
					}
					if(l1[i]=='@'){
						paper++;
					}
					if(l1[i+1]=='@'){
						paper++;
					}
					if(l3[i-1]=='@'){
						paper++;
					}
					if(l3[i+1]=='@'){
						paper++;
					}
					if (paper<4){
						wynik++;
						cout << "l" << i;
					}
				}
			}
		}
        cout << "|" << wynik;
    }else{
        cout << "nie otwarlo sie";
    }
}
```

Dalej możemy pozbyć się tej gigantycznej liczby ifów, zmieniając lekko kolejność warunków. Zmieniamy tylko pętlę `while(infile>>l3)`:

```cpp
		while(infile >> l3){
			for(int i = 0; i<l2.size(); i++){
                int paper = 0;
            	if (l2[i]=='@'){
                        if(i != 0){
                            if(l1[i-1]=='@'){
							    paper++;
						    }
                            if(l2[i-1]=='@'){
							    paper++;
						    }
                            if(l3[i-1]=='@'){
							    paper++;
						    }
                        }
                        if(i != l1.size() - 1){
                            if(l1[i+1]=='@'){
							    paper++;
						    }
						    if(l2[i+1]=='@'){
							    paper++;
						    }
                            if(l3[i+1]=='@'){
							    paper++;
						    }
                        }
						if(l1[i]=='@'){
							paper++;
						}

						if(l3[i]=='@'){
							paper++;
						}
						if (paper<4){
							wynik++;
							cout << "l" << i;
						}
				}
			}
        	l1=l2;
        	l2=l3;
          cout << "|" << wynik;
		}
```

A najbardziej czytelnie i z jeszcze mniejszą liczbą ifów overall, będzie, gdy wrzucimy zliczanie sąsiednich rolek papieru do osobnej funkcji:

```cpp
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int sasiedzi(string l1, string l2, string l3){
    int wynik=0;

	for(int i = 0; i<l2.size(); i++){
        int paper = 0;
        if (l2[i]=='@'){
            if(!l1.empty()){
                if(i!=0 && l1[i-1]=='@'){
					paper++;
				}
                if(i != l2.size() - 1 && l1[i+1]=='@'){
					paper++;
				}
                if(l1[i]=='@'){
					paper++;
				}
            }
            if(!l3.empty()){
                if(i != 0 && l3[i-1]=='@'){
					paper++;
				}
                if(i != l2.size() - 1 && l3[i+1]=='@'){
					paper++;
				}
                if(l3[i]=='@'){
					paper++;
				}
            }
            if(i != 0 && l2[i-1]=='@'){
				paper++;
			}
            if(i != l2.size() - 1 && l2[i+1]=='@'){
				paper++;
			}
            if(paper < 4){
                wynik ++;
            }
		}
	}

    return wynik;
}

int main(){
    ifstream infile;
	infile.open("DANE.txt");
	if(infile.is_open()){
        string l1,l2,l3;
        int wynik=0;

        infile >> l1 >> l2;
        wynik += sasiedzi("", l1, l2);

		while(infile >> l3){
            wynik += sasiedzi(l1,l2,l3);
        	l1=l2;
        	l2=l3;
		}

        wynik += sasiedzi(l1,l3,"");
        cout << wynik;

    }else{
        cout << "nie otwarlo sie";
    }
}
```

Metoda `.empty()` sprawdza, czy string jest pusty.

### Otrzymujesz 4 punkty za rozwiązanie pierwszej części zadania.
