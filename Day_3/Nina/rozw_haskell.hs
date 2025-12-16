import Control.Monad

main = do
    dane <- lines <$> readFile "dane.txt"
    print "Rozwiazanie czesci pierwszej:"
    print $ sum . map (read . fst <$> (maxJoltage <=< ((\(x:xs) -> (x:) <$> maxJoltage xs) . reverse))) $ dane 
    print "Rozwiazanie czesci drugiej:"
    print $ sum . map (read . fst <$> (maxJoltage <=< (\(ys,xs) -> foldM (\acc y -> (y:) <$> maxJoltage acc) xs (reverse ys)) . splitAt 11 . reverse)) $ dane

maxJoltage :: String -> (String, String)
maxJoltage xs = foldr (\x (y,ys) -> if y >= [x]
                                    then (y,x:ys)
                                    else ([x],[])) ([last xs],[]) (init xs)
