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
