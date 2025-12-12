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
    char c;                                       //to nie działa
    while (infile >> id_min >> c >> id_max >> c){ // działałoby, gdyby w ostatniej linijce był ',' lub inny znak na końcu
...
```

albo funkcji składowej (metody) `ignore()` (jest w `iostream`):

```cpp
         while(!infile.eof()){          // dopóki nie dojdziemy do końca pliku
            infile >> id_min;
            infile.ignore(1);           // ignore(n) -- zignoruj n znaków
            infile >> id_max;           // można też użyć ignore(n,znak) wtedy ignoruje wszystko do znaku znak
            infile.ignore(1);           // albo n znaków, jeśli do n-tej pozycji znak nie występuje
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
				if (id >= id_min)                      // ten if mógłby być teoretycznie przed pętlą, wtedy by było mniej sprawdzania, ale więcej trzebaby było napisać
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

### Uwagi do rozwiązania części drugiej zadania:

Zadanie rozwiązane w sposób poprawny.

Nie piszę już o tym, na co zwracałam uwagę przy pierwszej części zadania, a co w oczywisty sposób możemy przenieść na drugą część.

Będziemy chcieli zmienić poniższy kawałek kodu

```cpp
20			while (id_min <= id_max) {
21            std::string id_string = std::to_string(id_min);
22            lenght = id_string.size();
23            liczba_znakow = 1;
24            while(liczba_znakow <= lenght/2){
25            	first_part = id_string.substr(0, liczba_znakow);
26            	second_part = id_string.substr(liczba_znakow, liczba_znakow);
27            	ilosc_czesci = 1;
28            	zgad_czesci = 1;
29            	if(first_part == second_part) {
30            		while (second_part != "."){
31            			if (first_part == second_part){
32            				zgad_czesci++;
33						}
34					first_part = second_part;
35            		ilosc_czesci++;
36            		if(liczba_znakow*ilosc_czesci < lenght){
37            		second_part = id_string.substr(liczba_znakow*ilosc_czesci, liczba_znakow);
38            		}else{
39            			second_part = ".";
40					}
41            		}
42            		if (zgad_czesci == ilosc_czesci && second_part=="."){
43            			wynik = wynik + id_min;
44            			zgodnosc++;
45            			std::cout << id_min << zgodnosc << "|";
46					}
47				}
48				if (zgodnosc==1){
49					liczba_znakow = 100;
50					zgodnosc--;
51				}
52				liczba_znakow++;
53			}
54            id_min++;
55            }
```

tak abyśmy też nie przechodzili przez kolejne `id` między `id_min` a `id_max`, a tylko kolejne niepoprawne `id`. Najpierw jednak uprościmy trochę powyższy kod. Po pierwsze przypisanie `second_part = "."` (linijka 39) i sprawdzanie, czy `second_part != "."` (linjka 30) możemy sobie podarować i zastąpić warunek z linijki 30 warunkami z linijek  29 i 36, dokładnie:

```cpp
		while (id_min <= id_max) {
			std::string id_string = std::to_string(id_min);
			lenght = id_string.size();
			liczba_znakow = 1;
            while(liczba_znakow <= lenght/2){
            	first_part = id_string.substr(0, liczba_znakow);
            	second_part = id_string.substr(liczba_znakow, liczba_znakow);
            	ilosc_czesci = 1;
            	zgad_czesci = 1;
				while(first_part == second_part && liczba_znakow * ilosc_czesci < lenght){
					zgad_czesci++;
					first_part = second_part;
            		ilosc_czesci++;
            		second_part = id_string.substr(liczba_znakow*ilosc_czesci, liczba_znakow);
				}
				if (liczba_znakow * ilosc_czesci >= lenght){         // jeśli wypadliśmy z pętli, bo przekroczyliśmy lenght, to zwiększamy wynik
					wynik = wynik + id_min;
            			zgodnosc++;
            			std::cout << id_min << zgodnosc << "|";
				}
				if (zgodnosc==1){
					liczba_znakow = 100;
					zgodnosc--;
				}
				liczba_znakow++;
			}
            id_min++;
            }
```

albo w pętli mamy tylko warunek z linijki 29, a warunek `liczba_znakow * ilosc_czesci >= lenght` sprawdzamy wewnątrz pętli i, jeśli jest spełniony, opuszczamy pętle dzięki użyciu polecenia `break`:

```cpp
		while (id_min <= id_max) {
			std::string id_string = std::to_string(id_min);
			lenght = id_string.size();
			liczba_znakow = 1;
            while(liczba_znakow <= lenght/2){
            	first_part = id_string.substr(0, liczba_znakow);
            	second_part = id_string.substr(liczba_znakow, liczba_znakow);
            	ilosc_czesci = 1;
            	zgad_czesci = 1;
				while(first_part == second_part && liczba_znakow * ilosc_czesci < lenght){
					zgad_czesci++;
					first_part = second_part;
            		ilosc_czesci++;
            		second_part = id_string.substr(liczba_znakow*ilosc_czesci, liczba_znakow);
					if (liczba_znakow * ilosc_czesci >= lenght){         // jeśli wypadliśmy z pętli, bo przekroczyliśmy lenght, to zwiększamy wynik
						wynik = wynik + id_min;
            			zgodnosc++;
            			std::cout << id_min << zgodnosc << "|";
						break;
					}
				}
				if (zgodnosc==1){
					liczba_znakow = 100;
					zgodnosc--;
				}
				liczba_znakow++;
			}
            id_min++;
            }
```

Zostańmy jesnak przy pierwszej wersji. Zauważmy, że zmienna `zgad_czesci` nie jest już nam w ogóle potrzebna. Możemy się również pozbyć zgodności i zamiast ustawiać `ilosc_znakow` na dużą liczbę, użyć `break`, a mianowicie:

```cpp
		while (id_min <= id_max) {
			std::string id_string = std::to_string(id_min);
			lenght = id_string.size();
			liczba_znakow = 1;
            while(liczba_znakow <= lenght/2){                     // pętla (*)
            	first_part = id_string.substr(0, liczba_znakow);
            	second_part = id_string.substr(liczba_znakow, liczba_znakow);
            	ilosc_czesci = 1;
				while(first_part == second_part && liczba_znakow * ilosc_czesci < lenght){
					first_part = second_part;
            		ilosc_czesci++;
            		second_part = id_string.substr(liczba_znakow*ilosc_czesci, liczba_znakow);
				}
				if (liczba_znakow * ilosc_czesci >= lenght){
					wynik = wynik + id_min;
					break;                                        //ten break wyrzuca nas z pętli (*)
				}
				liczba_znakow++;
			}
            id_min++;
            }
```

Popatrzmy jeszcze raz na kod, do którego użyliśmy przy rozwiązaniu części pierwszej zadania:

```cpp
            long long first_half_id;
            std::string id_string = std::to_string(id_min);
             lenght = id_string.size();
             if(lenght%2 == 0){
                first_half = id_string.substr(0, lenght / 2);
                first_half_id = std::stoll(first_half);
             }
             else{
				first_half.assign(lenght / 2, '0');
                first_half = "1" + first_half;
                first_half_id = std::stoll(first_half);
			 }
             id_string = first_half + first_half;
             long long id = std:: stoll(id_string);
             while (id <= id_max){
				if (id >= id_min)                      
                    wynik = wynik + id;
                first_half_id++;
                first_half = std::to_string(first_half_id);
                id_string = first_half + first_half;
                id = std:: stoll(id_string);
             }
```

Naiwnie moglibyśmy zmienić ten kod, aby dostosować go do drugiej części zadania w następujący sposób:

```cpp
// pójdziemy po ilości części, żeby było podobnie do pierwszej części zadania
			ilosc_czesci = 2;                                   // zaczynamy od dwóch części
			ilosc_czesci_max = (std::to_string(id_max)).size(); // maksymalnie będzie tyle części, jak długie jest id_max
			long long first_part_id;
            while(ilosc_czesci <= ilosc_czesci_max){
				id_string = std::to_string(id_min);
				lenght = id_string.size();
				int liczba_znakow = lenght / ilosc_czesci; //liczbę znaków też daję, żeby łatwiej się czytało.
             	if(lenght % ilosc_czesci == 0){
                	first_part = id_string.substr(0, liczba_znakow);
                	first_part_id = std::stoll(first_part);
             	}
            	else{
					first_part.assign(liczba_znakow, '0');
                	first_part = "1" + first_part;
                	first_part_id = std::stoll(first_part);
			 	}
             	id_string = first_part;
				for(int i = 1; i < ilosc_czesci; i++)
					id_string += first_part;
             	long long id = std:: stoll(id_string);
				while (id <= id_max){
					if (id >= id_min)                      
                    	wynik = wynik + id;
                	first_part_id++;
                	first_part = std::to_string(first_part_id);
                	id_string = first_part;
					for(int i = 1; i< ilosc_czesci; i++)
						id_string += first_part;
                	id = std:: stoll(id_string);
             	}
				ilosc_czesci++;
			}
```

Niestety, takie rozwiązanie nie działa — jeśli mamy np. `111111`, to policzy nam ją 3 razy: przy podziale na 6, 3 i 2 części. Ja w swoich rozwiązania po prostu trzymałam wszystko w jednym wektorze i na końcu brałam z niego unikalne wartości i sumowałam. Tu możemy zrobić coś podobnego.

```cpp
			string wektor[];                                  // to tablica stringów
			ilosc_czesci = 2;                                   
			ilosc_czesci_max = (std::to_string(id_max)).size();
			long long first_part_id;
            while(ilosc_czesci <= ilosc_czesci_max){
				id_string = std::to_string(id_min);
				lenght = id_string.size();
				int liczba_znakow = lenght / ilosc_czesci;
             	if(lenght % ilosc_czesci == 0){
                	first_part = id_string.substr(0, liczba_znakow);
                	first_part_id = std::stoll(first_part);
             	}
            	else{
					first_part.assign(liczba_znakow, '0');
                	first_part = "1" + first_part;
                	first_part_id = std::stoll(first_part);
			 	}
             	id_string = first_part;
				for(int i = 1; i < ilosc_czesci; i++)
					id_string += first_part;
             	long long id = std:: stoll(id_string);
				while (id <= id_max){
					if (id >= id_min){
						if(find(wektor.begin(), wektor.end(), id_string) == wektor.end())    // jeśli id_string nie ma w wektorze            
                    		wektor.push_back(id_string);                                     // dołóż id_string do wektora
					}
                	first_part_id++;
                	first_part = std::to_string(first_part_id);
                	id_string = first_part * ilosc_czesci;
                	id = std:: stoll(id_string);
             	}
				ilosc_czesci++;
			}
			for(int i = 0, i < wektor.size(); i++
				wynik += std::stoll(wektor[i]);
```

Alternatywnie można też wykonywać kod z poprzedniego kawałka kodu tylko wtedy, gdy `ilosc_czesci` jest liczbą pierwszą.

Otrzymujesz **4 punkty** za rozwiązanie drugiej części zadania.

### Gratulacje! Zdobyłeś maksimum 8 punktów za zadanie drugie!
