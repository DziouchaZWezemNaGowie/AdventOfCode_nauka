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

### Pierwsza część zadania

Najpierw omówię wszystkie funkcje pomocnicze

```haskell
43 halveUp :: String -> Int
44 halveUp s
45    | even n = read $ take n2 s
46    | otherwise = read $ '1' : replicate n2 '0'
47    where n = length s
48          n2 = n `div` 2
```

`halveUp` to funkcja, która bierze Stringa `s`, w domyśle pierwszą liczbę z zadanego przedziału, i, jeśli długość `s` jest parzysta zwraca pierwszą połowę `s`a jako liczbę całkowitą (Int), w przeciwnym wypadku `halveUp` zwraca liczbę złożoną z jedynki i długości `s` podzielonej dzieleniem całkowitym na `2` zer, czyli połowę najmniejszej liczby parzystocyfrowej większej niż liczba z `s`. Pionowe '|' oznaczają w Haskellu kolejne warunki (kolejne `|` to odpowiednik C++-owego `if...else if... elif...` i Pythonowego `if... elif...elif...`, `otherwise` w ostatnim warunku jest jak `else` kończący taki ciąg — wyłapuje pozostałe przypadki), funkcja przyjmuje wartość dla pierwszego warunku spełnionego przez argument(y). Po `where` możemy zapisać, co oznaczają zmienne/funkcje pomocnicze użyte powyżej, równoważnie możnaby to było zapisać np. tak

```haskell
halveUp :: String -> Int
halveUp s = let n = length s
                n2 = n `div` 2
            in if even n
               then read $ take n2 s
               else read $ '1' : replicate n2 '0'
```

```haskell
50 halveDown :: String -> Int
51 halveDown s
52    | even n = read $ take n2 s
53    | otherwise = if n2 == 0
54                  then 0
55                  else read $ replicate n2 '9'
56    where n = length s
57          n2 = n `div` 2
```

`halveDown` działa podobnie do `halveUp`, tylko jeśli `s` ma nieparzystą długość, to funkcja zwraca liczbę złożoną z długości `s` podzielonej dzieleniem całkowitym na `2` dziewiątek, czyli połowę największej liczby parzystocyfrowej mniejszej od liczby z `s`.

Kolejna funkcja

```haskell
59 niceRange :: (String, String) -> Maybe (Int, Int)
60 niceRange (x, y)
61    | polX <= polY = Just (polX, polY)
62    | otherwise = Nothing
63    where polX = halveUp x
64          polY = halveDown y
```

ma typ `(String, String) -> Maybe (Int, Int)`, czyli przypisuje parze Stringów wartość `Maybe (Int, Int)`. `Maybe` jest używane, gdy funkcja może nas w jakiś sposób zawieść. Jeśli wszystko jest OK, to dostajemy `Just <wartość>`, a jeśli nie, to `Nothing`. Tutaj funkcja `niceRange` bierze parę Stringów — `(x,y)`, to w domyśle będą nasze zasięgi, których listę mamy w `dane`; przypisuje `polX = halveUp x`, `polY = halveDown y`, i, jeśli `polX <= polY` dostajemy `Just (polX, polY)`, a w przeciwnym wypadku `Nothing`, bo jeśli szukamy nieprawidłowych id i połówka pierwszej liczby jest większa od drugiej (tak się dzieje jak obie liczby są nieparzystocyfrowe i mają tyle samo cyfr), to nie ma czego dalej szukać.

```haskell
66 sillyList :: (Int, Int) -> [Int]
67 sillyList (x,y) = map (read . (\x -> x ++ x) . show) [x..y]
```

`sillyList` da nam listę złych id, `(x,y)` to połówki pierwszej i drugiej liczby z przedziału, jaki mamy rozważyć. `[x..y]` oznacza listę kolejnych liczb całkowitych od `x` do `y` włącznie. Po takiej liście mapujemy, czyli tworzymy listę złożoną z wartości funkcji `read . (\x -> x ++ x) . show` dla kolejnych liczb w liście `[x..y]`. Trochę niefortunnie użyłam tutaj `x`-a w środku, powinnam była napisać

