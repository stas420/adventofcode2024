#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cstdint>
#include <algorithm>

using AntennaMap_t = std::map<char, std::vector<std::pair<std::int64_t, std::int64_t>>>;
using Antenna_t = std::pair<const char, std::vector<std::pair<std::int64_t, std::int64_t>>>;
using Coords_t = std::pair<std::int64_t, std::int64_t>;

std::int64_t maxRowIndex = 0;
std::int64_t maxColIndex = 0;

AntennaMap_t ParseInput()
{
    std::fstream file("input.txt", std::ios::in);
    AntennaMap_t map;

    if (file.is_open())
    {
        std::string line;
        std::uint64_t i = 0;
        std::uint64_t j = 0;

        while(std::getline(file, line))
        {
            for (i = 0; i < line.length(); i++)
            {
                if (line[i] != '.')
                {
                    map[line[i]].push_back(std::make_pair(j, i));
                }
            }

            j++;
        }

        maxRowIndex = j - 1;
        maxColIndex = i - 1;

        file.close();
    }
    else
    {
        std::cout << "File not opened, skill issue" << std::endl;
    }

    return map;
}

std::vector<Coords_t> foundAntinodes;

std::int64_t CheckTwoCords(const Coords_t& first, const Coords_t& second,
                              const std::int64_t& maxRow, const std::int64_t& maxCol)
{
    std::int64_t output = 0;

    const Coords_t diff = std::make_pair(
        abs(first.first - second.first), abs(first.second - second.second)
    );

    Coords_t antinode = std::make_pair(0, 0);

    if (first.first < second.first)
    {
        if (first.second < second.second)
        {
            antinode.first = first.first - diff.first;
            antinode.second = first.second - diff.second;

            if (antinode.first >= 0 && antinode.second >= 0)
            {
                if (std::find(foundAntinodes.begin(), foundAntinodes.end(), antinode) == foundAntinodes.end())
                {
                    foundAntinodes.push_back(antinode);
                    output++;
                }
            }

            antinode.first = second.first + diff.first;
            antinode.second = second.second + diff.second;

            if (antinode.first <= maxRow && antinode.second <= maxCol)
            {
                if (std::find(foundAntinodes.begin(), foundAntinodes.end(), antinode) == foundAntinodes.end())
                {
                    foundAntinodes.push_back(antinode);
                    output++;
                }
            }

        }
        else
        {  
            antinode.first = first.first - diff.first;
            antinode.second = first.second + diff.second;

            if (antinode.first >= 0 && antinode.second <= maxCol)
            {
                if (std::find(foundAntinodes.begin(), foundAntinodes.end(), antinode) == foundAntinodes.end())
                {
                    foundAntinodes.push_back(antinode);
                    output++;
                }
            }
            
            antinode.first = second.first + diff.first;
            antinode.second = second.second - diff.second;

            if (antinode.first <= maxRow && antinode.second >= 0)
            {
                if (std::find(foundAntinodes.begin(), foundAntinodes.end(), antinode) == foundAntinodes.end())
                {
                    foundAntinodes.push_back(antinode);
                    output++;
                }
            }
        }
    }
    else
    {
        if (first.second >= second.second)
        {
            antinode.first = first.first + diff.first;
            antinode.second = first.second + diff.second;

            if (antinode.first <= maxRow && antinode.second <= maxCol)
            {
                if (std::find(foundAntinodes.begin(), foundAntinodes.end(), antinode) == foundAntinodes.end())
                {
                    foundAntinodes.push_back(antinode);
                    output++;
                }
            }

            antinode.first = second.first - diff.first;
            antinode.second = second.second - diff.second;

            if (antinode.first >= 0 && antinode.second >= 0)
            {
                if (std::find(foundAntinodes.begin(), foundAntinodes.end(), antinode) == foundAntinodes.end())
                {
                    foundAntinodes.push_back(antinode);
                    output++;
                }
            }
        }
        else
        {
            antinode.first = first.first + diff.first;
            antinode.second = first.second - diff.second;

            if (antinode.first <= maxRow && antinode.second >= 0)
            {
                if (std::find(foundAntinodes.begin(), foundAntinodes.end(), antinode) == foundAntinodes.end())
                {
                    foundAntinodes.push_back(antinode);
                    output++;
                }
            }

            antinode.first = second.first - diff.first;
            antinode.second = second.second + diff.second;

            if (antinode.first >= 0 && antinode.second <= maxCol)
            {
                if (std::find(foundAntinodes.begin(), foundAntinodes.end(), antinode) == foundAntinodes.end())
                {
                    foundAntinodes.push_back(antinode);
                    output++;
                }
            }
        }
    }

    return output;
}

void PartOne()
{
    AntennaMap_t map = ParseInput();
    std::uint64_t i = 0;
    std::uint64_t j = 0;
    std::uint64_t answer = 0;

    for (Antenna_t& a : map)
    {
        for (i = 0; i < a.second.size(); i++)
        {
            for (j = i + 1; j < a.second.size(); j++)
            {
                answer += CheckTwoCords(a.second[i], a.second[j], maxRowIndex, maxColIndex);
            }
        }
    }

    std::cout << "Part one answer " << answer << std::endl;
    // 256
}

int main()
{
    PartOne();
    return 0;
}