### Uwagi do części pierwszej zadania:

Zadanie rozwiązane w sposób w pełni poprawny.

Zamiast

```python
        while arrow > 99:
            arrow = arrow - 100
        while arrow < 0:
            arrow = arrow + 100
```

(linijki 71–75) można było użyć operatora *modulo* `%`, który zwraca resztę z dzielenia przez liczbę. Tj. napisać

```python
    arrow = arrow % 100   # arrow % 100 -- reszta z dzielenia arrow przez 100
```

albo nawet

```python
   arrow %= 100
```

Otrzymujesz **4 punkty** za rozwiązanie pierwszej części zadania.
