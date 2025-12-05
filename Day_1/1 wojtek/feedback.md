### Uwagi do pierwszej części zadania:

Zadanie rozwiązane w sposób w pełni poprawny.

Zamiast

```cpp
8    std::ifstream infile;
9    infile.open("3.txt");
```

możesz też napisać

```cpp
  std::ifstream infile.open("3.txt")
```

ale podaję to tylko jako ciekawostkę, tak jak napisałeś też jest OK.

Deklarujesz nowe zmienne, których używasz tylko raz tak naprawdę. Konkretnie zamiast:

```cpp
15  char r = 'R';   // ta zmienna jest kompletnie niepotrzebna
...
26  auto right = read.find(r); // można się kłócić, że psuje to czytelność kodu, bo się człowiek może zastanawiać, co to jest r xd
```

mogłeś napisać

```cpp
  auto right = read.find('R');
```

zamiast

```cpp
18        std::string str_z_liczba;                 // tutaj to nawet nie jest takie złe
...
24            str_z_liczba = read.substr(1,lenght); // poprawia się czytelność
25            liczba = std::stoi(str_z_liczba);     // szczególnie gdy dopiero się uczysz
```

mogłeś napisać

```cpp
            liczba = std::stoi(read.substr(1,lenght));
```

zamiast

```cpp
19        int size;            // lepiej niż r
...
22			size = read.size();    // ale też niepotrzebne
23      lenght = size - 1;
```

mogłeś napisać

```cpp
          lenght = read.size() - 1;
```

i zamiast

```cpp
26            auto right = read.find(r);
27            if (right == std::string::npos) {
...
```

mogłeś napisać

```cpp
          if (read.find('R') == std::string::npos) {
...
```

To wciąż tylko nitpicki. Takie dobre nawyki w programowaniu, bo w dużym programie można się naprawdę pogubić.

