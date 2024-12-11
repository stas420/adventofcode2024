#include <iostream>
#include <fstream>
#include <optional>
#include <vector>
#include <string>
#include <cstdint>
#include <map>

std::vector<std::uint64_t> ParseInput()
{
    std::fstream file("input.txt", std::ios::in);
    std::vector<std::uint64_t> Output;

    if (file.is_open())
    {
        std::string line;
        std::getline(file, line);

        file.close();
        
        std::uint64_t tmp = 0;

        for (std::uint64_t i = 0; i < line.length(); i++)
        {
            if (isdigit(line[i]))
            {
                tmp = atoll(&line[i]);
                Output.push_back(tmp);
                i += std::to_string(tmp).length();
            }
        }
    }
    else
    {
        std::cout << "File not opened, skill issue" << std::endl;
    }

    return Output;
}

std::pair<std::uint64_t, std::optional<std::uint64_t>> ProcessOneStone(const std::uint64_t& Stone)
{
    std::pair<std::uint64_t, std::optional<std::uint64_t>> Output;
    Output.second = {};

    if (Stone == 0)
    {
        Output.first = 1;
        return Output;
    }

    std::string stone = std::to_string(Stone);

    if (stone.length() % 2 == 0)
    {
        Output.first = std::stoull(stone.substr(0, stone.length()/2));
        Output.second = std::stoull(stone.substr(stone.length()/2, stone.length()/2));
        return Output;
    }
    else
    {
        Output.first = Stone * 2024;
        return Output;
    }
}

void PartOne(const std::uint32_t& Blinks)
{
    std::vector<std::uint64_t> Stones = ParseInput();
    std::vector<std::uint64_t> StonesCopy;
    
    std::pair<std::uint64_t, std::optional<std::uint64_t>> tmp;
    std::uint64_t j = 0;
    std::uint64_t size = 0;

    for (std::uint32_t i = 0; i < Blinks; i++)
    {
        size = Stones.size();
        StonesCopy.clear();
        StonesCopy.reserve(2 * size);

        for (j = 0; j < size; j++)
        {
            tmp = ProcessOneStone(Stones[j]);
            StonesCopy.push_back(tmp.first);

            if (tmp.second)
                StonesCopy.push_back(tmp.second.value());
        }

        Stones = StonesCopy;
    }

    std::cout << "Part one answer " << Stones.size() << std::endl;
    // 209412
}

std::map<std::uint64_t, std::uint64_t> FurtherOccurences(std::map<std::uint64_t, std::uint64_t> Stones)
{
    std::map<std::uint64_t, std::uint64_t> next;
    std::string s;

    for (std::pair<const std::uint64_t, std::uint64_t>& pair : Stones)
    {
        s = std::to_string(pair.first);

        if (pair.first == 0)
        {
            next[1] += pair.second;
        }
        else if (s.length() % 2 == 0)
        {
            next[std::stoull(s.substr(0, s.length()/2))] += pair.second;
            next[std::stoull(s.substr(s.length()/2, s.length()))] += pair.second;
        } 
        else
        {
            next[pair.first * 2024] += pair.second;
        }
    }

    return next;
}

void PartTwo(const std::uint32_t& Blinks)
{
    std::vector<std::uint64_t> Stones = ParseInput();
    std::map<std::uint64_t, std::uint64_t> stoneOccurences;
    std::map<std::uint64_t, std::uint64_t>::iterator iter;

    for (std::uint64_t& stone : Stones)
    {
        iter = stoneOccurences.find(stone);

        if (iter == stoneOccurences.end())
            stoneOccurences.insert({ stone, 1 });
        else
            iter->second++;
    }

    for (std::uint32_t i = 0; i < Blinks; i++)
    {
        stoneOccurences = FurtherOccurences(stoneOccurences);
    }

    std::uint64_t a = 0;

    for (std::pair<const std::uint64_t, std::uint64_t>& s : stoneOccurences)
    {
        a += s.second;
    }

    std::cout << "Part two result " << a << std::endl;
    // 248967696501656
}

int main()
{
    //PartOne(25); //< brute-forced, but with a class *sparkles*
    PartTwo(75); //< tried some other approach I found on reddit lol

    return 0;
}