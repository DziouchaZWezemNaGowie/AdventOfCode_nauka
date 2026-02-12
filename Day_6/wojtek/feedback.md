### Omówienie rozwiązania pierwszej części zadania:

Na początek przyjrzyjmy się zmiennym globalnym:

```cpp
10		vector<int> liczby;
11		vector<string> znaki;
12		string liczba;
13		int y;
14		string znak;
15		long long wynik = 0;
16		long long mwynik;
```

Zmienna `znaki` to tak naprawdę wektor jednoznakowych stringów. Nie ma co więc bawić się ze stringami, i możemy po prostu używać typu `char`. (`char` zajmuje mniej pamięci niż jednoelementowy `string`, nie są to też cyfry, więc nie musisz się martwić, że będą ci potrzebne potem funkcje jak `stoi`). Więc lepiej będzie zrobić:

```cpp
  vector<char> znaki;
```

Albo po prostu

```cpp
  string znaki;
```

bo w końcu string to ciąg charów.

Zmienne `y` i `znak` są potrzebne nam tylko w konkretnych miejscach, więc możemy je deklarować tam, gdzie ich potrzebujemy jako zmienne lokalne.

Dalej wczytujemy dane:

```cpp
17		while(infile >> liczba){
18			if(liczba.find('+') == string::npos && liczba.find('*') == string::npos){
19				liczby.push_back(stoi(liczba));
20			}else{
21				znaki.push_back(liczba);
22			}
23		}
```

Możemy wykorzystać fakt, że plusy i gwiazdki są tylko w ostatniej linijce z pomocą `getline` (to pokażę w omówieniu drugiej części). Zamiast tego możemy lekko poprawić twój kod, proponuję zrobić coś takiego:

```cpp
		vector<int> liczby;
		string znaki;           // zmieniliśmy na string
		string liczba;
		//int y;                // wprowadzimy go potem lokalnie
		char znak;              // przyda nam się jednak przy wczytywaniu, ale może to być nowa zmienna, inna od lokalnego znak (wszystko jedno)
		long long wynik = 0;
		long long mwynik;
		while (infile >> liczba && liczba != "+" && liczba != "*"){
            liczby.push_back(stoi(liczba));
        }
        znaki = liczba;
        while (infile >> znak){
            znaki.push_back(znak);
        }
```

Wykorzystaliśmy fakt, że od pewnego miejsca w pliku nie mamy już liczb, "przełamując" pętlę `while` w momencie gdy napotkamy `"+"` lub `"*"`. Zamiast używać kosztownego czasowo `find` używamy po prostu `==` (nie musi wtedy sprawdzać liczby znak po znaku).

Po pierwszej pętli `while` `liczba` jest równa `"+"` lub `"*"` – to pierwszy niebiały znak w ostatniej linijce. Wskaźnik pilnujący nam gdzie jesteśmy przy wczytywaniu pliku jest za tym znakiem. Dalej wczytujemy już kolejne chary i dopisujemy je do stringa `znaki`.

Dalej mamy taki kod z linijek 24–40, po poprawieniu, aby działało dla `char znak` i zmienieniu `y` na zmienną lokalną:

```cpp
        for(int i = 0; i<znaki.size(); i++){   // możesz dodać zmienną int n = znaki.size(), bo wywołujesz to kilka razy -- większa czytelność + szybciej
			znak = znaki.at(i);
			if (znak == '*'){                        // tego
				mwynik = 1;                            // kodu
			}else{                                   // można
				mwynik = 0;                            // się
			}                                        // pozbyć
			for (int i2 = 0; i2 < liczby.size(); i2 += znaki.size()){
				int y = liczby.at(i2 + i);
				if (znak == '+'){
					mwynik += y;
				}else{
					mwynik = mwynik * y;                 // możesz też napisać mwynik *= y;
				}
			}
			wynik += mwynik;	
		}
```

Możemy pozbyć się zaznaczonego pięknie przeze mnie kawałka kodu zaczynając wewnętrzną pętlę `for` od `n = znaki.size()`:

```cpp
        int n = znaki.size();
        for(int i = 0; i<n; i++){
			znak = znaki.at(i);                    
            long long mwynik = liczby.at(i);               // przy okazji zmieniłam mwynik na zmienną lokalną, usunęłam jej deklarację wyżej
			for (int i2 = n; i2 < liczby.size(); i2 += n){
				int y = liczby.at(i2 + i);
				if (znak == '+'){
					mwynik += y;
				}else{
					mwynik = mwynik * y;
				}
			}
			wynik += mwynik;
```

Zamiast przypisywać do `mwynik` `1` lub `0`, przypisujemy liczbę w pierwszym wierszu w danej kolumnie, a zmienianie `mwynik` zaczynamy od wiersza drugiego.		

Otrzymujesz **4 punkty** za rozwiązanie pierwszej części zadania.

### Omówienie rozwiązania drugiej części zadania.

Zadanie nie jest rozwiązane w sposób poprawny.

Przeanalizujmy kod od początku do końca z moimi typowymi uwagami, aż dojdziemy do miejsca, w którym jest błąd.

Zmienne `czy, x, y, znak, mwynik` są wykorzystywane w środku pętli, więc można je tam wprowadzić. Znów `znak` lepiej zrobić jako `char`, tym bardziej, że póżniej masz `znak = znaki[i];`.

