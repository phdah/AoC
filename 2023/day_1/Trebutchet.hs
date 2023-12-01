import System.Environment (getArgs)
import System.IO

import Data.Char (isDigit, digitToInt)
import Data.Maybe (fromJust)
import Data.List (isPrefixOf)

main :: IO ()
main = do
    args <- getArgs
    case args of
        [input] -> do
            contents <- readFile input

            let partOne = show $ solvePartOne $ lines contents
            let partTwo = show $ solvePartTwo $ lines contents

            -- putStrLn $ "Part one: " ++ partOne
            putStrLn $ "Part two: " ++ partTwo

        _ -> putStrLn "Usage: program <input>"

    where
        solvePartOne :: [String] -> Int
        solvePartOne = sum . map buildNumber

        solvePartTwo :: [String] -> Int
        solvePartTwo = solvePartOne . map filterDigits

            where
                filterDigits :: String -> String
                filterDigits [] = []
                filterDigits (firstChar:restOfChars)
                    | "one"     `isPrefixOf` (firstChar:restOfChars) = '1' : filterDigits restOfChars
                    | "1"       `isPrefixOf` (firstChar:restOfChars) = '1' : filterDigits restOfChars
                    | "two"     `isPrefixOf` (firstChar:restOfChars) = '2' : filterDigits restOfChars
                    | "2"       `isPrefixOf` (firstChar:restOfChars) = '2' : filterDigits restOfChars
                    | "three"   `isPrefixOf` (firstChar:restOfChars) = '3' : filterDigits restOfChars
                    | "3"       `isPrefixOf` (firstChar:restOfChars) = '3' : filterDigits restOfChars
                    | "four"    `isPrefixOf` (firstChar:restOfChars) = '4' : filterDigits restOfChars
                    | "4"       `isPrefixOf` (firstChar:restOfChars) = '4' : filterDigits restOfChars
                    | "five"    `isPrefixOf` (firstChar:restOfChars) = '5' : filterDigits restOfChars
                    | "5"       `isPrefixOf` (firstChar:restOfChars) = '5' : filterDigits restOfChars
                    | "six"     `isPrefixOf` (firstChar:restOfChars) = '6' : filterDigits restOfChars
                    | "6"       `isPrefixOf` (firstChar:restOfChars) = '6' : filterDigits restOfChars
                    | "seven"   `isPrefixOf` (firstChar:restOfChars) = '7' : filterDigits restOfChars
                    | "7"       `isPrefixOf` (firstChar:restOfChars) = '7' : filterDigits restOfChars
                    | "eight"   `isPrefixOf` (firstChar:restOfChars) = '8' : filterDigits restOfChars
                    | "8"       `isPrefixOf` (firstChar:restOfChars) = '8' : filterDigits restOfChars
                    | "nine"    `isPrefixOf` (firstChar:restOfChars) = '9' : filterDigits restOfChars
                    | "9"       `isPrefixOf` (firstChar:restOfChars) = '9' : filterDigits restOfChars
                    | otherwise = filterDigits restOfChars

        buildNumber :: String -> Int
        buildNumber line = 10*firstDigit line + lastDigit line

        firstDigit :: String -> Int
        firstDigit = fromJust . foldr keepFirstNumber Nothing

        lastDigit :: String -> Int
        lastDigit = firstDigit . reverse

        keepFirstNumber :: Char -> Maybe Int -> Maybe Int
        keepFirstNumber c acc = if isDigit c then Just (digitToInt c) else acc


