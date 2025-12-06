### Słowem wstępu

Haskell to czysto deklaratywny (dokładnie funkcyjny) język programowia z silnym, statycznym typowaniem. Poza tym Haskell to obecnie mój ulubiony język, ale postaram się zbytnio nie rozwodzić. Najprościej wyjaśnić, o co chodzi w tym języku można w kilku punktach:

1. Wszystko jest funkcją (stałe/zmienne to funkcje 0-argumentowe).
2. Nazwy funkcji są pisane z małych liter, a typów, klas, modułów (pakietów, bibliotek) z dużej.
3. Kompilator musi wiedzieć, jaki typ co ma.
4. Zamiast mówić programowi co ma robić (jak w językach imperatywnych), mówimy czym rzeczy są.
5. Dlatego nie ma pętli, a dane są niezmienialne (jak napiszemy gdzieś w kodzie, że `x = 5`, to `x == 5` już zawsze).
6. Funkcje traktujemy tak jak lubił Haskell Curry (stąd nazwa), czyli zamiast `f(x,y,z)` piszemy `f x y z`.
7. Jak definiujemy funkcję, to możemy to zrobić w kilku linijkach, zapisując jak funkcja ma działać dla argumentów takiej, a nie innej postaci.

Wymusza to trochę inny styl programowania niż w językach (głównie) imperatywnych, jak C++, Python czy R (chociaż one korzystają trochę z funkcyjności).

Wyjaśnię moje rozwiązanie zadania 1 w możliwie jak najprostszy sposób.

### Omówienie rozwiązania zadania krok po kroku

Tak wygląda mój plik z rozwiązaniem obu części zadania pierwszego.

```haskell
data Rotation = L Int | R Int

instance Read Rotation where
    readsPrec _ s = let (oks,r) = span (/= ' ') s
                    in case oks of
                       ('L':xs) -> [(L $ read xs, "")]
                       ('R':xs) -> [(R $ read xs, "")]
                       _ -> error "Źle zapisane dane!"

turn :: Int -> Rotation -> Int
turn s (L r) = (s - r) `mod` 100
turn s (R r) = (s + r) `mod` 100

main = do
    dane <- map read . lines <$> readFile "Zad_1.txt" :: IO [Rotation]
    print "Rozwiazanie cz. 1:"
    print $ length . filter (==0) . foldl (\acc x -> turn (head acc) x : acc) [50] $ dane
    print "Rozwiazanie cz. 2:"
    print $ snd . foldl (\(s, i) x -> let (y, j) = turn0 s x in (y, i+j)) (50,0) $ dane

turn0 :: Int -> Rotation -> (Int, Int)
turn0 s (L r) = let x = s - r
                in (x `mod` 100, abs (x `div` 100) + 
                                (if x `mod` 100 == 0 then 1 else 0) + 
                                (if s == 0 then -1 else 0))
turn0 s (R r) = let x = s + r
                in (x `mod` 100, x `div` 100)
```

Omówmy je krok po kroku. Na początku mamy

```haskell
data Rotation = L Int | R Int                           -- nowy typ Rotation

instance Read Rotation where                            -- jak wczytać ze stringa s typ Rotation
    readsPrec _ s = let (oks,r) = span (/= ' ') s       -- dziwny kod, bo z powodów historycznych wczytywanie trzeba tak dziwnie zdefiniować
                    in case oks of
                       ('L':xs) -> [(L $ read xs, "")]
                       ('R':xs) -> [(R $ read xs, "")]
                       _ -> error "Źle zapisane dane!"  -- użyłam nieopatrznie polskiego znaku!
```

na to nawet nie ma co patrzeć, to tylko ja bawię się stworzeniem specjalnego typu dla danych które dostajemy. Myślałam sobie, że może w drugiej części zadania okaże się, że L i R znaczą coś innego, no ale gdybym była mądrzejsza, to po prostu wczytałabym dane postaci `L<liczba>` jako liczby ujemne, a `R<liczba>` jako liczby dodatnie.

Potem mamy zdefiniowane 3 funkcje: `turn`, `main` i `turn0`. Kolejność zapisania nie ma znaczenia, więc zacznijmy od funkcji `main`, która, jak to główna funkcja, jest wywoływana przez kompilator przy kompilacji.

