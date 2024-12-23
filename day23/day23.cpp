#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_set>
#include <algorithm>

std::map<std::string, std::vector<std::string>> ParseInput()
{
    std::map<std::string, std::vector<std::string>> Output;
    std::fstream file("input.txt", std::ios::in);

    if (file.is_open())
    {
        std::map<std::string, std::vector<std::string>>::iterator iter;
        std::string line;
        std::string one, two;
        const size_t dashPos = 2, first = 0, second = 3;

        while (std::getline(file, line))
        {
            one = line.substr(first, dashPos);
            two = line.substr(second, line.length());

            iter = Output.find(one);

            if (iter == Output.end())
            {
                Output.insert({ one, { two } });
            }
            else
            {
                iter->second.push_back(two);
            }

            iter = Output.find(two);

            if (iter == Output.end())
            {
                Output.insert({ two, { one } });
            }
            else
            {
                iter->second.push_back(one);
            }
        }

        file.close();
    }
    else
    {
        std::cout << "File not opened, skill issue" << std::endl;
    }

    return Output;
}

template<typename T>
bool CheckExistenceInVector(const std::vector<T>& Vector, const T& Element)
{
    for (unsigned long i = 0; i < Vector.size(); i++)
    {
        if (Vector[i] == Element)
            return true;
    }

    return false;
}


unsigned long PartOne()
{
    std::map<std::string, std::vector<std::string>> Connections = ParseInput();
    std::vector<std::unordered_set<std::string>> Sets;
    std::unordered_set<std::string> tmpSet;
    unsigned long i = 0, j = 0;

    for (auto& Computer : Connections)
    {
        if (Computer.first[0] != 't')
            continue;
        
        for (i = 0; i < Computer.second.size(); i++)
        {
            for (j = i + 1; j < Computer.second.size(); j++)
            {
                tmpSet.clear();
                
                if (CheckExistenceInVector(Connections[Computer.second[i]], Computer.second[j]))
                {
                    tmpSet.insert(Computer.first);
                    tmpSet.insert(Computer.second[i]);
                    tmpSet.insert(Computer.second[j]);

                    if (!CheckExistenceInVector(Sets, tmpSet))
                        Sets.push_back(tmpSet);
                }
            }
        }
    }

    return Sets.size();
}



#include <chrono>

int main()
{
    auto start = std::chrono::system_clock::now();
    unsigned long ans = PartOne();
    auto dur = std::chrono::duration<double>(std::chrono::system_clock::now() - start).count();

    std::cout << "Part One answer " << ans << "; time: " << dur << std::endl;
    // 1366

    return 0;
}