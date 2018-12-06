import Data.List
main = putStrLn . solve . words =<< getContents

unpack :: [a] -> (a, a)
unpack = (,) . head . drop 1 <*> head

elemDiff :: Eq a => ([a], [a]) -> Int
elemDiff = length . filter id . uncurry (zipWith (/=))

solve :: Eq a => [[a]] -> [a]
solve = uncurry intersect . head . filter ((==1) . elemDiff) 
       . map unpack . flip mapM [1, 2] . const 
