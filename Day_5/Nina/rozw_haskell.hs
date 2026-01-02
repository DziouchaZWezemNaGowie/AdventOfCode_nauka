import Data.Tuple.Extra (both)

main = do
    (ranges,items) <- fmap (map read) . split (==[]) . lines <$> readFile "dane.txt" :: IO ([String], [Int])
    let fresh = map (both read . split (=='-')) ranges :: [(Int,Int)]
    print "Rozwiazanie pierwszej czesci:"
    print $ length . filter (\x -> any (between x) fresh) $ items
    print "Rozwiazanie drugiej czesci:"
    print $ sum . map (\(y,z) -> z - y + 1) . foldl newRange [] $ fresh

-- do wczytywania funkcji
split :: (a -> Bool) -> [a] -> ([a],[a])
split p l = (xs, drop 1 ys)
    where (xs, ys) = break p l

-- do pierwszej i drugiej części

between :: Int -> (Int, Int) -> Bool
between x (y,z) = x >= y && x <= z

-- do drugiej części

newRange :: [(Int, Int)] -> (Int, Int) -> [(Int, Int)]
newRange [] x = [x]
newRange xs x@(x1, x2)
    | (&&) <$> (not . any (between x1)) <*> (not . any (between x2)) $ xs          -- x1 i x2 nie są w żadnym range'u; usuwamy range'e między x1 a x2
        = x : filter (\(a,b) -> not (between a x)) xs                              -- wystarczy sprawdzić, czy tylko a jest między x1 a x2, bo w xs range'e są parami rozłączne
    | (start, (y,z) : end) <- break (between x1) xs                                -- x1 w jednym range'u
    , (start2, (y2, z2) : end2) <- break (between x2) (start ++ end)               -- a x2 w drugim
        = (y,z2) : filter (\(a,b) -> not (between a x)) (start2 ++ end2)
    | (start, (y,z) : end) <- break (between x1) xs                                -- tylko x1 w range'u lub x1, x2 w jednym
         = if x2 <= z then xs else (y,x2) : filter (\(a,b) -> not (between a x)) (start ++ end)
    | (start, (y,z) : end) <- break (between x2) xs                                -- tylko x2 w range'u
         = (x1,z) : filter (\(a,b) -> not (between a x)) (start ++ end)
