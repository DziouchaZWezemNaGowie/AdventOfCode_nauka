### Uwagi do rozwiązania pierwszej części zadania

Zadanie rozwiązane w sposób w pełni poprawny.

Możesz użyć zmiennej pomocniczej, żeby nie musieć wykonywać przeszukiwania kilka razy, tj. zamiast:

```cpp
26				zmin = stoll(z.substr(0,z.find('-')));
27				zmax = stoll(z.substr(z.find('-')+1,z.size()-z.find('-')));
```

możesz napisać

```cpp
        int kreska = z.find('-');
        zmin = stoll(z.substr(0,kreska));
        zmax = stoll(z.substr(kreska + 1, z.size() - kreska));
```

Przy tylko kilku wyszukiwaniach na stosunkowo krótkich danych to nie ma większego znaczenia.

Zamiast nadpisywać indeks tak, żeby był poza zakresem:

```cpp
30					iz = zasieg.size
```

Możesz po prostu użyć polecenia

```cpp
            break;
```

żeby wyjść z pętli.

Poza tym nie mam uwag.

Otrzymujesz **4 punkty** za rozwiązanie pierwszej części zadania.
