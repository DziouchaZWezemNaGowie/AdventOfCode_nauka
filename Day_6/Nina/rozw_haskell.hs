import Data.List (transpose)
import Data.Char (isSpace)
import Data.List.Split (splitWhen)

main = do
    dane <- lines <$> readFile "dane.txt"
    -- pierwsza czesc
    let liczby = map (map read) . transpose . map words . init $ dane :: [[Int]]
    let operatory = words . last $ dane
    print "Rozwiazanie pierwszej czesci:"
    print $ licz operatory liczby
    -- druga czesc
    let liczby2 = map (map read) . splitWhen null . map (filter (not . isSpace)) . transpose . init $ dane :: [[Int]]
    -- operatory są takie same
    print "Rozwiazanie drugiej czesci:"
    print $ licz operatory liczby2

-- funkcja pomocnicza
licz :: [String] -> [[Int]] -> Int
licz ops = sum . zipWith (\x -> foldr1 (case x of "+" -> (+); "*" -> (*))) ops
