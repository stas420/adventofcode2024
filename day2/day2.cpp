#include <string>
#include <fstream> // file IO
#include <vector>
#include <iostream>
#include <cstdint> // for fixed width integers

const std::string test = "test.txt";
const std::string input = "input.txt";

// currently done by iterating through each report twice;
// should probably be done with two alternating "pointers";
// well whatevr
void PartOne()
{
    std::fstream file(input, std::ios::in);

    if (file.is_open())
    {
        constexpr int MAX_DIFF = 3;

        std::string report = "";
        std::uint32_t result = 0;

        std::vector<std::int64_t> levels;
        std::uint32_t i = 0;
        std::int64_t tmp = 0;

        bool decreasing = false;
        bool safe = true;

        while (std::getline(file, report))
        {
            levels.clear();
            safe = true;

            for (i = 0; i < report.length(); i++)
            {
                if (isdigit(report[i]))
                {
                    tmp = atoll(&report[i]);
                    i += std::to_string(tmp).length();
                    levels.push_back(tmp);
                }
                else
                {
                    i++;
                }
            }

            for (i = 0; i < (levels.size() - 1); i++)
            {
                tmp = levels[i] - levels[i + 1];

                if (tmp == 0)
                {
                    safe = false;
                    break;
                }

                if (i == 0)
                {
                    decreasing = (tmp > 0);
                }

                if (((tmp > 0) != decreasing) || abs(tmp) > MAX_DIFF)
                {
                    safe = false; 
                    break;
                }
            }

            if (safe)
            {
                result += 1;
            }
        }

        std::cout << "Part one result " << result << std::endl;
        // 299 
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
        constexpr int MAX_DIFF = 3;

        std::string report = "";
        std::uint32_t result = 0;

        std::vector<std::int64_t> levels;
        std::uint32_t i = 0;
        std::int64_t tmp = 0;

        bool decreasing = false;
        bool safe = true;

        while (std::getline(file, report))
        {
            levels.clear();
            safe = true;

            for (i = 0; i < report.length(); i++)
            {
                if (isdigit(report[i]))
                {
                    tmp = atoll(&report[i]);
                    i += std::to_string(tmp).length();
                    levels.push_back(tmp);
                }
                else
                {
                    i++;
                }
            }

            for (i = 0; i < (levels.size() - 1); i++)
            {
                tmp = levels[i] - levels[i + 1];

                if (tmp == 0)
                {
                    safe = false;
                    break;
                }

                if (i == 0)
                {
                    decreasing = (tmp > 0);
                }

                if (((tmp > 0) != decreasing) || abs(tmp) > MAX_DIFF)
                {
                    safe = false; 
                    break;
                }
            }

            if (safe)
            {
                result += 1;
            }
        }

        std::cout << "Part one result " << result << std::endl;
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