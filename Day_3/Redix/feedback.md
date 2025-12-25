### Omówienie rozwiązania pierwszej części zadania

Zadanie rozwiązane w sposób w pełni poprawny.

Masz w swoim kodzie użytą zagnieżdżoną pętlę:

```cpp
23        for (int i = 0; i < dlugosc - 1; i++) {
24        
25            for (int j = i + 1; j < dlugosc; j++) {
26                
27              
28                int pierwsza = linia[i] - '0'; 
29                int druga = linia[j] - '0';
30
31             
32                int liczba = pierwsza * 10 + druga;
33
34             
35                if (liczba > max_napiecie) {
36                    max_napiecie = liczba;
37                }
38            }
39        }
40
41       
42        suma += max_napiecie;
```

Sprawdzasz każde możliwe napięcie. Czyli dla długości równej `n` masz `1/2 * (n-1)^2` porównań. Złożoność czasowa to `O(n^2)`. Wystarczy jedna pętla:

```cpp
        for (int i = 0; i < dlugosc - 1; i++) {

                int liczba = linia[i] - '0';

                if (liczba > pierwsza){
                    pierwsza = liczba;
                    druga = 0;
                }
                else if (liczba > druga){
                    druga = liczba;
                }
        }

        int liczba = linia[dlugosc - 1] - '0';

        if (liczba > druga){
            druga = liczba;
        }

        suma += 10*pierwsza + druga;
```

Wtedy masz mniej niż `2 * n` porównań i złożoność czasową `O(n)`. Zmienna `max_napięcie` jest niepotrzebna.

Otrzymujesz **4 punkty** za rozwiązanie pierwszej części zadania.
