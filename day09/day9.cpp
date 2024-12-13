#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <limits>
#include <algorithm>

// this represents one file block 
// for example input "4" creates 4 DiskSpaceChunk of ID 0 
//
// the same goes with "spaces" but the ID is set to maximum possible int64_t value, cuz why not
struct DiskSpaceChunk
{
    std::uint64_t ID;

    bool IsFile;
};

std::vector<DiskSpaceChunk> ParseDisk()
{
    std::fstream file("input.txt", std::ios::in);

    if (file.is_open())
    {
        std::string line;
        std::getline(file, line);        
        file.close();

        std::vector<DiskSpaceChunk> Output;
        Output.reserve(line.length());

        std::int64_t num = 0;
        std::uint64_t IDCounter = 0;
        DiskSpaceChunk ch;
        bool isFile = true;

        std::uint64_t j = 0;

        for (std::uint64_t i = 0; i < line.length(); i++)
        {
            num = std::stoi(std::string({ line[i], '\0' }));

            if (num > 0)
            {
                ch.IsFile = isFile;

                if (isFile)
                {
                    ch.ID = IDCounter;
                    IDCounter++;
                }
                else
                {
                    ch.ID = std::numeric_limits<std::uint64_t>::max();
                }

                for (j = 0; j < num; j++)
                {
                    Output.push_back(ch);                    
                }
            }

            isFile = !isFile;
        }        

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
    // read and parse input
    std::vector<DiskSpaceChunk> ParsedDisk = ParseDisk();

    std::uint64_t p = 0;
    std::uint64_t q = ParsedDisk.size() - 1;
    DiskSpaceChunk ch;

    // moving file blocks
    while (p < q)
    {
        if (ParsedDisk[q].IsFile)
        {
            while(ParsedDisk[p].IsFile)
                p++;

            if (p >= q)
                break;

            ch = ParsedDisk[p];
            ParsedDisk[p] = ParsedDisk[q];
            ParsedDisk[q] = ch;
        }

        q--;
    }

    std::int64_t answer = 0;

    for (p = 0; p < ParsedDisk.size(); p++)
    {
        if (ParsedDisk[p].IsFile)
            answer += ParsedDisk[p].ID * p;
    }

    std::cout << "Part one result " << answer << std::endl;
    // 6398608069280
}

bool FindSpaceIndex(std::vector<DiskSpaceChunk>& Disk, const std::uint64_t& SpaceSize, std::uint64_t& OutputIndex)
{
    const std::uint64_t IndexDiff = SpaceSize - 1;
    std::uint64_t i = 0;
    std::uint64_t j = 0;

    while (i < Disk.size())
    {
        if (!Disk[i].IsFile)
        {
            j = i;

            while (!Disk[i].IsFile && i < Disk.size())
            {
                if (i - j == IndexDiff)
                {
                    OutputIndex = j;
                    return true;
                }

                i++;
            }
        }

        i++;
    }

    return false;
}

void PartTwo()
{
    // read and parse input
    std::vector<DiskSpaceChunk> ParsedDisk = ParseDisk();

    // moving whole files...
    DiskSpaceChunk ch;
    std::uint64_t tmpID = 0;
    std::uint64_t tmpIndex = 0;
    std::uint64_t p = 0;
    std::uint64_t q = ParsedDisk.size() - 1;

    while (q > 0)
    {
        if (ParsedDisk[q].IsFile)
        {
            tmpID = ParsedDisk[q].ID;
            tmpIndex = q;

            do 
            {
                q--;

            } while(ParsedDisk[q].ID == tmpID && q > 0);

            // after the do-while, I am pointing with 'q' at the next file 

            // found index should be to the left of the end of the file
            // otherwise it will not be "moving files to the left"
            if (FindSpaceIndex(ParsedDisk, (tmpIndex - q), p) && (p < q))
            {
                for (std::uint64_t i = 0; i < (tmpIndex - q); i++)
                {
                    // mm, some index fun UwU
                    ch = ParsedDisk[p + i];
                    ParsedDisk[p + i] = ParsedDisk[tmpIndex - i];
                    ParsedDisk[tmpIndex - i] = ch;
                }
            }
        }
        // this else is important, due to the way 'q' works above
        else 
            q--;
    }

    std::int64_t answer = 0;

    for (p = 0; p < ParsedDisk.size(); p++)
    {
        if (ParsedDisk[p].IsFile)
            answer += ParsedDisk[p].ID * p;
    }

    std::cout << "Part two result " << answer << std::endl;
    // 6427437134372
}

int main()
{
    //PartOne();
    PartTwo();
    return 0;
}

/*


    std::uint64_t i = 0;
    if (FindSpaceIndex(ParsedDisk, 3, i))
        std::cout << "found at " << i << std::endl;

*/