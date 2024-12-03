#include <string>
#include <fstream> // file IO
#include <vector>
#include <iostream>
#include <cstdint> // for fixed width integers
#include <regex>

const std::string test = "test.txt";
const std::string input = "input.txt";

std::pair<std::int64_t, std::int64_t> parseMul(const std::string& mulStr)
{
    std::pair<std::int64_t, std::int64_t> output;
    std::int64_t tmp = 0;
    bool second = false;

    for (std::uint32_t i = 0; i < mulStr.length(); i++)
    {
        if (isdigit(mulStr[i]))
        {
            tmp = atoll(&mulStr[i]);
            i += std::to_string(tmp).length();

            if (second)
            {
                output.second = tmp;
                break;
            }
            else
            {
                output.first = tmp;
                second = true;
            }
        }
        else
        {
            i++;
        }
    }

    return output;
}

void PartOne()
{
    std::fstream file(test, std::ios::in);

    if (file.is_open())
    {
        std::string line;
        while (std::getline())
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
    //PartOne();
    //PartTwo();

    return 0;
}

/*


*/