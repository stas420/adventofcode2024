#include <string>
#include <fstream> // file IO
#include <vector>
#include <iostream>
#include <cstdint> // for fixed width integers
#include <unordered_map>

const std::string test = "test.txt";
const std::string input = "input.txt";

constexpr int MASsize = 3;
const char MASarray[MASsize] = { 'M', 'A', 'S' };

enum Direction { 
    UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT 
};

namespace std {
    template <>
    struct hash<Direction> {
        std::size_t operator()(Direction d) const noexcept {
            return static_cast<std::size_t>(d);
        }
    };
}

// map enum Direction -> { x, y } cords change
const std::unordered_map<Direction, std::pair<std::int8_t, std::int8_t>> DirectionsMap = {
    { Direction::UP, { 0, -1 } },
    { Direction::UP_RIGHT, { 1, -1 } },
    { Direction::RIGHT, { 1, 0 } },
    { Direction::DOWN_RIGHT, { 1, 1 } },
    { Direction::DOWN, { 0, 1 } },
    { Direction::DOWN_LEFT, { -1, 1 } },
    { Direction::LEFT, { -1, 0 } },
    { Direction::UP_LEFT, { -1, -1 } }
};

bool XMAScheck(const std::vector<std::string>& search, std::int64_t row, std::int64_t col,
               const std::uint32_t& maxRow, const std::uint32_t& maxCol, 
               const Direction& direction)
{
    std::pair<std::int8_t, std::int8_t> d = DirectionsMap.find(direction)->second;
    std::cout << "dir " << d.first << " | " << d.second << std::endl;

    std::int8_t index = 0;

    while ((index < (MASsize - 1)) && (col >= 0) && (col <= maxCol) 
            && (row >= 0) && (row <= maxRow))
    {
        row += d.first;
        col += d.second;

        if (search[row][col] != MASarray[index])
            return false;
        
        index++;
    }

    return true;
}

void PartOne()
{
    std::fstream file(test, std::ios::in);

    if (file.is_open())
    {
        std::vector<std::string> wordSearch;
        std::string tmp;

        while(std::getline(file, tmp))
        {
            wordSearch.push_back(tmp);
        }

        file.close();

        const std::uint32_t rows = wordSearch.size();
        const std::uint32_t cols = wordSearch[0].length();
        std::vector<Direction> dirs;
        std::uint32_t answer = 0;
        Direction dir = Direction::UP;

        for (std::int64_t i = 0; i < rows; i++)
        {
            for (std::int64_t j = 0; j < cols; j++)
            {
                if (wordSearch[i][j] == 'X')
                {
                    dirs.clear();

                    if (i > MASsize)
                        dirs.push_back(Direction::UP);

                    if (i < (rows - MASsize))
                        dirs.push_back(Direction::DOWN);

                    if (j > MASsize)
                        dirs.push_back(Direction::LEFT);

                    if (j < (cols - MASsize))
                        dirs.push_back(Direction::RIGHT);

                    if ((i > MASsize) && (j > MASsize))
                        dirs.push_back(Direction::UP_LEFT);

                    if ((i > MASsize) && (j < (cols - MASsize)))
                        dirs.push_back(Direction::UP_RIGHT);

                    if ((i < (rows - MASsize)) && (j > MASsize))
                        dirs.push_back(Direction::DOWN_LEFT);

                    if ((i < (rows - MASsize)) && (j < (cols - MASsize)))
                        dirs.push_back(Direction::DOWN_RIGHT);


                    std::cout << dirs.size() << std::endl;

                    for (Direction d : dirs)
                    {
                        if (XMAScheck(wordSearch, i, j, (rows - 1), (cols - 1), d))
                            answer++;
                    }                    
                }
            }
        }

        std::cout << "Part one answer " << answer << std::endl;
    }
    else
    {
        std::cout << "File not opened, skill issue" << std::endl;
    }
}

void PartTwo()
{
    std::fstream file(test, std::ios::in);

    if (file.is_open())
    {

    }
    else
    {
        std::cout << "File not opened, skill issue" << std::endl;
    }
}

int main()
{
    for (auto x : DirectionsMap)
    {
        std::cout << x.second.first << " | " << x.second.second << "\n";
    }

    //PartOne();
    //PartTwo();

    return 0;
}