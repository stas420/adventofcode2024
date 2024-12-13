#include <string>
#include <fstream> // file IO
#include <vector>
#include <iostream>
#include <algorithm> // std::sort function
#include <cstdint> // for fixed width integers
#include <unordered_map>

const std::string test = "test.txt";
const std::string input = "input.txt";

void PartOne()
{
    std::fstream file(input, std::ios::in);

    if (file.is_open())
    {
        std::vector<std::uint64_t> list1, list2;
        std::string line;

        bool ifList1 = true;
        std::uint64_t tmp = 0;

        while (std::getline(file, line))
        {
            for (std::uint64_t i = 0; i < line.length(); i++)
            {
                if (isdigit(line[i]))
                {
                    tmp = atoll(&line[i]);
                    i += std::to_string(tmp).length();

                    if (ifList1)
                    {
                        list1.push_back(tmp);
                        ifList1 = false;
                    }
                    else
                    {
                        list2.push_back(tmp);
                        ifList1 = true;
                    }
                }
            }
        }
        
        file.close();
        tmp = list1.size();

        if (tmp != list2.size())
        {
            std::cout << "Lists do not have the same sizes, skill issue" << std::endl;
            return;
        }

        std::sort(list1.begin(), list1.end());
        std::sort(list2.begin(), list2.end());

        std::uint64_t result = 0;
        std::int64_t diff = 0; // < important - int overflow is such a bitch

        for (std::uint64_t i = 0; i < tmp; i++)
        {
            diff = list1[i] - list2[i];

            if (diff < 0)
                diff *= (-1);

            std::cout << "list1 " << list1[i] << " | " << list2[i] << std::endl;
            std::cout << "diff " << diff << std::endl; 
                         
            result += diff;
        }

        std::cout << "Part one result: " << result << std::endl;
        // 3714264
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
        std::vector<std::uint64_t> list1, list2;
        std::string line;

        bool ifList1 = true;
        std::uint64_t tmp = 0;

        while (std::getline(file, line))
        {
            for (std::uint64_t i = 0; i < line.length(); i++)
            {
                if (isdigit(line[i]))
                {
                    tmp = atoll(&line[i]);
                    i += std::to_string(tmp).length();

                    if (ifList1)
                    {
                        list1.push_back(tmp);
                        ifList1 = false;
                    }
                    else
                    {
                        list2.push_back(tmp);
                        ifList1 = true;
                    }
                }
            }
        }

        file.close();
        tmp = list1.size();

        if (tmp != list2.size())
        {
            std::cout << "Lists do not have the same sizes, skill issue" << std::endl;
            return;
        }

        std::unordered_map<std::uint64_t, std::uint64_t> occurences;
        std::unordered_map<std::uint64_t, std::uint64_t>::iterator it;

        for (std::uint64_t list2item : list2)
        {
            it = occurences.find(list2item); 

            if (it == occurences.end())
            {
                occurences.insert(std::pair<std::uint64_t, std::uint64_t>(list2item, 1));
            }
            else
            {
                it->second++;
            }
        }

        tmp = 0; // why declare another variable, if I already have a not-used one?

        for (std::uint64_t list1item : list1)
        {
            it = occurences.find(list1item);

            if (it != occurences.end())
            {
                tmp += list1item * it->second;
            }
        }

        std::cout << "Part two result: " << tmp << std::endl;
        // 18805872
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