```haskell
main = do                                                                      -- funkcja main ma typ IO (), czyli jest operacją wejścia-wyjścia, która nic nie zwraca, ale może printować coś w outpucie konsoli
    dane <- map read . lines <$> readFile "Zad_1.txt" :: IO [Rotation]    -- ładowanie danych
    print "Rozwiazanie cz. 1:"
    print $ length . filter (==0) . foldl (\acc x -> turn (head acc) x : acc) [50] $ dane -- print liczbę, która jest rozwiązaniem cz. 1
    print "Rozwiazanie cz. 2:"
    print $ snd . foldl (\(s, i) x -> let (y, j) = turn0 s x in (y, i+j)) (50,0) $ dane   -- print liczbę, która jest rozwiązaniem cz. 2
```

Składnia funkcji main jest napisana w sposób imperatywny, ale to tylko taki sposób zapisu (powstrzymuję się nad rozwodzeniem). `do` oznacza, że robimy po kolei to, co mamy w kolejnych linijkach niżej. Pierwsza linijka to wczytywanie danych.

```haskell
    dane <- map read . lines <$> readFile "Zad_1.txt" :: IO [Rotation]
```

Tam mamy

```haskell
map read . lines <$> readFile "Zad_1.txt"
```

Znak `.` oznacza składanie funkcji, a `<$>` taką specjalną aplikację, nie musicie nic z tego rozumieć, chodzi o to, że czytamy od prawej, co po kolei robi ten kawałek.

```haskell
readFile "Zad_1.txt"
```

To nam wczytuje dane z pliku `Zad_1.txt` to takiego wielkiego stringa, który wygląda tak: `"L45\nR35\n..."`. Chcemy dostać listę (w C++ tablicę) naszych instrukcji, więc robimy

```haskell
lines <$> readFile "Zad_1.txt"
```

Funkcja `lines` bierze naszego wielkiego stringa, i robi z niego listę stringów. Znakiem oddzielającym kolejne stringi z listy, którą dostaniemy, w naszym wielkim stringu jest znak nowej linii `'\n'`. Teraz mamy listę `["L45","R35",...]`. Robimy

```haskell
map read . lines <$> readFile "Zad_1.txt"
```

Funkcja `map read` wczyta nam każdy element naszej listy. Musimy tylko jej dać znać, jakiego typu mają być dane po wczytaniu. Dlatego piszę:

```haskell
map read . lines <$> readFile "Zad_1.txt" :: IO [Rotation] -- a :: B oznacza "a jest typu B"
```

`::` oznacza przypisanie typu po prawej wyrażeniu po lewej. Typ `IO [Rotation]` oznacza, że dostajemy operację wejścia-wyjścia (bo wczytujemy dane z zewnątrz), która zwraca nam listę rotacji — `Rotation`

Na koniec

```haskell
dane <- map read . lines <$> readFile "Zad_1.txt" :: IO [Rotation]
```

Przypisujemy całość do stałej `dane`. Strzałka `<-` wyciąga nam listę z `IO`, czyli `dane` ma typ `[Rotation]`, jest listą rotacji.

Jak bym była mądrzejsza i nie definiowała specjalnego typu `Rotation`, to pewnie zrobiłabym coś w tym stylu:

```haskell
wczytaj :: String -> Int              -- definiuję nową funkcję wczytaj, która bierze String i zwraca Int; zapis x:lista oznacza listę, która na początku ma x, a potem jest lista lista, String to lista Char
wczytaj ('L':xs) = (-1) * (read xs)   -- jeśli String zaczyna się od 'L', to wczytujemy (-1) * liczba, którą wczyta nam systemowa funkcja read z reszty Stringa
wczytaj ('R':xs) = read xs            -- jeśli String zaczyna się od 'R', to wczytujemy po prostu liczbę

main = do
  dane <- map wczytaj . lines <$> readFile "Zad_1.txt" :: IO [Int]
...
```

Dalej mamy

```haskell
    print "Rozwiazanie cz. 1:"
```

Czyli po prostu printujemy w konsoli "Rozwiązanie cz. 1:". Potem jest

```haskell
    print $ length . filter (==0) . foldl (\acc x -> turn (head acc) x : acc) [50] $ dane
```

Tutaj pojawia się funkcja `turn`, więc najpierw ją wyjaśnijmy:

```haskell
turn :: Int -> Rotation -> Int     -- funkcja ma dwa argumenty, Int s - liczba od której startujemy i Rotation, zwraca nam Int, liczbę, na której znajdujemy się po obróceniu pokrętła z s o podaną rotację
turn s (L r) = (s - r) `mod` 100   -- jak obracamy w lewo o r, to zwracamy (s - r) modulo 100
turn s (R r) = (s + r) `mod` 100   -- jak obracamy w prawo o r, to zwracamy (s - r) modulo 100
```

Funkcja `turn` ma 2 argumenty, pozycję startową s i rotację, zwraca nam liczbę całkowitą (Int), na której ląduje pokrętło po jednej rotacji. `mod` to modulo w Haskellu, zwraca nam resztę z dzielenia liczby przez 100 w przez 100 w przedziale <0,99>.

Jak bym była mądrzejsza i wczytywała rotacje jako ujemne i dodatnie liczby, to napisałabym po prostu coś takiego:

```haskell
turn :: Int -> Int -> Int
turn s r = (s + r) `mod` 100
```

Teraz możemy przeanalizować linijkę z rozwiązaniem cz. 1, znów idąc od prawej do lewej.

```haskell
foldl (\acc x -> turn (head acc) x : acc) [50] $ dane   -- nie przejmujcie się $
```

`foldl` to tzw. funkcja składająca, de facto zastępuje ona pętle. Ma ona trzy argumenty: funkcję, którą wykonujemy "składanie"

```haskell
(\acc x -> turn (head acc) x : acc)
```

tzw. akumulator startowy

```haskell
[50]     -- lista z 1 elementem - 50
```

i listę, którą będziemy składać

```haskell
dane
```

A działa to tak: Funkcja

```haskell
(\acc x -> turn (head acc) x : acc)
```

bierze akumulator – `acc` i element listy `dane` – `x` i wykonuje

```haskell
turn (head acc) x
```

Czyli obrót z pozycji `head acc`, czyli pierwszego elementu listy `acc`, naszego akumulatora o `x`, a następnie dopisuje go na początek listy `acc`, co jest zapisane jako

```haskell
turn (head acc) x : acc    -- nowa lista, która na początku ma turn (head acc) x, a potem kolejne elementy z `acc`
```

Wykonujemy funkcję, przy której pomocy składamy najpierw dla akumulatora startowego – `[50]` i pierwszego elementu listy `dane`, dostajemy w ten sposób nowy akumulator, dla którego znów wykonujemy tę funkcję dla drugiego elementu listy `dane` itd. aż przejdziemy całą listę. W rezultacie otrzymamy listę wszystkich pozycji, na których spoczywa wskaźnik pokrętła po każdym obrocie, ale w odwrotnej kolejności.

Wiem, że może być trudno ogarnąć, co tu się dzieje, więc powiem, że jest to równoważne takiej pętli `for` w Pythonie:

```python
acc = [50]
for x in dane:
  s = acc[0]
  acc.insert(0, turn(s,x))    # zakładam, że mam gdzieś zdefiniowane turn jako funkcję 2-argumentową
```

a takiej pętli `for` w C++

```cpp
int n = dane.size();
int acc[n];
acc[n-1] = 50;

for(i = 0; i < n; i++)
  x = dane[i];
  acc[n - 2 - i] = turn(acc[n - 1 - i], x);
```

Ufff... No to jak mamy już listę wszystkich pozycji, na których spoczywa pokrętło po kolejnych obrotach, to robimy

```haskell
filter (==0) . foldl (\acc x -> turn (head acc) x : acc) [50] $ dane
```

czyli filtrujemy tę listę tak, że zostają nam same zera, które w niej były. A potem

```haskell
length . filter (==0) . foldl (\acc x -> turn (head acc) x : acc) [50] $ dane
```

długość tej listy, co daje nam ilość zer, na których pokrętło się zatrzymało, czyli rozwiązanie cz. 1. Printujemy wynik.

OK, teraz cz. 2:

```haskell
    print $ snd . foldl (\(s, i) x -> let (y, j) = turn0 s x in (y, i+j)) (50,0) $ dane
```

Znów zaczynamy od `foldl`:

```haskell
foldl (\(s, i) x -> let (y, j) = turn0 s x in (y, i+j)) (50,0) $ dane
```

W środku jest funkcja `turn0`, więc najpierw jej się przyjrzyjmy:

