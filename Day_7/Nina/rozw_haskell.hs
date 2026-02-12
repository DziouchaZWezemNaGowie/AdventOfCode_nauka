import Data.List (transpose, foldl')
import Data.Set (Set, singleton, insert, delete, mapMonotonic) 
import Data.Sequence (Seq, fromList, elemIndexL, (!?))
import Data.Map (Map, insertWith, foldrWithKey)
import qualified Data.Map as M

main = do
    (start:dane) <- map fromList . lines <$> readFile "dane.txt"
    let Just i = 'S' `elemIndexL` start
    print "Rozwiazanie czesci pierwszej:"
    print . snd $ foldl' findSplits (singleton i,0) dane
    print "Rozwiazanie czesci drugiej:"
    --print $ possibleWorlds dane i              -- strasznie wolne rozwiązanie
    print . snd $ foldl' findSplits' (M.singleton i 1,1) dane

-- do pierwszej części
findSplits :: (Set Int, Int) -> Seq Char -> (Set Int,Int)
findSplits (is,n) x = let
    checkingFunc i (s,k) = case x !? i of
        Just '^' -> (delete i . insert (i - 1) . insert (i + 1) $ s, k + 1)
        Nothing  -> (delete i s,k)     -- ten przypadek tak naprawdę nie powinien zachodzić
        _        -> (s,k)
    in foldr checkingFunc (is,n) is

-- do drugiej części
-- possibleWorlds jest wolne: > 2 h
possibleWorlds :: [Seq Char] -> Int -> Int
possibleWorlds [] _ = 1
possibleWorlds (x:xs) i = case x !? i of
    Just '^' -> possibleWorlds xs (i - 1) + possibleWorlds xs (i + 1)
    Just _   -> possibleWorlds xs i
    Nothing  -> 0                      -- ten przypadek tak naprawdę nie powinien zachodzić

-- findSplits' jest szybkie: (2.09 secs, 13,721,744 bytes) (cały program)
findSplits' :: (Map Int Int, Int) -- (pary (indeks, liczba ścieżek do tego indeksu), liczba ścieżek overall)
            -> Seq Char
            -> (Map Int Int,Int)
findSplits' (is,n) x = let
    checkingFunc i ni (s,k) = case x !? i of
        Just '^' -> (M.delete i . insertWith (+) (i - 1) ni . insertWith (+) (i + 1) ni $ s, k + ni)
        Nothing  -> (M.delete i s,k)   -- ten przypadek tak naprawdę nie powinien zachodzić
        _        -> (s,k)
    in foldrWithKey checkingFunc (is,n) is
