### Preambuła + wczytywanie danych

Na samym początku pliku znajduje się preambuła

```haskell
1 import Control.Monad (liftM2)
2 import Data.List (nub)
```

to po prostu wczytanie funkcji, których używam dalej w programie, a które nie są częścią pakietu (modułu) podstawowego.

Dalej deklaruję funkcję `main`. Na samym początku wczytuję dane

```haskell
4    dane <- map range . dziel <$> readFile "Zad_2.txt"
```

ponieważ nie znam funkcji, które pozwoliłyby mi podzielić dane w sposób wymagany przez zadanie, zadeklarowałam je sobie sama:

```haskell
32 -- funkcje do wczytywania
33 dziel :: String -> [String]
34 dziel [] = []
35 dziel s = let (range, rest) = break (== ',') s
36           in range : dziel (drop 1 rest)
37
38 range :: String -> (String, String)
39 range s = let (x,y) = break (== '-') s
40           in (x, drop 1 y)
```

W Haskellu czytamy co robimy od prawej do lewej, najpierw wykonujemy

```haskell
    readFile "Zad_2.txt"
```

to nam wczytuje dane z pliku `Zad_2.txt` jako String. Jest to String zawierający pary liczb rozdzielone przecinkami. Następnie wykonujemy na nim funkcję `dziel`, funkcja ta tworzy ze Stringa listę Stringów w następujący sposób:

- jeśli String jest pusty, to `dziel` zwraca pustą listę
- w przeciwnym wypadku, dla `s` oznaczającego naszego Stringa niech `(range, rest) = break (== ',') s`. Funkcja `break (== ',')` zwraca parę uporządkowaną, `range` to część Stringa przed pierwszym wystąpieniem `','`, `rest` to reszta Stringa (zaczyna się od pierwszego wystąpienia `','`). Zwracamy `range : dziel (drop 1 rest)`, czyli listę, której pierwszym elementem jest `range`, a pozostałą częścią listy jest lista `dziel (drop 1 rest)`, czyli to, co zwraca funkcja `dziel` dla Stringa `rest` bez pierwszego znaku, którym, jak wiemy, jest `','`.

Mamy więc listę par liczb. Każde dwie liczby w parze są rozdzielone znakiem `'-'`. Aby zrobić z tak zapisanej pary liczb parę uporządkowaną wykorzystuję funkcję `range`, która bierze Stringa rozdzielonego znakiem `'-'` i zwraca parę uporządkowaną postaci (<część Stringa przed `'-'`, część Stringa po `'-'`. Aplikujemy do listy Stringów, którą uzyskaliśmy `map range`, czyli wykonujemy `range` na każdym elemencie listy. Dostajemy listę par Stringów (`[(String,String)]`).
