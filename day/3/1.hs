import Prelude hiding (id)
import Control.Applicative
import Data.Either
import Numeric.Matrix hiding (map, sum)
import Text.Parsec
import Text.Parsec.Char
import Text.Parsec.String
import Text.Parsec.Combinator

main = print
        -- . sum . filter (>1) 
        -- . concat . toList
        . coordinates . head
        -- . foldr (flip mergeClaim) fabric 
        . parseInput =<< getContents

coordinates :: Claim -> [(Int, Int)]
coordinates c = liftA2 (,) [x..x+w] [y..y+h]
        where
            x = fst $ position c
            y = snd $ position c
            w = fst $ size c
            h = snd $ size c

mergeClaim :: Matrix Int -> Claim -> Matrix Int
mergeClaim m = foldr (setValue (+1)) m . coordinates

setValue :: MatrixElement f => (f -> f) -> (Int, Int) -> Matrix f -> Matrix f
setValue f pos m = mapWithIndex (\idx e -> if idx == pos then f e else e) m

fabric :: Matrix Int
fabric = matrix (1000, 1000) (const 0)

claimMatrix :: Claim -> Matrix Int
claimMatrix c = matrix (size c) (const 1)

parseInput :: String -> [Claim]
parseInput = rights . map (parse claim' "(stdin)") . lines 

data Claim = Claim { id :: Int
                   , position :: (Int, Int)
                   , size :: (Int, Int)
                   } deriving (Show)

integer :: Parser Int
integer = read <$> many1 digit

around :: Parser x -> Parser a -> Parser b -> Parser (a, b)
around skip f g = do
    a <- f
    _ <- skip
    b <- g
    return (a, b)

id' :: Parser Int
id' =  read <$> (char '#' *> many1 digit)

position' :: Parser (Int, Int)
position' = around (char ',') integer integer

size' :: Parser (Int, Int)
size' = around (char 'x') integer integer

claim' :: Parser Claim
claim' = do
    a <- id'
    b <- between (string " @ ") (string ": ") position'
    c <- size'
    return $ Claim a b c
