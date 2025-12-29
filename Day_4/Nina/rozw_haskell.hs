main = do
    dane <- map (map liczbuj) . lines <$> readFile "dane.txt"
    print "Rozwiązanie czesci pierwszej:"
    print $ length . concatMap (filter (<=4) . filter (>0)) . sasiedzi $ dane
    print "Rozwiazanie czesci drugiej:"
    print $ rob dane

-- funkcja do wczytywania danych

liczbuj :: Char -> Int
liczbuj '.' = 0
liczbuj '@' = 1

-- funkcje do pierwszej części zadania

bezIndeksu :: Int -> [a] -> [a]
bezIndeksu n = (++) <$> take (n-1) <*> drop n

sasiedzi :: [[Int]] -> [[Int]]
sasiedzi x = foldr
             (zipWith (zipWith (\a b -> if b == 0 then 0 else a + b)))  -- dodawaj, o ile w polu w x nie ma 0
             x
             . bezIndeksu 5                         -- wyrzuć środkowe z 9 pól
             . map ($ x)                            -- zaaplikuj do x
             $ (.) 
               <$> [ (replicate n 0 :) . init          -- górny sąsiad
                   , id                                -- środek
                   , (++ [replicate n 0]) . tail       -- dolny sąsiad
                   ]
               <*> [ map ((0:) . init)                 -- lewy sąsiad
                   , id                                -- środek
                   , map ((++ [0]) . tail)             -- prawy sąsiad
                   ]
    where n = length . head $ x

-- funkcje do drugiej czesci zadania

rob :: [[Int]] -> Int
rob x
    | any (any ((&&) <$> (>0) <*> (<=4))) y = (length . concatMap (filter (<=4) . filter (>0)) $ y) + rob (map (map (\a -> if a <= 4 then 0 else 1)) y)
    | otherwise = 0
    where y = sasiedzi x
