#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

void ParseInput(std::vector<std::string>& OutputAvailablePatterns, 
                std::vector<std::string>& OutputDesiredDesigns)
{
    std::fstream file("input.txt", std::ios::in);
    
    if (file.is_open())
    {
        std::string line;
        unsigned long i = 0;

        // read available patterns
        std::getline(file, line);
        OutputAvailablePatterns.push_back("");

        for (i = 0; i < line.length(); i++)
        {
            if (line[i] == ',')
            {
                OutputAvailablePatterns.push_back("");                
            }
            else if (line[i] != ' ')
            {
                OutputAvailablePatterns.back().append({ line[i] });
            }
        }

        // read desired designs
        while (std::getline(file, line))
        {
            if (!line.empty())
            {
                OutputDesiredDesigns.push_back(line);
            }
        }

        file.close();
    }   
    else
    {
        std::cout << "File not opened, skill issue" << std::endl;
    }
}

void PartOne()
{
    std::vector<std::string> Patterns, Designs, Stack;
    ParseInput(Patterns, Designs);

    std::sort(Patterns.begin(), Patterns.end(), 
        [](const std::string& first, const std::string& second)
        {
            return first.length() > second.length();
        }
    );

    unsigned long ans = 0;


    std::cout << "Part one answer " << ans << std::endl;
}

int main()
{
    PartOne();
    //PartTwo();
    return 0;
}