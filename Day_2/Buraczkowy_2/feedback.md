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

### Uwagi do rozwiązania drugiej części:

Piszesz

```python
67            for z in range(100):
68                if patrzyk(start,z+1):
...
90 def patrzyk(loddzik,szczepek):
...
98  if len(loddzik) <= szczepek or len(loddzik) % szczepek != 0:
99      return False
```

czyli sprawdzasz w funkcji `patrzyk`, za każdym razem dla `szczepek` od `1` do `100`, czy `len(loddzik) <= szczepek`, jeśli tak, to zwrasz `False`. Dużo szybciej będzie, zamiast sprawdzać wszystkie liczby od `1` do `100` (dla każdego `start` ponadto!), sprawdzać tylko liczby od `1` do `len(loddzik) - 1`, czyli inaczej `len(str(start)) - 1`. Tak więc zamiast powyższego napisać:

```python
            for z in range(len(str(start)) - 2)
                  if patrzyk(start,z+1):
...
def patrzyk(loddzik,szczepek):
...
      if len(loddzik) % szczepek != 0:             # wystarczy nam tylko drugi warunek, bo szczepek jest z przedziału <1, len(loddzik) - 1>
            return False
```

Albo jeszcze lepiej, można wykorzystać fakt, że `szczepek` to liczba znaków, które są w jednym kawałku `loddzik` przy dzieleniu, a skoro dzielimy na co najmniej `2` części, to wystarczy nam sprawdzać w funkcji `patrzyk` dla `szczepek` od `1` do `len(loddzik) // 2`, czyli:

```python
            for z in range(len(str(start)) // 2)
                  if patrzyk(start,z+1):
...
def patrzyk(loddzik,szczepek):
...
      if len(loddzik) % szczepek != 0:
            return False
```

Dalej, skoro teraz mamy coś takiego

```python
#piszę, w których linijkach był kod przed zmianą
67            for z in range(len(str(start)) // 2):
68                if patrzyk(start,z+1):
69                    nanoomegalodoimus =True
```

to możemy wykonywać przypisanie `nanoomegalodoimus = True` wiele razy, kiedy tak naprawdę wystarczy nam jedno. Możemy użyć polecenia `break`, żeby wyjść z pętli `for`:

```python
            for z in range(len(str(start__ // 2):
                if patrzyk(start,z+1):
                    nanoomegalodoimus =True
                    break
```

Dalej sprawdzasz czy `nanoomegalodoimus == True`. Oczywiście skoro `nanoomegalodoimus` jest typu `bool`, wystarczy w warunku wpisać `nanoomegalodoimus`.

Ale zmienna `nanoomegalodoimus` jest nam w ogóle niepotrzebna. Zamiast:

```python
67            for z in range(len(str(start__ // 2):
68                if patrzyk(start,z+1):
69                    nanoomegalodoimus =True
                      break
70
71            if nanoomegalodoimus ==True:
72                hexacentroptimus = hexacentroptimus + int(start)
73                print(start)
```

możemy po prostu napisać

```python
            for z in range(len(str(start__ // 2):
                if patrzyk(start,z+1):
                    hexacentroptimus = hexacentroptimus + int(start)
                    print(start)
                    break
```

Teraz przyjrzyjmy się funkcji `patrzyk`. Bardzo często używasz `len(loddzik)`. Nie wiem do końca jak to działa w Pythonie, ale zazwyczaj przy każdym takim wywołaniu komputer musi policzyć wartość funkcji `len()` od `loddzik`, a poza tym jest to trochę nieczytelne, więc sugeruję, żeby po prostu przypisać tę wartość do zmiennej, np.

```python
      n = len(loddzik)
```

i zastąpić wszystkie `len(loddzik)` zmienną `n`. Ja tutaj w poprawkach nie będę uwzględniać tej zmiany.

Dalej mamy coś takiego:

```python
103    for c in range(int(int(len(loddzik))/int(szczepek))-1):
```

Jest tu dużo niepotrzebnego zamieniania zmiennych w inty. `len(loddzik)` i `szczepek` już są typu `int`, więc `int()` wokół nich jest totalnie niepotrzebne, a zamiast robić `int(len(loddzik) / szczepek)` możemy użyć dzielenia całkowitego (mamy mniej operacji wtedy, więc jest to troszkę szybsze):

```python
      for c in range(len(loddzik) // szczepek - 1):        # nie trzeba dodatkowego nawiasu, bo kolejność działań
```

Zamiast

```python
105     if loddzik[(len(loddzik)-szczepek-c*szczepek)-szczepek:(len(loddzik)-c*szczepek)-szczepek] != loddzik[len(loddzik)-szczepek-c*szczepek:len(loddzik)-c*szczepek]:
```

można napisać

