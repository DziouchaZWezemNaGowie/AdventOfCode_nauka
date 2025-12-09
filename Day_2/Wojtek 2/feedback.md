### Uwagi do rozwiązania pierwszej części zadania:

Zadanie rozwiązane w sposób w pełni poprawny.

Zmiennej

```cpp
10        int id_reversed;
```

w ogóle nie używasz, więc można się jej po prostu pozbyć (pewnie to pozostałość po jakimś starszym rozwiązaniu).

Zmienne `id_string_min` i `id_string_max` są używane tylko przy wczytywaniu danych z pliku, potem od razu zmieniasz je na odpowiednio `id_min` i `id_max` typu `long long`. Zamiast

```cpp
14        std::string id_string, id_string_min, id_string_max;
15        while(getline(infile, id_string_min, '-') && getline(infile, id_string_max, ',')){
16			id_min = std::stoll(id_string_min);
17          id_max = std::stoll(id_string_max);
...
```

mogłeś przypisywać od razu dane z pliku do `id_min` lub `id_max`, np. używając zmiennej pomocniczej, ja tu ją nazwałam `c`:

```cpp
    char c;
    while (infile >> id_min >> c >> id_max >> c){
...
```

albo funkcji składowej (metody) `ignore()` (jest w `iostream`):

```cpp
         while(!infile.eof()){          \\ dopóki nie dojdziemy do końca pliku
            infile >> id_min;
            infile.ignore(1);           \\ ignore(n) -- zignoruj n znaków
            infile >> id_max;           \\ można też użyć ignore(n,znak) wtedy ignoruje wszystko do znaku znak
            infile.ignore(1);           \\ albo n znaków, jeśli do n-tej pozycji znak nie występuje
...
```

Teraz popatrzmy na dalszą część twojego rozwiązania:

```cpp
			while (id_min <= id_max) {
            std::string id_string = std::to_string(id_min);
            lenght = id_string.size();
            if(lenght%2 == 0){
            first_half = id_string.substr(0, lenght / 2);
            second_half = id_string.substr(lenght / 2, lenght / 2);
            if (first_half == second_half) {
                wynik = wynik + id_min;
                std::cout << id_min << std::endl;
            }
            }
            id_min++;
            }
```

Wyobraźmy sobie, że w naszych danych była taka para liczb:

```
111111000000-111111999999
```
