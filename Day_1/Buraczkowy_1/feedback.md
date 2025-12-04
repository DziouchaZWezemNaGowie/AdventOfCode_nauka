### Uwagi do części pierwszej zadania:

Zadanie rozwiązane w sposób w pełni poprawny.

Zamiast

```python
71        while arrow > 99:
72            arrow = arrow - 100
73        while arrow < 0:
74            arrow = arrow + 100
```

(linijki 71–74) można było użyć operatora *modulo* `%`, który zwraca resztę z dzielenia przez liczbę. Tj. napisać

```python
    arrow = arrow % 100   # arrow % 100 -- reszta z dzielenia arrow przez 100
```

albo nawet

```python
   arrow %= 100
```

Otrzymujesz **4 punkty** za rozwiązanie pierwszej części zadania.

### Uwagi do części drugiej zadania:

Zadanie rozwiązane w sposób w pełni poprawny.

Znów, użycie pętli `while` można było zastąpić użyciem operatora modulo `%` dla zmiennej `arrow` oraz operatora *dzielenia całkowitego* `//` dla zmiennej `sigma`. Tj. zamiast

```python
75        while arrow > 99:
76            arrow = arrow - 100
77            ######################
78            sigma = sigma + 1    #
79            print("plus")        #
80            if arrow == 0:       #
81                sigma = sigma-1  #
82                print("minus")   #
83            ######################    
```

napisać

```python
        if arrow > 99:
            sigma = sigma + arrow // 100 # najpierw zmieniamy sigmę, bo używamy starej wartości arrow
            arrow = arrow % 100          # potem arrow
            if arrow == 0:
                sigma = sigma - 1
```

a zamiast

```python
84        while arrow < 0:
85            arrow = arrow + 100
86            #####################
87            sigma = sigma + 1   #
88            print("plus")       #
89            #####################
```

możemy napisać

```python
        if arrow < 0:
            sigma = sigma - arrow // 100 # teraz arrow jest ujemne, więc arrow // 100 jest ujemne
            arrow = arrow % 100
```

Oba przypadki są bardzo podobne. Zauważmy, że dla `0 < arrow < 99` mamy `arrow // 100 == 0` i `arrow % 100 == arrow`. Tak więc postępujemy następująco: 

1. Jeśli `arrow // 100` jest dodatnie (lub 0), to `sigma = sigma + arrow // 100`, w przeciwnym wypadku `sigma = sigma - arrow // 100`.
2. `arrow = arrow % 100`

Aby nie musieć sprawdzać, jaki znak ma `arrow // 100`, możemy posłużyć się wartością bezwzględną, w Pythonie to funkcja `abs()`.

Cały kod w linijkach 75–89 można więc zastąpić następującym kodem:

```python
        if arrow > 99 and arrow % 100 == 0:   # potrzebujemy starej wartości arrow do warunku
            sigma = sigma - 1                 # więc zmniejszanie sigma wykonujemy jako pierwsze
        sigma = sigma + abs(arrow // 100)
        arrow = arrow % 100
```

Kolejna kwestia, to pomniejszanie zmiennej `sigma` o `1` (w pliku linijki 80–81; powyżej dwie pierwsze), po to, aby na końcu pliku znów zwiększyć `sigma` o `1`:

```python
92        if arrow == 0:
93         sigma = sigma + 1
94        print("korekta ",arrow,"sigma",sigma)
```

Zamiast tego można powiększać `sigma` o `1` tylko tam, gdzie nie trzeba wartości zmiennej zmniejszać. Tzn. zamiast tego, co napisałam w przedostatnim kawałku kodu możemy napisać:

```python
        if arrow <= 0 and arrow % 100 == 0:
            sigma = sigma + 1
        sigma = sigma + abs(arrow // 100)
        arrow = arrow % 100
```

i pozbyć się linijek 92–94.

Otrzymujesz **4 punkty** za rozwiązanie drugiej części zadania.

### Gratulacje! Zdobyłeś maksimum 8 punktów za zadanie 1!