Dalej, używasz funkcji składowej (metody) `find` do znajdowania `'R'` w stringu. Metoda `find` przeszukuje cały string, żeby sprawdzić, że nic nie znalazła (wtedy wartością `read.find('R')` jest `std::string::npos`. Tutaj to nie jest duży problem, bo stringi w danych są krótkie, ale gdyby było duuużo danych i dłuuugie stringi, to będzie miało to wpływ na czas wykonywania programu. Możesz wykorzystać fakt, że w C++ `string` to tak naprawdę tablica znaków – `char` i napisać

```cpp
        if (read[0] != 'R'){
...
```

Jest to prostsze i czytelniejsze (w twoim kodzie sprawdzasz, czy `'R'` w ogóle znajduje się w `read`, tutaj, czy string `read` zaczyna się od znaku `'R'`). Złożoność czasowa twojego warunku to O(n) (czyli zależy od długości stringa), a powyższego warunku to O(1) (jest stała i bardzo mała do tego).

Na koniec 2 pętle

```cpp
32            while(licz > 99){
33            	licz = licz - 100;
34            	std::cout << wynik << ",";
35			}
36			while(licz < 0) {
37				licz = licz + 100;
38				std::cout << wynik << ".";
39			}
```

można było wyeliminować korzystając z operatora modulo (który zwraca resztę z dzielenia przez liczbę), który w C++ zapisujemy `%`. Czyli zamiast powyższych dwóch pętli napisać

```cpp
      licz = licz % 100      // reszta z dzielenia licz przez 100
```

Na koniec pochwała dla ciebie, że pamiętałeś o tym, że plik może się nie wczytać (w przeciwieństwie do mnie w zadaniu przykładowym) 😃

Otrzymujesz **4 punkty** za rozwiązanie pierwszej części zadania.

### Uwagi do drugiej części zadania:

Zadanie rozwiązane w sposób w pełni poprawny.

Nie piszę już o problemach, na które zwróciłam uwagę w pierwszej części zadania.

Zamiast odejmować/dodawać `100` w pętlach `while` i liczyć, ile razy trzeba to zrobić, żeby znaleźć się w przedziale `<0,99>`

```cpp
36      while(licz > 99){
37        if(licz != 100){
38          wynik++;
39				}
40        licz = licz - 100;
41        std::cout << wynik << ",";
42			}
43			while(licz < 0) {
44				wynik++;
45				licz = licz + 100;
46				std::cout << wynik << ".";
47			}
```

można było użyć wspomnianego już operatora modulo `%` oraz zwykłego dzielenia `/`, zwracając uwagę na to, jak one działają w C++:

```cpp
// a % b zwraca resztę z dzielenia a przez b z tym samym znakiem co a
// czyli
7 % 5 == 2
-7 % 5 == -2
// wynik a % b jest w przedziale <-b+1,...b-1>

// jeśli powiemy, że wynik dzielenia ma być intem, to działa to tak:
int c = 7 / 2   // wynik 3
int d = -7 / 2  // wynik -3

// wybiera, czy zaokrąglić wynik dzielenia w górę, czy w dół w zależności, co jest bliżej 0
// czyli dla a> 0 int a/b zaokrągla do całości w dół, a dla a<0 w górę
```

Nie działa to do końca tak, jak efekt, który uzyskujesz w pętlach. Dzięki pętlom uzyskujesz `licz` w przedziale <0,99>. Aby wymusić taki wynik trzeba zastosować

```cpp
// aby dostać resztę z dzielenia a przez b w przedziale <0,b> robimy
// (a % b + b) % b
(7 % 5 + 5) % 5 == 2
(-7 % 5 + 5) % 5 == 3
```

można zdefiniować to w funkcji, nazwałam ją `mod`

```cpp
int mod (int a, int b){   // ja jej nie będę używać, bo tylko raz takie modulo będzie nam potrzebne
  (a % b + b) % b         // gdzie indziej sprawdzamy podzielność przez 100 (jak w części 1 zadania)
}                         // do tego wystarczy %
```

Z dzieleniem również jest problem. Po pierwsze, może być ujemne, co łatwo naprawić używając wartości bezwzględnej – funkcja `std::abs()`, Ponieważ `-1 / 100 == 0`, nie wyłapuje nam ono przekroczenia `0` przy zmianie znaku, najłatwiej zrobić to z pomocą `if` i dodaniem brakującej jedynki. Proponuję zastąpić 2 pętle `while` czymś w tym stylu:

```cpp
            if (licz > 99 && licz % 100 == 0) // za warunek w linijce 37
                wynik--;                      // tam nie dodawaliśmy raz, tutaj z dzielenia będziemy mieli to dodanie przy 100, więc trzeba raz odjąć
            if (licz < 0 && licz % 100 != 0)  // poprawa dzielenia dla ujemnych, dla podzielnych przez 100 jest dobrze
                wynik++;
            wynik += std::abs(licz / 100);    // wartość bezwzględna z dzielenia, zapis a += b oznacza a = a + b
            licz = (licz % 100 + 100) % 100;  // reszta w przedziale <0,99>
```

Teraz popatrzmy na warunki

```cpp
          if (licz > 99 && licz % 100 == 0)   // obniżamy wynik o 1 dla podzielnych przez 100 większych od 99 (czyli od 0 tak naprawdę)
            wynik--;
          if (licz < 0 && licz % 100 != 100)  // podwyższamy wynik o 1 dla niepodzielnych przez 100 mniejszych od 0
            wynik++;
...
48            if(licz == 0) {                 // podwyższamy wynik o 1 dla podzielnych przez 100
49            	wynik++;
50                std::cout << wynik << ";;";
51            }
```

Możemy te 3 warunki zastąpić jednym, zwiększającym `wynik` o `1` gdy `licz <= 0`. Tak więc zamiast dwóch pętli `while` możemy napisać

```cpp
            if (licz <=0)
                wynik++;
            wynik += std::abs(licz / 100);
            licz = (licz % 100 + 100) % 100;
```

i usunąć linijki 48–51.

Otrzymujesz **4 punkty** za rozwiązanie drugiej części zadania.

### Gratulacje! Zdobyłeś maksimum 8 punktów za zadanie 1!
