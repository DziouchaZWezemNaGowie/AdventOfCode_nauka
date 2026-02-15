{-# LANGUAGE MultiWayIf #-}

import Data.List.Split (splitOn)
import qualified Data.Heap as H
import qualified Data.Set as S
import Data.Foldable
import Data.List (sort)

type Point = (Double, Double, Double)

main = do
    dane <- map ((\[a,b,c] -> (a,b,c)) . map read . splitOn ",") .  lines <$> readFile "dane.txt" :: IO [Point]
    print "Rozwiazanie pierwszej czesci:"
    print . product . take 3 . reverse . sort . map S.size . S.toList . box 1000 S.empty . distances $ dane
    print "Rozwiananie drugiej czesci:"
    let n = length dane
    print . floor . uncurry (*) . boxing n S.empty . distances $ dane

-- pierwsza część
distance :: Point -> Point -> Double
distance (x1,y1,z1) (x2,y2,z2) = sqrt $ (x1 - x2)^2 + (y1 - y2)^2 + (z1 - z2)^2

distances :: [Point] -> H.Heap (Double,(Point, Point))
distances points = H.fromList [(distance a b, (a,b)) | a <- points, b <- points, a < b]

box :: Int -> S.Set (S.Set Point) -> H.Heap (Double, (Point,Point)) -> S.Set (S.Set Point)
box 0 bs xs = bs
box n bs xs = let 
 bs' = 
  if| H.null xs                       -> bs      -- można ten warunek usunąć, bo nie powinno do tego dojść
    | Just b1 <- find (S.member x) bs ->
        if | S.member y b1                   -> bs
           | Just b2 <- find (S.member y) bs -> S.insert (b1 <> b2) . S.delete b1 . S.delete b2 $ bs
           | otherwise                       -> S.insert (S.insert y b1) . S.delete b1 $ bs
    | Just b2 <- find (S.member y) bs -> S.insert (S.insert x b2) . S.delete b2 $ bs
    | otherwise                       -> S.insert (S.fromList [x,y]) bs
 in box (n-1) bs' xs'
 where (dist, (x,y)) = H.minimum xs
       xs' = H.deleteMin xs

-- druga część
-- box' robi jeden krok
box' :: S.Set (S.Set Point) -> H.Heap (Double, (Point, Point)) -> ((Double, Double), S.Set (S.Set Point))
box' bs xs = let 
 bs' =
  if| H.null xs                       -> error "Pusty heap"
    | Just b1 <- find (S.member x) bs ->
        if | S.member y b1                   -> bs
           | Just b2 <- find (S.member y) bs -> S.insert (b1 <> b2) . S.delete b1 . S.delete b2 $ bs
           | otherwise                       -> S.insert (S.insert y b1) . S.delete b1 $ bs
    | Just b2 <- find (S.member y) bs -> S.insert (S.insert x b2) . S.delete b2 $ bs
    | otherwise                       -> S.insert (S.fromList [x,y]) bs
 (xx,_,_) = x
 (xy,_,_) = y
 in ((xx,xy),bs')
 where (dist, (x,y)) = H.minimum xs

boxing :: Int  -> S.Set (S.Set Point) -> H.Heap (Double, (Point,Point)) -> (Double, Double)
boxing n bs xs = let 
    (xcoords,bs') = box' bs xs
    in if S.size bs' == 1 && S.size (S.elemAt 0 bs') == n
        then xcoords
        else boxing n bs' (H.deleteMin xs)
