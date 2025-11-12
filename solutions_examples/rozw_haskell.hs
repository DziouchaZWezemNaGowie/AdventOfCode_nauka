import Data.List

main = do
    dane <- readFile "Dane/1.txt"
    let a = map (read . head . words) $ lines dane :: [Int]
        b = map (read . last . words) $ lines dane :: [Int]
    print "Rozwiazanie czesci pierwszej:"
    print $  foldl (\acc (x,y) -> abs (x - y) + acc) 0 $ zip (sort a) (sort b)
    print "Rozwiazanie czesci drugiej:"
    print $ foldl (\acc x -> (length . filter (== x) $ b)*x + acc) 0 a
