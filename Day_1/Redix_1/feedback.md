### Uwagi do rozwiązania części pierwszej:

Zadanie rozwiązane w pełni poprawnie.

Zamiast dwóch pętli `while` (dla kierunku równego `'R'` i `'L'`) można było użyć operatora *modulo* – `%` w C++, który zwraca resztę z dzielenia przez liczbę. Tj. zamiast:

```cpp
20        if (kierunek == 'R') { //obrot w prawo
21            pozycja = pozycja + wartosc;
22            while (pozycja >= 100) {
23                pozycja = pozycja - 100; // jezeli pozycja przekroczy 100, odedjmujemy 100 od pozycji
24            }
25        }
26        else if (kierunek == 'L') {  // obrot w lewo
27            pozycja = pozycja - wartosc;
28           while (pozycja < 0) {
29                pozycja = pozycja + 100;
30            }
31        }
```

napisać

```cpp
          if (kierunek == 'R'){            \\ ten nawias klamrowy też można opuścić
            pozycja = pozycja + wartosc;   \\ bo jest tylko jedna rzecz pod ifem
          }
          else if (kierunek == 'L') {      \\ sprawdzanie czy kierunek == 'L' też można sobie podarować
            pozycja = pozycja - wartosc;   \\ bo wiemy, że kierunek równa się tylko 'R' albo 'L'
          }
          pozycja = pozycja % 100;
```

albo krócej

```cpp
          if (kierunek == 'R')
              pozycja = pozycja + wartosc;
          else
              pozycja = pozycja - wartosc;
          pozycja = pozycja % 100;
```

Poza tym kod jest napisany w sposób bardzo czysty i czytelny. Bardzo przyjemnie się go czytało.

Otrzymujesz **4 punkty** za rozwiązanie pierwszej części zadania.
