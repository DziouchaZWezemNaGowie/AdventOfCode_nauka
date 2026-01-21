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
		}
```

Zamiast przypisywać do `mwynik` `1` lub `0`, przypisujemy liczbę w pierwszym wierszu w danej kolumnie, a zmienianie `mwynik` zaczynamy od wiersza drugiego.

Otrzymujesz **4 punkty** za rozwiązanie pierwszej części zadania.
