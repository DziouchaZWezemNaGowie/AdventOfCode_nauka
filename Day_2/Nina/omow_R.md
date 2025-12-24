### Wczytywanie danych

Zaczynamy tradycyjnie od wczytania biblioteki

```r
library(tidyverse)
```

Następnie wczytujemy dane

```r
dane <- read_delim("Zad_2.txt", col_names = FALSE) %>% 
  t() %>% 
  as_tibble() %>% 
  separate_wider_delim(V1, delim = "-", names = c("start", "koniec"))
```

`read_delim()` domyślnie rozdziela dane na przecinkach (i usuwa białe znaki na bokach danych). Wczytuje jednak dane jako poziomą tabelę, a my chcemy potrzebujemy pionowej, więc robimy `t()` (transpozycję tabeli, czyli zamianę wierszy i kolumn i vice-versa), `as_tibble()` zmienia nam całość w `tibble`, taką specjalną ładną tabelkę, na której zazwyczaj się pracuje w `tidyverse`. Na koniec robimy `seperate_wider_delim()`, jest to funkcja, która bierze kolumne w tibble (u nas to jedyna kolumna, nazwana przez dotychczasowe operacje `V1`) i znak rozdzielający `delim`, a następnie rozdziela dane w podanej kolumnie rozdzielone znakiem `delim` na kilka kolumn o nazwach podanych w parametrze `names`. Dostajemy `tibble` o 2 kolumnach: `start` i `koniec`, z liczbami (ale jako stringami) oznaczającymi początki i końce przedziałów, w których szukamy złych id.

### Rozwiązanie pierwszej części zadania

Zaczynamy od zdefiniowania funkcji `devide`:

```r
# wyciągnij część, co będzie powtarzana

devide <- function(start, koniec,k=2){
  
dl_start <-  str_width(start)
dl_koniec <-  str_width(koniec)
dziel_start <-  floor(dl_start / k)
dziel_koniec <- floor(dl_koniec / k)

part_start <- if_else(dl_start %% k == 0,
                      strtrim(start, dziel_start),
                      paste0("1",str_dup('0', dziel_start)))
part_koniec <- if_else(dl_koniec %% k == 0,
                       strtrim(koniec, dziel_koniec),
                       str_dup('9', dziel_koniec))

return(list(part_start = part_start,
            part_koniec = part_koniec))
}
```

Funkcja `devide` bierze za agumenty `start` i `koniec` przeszukiwanego przedziału oraz parametr `k`, ile powtarzających się części będzie miało dane id (domyślnie `2`). Omówmy ją krok po kroku.

```r
dl_start <-  str_width(start)
dl_koniec <-  str_width(koniec)
dziel_start <-  floor(dl_start / k)
dziel_koniec <- floor(dl_koniec / k)
```

Przypisujemy do zmiennych długość stringów `start` i `koniec` — `dl_start` i `dl_koniec` oraz jak długie będą powtarzane fragmenty — `dziel_start` i `dziel_koniec` (podłoga z dzielenia).

```r
part_start <- if_else(dl_start %% k == 0,
                      strtrim(start, dziel_start),
                      paste0("1",str_dup('0', dziel_start)))
part_koniec <- if_else(dl_koniec %% k == 0,
                       strtrim(koniec, dziel_koniec),
                       str_dup('9', dziel_koniec))
```

`part_start` i `part_koniec` tworzą przedział stringów, które będziemy powtarzać `k` razy i sprawdzać, czy powstała w ten sposób liczba jest w przedziale od `start` do `koniec`. Jeśli `dl_start` jest podzielna przez `k`, to przypisujemy do `part_start` pierwsze `dziel_start` znaków stringa `start`, w przeciwnym wypadku przypisujemy stringa utworzonego z `1` i `dziel_start` zer (pierwszą 1/k-tą stringa o długości podzielnej przez `k` większego (jako liczba) od `start`). Podobnie dla `part_koniec`, jeśli `dl_koniec` jest podzielna przez `k`, to przypisujemy do `part_koniec` pierwsze `dziel_koniec` znaków stringa `koniec`, w przeciwnym wypadku string złożony z `dziel_koniec` dziewiątek (pierwszą 1/k-tą stringa o długości podzielnej przez `k` mniejszego (jako liczba) od `koniec`).