Przyjrzyjmy się wczytywaniu danych:

```cpp
18		while(getline(infile, liczba, '\n')){                                          //to '\n' jest tu niepotrzebne
19			if(liczba.find('+') == string::npos && liczba.find('*') == string::npos){
20			liczby.push_back(liczba);
21			}else{
22				znaki = liczba;
23			}
24		}
```

zamiast sprawdzać w każdej linijce, czy w `liczba` znajdują się znaki `'+'` lub `'*'`, możemy wykorzystać fakt, że operatory są w ostatniej linijce w pliku:

```cpp
		while(getline(infile, liczba)){
			liczby.push_back(liczba);
		}
		znaki = liczby.back();
		liczby.pop_back();
```

metoda `back()` zwraca ostatni element wektora, a `pop_back()` usuwa ostatni element w wektorze.

Dalej masz zmienną `lenght`, której potem w ogóle nie używasz.

```cpp
25		lenght = liczby[0].length();
```

Jest ona równa `znaki.lenght()`, więc żeby nie marnować pracy, którą włożyłeś w napisanie linijki 25, będę z tej zmiennej korzystać w moich sugestiach.

Dalej mam uwagi do tej pętli:

```cpp
35				for(int j = 0;czy < liczby.size(); j++){
36  				czy = 0;
37					x = 0;
38					for(int k = 0; k < liczby.size(); k++){
39						if (liczby[k][i+j] == '1' || liczby[k][i+j] == '2' || liczby[k][i+j] == '3' || liczby[k][i+j] == '4' || liczby[k][i+j] == '5' || liczby[k][i+j] == '6' || liczby[k][i+j] == '7' || liczby[k][i+j] == '8' || liczby[k][i+j] == '9' || liczby[k][i+j] == '0'){
40							liczba = liczby[k][i+j];
41							y = stoi(liczba);
42							x = x * 10 + y;
43							
44						}else{
45						czy++;
46						}
47					}
48					if(znak == "*" && x != 0){
49						mwynik = mwynik * x;
50					}else if(x != 0){
51						mwynik += x;
52					}
53					if (j == liczby.size() - 1)
54					czy = liczby.size();
55				}
56				cout << mwynik << endl;
57				wynik += mwynik;
58			}
```

Są tu 2 błędy, które sprawiają, że twoje rozwiązanie jest niepoprawne.

Najpierw przyjrzyjmy się logice pętli. Mamy wyjść z pętli w dwóch przypadkach:
- gdy `czy >= liczby.size()`, czyli kiedy w jednej z kolumn będą same spacje ✔️ to jest dobrze
- gdy `j == liczby.size() - 1`, a dzieje się tak wtedy gdy sprawdzana przez nas "wieża" jest szersza niż `liczby.size()

np. dla inputu
```
11111
11111
11111
11111
+
```

twój program zwraca `4444` zamiast `5555`.

Warunek `j == liczby.size() - 1` zapewne dodałeś, żeby wychodzić z pętli gdy dojdziemy do ostatniej kolumny. Jest tak, gdy `i + j == lenght - 1` 🙂

Kolejny problem leży w linijkach 48–52. Nie zmieniasz zmiennej `mwynik` jeśli `x == 0`, a może tak się zdarzyć, gdy
- przeszliśmy przez kolumnę samych spacji (i skuli tego przypadku dodałeś ten warunek)
- w danych naprawdę mamy zero

dlatego dla inputu

```
110
20 
3  
*
```

Twój program da odpowiedź `1230` zamiast `0`.

Poniżej prezentuję, jakbym poprawiła twój kod, opisując zmiany w komentarzach.

```cpp
				for(int j = 0; i + j < lenght; j++){        // sprawdzamy w warunku pętli, czy nie doszliśmy do końca wiersza
					int czy = 0;                            // teraz można czy = 0 sprzed pętli usunąć
					int x = 0;                              // jak widzisz przeniosłam deklaracje zmiennych tam gdzie ich używamy
					for(int k = 0; k < liczby.size(); k++){
						if (liczby[k][i+j] != ' '){         // tu wystarczy sprawdzić, czy != ' ' zamiast tego długiego warunku xd
							liczba = liczby[k][i+j];
							x = x * 10 + stoi(liczba);	    // pozbyłam się y
						}else{
							czy++;
						}
					}
					if (czy == liczby.size()){              // zaraz po przejściu przez kolumnę sprawdzam, czy nie była wypełniona spacjami
						break;                              // break wyrzuca nas z najbardziej wewnętrznej pętli. Lepiej robić tak, niż warunkiem
					}                                       // też sprawdzam to tutaj, żeby od razu wyjść z pętli, gdy dojdziemy do kolumny spacji
					if(znak == '*'){                        // tutaj już x == 0 tylko gdy tak było w danych
						mwynik = mwynik * x;                // jak była kolumna spacji, to nie dochodzimy tutaj, bo wyskoczyliśmy z pętli breakiem
					}else{                                  // zauważ też, że zrobiłam znak jako char
						mwynik += x;                        // oczywiście wyżej w kodzie pozmieniałam wszystko, żeby znak był typu char
					}
				}
```

Otrzymujesz **2punkty** za rozwiązanie drugiej części zadania.

### Brawo! Zdobyłeś razem 6 punktów za zadanie szóste!
