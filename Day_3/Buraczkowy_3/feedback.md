### Omówienie rozwiązania pierwszej części zadania:

Zadanie rozwiązane w sposób w pełni poprawny.

Przy wczytywaniu masz ten problem, że gdy robisz `for line in f:`, to `line` ma na końcu znak końca linii `\n`. Rozwiązujesz ten problem w taki sposób:

```cpp
52        for line in f:
53            parts = str(line.strip().split("/n"))
54            parts = parts[2:-2]
```

Mogłeś to zrobić prościej, np. tak:

```cpp
    for line in f:
      parts = line[:-1]
```

Albo

```cpp
        for line in f:
            parts = line.strip().split("/n")[0]   # line.strip().split("/n") to jednoelementowa lista
```

Poza tym nie mam uwag.

Otrzymujesz **4 punkty** za rozwiązanie pierwszej części zadania.
