###### *English below if needed eventually*
# Uczmy się programować z Advent of Code 2025!

## O projekcie
  Projekt ma na celu rozwijać nasze programistyczne umiejętności rozwiązując zadania z [Advent of Code](https://adventofcode.com/), omawiając ~co tydzień na żywo nasze rozwiązania (lub próby rozwiązań) zadań

## Jak dołączyć?
  Dodajcie się do tabelki w pliku [`participants.md`](https://github.com/DziouchaZWezemNaGowie/AdventOfCode/blob/main/participants.md) + jeśli nie ma was na serwerze na Discordzie, napiszcie do mnie (DziouchyZWężemNaGowie) DMa gdziekolwiek.

## Spotkania i deadline na rozwiązanie zadań
  Będziemy się spotykać co tydzień w weekendy (dokładne terminy do ustalenia, co tydzień to wstępny rozkład, na pewno będą przerwy na święta, nowy rok itd.) i omawiać rozwiązania. Spotkania nie są obowiązkowe (będę starała się dać też jakiś feedback na GitHubie), 
  
  Swoje rozwiązania proszę zamieszczać na GitHubie (w tym repozytorium) w odpowiednim folderze najpóźniej na dobę przed planowanym spotkaniem.

  Jeśli **wszyscy** rozwiążą więcej zadań niż przewidziane na dany tydzień, to spotkanie może dotyczyć kilku zadań, a następny tydzień będzie dotyczył kolejnego nierozwiązanego zadania, o ile wszyscy się na to zgodzą.

## Przygotowanie
  Dobrze zanim rozpoczniemy naszą przygodę wiedzieć, jak w waszym wybranym języku załadować dane z pliku .txt (Advent of Code wyświetla wam dane w nowym oknie przeglądarki, więc najłatwiej jest wcisnąć `Ctrl + A`, `Ctrl + C` i potem wkleić całość do notatnika). Tak, wiem, może kusić, żeby wkleić sobie te dane do ładnej tabelki w Excelu i potem od razu wczytać dane w formie tabelki do waszego programu (o ile wasz język lubi pracę z  tabelkami, jak `R` np.), ale dobrze jest jednak całość zadania rozwiązać w swoim języku programowania. W zależności od języka, niektóre kursy wprowadzają wczytywanie danych z pliku na dość późnym etapie, więc jeśli jeszcze do niego nie dotarliście, to warto ten jeden aspekt uzupełnić.

  *Fun fact:* Dane do zadań w części praktycznej matury z informatyki są w formie plików .txt 😃

  W folderze [solution_examples](https://github.com/DziouchaZWezemNaGowie/AdventOfCode_nauka/tree/main/solutions_examples) znajduje się skrót treści [zadania 1 z 2024 r.](https://adventofcode.com/2024/day/1) oraz rozwiązania w różnych językach (jak waszego tam brakuje, to za niedługo dodam rozwiązanie), więc możecie spróbować rozwiązać te zadania samodzielnie, a potem porównać z zamieszczonymi przeze mnie rozwiązaniami.

## Sposób rozwiązania
  Ważne jest rozwiązanie zadań samemu. Można oczywiście korzystać z wszelkich pomocy naukowych (podręczników, tutoriali, notatek z zajęć itd.) Jeśli chodzi o AI bynajmniej **nie** używajcie go do rozwiązania za was zadań, jak nie jesteście pewni, czy możecie w danej sytuacji użyć AI służę przykładem.

  Popatrzmy na pierwszą część [zadania z dnia 1 2024 r.](https://adventofcode.com/2024/day/1)

  ### :x: Co nie jest OK?
  Napisanie do AI:

  :x: *Hej, jak rozwiązać część pierwszą zadania z pierwszego dnia AoC z 2024 r.?*
    
  :x: *Hej, jak rozwiązać takie zadanie:* <<wklejona treść zadania>>
    
  :x: *Mam dane liczbowe w pliku .txt w dwóch kolumnach. Zadanie polega na posortowaniu tych kolumn osobno od najmniejszej do największej, a następnie dodaniu wartości bezwględnych różnic w wierszach między posortowanymi kolumnami. Jak to rozwiązać?*

  ### ✅ Co jest OK?
  Napisanie do AI:

  *Jak nazywa się funkcja sortująca w <<moim języku>>?*
  *Kompilator wyrzuca mi <<taki a taki błąd>> co to oznacza?*
  
  Ewentualne zapytania typu:

  *Mam dane liczbowe w dwóch kolumnach w pliku .txt. Jak mogę w <<moim języku>> załadować je tak, aby pierwszą kolumnę przypisać do wektora/listy/innej struktury danych `a` (typu `int`/`Int`/itd. jak macie język przykładający dużą wagę do typów), a drugą do tej samej struktury danych, którą nazwę `b`?*

  Albo nawet pytanie typu:

  *To mój kod, i nie umiem znaleźć w nim błędu. Czemu to nie działa?*

  Też są OK, jeśli inne opcje was zawiodły. Najważniejsze, żeby algorytm (sposób rozwiązania zadania) był waszego autorstwa. Jednak najlepiej by było, żebyście używali AI co najwyżej jako podrasowanej wyszukiwarki. Pamiętajcie, że celem tego projektu jest rozwinięcie waszych umiejętności, a co to za programista, co tylko kopiuje kod wyhalucynowany przez chatGPT?
  
## Leaderboard

Poza prywatnym leaderboardem na Advent of Code, gdzie przyznawane są gwiazdki za każdą rozwiązaną część zadania + liczy się czas stworzymy sobie własny leaderboard, gdzie za każdą część zadania można dostać 4 punkty (czyli za całe zadanie 8):

- 1 punkt, jeśli rozwiązanie działa poprawnie dla przykładu podanego w treści zadania.
- 2 punkty, jeśli rozwiązanie działa dla przykładu z treści oraz waszego inputu, ale nie jest rozwiązaniem formalnie poprawnym (tj. nie zadziałałoby dla dowolnego inputu)
- 3 punkty, jeśli rozwiązanie działa poprawnie dla przykładu podanego w treści zadania oraz jest formalnie poprawnym rozwiązaniem zadania, ale program nie działa dla waszego inputu przez ograniczenia czasowe/obliczeniowe komputera (np. rozwiązanie jest poprawne, ale komputer musiałby pracować tydzień non-stop, żeby wyliczyć odpowiedź)
- 4 punkty, jeśli rozwiązanie działa dla przykładu z treści, waszego inputu oraz jest rozwiązaniem formalnie poprawnym.

## Umieszczanie rozwiązań na GitHubie

Rozwiązania umieszczamy w folderze dotyczącym konkretnego dnia. Jeśli foldera nie ma, możecie go stworzyć (przy umieszczaniu pliku w nazwie pliku zamiast `plik.rozszerzenie` piszecie `nazwa_foldera/plik.rozszerzenie`), nadając folderowi nazwę analogiczną do innych (`Day_n`).
