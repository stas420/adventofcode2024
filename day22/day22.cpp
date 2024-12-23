#include <fstream>
#include <vector>
#include <cstdint>
#include <iostream>
#include <string>
#include <map>
#include <array>

std::vector<std::uint64_t> ParseInput()
{
    std::fstream file("input.txt", std::ios::in);
    std::vector<std::uint64_t> output;

    if (file.is_open())
    {
        std::string line;

        while (std::getline(file, line))
        {
            output.push_back(std::stoull(line));
        }

        file.close();
    }
    else
    {
        std::cout << "File not opened, skill issue" << std::endl;
    }

    return output;
}

std::uint64_t NextSecretNumber(std::uint64_t n)
{
    static constexpr std::uint64_t X = 16777216;

    // step one
    n = (n ^ (n << 6)) % X;

    // step two
    n = (n ^ (n >> 5)) % X;

    // step three
    n = (n ^ (n << 11)) % X;

    return n;
}

void PartOne(const std::uint64_t& Iterations)
{
    std::vector<std::uint64_t> InitialNumbers = ParseInput();
    std::uint64_t i = 0, ans = 0;

    for (std::uint64_t& x : InitialNumbers)
    {
        i = 0;

        while (i < Iterations)
        {
            x = NextSecretNumber(x);
            i++;
        }

        ans += x;
    }

    std::cout << "Part one answer " << ans << std::endl;
    // 15613157363
}

void PartTwo(const std::uint64_t& Iterations)
{
    std::vector<std::uint64_t> InitialNumbers = ParseInput();
    std::vector<std::vector<std::uint64_t>> Prizes;
    std::vector<std::vector<std::int64_t>> Changes;
    std::map<std::array<std::int64_t, 4>, std::uint64_t> SequenceToBananas, tmpMap;
    std::map<std::array<std::int64_t, 4>, std::uint64_t>::iterator mapIter;

    Prizes.reserve(InitialNumbers.size());
    Changes.reserve(InitialNumbers.size());
    
    std::uint64_t i = 0;

    // for each buyer
    for (std::uint64_t& n : InitialNumbers)
    {
        tmpMap.clear();
        Prizes.push_back(std::vector<std::uint64_t>());
        Prizes.back().reserve(Iterations + 1);
        
        Changes.push_back(std::vector<std::int64_t>());
        Changes.back().reserve(Iterations);
        
        i = 0;
        // read each buyer's prize for the spot
        Prizes.back().push_back(n % 10);

        while(i < Iterations)
        {
            n = NextSecretNumber(n);
            Prizes.back().push_back(n % 10);
            i++;
        }

        // then calculate the prize changes
        i = 0;

        while (i < Prizes.back().size() - 1)
        {
            Changes.back().push_back(Prizes.back()[i + 1] - Prizes.back()[i]);
            i++;
        }

        // and for every set of four consecutive prize changes
        // find the first time this set occurs and find how many bananas there is available
        // ^ store this information as a map (4 changes -> bananas)
        i = 0;

        while (i < Changes.back().size() - 4)
        {
            if (((Changes.back()[i] != 0)  &&  (Changes.back()[i+2] != 0)) //<
               ||(Changes.back()[i+1] != 0) && (Changes.back()[i+3] != 0)) //< idk if important ("consecutive" != 0000, 000n etc.)
            {
                mapIter = tmpMap.find(
                    { Changes.back()[i], Changes.back()[i+1], 
                      Changes.back()[i+2], Changes.back()[i+3] }
                );

                if (mapIter == tmpMap.end())
                {
                    tmpMap.insert({
                        { Changes.back()[i], Changes.back()[i+1], 
                          Changes.back()[i+2], Changes.back()[i+3] },
                        Prizes.back()[i+4]
                    });
                }
            }

            i++;
        }

        // for each entry in map, insert the nonexistent ones to a global map
        // or add found occurences to already-existing ones
        for (std::pair<const std::array<std::int64_t, 4>, std::uint64_t>& x : tmpMap)
        {
            mapIter = SequenceToBananas.find(x.first);

            if (mapIter == SequenceToBananas.end())
            {
                SequenceToBananas.insert(x);
            }
            else
            {
                mapIter->second += x.second;
            }
        }
    } // repeat for each buyer

    // finally, find the 4-set which happens to have the most bananas
    std::pair<std::array<std::int64_t, 4>, std::uint64_t> tmp;
    tmp.first = {};
    tmp.second = 0;

    for (std::pair<const std::array<std::int64_t, 4>, std::uint64_t>& entry : SequenceToBananas)
    {
        if (entry.second > tmp.second)
        {
            tmp.first = entry.first;
            tmp.second = entry.second;
        }
    }

    std::cout << "Part two answer " << tmp.second << std::endl;
    // 1784
}

int main()
{
    //PartOne(2000);
    PartTwo(2000);
    return 0;
}