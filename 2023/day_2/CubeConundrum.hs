import System.Environment (getArgs)
import System.IO

import Data.List.Split (splitOn)

data GameStats = GameStats { redMax :: Int, blueMax :: Int, greenMax :: Int }

main :: IO ()
main = do
    args <- getArgs
    case args of
        [input] -> do
            contents <- readFile input
            let partOne = show $ solvePartOne contents
            let partTwo = show $ solvePartTwo contents

            putStrLn $ "Part one: " ++ partOne
            putStrLn $ "Part two: " ++ partTwo

        _ -> putStrLn "Usage: program <input>"

    where
        solvePartOne :: String -> Int
        solvePartOne = solve partOne

        solvePartTwo :: String -> Int
        solvePartTwo = solve solveTwo

        solve :: (String -> [Int]) -> String -> Int
        solve buildFunction = sum . map (sum . buildFunction) . lines

        partOne :: String -> [Int]
        partOne = partOneChecker. splitter
            where
                -- Check if there are any to large values
                partOneChecker :: [String] -> [Int]
                partOneChecker [] = []
                partOneChecker (x1:x2:x3:x4:xs) = checkerBool False (x1:x2:x3:x4:xs)
                  where
                    checkerBool :: Bool -> [String] -> [Int]
                    checkerBool True [g, gn] = [0]
                    checkerBool False [g, gn] = [read gn]
                    checkerBool False (g:gn:cn:cc:rest)
                        | cc == "red" && read cn > 12 = checkerBool True [g, gn]
                        | cc == "green" && read cn > 13 = checkerBool True [g, gn]
                        | cc == "blue" && read cn > 14 = checkerBool True [g, gn]
                        | otherwise = checkerBool False (g:gn:rest)
                    checkerBool _ xs = error ("Unexpected pattern: " ++ show xs)

        solveTwo :: String -> [Int]
        solveTwo = partTwoChecker defaultGameStats . splitter
            where
                defaultGameStats :: GameStats
                defaultGameStats = GameStats { redMax = 0, blueMax = 0, greenMax = 0 }

                multiplyStats :: GameStats -> Int
                multiplyStats stats = redMax stats * greenMax stats * blueMax stats

                partTwoChecker :: GameStats -> [String] -> [Int]
                partTwoChecker stats [g, gn] = [multiplyStats stats]
                partTwoChecker stats (g:gn:cn:cc:rest)
                    | cc == "red" && read cn > redMax stats = partTwoChecker (updateRedMax stats cn) (g:gn:rest)
                    | cc == "green" && read cn > greenMax stats = partTwoChecker (updateGreenMax stats cn) (g:gn:rest)
                    | cc == "blue" && read cn > blueMax stats = partTwoChecker (updateBlueMax stats cn) (g:gn:rest)
                    | otherwise = partTwoChecker stats (g:gn:rest)

                    where
                        -- Update specific value
                        updateRedMax :: GameStats -> String -> GameStats
                        updateRedMax stats cn = stats { redMax = read cn }

                        updateGreenMax :: GameStats -> String -> GameStats
                        updateGreenMax stats cn = stats { greenMax = read cn }

                        updateBlueMax :: GameStats -> String -> GameStats
                        updateBlueMax stats cn = stats { blueMax = read cn }


        -- Split the string in logical parts
        splitter :: String -> [String]
        splitter = concatMap (splitOn " ") . concatMap (splitOn ": ") . concatMap (splitOn "; ") . splitOn ", "

