#include <array>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>

constexpr unsigned short PossibleDirections = 4;
const std::array<std::pair<std::int64_t, std::int64_t>, PossibleDirections> Directions 
{ 
    std::make_pair(-1, 0), std::make_pair(0, 1), 
    std::make_pair(1, 0), std::make_pair(0, -1)
};

const char startingPosition = '^';

void PartOne(const std::string& fileName)
{
    std::fstream file(fileName, std::ios::in);

    if (file.is_open())
    {
        std::vector<std::string> situationMap;
        std::string line;

        while(std::getline(file, line))
        {
            situationMap.push_back(line);
        }

        file.close();

        std::pair<std::int64_t, std::int64_t> currPos;
        std::pair<std::int64_t, std::int64_t> currDir;
        unsigned short currDirIndex = 0;
        const std::int64_t maxRow = situationMap.size() - 1;
        const std::int64_t maxCol = situationMap[0].length() - 1;

        for (std::int64_t i = 0; i < situationMap.size(); i++)
        {
            for (std::int64_t j = 0; j < situationMap[i].length(); j++)
            {
                if (situationMap[i][j] == startingPosition)
                {
                    situationMap[i][j] = '.';
                    currPos.first = i;
                    currPos.second = j;
                    currDir = Directions[currDirIndex];
                    break;
                }
            }
        }
    
        std::uint64_t ans = 1;

        while (currPos.first > 0 && currPos.second > 0
               && currPos.first < maxRow && currPos.second < maxCol)
        {
            //std::cout << currPos.first << "; " << currPos.second << "\n";
            //std::cout << currDir.first << "; " << currDir.second << "\n";
            //std::cout << "--------------------------------\n";
            if (situationMap[currPos.first + currDir.first][currPos.second + currDir.second] != '#')
            {
                if (situationMap[currPos.first][currPos.second] != 'X')
                {
                    ans++;
                    situationMap[currPos.first][currPos.second] = 'X';
                }

                currPos.first += currDir.first;
                currPos.second += currDir.second;
            }
            else
            {
                currDirIndex++;

                if (currDirIndex == PossibleDirections)
                    currDirIndex = 0;
                
                currDir = Directions[currDirIndex];
            }

/*
            for (auto x : situationMap)
            {
                std::cout << x << std::endl;
            }
*/
        }

        std::cout << "Part one answer " << ans << std::endl;
        // 4826
    }
    else
    {
        std::cout << "File did not open, skill issue" << std::endl;
    }
}

void PartTwo(const std::string& fileName)
{
    std::fstream file(fileName, std::ios::in);

    if (file.is_open())
    {
        std::vector<std::string> situationMap;
        std::string line;

        while(std::getline(file, line))
        {
            situationMap.push_back(line);
        }

        file.close();

        std::pair<std::int64_t, std::int64_t> startPos;
        std::pair<std::int64_t, std::int64_t> currPos;
        std::pair<std::int64_t, std::int64_t> currDir;
        unsigned short currDirIndex = 0;
        const std::int64_t maxRow = situationMap.size() - 1;
        const std::int64_t maxCol = situationMap[0].length() - 1;

        for (std::int64_t i = 0; i < situationMap.size(); i++)
        {
            for (std::int64_t j = 0; j < situationMap[i].length(); j++)
            {
                if (situationMap[i][j] == startingPosition)
                {
                    situationMap[i][j] = '.';
                    startPos.first = i;
                    startPos.second = j;
                    currDir = Directions[currDirIndex];
                    break;
                }
            }
        }
    
    }
    else
    {
        std::cout << "File did not open, skill issue" << std::endl;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "no file given\n";
        return 1;
    }

    std::string file(argv[1]);

    PartOne(file);
    //PartTwo(file);


    return 0;
}