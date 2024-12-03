#include <string>
#include <fstream> // file IO
#include <vector>
#include <iostream>
#include <cstdint> // for fixed width integers

const std::string test = "test.txt";
const std::string input = "input.txt";

void PartOne()
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