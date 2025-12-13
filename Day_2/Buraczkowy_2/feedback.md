### Uwagi do rozwiązania pierwszej części:

Zadanie rozwiązane w sposób poprawny.

Twoje pierwotne rozwiązanie nie działało, ponieważ w pętli

```python
55      while start != end:
```

przechodzisz przez wartości od pierwotnego `start` to `end - 1`, a nieprawidłowe id mogą być od `start` do `end` włącznie. Poprawienie na

```python
      while start != end + 1:
```

oczywiście naprawia problem. Bardziej czytelniejsze byłoby może

```python
      while start <= end:
```

ale nie zadziałałoby, ponieważ na samym początku pierwszy start jest typu `str` i nie można określić, czy `start` jest mniejszy od `end`. Problem z tym związany mógłby także wystąpić, gdybyśmy mieli przedział jedno elementowy, np. `14-14`, w twoim pierwotnym rozwiązaniu warunek w pętli while `start != end` zwróciłby `true`, ponieważ `start` i `end` mają inne typy, program wpadłby w nieskończoną pętle. Ale przedziałów jednelementowych nie było w danych, a w poprawionej wersji (`start != end + 1`) tego problemu już nie ma, więc wspominam o tym tylko, żeby zwrócić na to twoją uwagę.

Dalej piszesz

```python
58            if (len(start)) % 2 == 0 and start[int((len(start))/2):] == start[:int((len(start))/2)]:
```

trochę tu niepotrzebnych nawiasów. Zamiast zmuszać `len(start)/2` do bycia intem, mogłeś użyć operatora dzielenia całkowitego `//`, o którym wspominałam przy rozwiązaniu zadania pierwszego

```python
            if len(start) % 2 == 0 and start[len(start) // 2:] == start[:len(start) // 2]:
```

Na koniec co do samego sposobu rozwiązania zadania, to jest on dość powolny. Gdybyśmy np. mieli zbadać przedział `111111000000-111111999999`, to sprawdzasz wszystkie 10 milionów liczb w tym przedziale, gdy tymczasem widać od razu, że nieprawidłowe id jest jedno — `111111111111`. Zamiast

```python
52        end = int(end)
53        
54
55        while start != end: #while start != end + 1: I działą
56            start = str(start)
57
58            if (len(start)) % 2 == 0 and start[int((len(start))/2):] == start[:int((len(start))/2)]:
59                print(hexacentroptimus,"+",start)
60                hexacentroptimus = hexacentroptimus + int(start)
61                
62            start = int(start)+1
```

Proponuję najpierw wyciągnąć pierwszą połówkę `start`

```python
        if (len(start) % 2 == 0):
            pol_start = int(start[:len(start) // 2])
        else:
            pol_start = int("1" + '0' * (len(start) // 2))
```

Jeśli `len(start)` jest liczbą parzystą, to `pol_start` to pierwsza połówka stringa `start`, jeśli jest nieparzysta, to, ponieważ nieprawidłowe id musi mieć parzystą liczbę cyfr, możemy zacząć sprawdzanie od następnej liczby parzystocyfrowej. Dla jednocyfrowego `start` będzie to `10`, dla trzycyfrowego — `1000`, dla pięciocyfrowego — `100000`. Pierwsza połówka takiej liczby to `1` a następnie `len(start) // 2` zer.

Podobnie wyciągamy pierwszą połówkę `end`:

```python
# wcześniej musimy usunąć
# end = int(end)
# żeby end był dalej str
        if (len(end) % 2 == 0):
            pol_end = int(end[:len(end) // 2])
        else:
            pol_end = int('9' * (len(start) // 2))
```

tutaj gdy `end` ma nieparzystą liczbę cyfr, to wystarczy szukać do najmniejszej poprzedniej liczby parzystocyfrowej.

Teraz wystarczy dodać poniższy kod:

```python
        start = int(start)
        end = int(end)

        while pol_start <= pol_end:
            pol_start = str(pol_start)
            id = int(pol_start * 2)

            if (start <= id <= end):
                hexacentroptimus = hexacentroptimus + id

            pol_start = int(pol_start) + 1
```

I gotowe!

Jeśli chodzi o złożoność czasową, to taka zmiana znacznie nam ją poprawia. Niech `n` oznacza długość `end`. W twoim rozwiązaniu sprawdzasz wszystkie liczby w przedziale od `start` do `end`, więc masz złożoność czasową `O(10^n)`, w poprawionym rozwiązaniu sprawdzasz tylko pierwsze połowy, więc będzie złożoność `O(10^(n/2)) == O(sqrt(10^n))` (sqrt to pierwiastek kwadratowy), czyli poprawione rozwiązanie zajmie ok. pierwiastek czasu twojego pierwotnego rozwiązania 🙂

Otrzymujesz **4 punkty** za rozwiązanie pierwszej części zadania.
