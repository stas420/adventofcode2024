#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

struct Region
{
    std::vector<std::pair<std::uint64_t, std::uint64_t>> PlotCords;
    char PlantType;
};

std::vector<Region> ParseInput()
{
    std::vector<Region> Output;
    std::fstream file("input.txt", std::ios::in);

    if (file.is_open())
    {
        std::string line;
        std::vector<std::string> gardenMap;

        while (std::getline(file, line))
            gardenMap.push_back(line);
        
        file.close();

        // parse .txt input to vector of regions
        
    }
    else
    {
        std::cout << "File not opened, skill issue" << std::endl;
    }

    return Output;
}