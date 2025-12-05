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
          if (kierunek == 'R'){
            pozycja = pozycja + wartosc;
          }
          else if (kierunek == 'L') {      // sprawdzanie czy kierunek == 'L' można sobie podarować
            pozycja = pozycja - wartosc;   // bo wiemy, że kierunek równa się tylko 'R' albo 'L'
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

### Uwagi do drugiej części zadania:

Zadanie rozwiązane w pełni poprawnie.

Twoje rozwiązanie bardzo dobrze oddaje ideę zawartą w treści zadania, ale jest bardzo czasochłonne.

Nasze dane były stosunkowo małe, więc nie było tego widać, ale twoje rozwiązanie wykorzystuje pętlę `for`:

```cpp
20        for (int i = 0; i < wartosc; i++) {  //tykanie 
21            
22            if (kierunek == 'R') { 
23                pozycja++;  //przesuwamy w prawo
24                if (pozycja == 100) {
25                    pozycja = 0; // wskakujemy na 0 od konca
26                }
27            }
28            else if (kierunek == 'L') { 
29                pozycja--; // Przesuwamy w lewo
30                if (pozycja < 0) {
31                    pozycja = 99; // wskakujemy na 0 od poczatku
32                }
33            }
34
35        
36            if (pozycja == 0) {
37                ilosc_zer++;
38            }
39        }
```

przechodzisz iteratorem `i` od `0` do `wartosc`, więc twoje rozwiązanie jest mocno zależne od tego, jak duża jest wartość — ma złożoność czasową O(n) -- zależną od `n = wartosc`.

Do tego przechodzisz kolejno każdą z pozycji od `1` do `99`, mimo że tam nie może być `0`. Zauważyli to Wojtek i Wiktor, w ich rozwiązaniach pokrętło "przeskakiwało" o `100` i liczyli ile takich przeskoków pokrętło wykona. Ich rozwiązania wciąż mają złożoność O(n), tj. zależą bezpośrednio od tego, o jaką wartość trzeba było pokrętło obrócić, ale jest `k * 100` razy szybsze (`k` to stosunek liczby operacji w twojej pętli do liczby operacji w ich, sorry, matematyk ze mnie wychodzi)

Ale, liczenie ile razy liczba `100` mieści się w innej liczbie to tak naprawdę dzielenie! Więc zamiast pętli `for` można było napisać:

```cpp
          if (kierunek == 'R')
              pozycja = pozycja + wartosc;
          else
              pozycja = pozycja - wartosc;

          ilosc_zer = ilosc_zer + abs(licz / 100);  // objaśniam kod poniżej
          pozycja = (pozycja % 100 + 100) % 100;    // a to jeszcze niżej
```

Takie rozwiązanie ma złożoność O(1), czyli stałą, nie zależy od tego, jak duża jest `wartosc`.

Dzielenie w C++ dopasowuje się do typu zmiennej, więc skoro wcześniej zadeklarowałeś

```cpp
16    int ilosc_zer = 0;
```

to dzielenie w równaniu zmieniającym wartość zmiennej `ilosc_zer` "domyśli się", że chcesz, aby wynik dzielenia był liczbą całkowitą, innym słowem typu `int`.

Dzielenie to działa w następujący sposób:

```cpp
// jeśli powiemy, że wynik dzielenia ma być intem, to działa to tak:
int c = 7 / 2   // wynik 3
int d = -7 / 2  // wynik -3
```

dzielenie zaokrągla od prawdziwego wyniku dzielenia, jeśli jest on dodatni w dół, a jeśli ujemny — w górę, innymi słowy do liczby bliższej `0`.

*Działa to trochę inaczej niż operator dzielenia całkowitego w Pythonie – `//`. W Pythonie `7 // 2 == 3`, a `-7 // 2 == -4`.*

Wartość dzielenia dajemy do funkcji `abs()`, czyli wartości bezwzględnej.

Musimy wziąć poprawkę na to, że dzielenie liczby ujemne zaokrągla w górę. Jeśli startowaliśmy z pozycji między `1` a `99`, a po odjęciu wartości pozycja jest równa `-3`, to znaczy, że minęliśmy `0` raz, a dzielenie `-3/100` da nam wynik `0`! Z kolei jeśli startowaliśmy z pozycji `0`, to rzeczywiście minęliśmy `0` 0 razy. Do naszego kodu musimy dodać poprawki, chyba prościej niż jak zrobiłam poniżej się zrobić nie da:

```cpp
          if (kierunek == 'R')
              pozycja = pozycja + wartosc;
          else{
              if (pozycja == 0)                     // jak idziemy z zera, to dzielenia nie trzeba poprawiać
                   ilosc_zer--;
              pozycja = pozycja - wartosc;
          }

          if (pozycja <= 0)                         // równość, bo jak zeszliśmy z 50 na 0, to dzielenie też tego nie widzi
              ilosc_zer++;                          // poprawiamy to, czego dzielenie nie wyłapało

          ilosc_zer = ilosc_zer + abs(licz / 100);
          pozycja = (pozycja % 100 + 100) % 100;    // objaśnienia tego poniżej
```

W ostatniej linijce chcemy, żeby `pozycja` była liczbą z przedziału <0,99>. Niestety, w C++ modulo działa tak:

```cpp
// a % b zwraca resztę z dzielenia a przez b z tym samym znakiem co a
// czyli
7 % 5 == 2
-7 % 5 == -2
// wynik a % b jest w przedziale <-b+1,...b-1>
```

dlatego, aby uzyskać liczbę z przedziału <0,99> musimy dodać `100`, aby przejść z przedziału <-99,-1> do <1,99> i jeszcze raz wziąć całość modulo `100`, bo jeśli `pozycja % 100` była w przedziale <0,99>, to teraz jest w przedziale <100,199>.

*Modulo w wielu innych językach działa inaczej. Np. w Pythonie, gdzie modulo też oznacza się przez `%` jest `7 % 5 == 2` i `-7 % 5 == 3`*

Otrzymujesz **4 punkty** za rozwiązanie drugiej części zadania.

### Gratulacje! Zdobyłeś maksimum 8 punktów za zadanie 1!
