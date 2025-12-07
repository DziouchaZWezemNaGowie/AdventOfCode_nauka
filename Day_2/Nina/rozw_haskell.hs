import Control.Monad (liftM2)
import Data.List (nub)
main = do
    dane <- map range . dziel <$> readFile "Zad_2.txt"
    print "Rozwiazanie cz. 1"
    print $ sumM                                                  -- sumujemy całość
            . filter (/= Nothing)                                 -- jak gdzieś było Nothing, to usuwamy
            . map                                                 -- dla każdego range'a w dane
              (\(x,y) -> sum                                              -- sumujemy silly liczby dla jednego range'a
                         . filter ((&&) <$> (>= read x) <*> (<= read y))  -- filtrujemy gdy nie są między x a y
                         . sillyList                                      -- lista możliwych silly liczb
                         <$> niceRange (x,y)                              -- możliwy range początków, jeśli początek z x > początek z y to Nothing
              )                             
            $ dane
    print "Rozwiazanie cz. 2"
    print $ fmap sum                                      -- sumujemy
                 . concatM                                -- łączymy listy silly liczb dla różnych range'ów
                 . map                                    -- dla każdego range'a w dane                     
                   (fmap nub                                                   -- usuwamy duplikaty
                         . concatM                                             -- łączymy listy silly liczb dla różnych k
                         . filter (/= Nothing)                                 -- jak gdzieś było Nothing, to usuwamy
                         . (\(x,y) -> map                                      -- dla każdego k
                                      (\k -> filter ((&&) <$> (>= read x) <*> (<= read y))  -- filtrujemy silly liczby gdy nie są między x a y
                                             . sillyList' k                                 -- lista możliwych silly liczb dla k i range'a (x,y)
                                             <$> niceRange' k (x,y)                         -- możliwy range początków dla k i range'a (x,y)
                                      )                        
                                      [2..(max (length x) (length y))]                      -- k jest od 2 do max długości x i y
                           )
                   )
          $ dane

-- funkcje do wczytywania
dziel :: String -> [String]
dziel [] = []
dziel s = let (range, rest) = break (== ',') s
          in range : dziel (drop 1 rest)

range :: String -> (String, String)
range s = let (x,y) = break (== '-') s
          in (x, drop 1 y)

-- funkcje do pierwszej części zadania
halveUp :: String -> Int
halveUp s
    | even n = read $ take n2 s
    | otherwise = read $ '1' : replicate n2 '0'
    where n = length s
          n2 = n `div` 2

halveDown :: String -> Int
halveDown s
    | even n = read $ take n2 s
    | otherwise = if n2 == 0
                  then 0
                  else read $ replicate n2 '9'
    where n = length s
          n2 = n `div` 2

niceRange :: (String, String) -> Maybe (Int, Int)
niceRange (x, y)
    | polX <= polY = Just (polX, polY)
    | otherwise = Nothing
    where polX = halveUp x
          polY = halveDown y

sillyList :: (Int, Int) -> [Int]
sillyList (x,y) = map (read . (\x -> x ++ x) . show) [x..y]

sumM :: (Monad m, Num a) => [m a] -> m a
sumM = foldr (liftM2 (+)) (return 0)

-- funkcje do drugiej części zadania

devideUp :: Int -> String -> Int      -- halveUp = devideUp 2
devideUp k s
    | n `mod` k == 0 = read $ take nk s
    | otherwise = read $ '1' : replicate nk '0'
    where n = length s
          nk = n `div` k

devideDown :: Int -> String -> Int    -- halveDown = devideDown 2
devideDown k s
    | n `mod` k == 0 = read $ take nk s
    | otherwise = read $ replicate nk '9'
    where n = length s
          nk = n `div` k

niceRange' :: Int -> (String, String) -> Maybe (Int, Int)  -- niceRange = niceRange' 2
niceRange' k (x,y)
    | partX <= partY = Just (partX, partY)
    | otherwise = Nothing
    where partX = devideUp k x
          partY = devideDown k y

sillyList' :: Int -> (Int, Int) -> [Int]                   -- sillyList = sillyList' 2
sillyList' k (x,y) = map (read . concat . replicate k . show) [x..y]

concatM :: (Monad m) => [m [a]] -> m [a]
concatM = foldr fromMonad (pure [])
    where fromMonad xm accm = do
            x <- xm
            acc <- accm
            return $ x ++ acc