```haskell
sillyList :: (Int, Int) -> [Int]
sillyList (x,y) = map (read . (\z -> z ++ z) . show) [x..y]
```

Haskell jak większość języków programowania przyjmuje, że w razie kolizji zmiennych chodzi o jej najbardziej "lokalną" wersję. Funkcja `read . (\z -> z ++ z) . show` dla danej liczby najpier wykonuje `show`, czyli zmienia ją z Inta w Stringa, potem `\z -> z ++ z`, czyli bierze tego Stringa i "zlepia" go samego ze sobą (`++` to konkatenacja, czyli zlepianie stringów ), a na końcu wykonuje `read`, czyli zmienia Stringa znów w Inta.

Ostatnią funkcją pomocniczą `sumM` się nie przejmujcie. Musiałam mieć inną wersję zwykłego `sum`, przez to, że w jednym momencie algorytmu dostajemy wartości z `Maybe`. Jeszcze do tego zapomniałam o funkcji z pakietu bazowego `sequence`, która pozwala mi uciec od tego problemu (tak naprawdę `sumM = fmap sum . sequence`, ale to nieważne), więc napisałam swoją funkcję od zera.

Rozwiązanie pierwszej części zadania wygląda następująco:

```haskell
6    print $ sumM                                                  -- sumujemy całość
7            . filter (/= Nothing)                                 -- jak gdzieś było Nothing, to usuwamy
8            . map                                                 -- dla każdego range'a w dane
9              (\(x,y) -> sum                                              -- sumujemy silly liczby dla jednego range'a
10                        . filter ((&&) <$> (>= read x) <*> (<= read y))  -- filtrujemy gdy nie są między x a y, zapis jest na wyższym poziomie abstrakcji, nie przejmujcie się tym
11                        . sillyList                                      -- lista możliwych silly liczb (złych id)
12                        <$> niceRange (x,y)                              -- możliwy range początków (pierwszych połów), jeśli początek z x > początek z y to Nothing
13             )                             
14         $ dane
```

Myślę, że opisy, które dodałam w komentarzach wyjaśniają sprawę. Dodam tylko, że gdybyśmy nie usunęli `Nothing`, to przy `sumM`, jeśli przynajmniej jeden element z listy jest równy `Nothing`, to cała suma jest równa `Nothing`.

Jeszcze dopiszę typy w każdym kroku

```haskell
    print $ sumM                                                  -- Maybe Int, ale ponieważ usunęliśmy Nothing-i mamy Just Int, naszą odpowiedź
            . filter (/= Nothing)                                 -- [Maybe Int], ale to lista tylko z wartościami postaci Just Int
            . map                                                 -- [Maybe Int], czyli lista wartości postaci Just Int lub Nothing
              (\(x,y) -> sum                                              -- Maybe Int, czyli Just Int lub Nothing
                         . filter ((&&) <$> (>= read x) <*> (<= read y))  -- Maybe Int, czyli Just [Int] lub Nothing
                         . sillyList                                      -- Maybe [Int], czyli Just [Int] lub Nothing
                         <$> niceRange (x,y)                              -- Maybe (Int, Int), czyli Just (Int, Int) lub Nothing
              )                             
            $ dane                                                -- [(String, String)]
```

### Druga część zadania

Funkcje pomocnicze `devideUp`, `devideDown`, `niceRange'` i `sillyList'` są analogiczne do odpowiednio funkcji `halveUp`, `halveDown`, `niceRange` i `sillyList`, jedynie dodatkowo biorą za pierwszy argument liczbę całkowitą `k`, która oznacza, na ile takich samych kawałków dzieli się niewłaściwe id.

