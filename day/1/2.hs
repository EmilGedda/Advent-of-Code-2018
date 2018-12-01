import Data.List.Extra
import Control.Arrow

main = print . solve =<< getContents

solve :: String -> Integer
solve = firstDuplicate . scanl (+) 0 . cycle . parseInput

parseInput :: String -> [Integer]
parseInput = map read . words . filter (/= '+')

firstDuplicate :: [Integer] -> Integer
firstDuplicate = head . uncurry drop . first matchingElements . ((nubOrd &&& id) &&& id) 

matchingElements :: ([Integer], [Integer]) -> Int
matchingElements = length . takeWhile id . uncurry (zipWith (==))

