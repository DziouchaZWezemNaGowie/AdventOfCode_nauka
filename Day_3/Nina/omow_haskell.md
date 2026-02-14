Na początek mamy wczytanie potrzebnegi modułu i danych:

```haskell
1 import Control.Monad
2
3 main = do
4     dane <- lines <$> readFile "dane.txt"
```

W rozwiązaniu używamy tylko jednej funkcji pomocniczej, `maxJoltage`:

```haskell
10 maxJoltage :: String -> (String, String)
11 maxJoltage xs = foldr (\x (y,ys) -> if y >= [x]
12                                     then (y,x:ys)
13                                     else ([x],[])) ([last xs],[]) (init xs)
```

Funkcja `maxJoltage` bierze za argument Stringa — `xs` i zwraca parę uporządkowaną Stringów. Pierwszy ma być wybraną baterią (odpowiednią cyfrą), a drugi to część Stringa, w której mogą znaleźć się kolejne cyfry.

Funkcja `foldr` ma 3 argumenty: funkcję składającą, początkowy akumulator i listę. Lista to `init xs`, czyli String `xs` bez ostatniego elementu. Początkowy akumulator to `([last xs],[])` para uporządkowana, gdzie pierwszy element to String złożony z ostatniego znaku w `xs`, a drugi to pusty String.

Przyjrzyjmy się funkcji składającej:

```haskell
\x (y,ys) -> if y >= [x]
             then (y, x:ys)
             else ([x],[])
```

Bierzemy `x` — element listy `init xs` (String to lista Char-ów) po kolei od prawej oraz akumulator postaci `(y,ys)`. Jeśli String `y` jest większy lub równy Stringowi złożonymi tylko ze znaku `x` (nasza funkcja jest tak ustawiona, że `y` zawsze jest jednoznakowym Stringiem, więc porównujemy tak naprawdę ze sobą cyfry), to nowy akumulator ma postać `(y, x:ys)` (dorzucamy `x` na początek `ys`), w przeciwnym wypadku nowy akumulator to `([x],[])`.

### Rozwiązanie pierwszej częsci zadania

```haskell
6    print $ sum . map (read . fst <$> (maxJoltage <=< ((\(x:xs) -> (x:) <$> maxJoltage xs) . reverse))) $ dane
```

Jak zwykle czytamy kod od prawej do lewej. Najpierw bierzemy `dane`, czyli listę Stringów, najpierw wykonujemy mapowanie, czyli dla każdego elementu `dane` wykonujemy:

```haskell
read . fst <$> (maxJoltage <=< ((\(x:xs) -> (x:) <$> max Joltage xs) . reverse))
```

Zaczynamy od `reverse`, czyli odwrócenia kolejności w Stringu. Zrobiłam to dlatego, że listy w Haskellu będą działać bardziej wydajnie w takim rozwiązaniu, nie będę się zagłębiać w zbędne szczegóły.

Następnie dla naszego odwróconego Stringa, oznaczamy jego pierwszy znak jako `x`, a resztę jako `xs` i wykonujemy `maxJoltage xs`, dostajemy w ten sposób parę uporządkowaną Stringów: pierwszy to pierwsza cyfra szukanej liczby, drugi to część oryginalnego Stringa, w którym może znajdować się druga cyfra. Dorzucamy do tego Stringa `x` na początek. Wykonujemy `maxJoltage` na drugim elemencie pary, w rezultacie dostajemy parę uporządkowaną Stringów, gdzie pierwszy element to String złożony z pierwszej szukanej cyfry i drugiej (którą dostaliśmy z drugiego `maxJoltage`), a drugi to String w którym mogłaby się znaleźć potencjalna trzecia cyfra (tak działa monadyczne składanie w Haskellu). Bierzemy pierwszy element tej pary (`fst`) i wczytujemy go jako liczbę `read`). Dostajemy szukaną liczbę dla każdego Stringa.

Dalej wykonujemy `sum` i otrzymujemy poszukiwaną odpowiedź.

### Rozwiązanie drugiej części zadania

```haskell
8    print $ sum . map (read . fst <$> (maxJoltage <=< (\(ys,xs) -> foldM (\acc y -> (y:) <$> maxJoltage acc) xs (reverse ys)) . splitAt 11 . reverse)) $ dane
```

Znów zaczynamy od mapowania

```haskell
read . fst <$> (maxJoltage <=< (\(ys,xs) -> foldM (\acc y -> (y:) <$> maxJoltage acc) xs (reverse ys)) . splitAt 11 . reverse)
```

Zaczynamy od odwrócenia Stringa (`reverse`), następnie wykonujemy `splitAt 11`, dzieli to nam Stringa na parę uporządkowaną Stringów; pierwszy to jego pierwsze 11 znaków, a drugi to pozostała jego część. Oznaczamy pierwszy element pary jako `ys`, drugi jako `xs` i wykonujemy

```haskell
foldM (\acc y -> (y:) <$> maxJoltage acc) xs (reverse ys)
```

`foldM` jest jak `foldl` (składanie od lewej), tylko działa monadycznie, czyli na wyższym poziomie abstrakcji (nie wchodzę w szczegóły). Początkowy akumulator to `xs`, a lista, po której składamy to `reverse ys`, funkcja składająca — `\acc y -> (y:) <$> maxJoltage acc`. Czyli mamy 11 ostatnich cyfr Stringa z danych (tam nie można mieć pierwszej cyfry) i kolejno wykonujemy `maxJoltage` i dorzucamy cyfrę z końcówki do przeszukiwanych cyfr. W efekcie dostaniemy parę Stringów, gdzie pierwszy element to pierwsze 11 cyfr szukanej liczby, a drugi to String cyfr, wśród których jest ostatnia cyfra. Wykonujemy `maxJoltage` jeszcze raz, pierwszy element pary uporządkowanej, którą dostajemy to szukana 12-cyfrowa liczba, więc ją bierzemy (`fst`) i wczytujemy jako liczbę (`read`). Na koniec sumujemy (`sum`) całość.
