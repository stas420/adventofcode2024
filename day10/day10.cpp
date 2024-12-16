#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <iostream>

using namespace std; //< no noob, just tired of a lot of "std::" 

vector<string> ReadInput()
{
    fstream file("input.txt", ios::in);
    vector<string> Output;

    if (file.is_open())
    {
        string line;

        while (getline(file, line))
            Output.push_back(line);

        file.close();
    }
    else
    {
        cout << "File not opened, skill issue" << endl;
    }

    return Output;
}

const pair<int64_t, int64_t> Directions[4] = {
    make_pair(-1, 0), make_pair(0, 1), make_pair(1, 0), make_pair(-1, 0)
};



void PartOne()
{
    vector<string> Map = ReadInput();

}