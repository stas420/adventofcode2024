#include <string>
#include <vector>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

const std::string rulesFile = "rules.txt";
const std::string updatesFile = "updates.txt";

std::vector<std::pair<std::uint32_t, std::uint32_t>> rulesVector;
std::vector<std::vector<std::uint32_t>> updatesVector;

void ReadAndParseInput()
{
    std::fstream rules(rulesFile, std::ios::in);
    std::string line = "";

    if (rules.is_open())
    {
        std::uint16_t i = 0;
        std::uint32_t p = 0;
        std::uint32_t q = 0;
        bool firstRule = true;

        while(std::getline(rules, line))
        {
            firstRule = true;

            for (i = 0; i < line.length(); i++)
            {
                if (isdigit(line[i]))
                {
                    if (firstRule)
                    {
                        p = atoll(&line[i]);
                        i += std::to_string(p).length();
                        firstRule = false;
                    }
                    else
                    {
                        q = atoll(&line[i]);
                        i += std::to_string(q).length();
                    }
                }
            }

            rulesVector.emplace_back(p, q);
        }

        rules.close();
    }
    else
    {
        std::cout << "File " << rulesFile << " not opened, skill issue" << std::endl;
        return;
    }

    std::fstream updates(updatesFile, std::ios::in);

    if (updates.is_open())
    {
        std::vector<std::uint32_t> tmp;
        std::uint32_t i = 0;
        std::uint32_t j = 0;

        while(std::getline(updates, line))
        {
            tmp.clear();

            for (i = 0; i < line.length(); i++)
            {
                if (isdigit(line[i]))
                {
                    j = atoll(&line[i]);
                    i += std::to_string(j).length();
                    tmp.push_back(j);
                }
            }

            updatesVector.push_back(tmp);
        }

        updates.close();
    }
    else
    {
        std::cout << "File " << updatesFile << " not opened, skill issue" << std::endl;
        return;
    }
}

void PartOne()
{
    ReadAndParseInput();

    std::vector<std::vector<std::uint32_t>> updatesRef = updatesVector;

    std::sort(rulesVector.begin(), rulesVector.end(), 
        // return true if a is less than b
        [](const std::pair<std::uint32_t, std::uint32_t>& a, 
        const std::pair<std::uint32_t, std::uint32_t>& b)
        {
            return a.second < b.second;
        }
    );

    std::map<std::uint32_t, std::vector<std::uint32_t>> rulesAsSubsets;
    std::map<std::uint32_t, std::vector<std::uint32_t>>::iterator iter;

    for (std::pair<std::uint32_t, std::uint32_t>& pair : rulesVector)
    {
        iter = rulesAsSubsets.find(pair.second); 

        if (iter != rulesAsSubsets.end())
        {
            iter->second.push_back(pair.first);
        }
        else
        {
            rulesAsSubsets.insert({ pair.second, std::vector<std::uint32_t>({ pair.first }) });
        }
    }

    for (iter = rulesAsSubsets.begin(); iter != rulesAsSubsets.end(); iter++)
    {
        std::sort(iter->second.begin(), iter->second.end());
    }

    std::uint64_t answer = 0;

    for (std::vector<std::uint32_t>& u : updatesVector)
    {
        std::sort(u.begin(), u.end(), 
            // return true if a is less than b
            [&rulesAsSubsets, &iter](const std::uint32_t& a, const std::uint32_t& b)
            {
                iter = rulesAsSubsets.find(b);
                return std::find(iter->second.begin(),
                                 iter->second.end(),
                                 a)                     != iter->second.end();
            }
        );
    }

    bool brong = false;

    for (std::uint64_t i = 0; i < updatesVector.size(); i++)
    {
        brong = false;

        for (std::uint64_t k = 0; k < updatesVector[i].size(); k++)
        {
            if (updatesVector[i][k] != updatesRef[i][k])
            {
                brong = true;
                break;
            }
        }

        if (!brong)
        {
            answer += updatesRef[i][updatesRef[i].size() / 2];
        }
    }

    std::cout << "Part one answer " << answer << std::endl;
    // 5391
}

void PartTwo()
{
    ReadAndParseInput();

    std::vector<std::vector<std::uint32_t>> updatesRef = updatesVector;

    std::sort(rulesVector.begin(), rulesVector.end(), 
        // return true if a is less than b
        [](const std::pair<std::uint32_t, std::uint32_t>& a, 
        const std::pair<std::uint32_t, std::uint32_t>& b)
        {
            return a.second < b.second;
        }
    );

    std::map<std::uint32_t, std::vector<std::uint32_t>> rulesAsSubsets;
    std::map<std::uint32_t, std::vector<std::uint32_t>>::iterator iter;

    for (std::pair<std::uint32_t, std::uint32_t>& pair : rulesVector)
    {
        iter = rulesAsSubsets.find(pair.second); 

        if (iter != rulesAsSubsets.end())
        {
            iter->second.push_back(pair.first);
        }
        else
        {
            rulesAsSubsets.insert({ pair.second, std::vector<std::uint32_t>({ pair.first }) });
        }
    }

    for (iter = rulesAsSubsets.begin(); iter != rulesAsSubsets.end(); iter++)
    {
        std::sort(iter->second.begin(), iter->second.end());
    }

    std::uint64_t answer = 0;

    for (std::vector<std::uint32_t>& u : updatesVector)
    {
        std::sort(u.begin(), u.end(), 
            // return true if a is less than b
            [&rulesAsSubsets, &iter](const std::uint32_t& a, const std::uint32_t& b)
            {
                iter = rulesAsSubsets.find(b);
                return std::find(iter->second.begin(),
                                 iter->second.end(),
                                 a)                     != iter->second.end();
            }
        );
    }

    bool brong = false;

    for (std::uint64_t i = 0; i < updatesVector.size(); i++)
    {
        brong = false;

        for (std::uint64_t k = 0; k < updatesVector[i].size(); k++)
        {
            if (updatesVector[i][k] != updatesRef[i][k])
            {
                brong = true;
                break;
            }
        }

        if (brong)
        {
            answer += updatesVector[i][updatesVector[i].size() / 2];
        }
    }

    std::cout << "Part two answer " << answer << std::endl;
    // 6142
}

int main()
{
    //PartOne();
    PartTwo();

    return 0;
}