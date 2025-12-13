### Uwagi do rozwiązania pierwszej części zadania

Zadanie rozwiązane w sposób w pełni poprawny.

W poniższej pętli `for` przechodzisz wszystkie id od `start` do `koniec` i sprawdzasz, czy któreś jest złe

```cpp
32        for (long long i = start; i <= koniec; i++) {
33            if (podzielnosc(i)) {
34                suma += i;
35            }
36        }
```

Jest to oczywiście poprawne, ale dość czasochłonne. Np. gdybyśmy mieli w danych przedział `111111000000-111111999999`, to twoje rozwiązanie sprawdza wszystkie liczby od `111111000000` do `111111999999` (10 milionów liczb), kiedy od razu widzimy, że w takim przedziale jest jedno nieprawidłowe id: `111111111111`.

Proponuję, żeby zamiast sprawdzać, czy kolejne id są poprawne czy złe, po prostu iść pętlą po kolejnych złych id w przedziale. Najpierw chcemy znaleźć przedział w jakim mogą być *pierwsze połowy* złych id (bo drugie połowy mamy takie same, więc możemy iść w pętli tylko po pierwszych połowach. Napisałam w tym celu funkcje pomocnicze `pol_start` i `pol_koniec`

```cpp
string pol_start(long long liczba){
    string s = to_string(liczba);
    int n = s.length();
    int polowa = n / 2;
    if (n % 2 != 0){
        return "1" + string(polowa, '0');  // string(polowa, '0') -- string złożony z polowa zer, gdy polowa = 0, to pusty string
    }                                      // + skleja 2 stringi (konkatenacja)
    else{
        return s.substr(0, polowa);
    }
}

string pol_koniec(long long liczba){
    string s = to_string(liczba);
    int n = s.length();
    int polowa = n / 2;
    if (n % 2 != 0){
        if(polowa == 0){                // jak liczba była jednocyfrowa
            return "0";                 // zwróć 0
        }
        else{
        return string(polowa, '9');     // string(polowa, '9') -- string złożony z polowa dziewiątek
        }     
    }
    else{
        return s.substr(0, polowa);
    }
}
```

Jeśli `start` ma parzystą liczbę cyfr, to `pol_start(start)` zwraca pierwszą połowę `start` (jako stringa); jeśli `koniec` ma parzystą liczbę cyfr, to `pol_koniec(koniec)` zwraca pierwszą połowę `koniec`. Co się dzieje jeśli `start` ma nieparzystą liczbę cyfr? Cóż, złe id muszą mieć parzystą liczbę cyfr, więc jeśli `start` jest jednocyfrowy, to złe id musi być mniejsze równe niż `10`, jeśli trzycyfrowy — `1000`, jeśli pięciocyfrowy — `100000` itd. Pierwsza połówka takiej liczby jest złożona z jedynki i `n / 2` zer, gdzie `n` to długość stringa utworzonego ze `start` (pamiętamy, że gdy `n` jest nieparzyste, `n / 2` zaokrągla nam w dół do liczby całkowitej). Podobnie gdy koniec jest nieparzyste, jeśli `koniec` jest jednocyfrowy, to nie będzie w ogóle złych id (tu nam `pol_koniec(koniec)` zwróci `0`), jeśli trzycyfrowy, to złe id jest mniejsze bądź równe `99`, jeśli pięciocyfrowy — '9999' itd., pierwszą połową takiego stringa jest `9` powtórzone `n / 2` razy.

Zamiast pętli `for` w linijkach 32–36 piszemy

```cpp
        for (long long i = stoll(pol_start(start)); i <= stoll(pol_koniec(koniec)); i++){
            string i_string = to_string(i);
            long long id = stoll(i_string + i_string);
            if (start <= id && id <= koniec){
                suma += id;
            }
        }
```

Musimy dodatkowo sprawdzić, czy `id` jest między `start` a `koniec`, bo np. gdybyśmy mieli przedział `111222-111999`, to `pol_start(start) == "111"`, `pol_koniec(koniec) == `111`, `id == 111111`.

Zauważmy, że jeśli `start` i `koniec` mają tę samą nieparzystą liczbę cyfr, np. `3`, to wtedy `pol_start(start) == "1000"`, `pol_koniec(koniec) == "99"` i w ogóle w pętlę `for` nie wchodzimy 🙂

Jeśli chodzi o złożoność czasową, to taka zmiana znacznie nam ją poprawia. Niech `n` oznacza długość stringa z `koniec`. W twoim rozwiązaniu sprawdzasz wszystkie liczby w przedziale <`start`,`koniec`>, więc masz złożoność czasową `O(10^n)`, w poprawionym rozwiązaniu sprawdzasz tylko pierwsze połowy, więc będzie złożoność `O(10^(n/2)) == O(sqrt(10^n))` (sqrt to pierwiastek kwadratowy), czyli poprawione rozwiązanie zajmie ok. pierwiastek czasu twojego pierwotnego rozwiązania 🙂

Otrzymujesz **4 punkty** za rozwiązanie pierwszej części zadania.
