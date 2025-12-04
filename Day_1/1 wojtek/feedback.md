### Uwagi do pierwszej części zadania:

Zadanie rozwiązane w sposób poprawny.

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
