#include <string>
#include <fstream> // file IO
#include <vector>
#include <iostream>
#include <cstdint> // for fixed width integers
#include <regex>
#include <algorithm>

const std::string test = "test.txt";
const std::string input = "input.txt";

std::int64_t parseMulAndMult(const std::string& mulStr)
{
    std::int64_t tmp = 0;
    bool second = false;

    for (std::uint32_t i = 0; i < mulStr.length(); i++)
    {
        if (isdigit(mulStr[i]))
        {
            if (second)
            {
                return (tmp * atoll(&mulStr[i]));
            }
            else
            {
                tmp = atoll(&mulStr[i]);
                i += std::to_string(tmp).length();
                second = true;
            }
        }
    }

    return tmp;
}

void PartOne()
{
    std::fstream file(test, std::ios::in);

    if (file.is_open())
    {
        std::string line = "";
        const std::regex expr ("mul\\(\\d+,\\d+\\)");
        std::sregex_iterator line_start, line_end, iter;
        std::int64_t result = 0;

        while (std::getline(file, line))
        {
            line_start = std::sregex_iterator(line.begin(), line.end(), expr);
            line_end = std::sregex_iterator();

            for (iter = line_start; iter != line_end; ++iter)
            {
                result += parseMulAndMult((*iter).str());
            }
        }

        std::cout << "Part one result is: " << result << std::endl;
        // 170807108
    }
    else
    {
        std::cout << "File not opened, skill issue" << std::endl;
    }
}

void PartTwo()
{
    std::fstream file(input, std::ios::in);

    if (file.is_open())
    {
        std::string line = "";

        const std::regex mul_expr ("mul\\(\\d+,\\d+\\)");
        const std::regex do_expr("do\\(\\)");
        const std::regex dont_expr("don\\'t\\(\\)");
        std::sregex_iterator line_start_mul, line_start_do, 
                             line_start_dont, line_end, iter;
        
        std::vector<std::pair<std::uint32_t, std::string>> positions;
        bool doMult = true;
        std::int64_t result = 0;

        while (std::getline(file, line))
        {
            positions.clear();
            
            line_start_mul = std::sregex_iterator(line.begin(), line.end(), mul_expr);
            line_start_do = std::sregex_iterator(line.begin(), line.end(), do_expr);
            line_start_dont = std::sregex_iterator(line.begin(), line.end(), dont_expr);
            line_end = std::sregex_iterator();

            for (iter = line_start_mul; iter != line_end; ++iter)
            {
                positions.push_back({ (*iter).position(), (*iter).str() });
            }

            for (iter = line_start_do; iter != line_end; ++iter)
            {
                positions.push_back({ (*iter).position(), (*iter).str() });
            }

            for (iter = line_start_dont; iter != line_end; ++iter)
            {
                positions.push_back({ (*iter).position(), (*iter).str() });
            }

            std::sort(positions.begin(), positions.end());

            for (std::pair<std::uint32_t, std::string> pair : positions)
            {
                if (pair.second[0] == 'm')
                {
                    if (doMult)
                    {
                        result += parseMulAndMult(pair.second);
                    }

                    continue;
                }

                if (pair.second == "do()")
                {
                    doMult = true;
                }
                else
                {
                    doMult = false;
                }
            }
        }

        std::cout << "Part two result is: " << result << std::endl;
        /// 74838033
    }
    else
    {
        std::cout << "File not opened, skill issue" << std::endl;
    }
}

int main()
{
    //PartOne();
    PartTwo();

    return 0;
}