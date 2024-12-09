#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <limits>
#include <algorithm>

struct DiskSpaceChunk
{
    std::uint64_t Position;
    std::uint64_t Length;
    std::uint64_t ID;

    bool IsFile;
};

std::vector<DiskSpaceChunk> ParseDisk()
{
    std::fstream file("input.txt", std::ios::in);

    if (file.is_open())
    {
        std::vector<DiskSpaceChunk> Output;
        std::string line;

        bool isFile = true;
        std::uint64_t IDCounter = 0;
        DiskSpaceChunk tmp;
        std::uint64_t len = 0;

        while(std::getline(file, line))
        {

            for (std::uint64_t i = 0; i < line.length(); i++)
            {
                len = std::stoi(std::string({ line[i], '\0'}));

                if (len > 0)
                {
                    tmp.Position = i;
                    tmp.Length = len;

                    if (isFile)
                    {
                        tmp.ID = IDCounter;
                        tmp.IsFile = true;
                        IDCounter++;

                        isFile = false;
                    }
                    else
                    {
                        tmp.ID = std::numeric_limits<std::uint64_t>::max();
                        tmp.IsFile = false;
                        
                        isFile = true;
                    }

                    Output.push_back(tmp);
                }
                else
                {
                    isFile = !isFile;
                }
            }
        }

        file.close();
        return Output;
    }
    else
    {
        std::cout << "File not opened, skill issue" << std::endl;
        return std::vector<DiskSpaceChunk>();
    }
}

void PartOne()
{
    std::vector<DiskSpaceChunk> ParsedDisk = ParseDisk();

    for (auto&x : ParsedDisk)
    {
        if(x.IsFile)
        {
            for (int i = 0; i < x.Length; i++)
                std::cout << x.ID;
        }
        else
        {
            for (int i = 0; i < x.Length; i++)
                std::cout << ".";
        }
    }

    std::cout << std::endl;

    std::uint64_t p = 0;
    std::uint64_t q = ParsedDisk.size() - 1;
    DiskSpaceChunk tmp = ParsedDisk[p];

    while (q > p)
    {
        if (ParsedDisk[q].IsFile)
        {
            while(ParsedDisk[p].IsFile)
                p++;
            
            tmp = ParsedDisk[p];
            std::cout << tmp.Position << " | " << tmp.Length << std::endl;
            ParsedDisk[p] = ParsedDisk[q];
            ParsedDisk[q] = tmp;
        }

        q--;
    }

    for (auto&x : ParsedDisk)
    {
        if(x.IsFile)
        {
            for (int i = 0; i < x.Length; i++)
                std::cout << x.ID;
        }
        else
        {
            for (int i = 0; i < x.Length; i++)
                std::cout << ".";
        }
    }

    std::cout << std::endl;

}

int main()
{
    PartOne();
    return 0;
}