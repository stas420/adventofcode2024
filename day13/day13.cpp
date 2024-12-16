#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
#include <iostream>
#include <cmath>

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
            while (line.empty())
                getline(file, line);
            
            i = 0;
            i = line.find('X');
            i += 2;
            tmp.buttonA.first = atoll(&line[i]);

            i = line.find('Y');
            i += 2;
            tmp.buttonA.second = atoll(&line[i]);

            getline(file, line);

            i = line.find('X');
            i += 2;
            tmp.buttonB.first = atoll(&line[i]);

            i = line.find('Y');
            i += 2;
            tmp.buttonB.second = atoll(&line[i]);

            getline(file, line);
            
            i = line.find('X');
            i += 2;
            tmp.prize.first = atoll(&line[i]);

            i = line.find('Y');
            i += 2;
            tmp.prize.second = atoll(&line[i]);

            Output.push_back(tmp);
        }

        file.close();
    }
    else
    {
        cout << "File not opened, skill issue" << endl;
    }

    return Output;
}

void PartOne()
{
    vector<ClawMachine> Machines = ReadAndParseInput();

    const long double costOfA = 3;

    int64_t ans = 0;
    long double mainDet = 0;
    long double a = 0;
    long double b = 0;

    for (ClawMachine& m : Machines)
    {
        mainDet = (m.buttonA.first * m.buttonB.second) - (m.buttonA.second * m.buttonB.first);

        if (mainDet != 0)
        {
            a = ((m.prize.first * m.buttonB.second) - (m.prize.second * m.buttonB.first))/mainDet;
            b = ((m.buttonA.first * m.prize.second) - (m.buttonA.second * m.prize.first))/mainDet;

            if ((modf(a, nullptr) == 0) && (modf(b, nullptr) == 0))  //< not good for the second part, type problems
            {
                ans += a * costOfA + b;
            }
        }
    }

    cout << "Part one answer " << ans << endl;
    // 37901
}

void PartTwo()
{
    vector<ClawMachine> Machines = ReadAndParseInput();

    const int64_t costOfA = 3;
    const int64_t offset = 10000000000000;

    int64_t ans = 0;
    int64_t mainDet = 0;
    int64_t a = 0;
    int64_t b = 0;

    for (ClawMachine& m : Machines)
    {
        m.prize.first += offset;
        m.prize.second += offset;

        mainDet = (m.buttonA.first * m.buttonB.second) - (m.buttonA.second * m.buttonB.first);

        if (mainDet != 0)
        {
            a = ((m.prize.first * m.buttonB.second) - (m.prize.second * m.buttonB.first))/mainDet;
            b = ((m.buttonA.first * m.prize.second) - (m.buttonA.second * m.prize.first))/mainDet;

            if (a * m.buttonA.first + b * m.buttonB.first == m.prize.first
            &&  a * m.buttonA.second + b * m.buttonB.second == m.prize.second)
                ans += a * costOfA + b;
        }
    }

    cout << "Part two answer " << ans << endl;
    // 77407675412647
}

int main()
{
    //PartOne();
    PartTwo();

    return 0;
}