```python
      if loddzik[len(loddzik) - (c + 2) * szczepek : len(loddzik) - (c + 1) * szczepek] != loddzik[len(loddzik) - (c + 1) * szczepek : len(loddzik) - c * szczepek]:
```

Jest to czytelniejsze.

Zamiast:

```python
96 megaoktohektoplazma = False
...
105      if loddzik[len(loddzik) - (c + 2) * szczepek : len(loddzik) - (c + 1) * szczepek] != loddzik[len(loddzik) - (c + 1) * szczepek : len(loddzik) - c * szczepek]:
106
107          megaoktohektoplazma = True
...
110 if megaoktohektoplazma:
111     return False
112 else:
113     
114     return True
```

lepiej napisać

```python
 megaoktohektoplazma = False
...
      if loddzik[len(loddzik) - (c + 2) * szczepek : len(loddzik) - (c + 1) * szczepek] != loddzik[len(loddzik) - (c + 1) * szczepek : len(loddzik) - c * szczepek]:

          megaoktohektoplazma = True
...
 return not megaoktohektoplazma
```

Jeszcze lepiej po prostu odwrotnie przypisać wartości:

```python
 megaoktohektoplazma = True
...
      if loddzik[len(loddzik) - (c + 2) * szczepek : len(loddzik) - (c + 1) * szczepek] != loddzik[len(loddzik) - (c + 1) * szczepek : len(loddzik) - c * szczepek]:

          megaoktohektoplazma = False
...
 return megaoktohektoplazma
```

A najlepiej pozbyć się zmiennej `magaoktohektoplazma` całkowicie i napisać:

```python
...
      if loddzik[len(loddzik) - (c + 2) * szczepek : len(loddzik) - (c + 1) * szczepek] != loddzik[len(loddzik) - (c + 1) * szczepek : len(loddzik) - c * szczepek]:
            return False
...
 return True
```

Zauważmy, że ten `return False` wychodzi nam z pętli `for` z linijki 103, więc też dzięki temu rozwiązaniu unikamy niepotrzebnego sprawdzania.

OK, tak poprawione rozwiązanie jest wyraźnie szybsze, ale wciąż dość wolne.

Spróbujmy rozwiązać drugą część zadania podobnie jak zaproponowane przeze mnie rozwiązanie części pierwszej. W tym celu zdefiniujemy funkcję pomocniczą `bremek`:

```python
def bremek(start,end,pablo):
  # pablo -- na ile części dzielimy
    lyta = set()                            # to będzie zbiór złych id

  ### część startu, którą będziemy powtarzać
    if (len(start) % pablo == 0):
        czesc_start = int(start[:len(start) // pablo])
    else:
        czesc_start = int("1" + '0' * (len(start) // pablo))

  ### część endu, do której zdążamy
    if (len(end) % pablo == 0):
        czesc_end = int(end[:len(end) // pablo])
    else:
        czesc_end = int('9' * (len(start) // pablo))

  ### pętla
    while czesc_start <= czesc_end:
        czesc_start = str(czesc_start)
        id = int(czesc_start * pablo)

        if(int(start) <= id <= int(end)):
            lyta.add(id)                 # dodajemy id do zbioru lyta
        
        czesc_start = int(czesc_start) + 1

    return lyta
```

Jak widać jest to bardzo podobne rozwiązanie do rozwiązania pierwszej części zadania, jedynie zamiast `2` wpisujemy liczbę powtarzających się części — `pablo` i zamiast od razu dodawać `id` do naszej sumy `hexacentroptimus`, dodajemy kolejne złe id do zbioru `lyta`. W funkcji `main` do linijki 54 wszystko zostaje bez zmian, a poniżej, dalej w pętli `for a in parts`, piszemy:

```python
        hexacentrum = set()                                       # zbiór złych id

        for z in range (1,len(end)):
            hexacentrum = hexacentrum | bremek(start, end, z + 1) # | daje nam sumę dwóch zbiorów (w matematyce symbol przypominający U

        for id in hexacentrum:
            hexacentroptimus = hexacentroptimus + id
```

A już poza pętlą `for a in parts` mamy

```python
    print("Odp:",hexacentroptimus)
```

Musimy użyć tutaj zbiorów, ponieważ może się zdażyć, że dla różnych `pablo` złe id będą nam się powtarzać, np. liczba `666666` jest w zbiorze `lyta` dla `pablo` równego `2`, `3` oraz `6`. Zbiory w Pythonie, jak i w matematyce, nie zachowują duplikatów.

Nie wiem jak na twoim komputerze, ale u mnie twoje pierwotne rozwiązanie zabierało kilkanaście sekund czasu, twoje rozwiązanie po poprawkach kilka sekund czasu, a rozwiązanie, które zapisałam powyżej wykonuje się od razu.

Otrzymujesz **4 punkty** za rozwiązanie drugiej części zadania.

### Gratulacje! Zdobyłeś maksimum 8 punktów za zadanie drugie!
