#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
#include <iostream>

using namespace std;

struct ClawMachine
{
    pair<int64_t, int64_t> buttonA;
    pair<int64_t, int64_t> buttonB;
    pair<int64_t, int64_t> prize;
};

vector<ClawMachine> ReadAndParseInput()
{
    fstream file("input.txt", ios::in);
    vector<ClawMachine> Output;

    if (file.is_open())
    {
        string line;
        ClawMachine tmp;
        int64_t i = 0;

        while(getline(file, line))
        {
            i = line.find('+');
        }
    }
    else
    {
        cout << "File not opened, skill issue" << endl;
    }

    return Output;
}