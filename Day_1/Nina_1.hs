data Rotation = L Int | R Int

instance Read Rotation where
    readsPrec _ s = let (oks,r) = span (/= ' ') s
                    in case oks of
                       ('L':xs) -> [(L $ read xs, "")]
                       ('R':xs) -> [(R $ read xs, "")]
                       _ -> error "Źle zapisane dane!"

turn :: Int -> Rotation -> Int
turn s (L r) = (s - r) `mod` 100
turn s (R r) = (s + r) `mod` 100

main = do
    dane <- map read . lines <$> readFile "Dane/Zad_1.txt" :: IO [Rotation]
    print "Rozwiazanie cz. 1:"
    print $ length . filter (==0) . foldl (\acc x -> turn (head acc) x : acc) [50] $ dane
    print "Rozwiazanie cz. 2:"
    print $ snd . foldl (\(s, i) x -> let (y, j) = turn0 s x in (y, i+j)) (50,0) $ dane

turn0 :: Int -> Rotation -> (Int, Int)
turn0 s (L r) = let x = s - r
                in (x `mod` 100, abs (x `div` 100) + 
                                (if x `mod` 100 == 0 then 1 else 0) + 
                                (if s == 0 then -1 else 0))
turn0 s (R r) = let x = s + r
                in (x `mod` 100, x `div` 100)