```haskell
turn0 :: Int -> Rotation -> (Int, Int)
turn0 s (L r) = let x = s - r                                          -- co oznacza x
                in (x `mod` 100, abs (x `div` 100) +                   -- po in mamy co zwraca funkcja
                                (if x `mod` 100 == 0 then 1 else 0) + 
                                (if s == 0 then -1 else 0))
turn0 s (R r) = let x = s + r                                          -- co oznacza x
                in (x `mod` 100, x `div` 100)                          -- po in mamy co zwraca funkcja.
```

Funkcja `turn0` ma 2 argumenty: pozycję, z której obracamy pokrętło – `s` i rotację, a zwraca nam parę liczb całkowitych. Pierwszą liczbą w parze będzie pozycja pokrętła po wykonaniu obrotu, a drugą, ile razy w trakcie wykonywania obrotu pokrętło minęło (lub skończyło na) `0`.

Jeśli wykonujemy obrót w lewo, to odejmuję od pozycji startowej `s` liczbę o ile obracam – `r`; oznaczam sobie `x = s - r`. Pokrętło po obrocie znajduje się na pozycji ```x `mod` 100```. Minęliśmy ```abs (x `div` 100)``` zer (`abs` to wartość bezwzględna, a `div` dzielenie całkowite/podłoga z dzielenia, czyli największa liczba całkowita <= wynikowi z dzielenia) + tak jak pisałam przy waszych rozwiązaniach, trzeba zawrzeć poprawki: jeśli wylądowaliśmy na zerze, to trzeba dodać 1, a jeśli startowaliśmy z zera, to trzeba odjąć 1.

Jeśli wykonujemy obrót w prawo, to dodaję do pozycji startowej `s` liczbę `r`; oznaczam sobie `x = s + r`. Pokrętło wylądowało na ```x `mod` 100```, a zero minęliśmy ```x `div` 100``` razy.

Jak bym była mądrzejsza i wczytywała dane jako liczby, to mogłabym napisać coś takiego:

```haskell
turn0 :: Int -> Int -> (Int, Int)
turn0 s r = let x = s + r
            in (x `mod` 100, abs (x `div` 100) +
                             if r < 0
                             then (if x `mod` 100 == 0 then 1 else 0) +
                                  (if s == 0 then -1 else 0)
                             else 0
               )
```

Wracając do funkcji `main`, przyjrzyjmy się teraz

```haskell
foldl (\(s, i) x -> let (y, j) = turn0 s x in (y, i+j)) (50,0) $ dane
```

Akumulator startowy to para (50, 0) – bo zaczynamy z pokrętłem na `50` i mamy `0` zer miniętych. Składamy funkcją, która bierze za argumenty akumulator postaci `(s,i)` i rotację `x` z listy `dane`. Oznaczamy `(y,j) = turn0 s x` i zwracamy nowy akumulator `(y, i + j)`. Po przejściu całej listy dostajemy parę uporządkowaną, gdzie pierwszy element to liczba na której spoczęło pokrętło po wszystkich obrotach, a druga to liczba miniętych zer, czyli nasze rozwiązanie. Funkcja `snd` zwraca drugi element pary uporządkowanej, 

```haskell
snd . foldl (\(s, i) x -> let (y, j) = turn0 s x in (y, i+j)) (50,0) $ dane
```

Da nam rozwiązanie cz. 2, które na koniec printujemy w konsoli.

### Uwaga na koniec

Oczywiście mogłam rozwiązanie cz. 1 napisać w podobny sposób jak rozwiązanie części drugiej, czyli zamiast

```haskell
print $ length . filter (==0) . foldl (\acc x -> turn (head acc) x : acc) [50] $ dane
```

zrobić

```haskell
print $ snd . foldl (\(s,i) x -> let y = turn s x
                                 in (y, i + if y == 0
                                            then 1
                                            else 0
                                    )
                    ) (50, 0)
      $ dane
```

To rozwiązanie ma taką samą złożoność czasową, ale lepszą złożoność pamięciową. Moje pierwotne rozwiązanie ma złożoność pamięciową O(n) (gdzie n – liczba danych), a to O(1), ponieważ tamte rozwiązanie wymaga od komputera trzymania całej listy pozycji pokrętła, a to tylko pary liczb.

Żeby nie było, że siebie się nie czepiam 😉
