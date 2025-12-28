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

### Omówienie rozwiązania drugiej części zadania

Zadanie nierozwiązane poprawnie.

Ogólnie wszystko jest dobrze, tylko masz źle postawion nawiasy klamrowe. W najbardziej zewnętrznej pętli masz:

```cpp
17 while (dane >> linia) {
18        
19        string wynik = "";      
20        int od = 0;     
21        int dlugosc = linia.length();
22        int do_znalezienia = 12; 
23
24        
25        for (int k = 0; k < 12; k++) {
26            
27          
28            char max_cyfra = -1;
29            int max_index = -1;
30
31         
32            int zostawic = 11 - k;
33
34            for (int i = od; i <= dlugosc - 1 - zostawic; i++) {
35
36         
37               if (linia[i] > max_cyfra) {
38                    max_cyfra = linia[i];
39                    max_index = i;
40                }
41            }
42        
43    
44        wynik += max_cyfra; 
45        
46     
47        od = max_index + 1;
48            suma += stoull(wynik);                      // W pętli for (int k = 0; k < 12; k++), powinno być w pętli while (dane >> linia)
49    }
50
51    cout << "Całkowite Napięcie:  " << suma << endl;    // W pętli while (dane >> linia), powinno być poza tą pętlą
52
53    return 0;                                           // W pętli while (dane >> linia), powinno być poza nią
54 }
```

Czyli dodajesz do `suma` `wynik` dla każdej kolejnej pozyskanej cyfry i wyświetlasz całkowite napięcie i zwracasz `0` już dla pierwszej linii w `dane`, dla pozostałych linii nie wykonujesz programu w ogóle. Po poprawieniu nawiasów w tym fragmencie, czyli:

```cpp
    while (dane >> linia) {
        
        string wynik = "";      
        int od = 0;     
        int dlugosc = linia.length();
        int do_znalezienia = 12; 

        
        for (int k = 0; k < 12; k++) {
            
          
            char max_cyfra = -1;
            int max_index = -1;

         
            int zostawic = 11 - k;

            for (int i = od; i <= dlugosc - 1 - zostawic; i++) {

         
               if (linia[i] > max_cyfra) {
                    max_cyfra = linia[i];
                    max_index = i;
                }
            }
        
    
        wynik += max_cyfra; 
        
     
        od = max_index + 1;
    }

                suma += stoull(wynik);
    }
    cout << "Całkowite Napięcie:  " << suma << endl;

    return 0;
```

program działa już poprawnie.
