#include <string>
#include <fstream> // file IO
#include <vector>
#include <iostream>
#include <cstdint> // for fixed width integers
#include <map>

const std::string test = "test.txt";
const std::string input = "input.txt";

void PartOne()
{
    std::fstream file(test, std::ios::in);

    if (file.is_open())
    {
        std::map<char, std::uint64_t> letters = {
            { 'X', 0 }, { 'M', 0 }, { 'A', 0 }, { 'S', 0 } 
        };

        std::map<char, std::uint64_t>::iterator iter;

        std::string line;

        while (std::getline(file, line))
        {
            for (char ch : line)
            {
                iter = letters.find(ch);

                if (iter != letters.end())
                {
                    iter->second++;
                }
            }
        }

        for (auto i : letters)
        {
            std::cout << i.first << " | " << i.second << std::endl;
        }
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
    PartOne();
    //PartTwo();

    return 0;
}