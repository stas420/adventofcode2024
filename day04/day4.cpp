#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> ReadInput()
{
    std::fstream file("input.txt", std::ios::in);
    std::vector<std::string> Output;

    if (file.is_open())
    {
        std::string line;

        while(std::getline(file, line))
        {
            Output.push_back(line);
        }

        file.close();
    }
    else
    {
        std::cout << "File not opened, skill issue" << std::endl;
    }

    return Output;
}

constexpr int MASsize = 3;
const char MAS[MASsize] = { 'M', 'A', 'S' };

const std::pair<std::int64_t, std::int64_t> Directories[8] = {
    std::make_pair(-1, 0), std::make_pair(-1, 1), std::make_pair(0, 1), std::make_pair(1, 1),
    std::make_pair(1, 0), std::make_pair(1, -1), std::make_pair(0 , -1), std::make_pair(1, -1)
};

std::uint16_t CheckXMAS(const std::vector<std::string>& search, const std::int64_t& i, const std::int64_t& j, 
                        const std::uint64_t& maxRow, const std::uint64_t& maxCol)
{
    std::uint64_t output = 0;
    std::int64_t _i = i;
    std::int64_t _j = j;
    std::uint8_t MASindex = 0;

    for (const std::pair<std::int64_t, std::int64_t>& dir : Directories)
    {
        _i = i + dir.first;
        _j = j + dir.second;
        MASindex = 0;

        while (MASindex < MASsize && _i >= 0 && _i <= maxRow && _j >= 0 && _j <= maxCol)
        {
            if (search[_i][_j] == MAS[MASindex])
            {
                MASindex++;
            }

            _i += dir.first;
            _j += dir.second;
        }

        if (MASindex == MASsize)
            output++;
    }

    return output;
}

void PartOne()
{
    std::vector<std::string> wordSearch = ReadInput();
    std::uint64_t ans = 0;
    const std::uint64_t maxRow = wordSearch.size() - 1;
    const std::uint64_t maxCol = wordSearch[0].length() - 1;

    for (std::int64_t i = 0; i <= maxRow; i++)
    {
        for (std::int64_t j = 0; j <= maxCol; j++)
        {
            if (wordSearch[i][j] == 'X')
                ans += CheckXMAS(wordSearch, i, j, maxRow, maxCol);
        }
    }

    std::cout << "Part one answer " << ans << std::endl;
}

int main()
{
    PartOne();
    //PartTwo();
}