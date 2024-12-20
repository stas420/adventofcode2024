#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <map>
#include <optional>

const std::int64_t spaceWidth = 101; // 11 in example, 101 in exercise
const std::int64_t spaceHeight = 103; // 7 in example, 103 in exercise

struct Robot 
{
    std::int64_t posX;
    std::int64_t posY;

    std::int64_t velX;
    std::int64_t velY;
};

std::vector<Robot> ReadAndParseInput()
{
    std::fstream file("input.txt", std::ios::in);
    std::vector<Robot> Output;

    if (file.is_open())
    {
        std::string line;
        std::uint64_t i = 0;
        std::uint64_t j = 0;
        Robot tmp;

        while(std::getline(file, line))
        {
            for (i = 0; i < line.length(); i++)
            {
                if (line[i] == 'p')
                {
                    i += 2;
                    j = i;

                    while (isdigit(line[i]) || line[i] == '-')
                        i++;
                    
                    tmp.posX = std::stoll(line.substr(j, i));

                    i++;
                    j = i;
                    
                    while (isdigit(line[i]) || line[i] == '-')
                        i++;
                    
                    tmp.posY = std::stoll(line.substr(j, i));
                }

                if (line[i] == 'v')
                {
                    i += 2;
                    j = i;

                    while (isdigit(line[i]) || line[i] == '-')
                        i++;
                    
                    tmp.velX = std::stoll(line.substr(j, i));

                    i++;
                    j = i;
                    
                    while (isdigit(line[i]) || line[i] == '-')
                        i++;
                    
                    tmp.velY = std::stoll(line.substr(j, i));
                }

            }

            Output.push_back(tmp);
        }

        file.close();
    }
    else
    {
        std::cout << "File not opened, skill issue" << std::endl;
    }

    return Output;
}

void PartOne(const std::uint64_t& Seconds)
{
    std::vector<Robot> Robots = ReadAndParseInput();
    std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t> TileToRobotCountMap;
    std::pair<std::int64_t, std::int64_t> position;
    std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t>::iterator iter;

    for (Robot& robot : Robots)
    {
        position.first = robot.posX + (Seconds * robot.velX);
        position.second = robot.posY + (Seconds * robot.velY);

        while (position.first >= spaceWidth)
            position.first -= spaceWidth;

        while (position.first < 0)
            position.first += spaceWidth;

        while (position.second >= spaceHeight)
            position.second -= spaceHeight;

        while (position.second < 0)
            position.second += spaceHeight;

        iter = TileToRobotCountMap.find(position);

        if (iter == TileToRobotCountMap.end())
        {
            TileToRobotCountMap.insert({position, 1});
        }
        else
        {
            iter->second++;
        }
    }

    std::int64_t lowerXbound = 0;
    std::int64_t higherXbound = 0;
    std::int64_t lowerYbound = 0;
    std::int64_t higherYbound = 0;

    if (spaceWidth % 2 == 1)
    {
        lowerXbound = (spaceWidth - 1)/2;
        higherXbound = lowerXbound;
    }
    else
    {
        higherXbound = spaceWidth/2;
        lowerXbound = higherXbound - 1;
    }

    if (spaceHeight % 2 == 1)
    {
        lowerYbound = (spaceHeight - 1)/2;
        higherYbound = lowerYbound;
    }
    else
    {
        higherYbound = spaceHeight/2;
        lowerYbound = higherYbound - 1;
    }

    std::int64_t qTL = 0;
    std::int64_t qTR = 0;
    std::int64_t qDL = 0;
    std::int64_t qDR = 0;

    for (auto& tile : TileToRobotCountMap) //< type name too long, may'auto' save me
    {
        if (tile.first.first < lowerXbound && tile.first.second < lowerYbound)
            qTL += tile.second;
        
        if (tile.first.first < lowerXbound && tile.first.second > higherYbound)
            qDL += tile.second;
        
        if (tile.first.first > higherXbound && tile.first.second < lowerYbound)
            qTR += tile.second;
        
        if (tile.first.first > higherXbound && tile.first.second > higherYbound)
            qDR += tile.second;
    }

    std::cout << "Part one result " << (qTL * qDL * qTR * qDR) << std::endl;
    // 222901875
}

void PartTwo()
{
    std::int64_t seconds = 17500;

    std::vector<Robot> Robots = ReadAndParseInput();
    std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t> TileToRobotCountMap;
    std::pair<std::int64_t, std::int64_t> position;
    std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t>::iterator iter;

    for (std::int64_t i = 0; i < seconds; i++)
    {
        for (Robot& robot : Robots)
        {
            position.first = robot.posX + robot.velX;
            position.second = robot.posY + robot.velY;

            while (position.first >= spaceWidth)
                position.first -= spaceWidth;

            while (position.first < 0)
                position.first += spaceWidth;

            while (position.second >= spaceHeight)
                position.second -= spaceHeight;

            while (position.second < 0)
                position.second += spaceHeight;

            iter = TileToRobotCountMap.find(position);

            if (iter == TileToRobotCountMap.end())
            {
                TileToRobotCountMap.insert({position, 1});
            }
            else
            {
                iter->second++;
            }
        }

        for (int q = 0; q < spaceHeight; q++)
        {
            for (int p = 0; p < spaceWidth; p++)
            {
                iter = TileToRobotCountMap.find({p, q});

                if (iter == TileToRobotCountMap.end())
                {
                    std::cout << ".";
                } 
                else
                {
                    std::cout << "#";
                }
            }

            std::cout << std::endl << std::endl;
        }
    }
}

int main()
{
    //PartOne(100);
    PartTwo();

    return 0;
}

/*


*/