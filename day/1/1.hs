main = print . sum . map read . words . filter (/= '+') =<< getContents 
