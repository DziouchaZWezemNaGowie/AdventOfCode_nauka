### Uwagi do rozwiązania pierwszej części zadania

Zadanie rozwiązane w sposób w pełni poprawny.

Możesz użyć zmiennej pomocniczej, żeby nie musieć wykonywać przeszukiwania kilka razy, tj. zamiast:

```cpp
26				zmin = stoll(z.substr(0,z.find('-')));
27				zmax = stoll(z.substr(z.find('-')+1,z.size()-z.find('-')));
```

możesz napisać

```cpp
        int kreska = z.find('-');
        zmin = stoll(z.substr(0,kreska));
        zmax = stoll(z.substr(kreska + 1, z.size() - kreska));
```

Przy tylko kilku wyszukiwaniach na stosunkowo krótkich danych to nie ma większego znaczenia.

Zamiast nadpisywać indeks tak, żeby był poza zakresem:

```cpp
30					iz = zasieg.size
```

Możesz po prostu użyć polecenia

```cpp
            break;
```

żeby wyjść z pętli.

Poza tym nie mam uwag.

Otrzymujesz **4 punkty** za rozwiązanie pierwszej części zadania.

### Uwagi do rozwiązania drugiej części zadania

Zadanie rozwiązane w sposób w pełni poprawny.

Zamiast zastępować odrzucane zasięgi zerami i zapisywać zera, gdy `zmin > zmax`, możemy po prostu wyrzucać niepotrzebne końcówki zasięgów z wektorów `zasiegmin` i `zasiegmax`. Tj. zamiast:

```cpp
25			for (int iz2=iz-1; iz2>=0;iz2--){
26				if(zasiegmin.at(iz2) >= zmin && zasiegmax.at(iz2) <= zmax){
27					wynik -= zasiegmax.at(iz2) - zasiegmin.at(iz2) + 1;
28					zasiegmax.at(iz2) = 0;
29					zasiegmin.at(iz2) = 0;
30				}else{
31				if (zmin >= zasiegmin.at(iz2) && zmin <= zasiegmax.at(iz2)){
32					zmin = zasiegmax.at(iz2) + 1;
33				}
34				if (zmax <= zasiegmax.at(iz2) && zmax >= zasiegmin.at(iz2)){
35					zmax = zasiegmin.at(iz2) - 1;
36				}
37				}
...
44			}else{
45				zasiegmin.push_back(0);
46				zasiegmax.push_back(0);
47			}
```

Możesz wykorzystać metodę `erase`:

```cpp
            for (int iz2 = zasiegmin.size() - 1; iz2 >= 0; iz2--){             // zaczynamy od zasiegmin.size() - 1, bo teraz rozmiar zasiegmin nie zależy od iz
                if(zmin <= zasiegmin.at(iz2) && zasiegmax.at(iz2) <= zmax){    // zapisałam w innej kolejności, bo tak lepiej widać, co jest między czym
                    wynik -= zasiegmax.at(iz2) - zasiegmin.at(iz2) + 1;
                    zasiegmin.erase(zasiegmin.begin() + iz2);                  // usuwamy element na pozycji iz2
                    zasiegmax.erase(zasiegmax.begin() + iz2);
                } else{
				if (zmin >= zasiegmin.at(iz2) && zmin <= zasiegmax.at(iz2)){
					zmin = zasiegmax.at(iz2) + 1;
				}
				if (zmax <= zasiegmax.at(iz2) && zmax >= zasiegmin.at(iz2)){
					zmax = zasiegmin.at(iz2) - 1;
				}
				}
            }
...
        }
// tego else'a możemy po prostu usunąć
```

Teraz możemy też pozbyć się zwiększania i zmniejszania wyniku

```cpp
27					wynik -= zasiegmax.at(iz2) - zasiegmin.at(iz2) + 1;
...
43			wynik += zmax - zmin + 1; 
```

Możemy usunąć te linijki i po pętli `for` z indeksem `iz` (linijki 21–49) możemy napisać

```cpp
        wynik = accumulate(zasiegmax.begin(), zasiegmax.end(), 0LL) - accumulate(zasiegmin.begin(), zasiegmin.end(),0LL) + zasiegmin.size();
```

W preambule pliku trzeba dodać `#include<numeric>`, żeby `accumulate` działało.

Funkcja `accumulate()` zwraca sumę elementów w wektorze. Wymaga ona od nas podania trzech argumentów: od którego elementu wektora zaczynamy sumowanie, na którym elemencie kończymy oraz wartości początkowej sumy (tutaj wpisujemy `0LL` czyli zero, ale typu `long long` (możesz zobaczyć, co się stanie, gdy dasz tam zwykłe `0`).

Więcej o `accumulate()` możesz przeczytać [tutaj](https://en.cppreference.com/w/cpp/algorithm/accumulate.html) i [tutaj](https://www.geeksforgeeks.org/cpp/accumulate-and-partial_sum-in-c-stl-numeric-header/).

Poza tym nie mam uwag.

Otrzymujesz **4 punkty** za rozwiązanie drugiej części zadania.

### Gratulacje! Zdobyłeś maksimum 8 punktów za rozwiązanie zadania piątego!
