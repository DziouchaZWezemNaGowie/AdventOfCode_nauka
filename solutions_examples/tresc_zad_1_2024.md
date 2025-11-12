[Link do treści zadania](https://adventofcode.com/2024/day/1)

# Skrót pierwszej części zadania:

  Dostajesz dane -- 2 listy liczb w dwóch kolumnach. Sparuj *najmniejszą liczbę w lewej liście* z *najmniejszą liczbą w prawej liście*, następnie *drugą najmniejszą liczbę w lewej* z *drugą najmniejszą liczbą w prawej* itd.
  
  W każdej parze, znajdź j*ak daleko od siebie* są te 2 liczby. Następnie *dodaj wszystkie te odległości*. Np. jeśli w sparujesz 3 z lewej listy z 7 z prawej listy, to odległość wynosi 9.

  Dla przykładowych danych:

```
3   4
4   3
2   5
1   3
3   9
3   3
```

- Najmniejszą liczbą w lewej liście jest `1`, a w prawej `3`. Odległość wynosi `2`
- Drugą najmniejszą liczbą w lewej liście jest `2`, a w prawej kolejne `3`. Odległość wynosi `1`.
- Trzecią najmniejszą liczbą w obu listach jest `3`, więc odległość między nimi to `0`.
- Kolejna para to `3` i `4`, z odległością `1`.
- Piątymi najmniejszymi liczbami w obu listach dą odpowiednio `3` i `5`, odległość to `2`.
- Wreszcie największą liczbą w lewej liście jest `4`, a największą liczbą w prawej liście jest `9`; odległość to `5`.

  Aby znaleźć *całkowitą odległość* między lewą i prawą listą, dodaj obliczone wcześniej odległości pomiędzy wszystkimi parami. W powyższym przykładzie to `2 + 1 + 0 + 1 + 2 + 5`, a więc pełna odległość wynosi **`11`**.

  **Jaka jest całkowita odległość między twoimi listami?**

# Skrót drugiej części zadania

Musisz znaleźć, dokładnie jak często każda liczba z lewej listy pojawia się w prawej liście. Oblicz *współczynnik podobieństwa* dodając każdą liczbę z lewej listy po pomnożeniu jej przez liczbę razy, kiedy pojawia się w prawej liście.

Dla naszego przykładu:

```
3   4
4   3
2   5
1   3
3   9
3   3
```

- Pierwszą liczbą w lewej liście jest `3`, które pojawia się w lewej liście 3 razy, więc współczynnik podobieństwa wzrasta o `3 * 3 = 9`.
- Drugą liczbą w lewej liście jest `4`. Pojawia się po prawej raz, więc współczynnik podobieństwa wzrasta o `4 * 1 = 4`.
- Trzecią liczbą po lewej jest `2`, które nie pojawia się w prawej liście, więc współczynnik podobieństwa nie rośnie (`2 * 0 = 0`).
- Czwarta liczba, `1`, również nie pojawia się w prawej liście.
- Piąta liczba, `3`, pojawia się w prawej liście 3 razy, więc współczynnik rośnie o `9`.
- Ostatnia liczba, `3`, pojawia się w prawej liście 3 razy, współczynnik znów rośnie o `9`.

  Zatem, dla naszego przykładu, współczynnik prawdopodobieństwa na końcu przykładu wynosi **`31`** (`9 + 4 + 0 + 0 + 9 + 9`).

  **Jaki jest współczynnik podobieństwa dla lewej i prawej listy z twojego inputu?**
