#include <string>
#include <fstream> // file IO
#include <vector>
#include <iostream>
#include <cstdint> // for fixed width integers

const std::string test = "test.txt";
const std::string input = "input.txt";

// done by going through each line two times;
// should probably be done with alternating "pointers" to 
// neighbour values in each line;
// well, whatevr
void PartOne()
{
    std::fstream file(input, std::ios::in);

    if (file.is_open())
    {
        std::string line;
        std::uint32_t i = 0;
        std::int64_t tmp = 0;
        std::uint32_t result = 0;

        bool isDecreasing = true;
        bool isSafe = true;

        constexpr int MIN_DIFF = 1;
        constexpr int MAX_DIFF = 3;

        std::vector<std::int64_t> report;

        while(std::getline(file, line))
        {
            report.clear();
            isSafe = true;

            for (i = 0; i < line.length(); i++)
            {
                if (isdigit(line[i]))
                {
                    tmp = atoll(&line[i]);
                    report.push_back(tmp);
                    i += std::to_string(tmp).length();
                }
                else 
                {
                    i++;
                }
            }

            for (i = 0; i < (report.size() - 1); i++)
            {
                tmp = report[i] - report[i+1]; //< positive = decr, negat - incr

                if (tmp == 0)
                {
                    isSafe = false;
                    break;
                }

                if (i == 0)
                {
                    isDecreasing = (tmp > 0);
                    continue;
                }

                if ((isDecreasing != (tmp > 0)) || abs(tmp) > MAX_DIFF || abs(tmp) < MIN_DIFF)
                {
                    isSafe = false;
                    break;
                }
            }

            if (isSafe)
                result++;
        }        

        std::cout << "Part one result " << result << std::endl;
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

/*

            for (std::uint32_t p : report)
            {
                std::cout << "report : " << p << std::endl;
            }


std::string line = "";
        std::uint32_t i = 0;
        std::int32_t tmp = 0;
        std::int32_t tmp_abs = 0;
        std::uint32_t result = 0;

        constexpr int MAX_DIFF = 3;

        bool isIncresing = true;
        bool isSafe = true;

        std::vector<std::uint32_t> report;

        while (std::getline(file, line))
        {
            std::cout << "------------------------------------\n";

            i = 0;
            report.clear();

            while (i < line.length())
            {
                if (isdigit(line[i]))
                {
                    report.push_back(atol(&line[i]));
                    i += std::to_string(report.back()).length();
                }
                else
                {
                    i++;
                }
            }

            for (auto k : report)
            {
                std::cout << "level " << k << std::endl; 
            }

            continue; 

            // surely assuming reports have at least three values
            tmp = report[0] - report[1];

            std::cout << "report 0 " << report[0] << " report[1] " << report[1] << std::endl;
            std::cout << "first tmp " << tmp << std::endl;

            if (tmp > 0)
            {
                isIncresing = false;
                std::cout << "false" << std::endl;
            }
            else if (tmp < 0)
            {
                isIncresing = true;
                std::cout << "true" << std::endl;
            }
            else
            {
                std::cout << "cont" << std::endl;
                continue;
            }

            isSafe = true;

            for (std::uint32_t j = 1; j < (report.size() - 1); j++)
            {
                tmp = report[j] - report[j+1]; // < positive means decrase, negative increase
                std::cout << "report j " << report[j] << " report j+1 " <<  report[j+1] << std::endl;

                if (tmp < 0)
                    tmp_abs = tmp * (-1);
                else
                    tmp_abs = tmp;

                std::cout << "tmp " << tmp << " tmp abs " << tmp_abs << std::endl;

                if ((tmp == 0) || ((tmp < 0) != isIncresing) || (tmp_abs > MAX_DIFF))
                {
                    std::cout << "not safe" << std::endl;
                    isSafe = false;
                    break;
                }
            }

            if (isSafe)
            {
                result++;
                std::cout << ">> SAFE " << result << std::endl;
            }
        }

        std::cout << "Part one result: " << result << std::endl;
*/