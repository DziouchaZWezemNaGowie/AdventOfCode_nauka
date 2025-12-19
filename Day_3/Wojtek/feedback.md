### Omówienie pierwszej części zadania

Zadanie rozwiązane w sposób w pełni poprawny.

Nie mam uwag.

Otrzymujesz **4 punkty** za rozwiązanie pierwszej części zadania.

### Omówienie drugiej części zadania

Zadanie rozwiązane w sposób w pełni poprawny.

Mam tylko kilka małych nitpicków.

Piszesz coś takiego:

```cpp
18		while (infile >> bank){
...
22			while (lukstr.size() < 12){
23			 lenght = bank.size();
...
```

wartość `lenght` zależy jedynie od rozmiaru stringa `bank`, możesz dać przypisanie `lenght = bank.size();` dać w zewnętrznej pętli, czyli:

```cpp
  while (infile >> bank({
    lenght = bank.size();
...
    while (lukstr.size() < 12){
...
```

wtedy przypisujesz wartość `lenght` raz dla każdego `bank`, a nie `12`, jak w pierwotnym rozwiązaniu. Chociaż oczywiście nie musisz w ogóle korzystać ze zmiennej `lenght`, bo wykorzystujesz ją tylko w jednym miejscu (linijka 26).

Zamiast

```cpp
25			licznik = 0 + pozycja;
```

możesz oczywiście napisać po prostu

```cpp
    licznik = pozycja;
```

Nie potrzebujesz też specjalnie tworzyć nowych zmiennych tylko do zmiany typu. Zamiast:

```cpp
36			luk1str = std::to_string(luk1);
37			lukstr.append(luk1str);
...
40			luk3 = stoll(lukstr);
...
42			wynik += luk3;
```

możesz napisać:

```cpp
    lukstr.append(std::to_string(luk1));
...
...
    wynik += stoll(lukstr);
```

Wydaje mi się to bardziej czytelne. Chociaż zrobienie tak jak ty, to nie jest jakaś straszna zbrodnia.

Otrzymujesz **4 punkty** za rozwiązanie drugiej części zadania.

### Gratulacje! Otrzymałeś maksimum 8 punktów za rozwiązanie zadania trzeciego!
