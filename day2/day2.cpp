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
constexpr int MAX_DIFF = 3;

bool isSafePtOne(const std::vector<std::int64_t>& levelsVec)
{
    std::int64_t tmp = 0;
    bool decreasing = true;

    for (std::int64_t i = 0; i < (levelsVec.size() - 1); i++)
    {
        tmp = levelsVec[i] - levelsVec[i + 1];

        if (tmp == 0)
        {
            return false;
        }

        if (i == 0)
        {
            decreasing = (tmp > 0);
        }

        if (((tmp > 0) != decreasing) || abs(tmp) > MAX_DIFF)
        {
            return false;
        }
    }

    return true;
}

void PartOne()
{
    std::fstream file(input, std::ios::in);

    if (file.is_open())
    {
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

            if (isSafePtOne(levels))
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

bool isSafePtTwo(const std::vector<std::int64_t>& levelsVec)
{
    if (isSafePtOne(levelsVec))
        return true;

    std::vector<std::int64_t> tmp;

    for (std::int32_t i = 0; i < levelsVec.size(); i++)
    {
        tmp = levelsVec;
        tmp.erase(tmp.begin() + i);

        if (isSafePtOne(tmp))
            return true;
    }

    return false;
}

void PartTwo()
{
    std::fstream file(input, std::ios::in);

    if (file.is_open())
    {
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

            if (isSafePtTwo(levels))
            {
                //std::cout << "safe";
                result += 1;
            }
            else
            {
                levels.erase(levels.begin());

                if (isSafePtOne(levels))
                    result += 1;
            }

            //std::cout << std::endl;
        }

        std::cout << "Part two result " << result << std::endl;
        // 364
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

/*

// first try??? smth brong
bool isSafePtTwo(const std::vector<std::int64_t>& levelsVec)
{
    //std::cout << "--------------\n";
    std::int64_t tmp = 0;
    std::vector<std::int64_t> vec(levelsVec);
    bool isDecreasing = true;

    for (std::int64_t i = 0; i < levelsVec.size(); i++)
    {
        tmp = levelsVec[i] - levelsVec[i+1];

        //std::cout << tmp << " = " << levelsVec[i] << " - " << levelsVec[i+1] << "\n";

        if (tmp == 0)
        {
            vec.clear();
            vec = levelsVec;
            vec.erase(vec.begin() + i);
            
            if (!isSafePtOne(vec))
            {
                vec = levelsVec;
                vec.erase(vec.begin() + i + 1);

                if (!isSafePtOne(vec))
                {
                    return false;
                }
            }
        }

        if (i == 0)
        {
            isDecreasing = (tmp > 0);
        }

        if (((tmp > 0) != isDecreasing) || abs(tmp) > MAX_DIFF)
        {
            vec.clear();
            vec = levelsVec;
            vec.erase(vec.begin() + i);
            
            if (!isSafePtOne(vec))
            {
                vec.clear();
                vec = levelsVec;
                vec.erase(vec.begin() + i + 1);

                if (!isSafePtOne(vec))
                {
                    return false;
                }

                break;
            }

            break;
        }

    }

    return true;
}
*/