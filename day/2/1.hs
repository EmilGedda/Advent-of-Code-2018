import Data.List
main = print . solve . words =<< getContents

solve :: [String] -> Int
solve =  product . map length . group . sort 
        . filter ((||) <$> (==2) <*> (==3)) 
        . concatMap (nub . map length . group . sort)
