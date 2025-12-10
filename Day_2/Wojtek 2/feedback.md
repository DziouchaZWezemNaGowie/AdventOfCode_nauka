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

Twój kod sprawdzałby wszystkie liczby w tym zakresie, a więc aż 10 milionów, kiedy w tym przedziale jest tylko jedno nieprawidłowe id, `111111111111`. Proponuję, żeby zamiast sprawdzać kolejne `i`d, wziąć pierwszą połówkę `id_min` i sprawdzić, czy powtórzona dwa razy jest w przedziale <`id_min`, `id_max`> np. tak:

```cpp
            long long first_half_id;
            std::string id_string = std::to_string(id_min);
             lenght = id_string.size();
             if(lenght%2 == 0){
                first_half = id_string.substr(0, lenght / 2);
                first_half_id = std::stoll(first_half);
             }
             else{
                // tu zaraz coś dopiszemy
			 }
             id_string = first_half + first_half;      // + dla dwóch stringów zlepia je ze sobą (konkatenacja)
             long long id = std:: stoll(id_string);    // id_string jako liczba (do porównywania)
             while (id <= id_max){
				if (id >= id_min)
                    wynik = wynik + id;                // do wyniku wliczamy tylko id w przedziale <id_min,id_max>
                first_half_id++;
                first_half = std::to_string(first_half_id);
                id_string = first_half + first_half;
                id = std:: stoll(id_string);
             }
```

Co jeśli `id_string` nie jest parzystej długości? Wtedy wiemy, że `id`, którego szukamy będzie co najmniej o jeden znak dłuższe niż `id_string`. Możemy więc zacząć nasze poszukiwania od najmniejszej liczby, która ma parzystą liczbę cyfr, większej od `id_min`. Jeśli `id_min` jest jednocyfrowe, to taką liczbą jest `10`. Jeśli trzycyfrowe — `1000`, jeśli pięciocyfrowe — `100000` itd. Jak popatrzymy na pierwsze połówki tych liczb, to zawsze wyglądają tak samo: jest to cyfra `1`, a następnie `lenght / 2` (pamiętamy, że dzielenie liczb całkowitych dodatnich zaokrągla nam w dół) zer. Zatem pod `else` możemy wpisać

```cpp
                first_half.assign(lenght / 2, '0');            // same zera lenght/2 razy
                first_half = "1" + first_half;
                first_half_id = std::stoll(first_half);
```

używamy tu metody `assign()`. `first_half.assign(n, c)` tworzy nam stringa składającego się z `n` powtórzeń chara `c`. Jeśli `n == 0`, to tworzy się pusty string.

Jeśli chodzi o złożoność czasową, to taka zmiana znacznie nam ją poprawia. Niech `n` oznacza długość stringa z `id_max`. W twoim rozwiązaniu sprawdzasz wszystkie liczby w przedziale <`id_min`,`id_max`>, więc masz złożoność czasową `O(10^n)`, w poprawionym rozwiązaniu sprawdzasz tylko pierwsze połowy, więc będzie złożoność `O(10^(n/2)) == O(sqrt(10^n))` (sqrt to pierwiastek kwadratowy), czyli poprawione rozwiązanie zajmie ok. pierwiastek czasu twojego pierwotnego rozwiązania 🙂

Jeszcze na koniec uwaga, staraj się nie nazywać zmiennych z błędami w pisowni (`lenght` zamiast `length`), bo potem jak z kimś współpracujesz, to temu komuś jest ciężko, bo albo musi pamiętać, żeby pisać z błędem, albo poprawić twój kod.

Otrzymujesz **4 punkty** za rozwiązanie pierwszej części zadania.