```haskell
74 devideUp :: Int -> String -> Int      -- halveUp = devideUp 2
75 devideUp k s
76    | n `mod` k == 0 = read $ take nk s
77    | otherwise = read $ '1' : replicate nk '0'
78    where n = length s
79          nk = n `div` k
80
81 devideDown :: Int -> String -> Int    -- halveDown = devideDown 2
82 devideDown k s
83    | n `mod` k == 0 = read $ take nk s
84    | otherwise = read $ replicate nk '9'
85    where n = length s
86          nk = n `div` k
87
88 niceRange' :: Int -> (String, String) -> Maybe (Int, Int)  -- niceRange = niceRange' 2
89 niceRange' k (x,y)
90    | partX <= partY = Just (partX, partY)
91    | otherwise = Nothing
92    where partX = devideUp k x
93          partY = devideDown k y
94
95 sillyList' :: Int -> (Int, Int) -> [Int]                   -- sillyList = sillyList' 2
96 sillyList' k (x,y) = map (read . concat . replicate k . show) [x..y]
```

Funkcja `sillyList'` nieznacznie różni się od funkcji `sillyList`. Tutaj mapujemy funkcję `read . concat . replicate k . show`. `replicate k` tworzy nam listę `k` tych samych elementów, `concat` konkatenuje (czyli zlepia) elementy listy.

`concatM` to znów specjalna wersja `concat`, która radzi sobie z `Maybe`, tu też mogłam zamiast tego użyć `sequence` (`concatM = fmap concat . sequence`)

Na koniec przyjrzyjmy się rozwiązaniu:

```haskell
16    print $ fmap sum                                      -- sumujemy
17                 . concatM                                -- łączymy listy silly liczb dla różnych range'ów
18                 . map                                    -- dla każdego range'a w dane                     
19                   (fmap nub                                                   -- usuwamy duplikaty
20                         . concatM                                             -- łączymy listy silly liczb dla różnych k
21                         . filter (/= Nothing)                                 -- jak gdzieś było Nothing, to usuwamy
22                         . (\(x,y) -> map                                      -- dla każdego k
23                                      (\k -> filter ((&&) <$> (>= read x) <*> (<= read y))  -- filtrujemy silly liczby gdy nie są między x a y
24                                             . sillyList' k                                 -- lista możliwych silly liczb dla k i range'a (x,y)
25                                             <$> niceRange' k (x,y)                         -- możliwy range początków dla k i range'a (x,y)
26                                      )                        
27                                      [2..(max (length x) (length y))]                      -- k jest od 2 do max długości x i y
28                           )
29                   )
30          $ dane
```

Na `fmap` nie zwracajcie uwagi, bo to ten wyższy poziom abstrakcji, funkcja `nub` zwraca listę bez duplikatów.

A to opis rozwiązania z typami:

```haskell
    print $ fmap sum                                      -- Maybe Int postaci Just Int -- nasza odpowiedź
                 . concatM                                -- Maybe [Int] postaci Just [Int]
                 . map                                    -- [Maybe [Int]], ale to lista z elementami postaci Just [Int]                   
                   (fmap nub                                                   -- Maybe [Int] postaci  Just [Int]
                         . concatM                                             -- Maybe [Int], ale postaci Just [Int]
                         . filter (/= Nothing)                                 -- [Maybe [Int]], ale to lista z elementami tylko postaci Just [Int]
                         . (\(x,y) -> map                                      -- [Maybe [Int]], czyli lista, w której wartości są postaci Just [Int] lub Nothing
                                      (\k -> filter ((&&) <$> (>= read x) <*> (<= read y))  -- Maybe [Int], czyli Just [Int] lub Nothing
                                             . sillyList' k                                 -- Maybe [Int], czyli Just [Int] lub Nothing
                                             <$> niceRange' k (x,y)                         -- Maybe (Int, Int), czyli Just (Int, Int) lub Nothing
                                      )                        
                                      [2..(max (length x) (length y))]                      -- [Int]
                           )
                   )
          $ dane                                           -- [(String,String)]
```