```r
return(list(part_start = part_start, # element listy o nazwie "part_start" jest równy part_start
            part_koniec = part_koniec))
```

Na koniec zwracamy `part_start` i `part_koniec` razem w formie listy.

Dalej mamy określoną funkcję `lacz`:

```r
# zliczanie nieprawidłowych raportów

lacz <- function(start, koniec, a, b, k=2){
  start <- start %>% as.numeric()
  koniec <- koniec %>% as.numeric()
  a <- a %>% as.numeric()
  b <- b %>% as.numeric()
  wynik <- 0
  
  for(i in a:b){
    i <- i %>% as.character()
    x <- str_dup(i,k) %>% as.numeric()
    if (x>= start && x <= koniec)
      wynik <- wynik + x
  }
  return(wynik)
}
```
Bierze ona argumenty `start`, `koniec`, `a`, `b` oraz `k` domyślnie równe `2`. Będziemy powtarzać pewnego stringa `k` razy, a potem sprawdzać, czy powstała w ten sposób liczba jest między `start` a `koniec`. Powtarzany string (jako liczba) ma być między `a` a `b`.

```r
  start <- start %>% as.numeric()
  koniec <- koniec %>% as.numeric()
  a <- a %>% as.numeric()
  b <- b %>% as.numeric()
  wynik <- 0
```

Na początku zmieniamy typy zmiennych `start`, `koniec`, `a` i `b` na liczbowy (`numeric`) i przypisujemy do zmiennej `wynik` zero.

```r
  for(i in a:b){
    i <- i %>% as.character()
    x <- str_dup(i,k) %>% as.numeric()
    if (x>= start && x <= koniec)
      wynik <- wynik + x
  }
```

W pętli `for` dla `i` od `a` do `b` (z obu stron włącznie) zmieniamy `i` na stringa, powtarczamy go `k` razy (to robi `str_dup(i,k)`) i zmieniamy na liczbę. Jeśli powstała w ten sposób liczba jest między `start` a `koniec`, to dodajemy ją do wyniku.

```r
  return(wynik)
```

Na koniec zwracamy `wynik`.

Wreszcie możemy przyjrzeć się rozwiązaniu części pierwszej:

```r
# Rozwiązanie części pierwszej

dane %>% 
  rowwise() %>% 
  mutate(tmp = list(devide(start, koniec))) %>% 
  unnest_wider(tmp) %>% 
  rowwise() %>% 
  filter(part_start <= part_koniec) %>% 
  mutate(ile = lacz(start, koniec, part_start, part_koniec)) %>% 
  ungroup() %>% 
  summarise(sum(ile))
```

Bierzemy `dane` i dla każdego wiersza (`rowwise()`) wykonujemy `devide`. polecenie `mutate(tmp = list(devide(start, koniec))) %>% unnest_wider(tmp)` doda nam do tabelki `dane` dwie kolumny: `part_start` i `part_koniec` z wydzielonymi powtarzanymi częściami dla `start` i `koniec` w danym wierszu. Dalej po wierszach (`rowwise()`) filtrujemy tylko te wiersze, w których `part_start <= part_koniec`, po czym tworzymy nową kolumnę — `ile`, w której mamy (dla każdego wiersza) wartość funkcji `lacz(start, koniec, part_start, part_koniec)`), czyli sumę nieprawidłowych id znajdujących się w danym zakresie. Potem robimy `ungroup()`, które anuluje nam wcześniejsze `rowwise()`, bo chcemy wykonać operację nie po wierszach, a dla całej tabeli, a mianowicie sumujemy wartości w kolumnie `ile`.
