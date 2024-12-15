#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <map>

using namespace std; //< you say it's noob, I say I don't want to write "std::" every fokin time

void ReadAndParseInput(vector<string>& OutputMap, string& OutputMoves)
{
    fstream file("input.txt", ios::in);

    if (file.is_open())
    {
        string line;
        bool isMap = true;

        while (getline(file, line))
        {
            if (line.empty())
            {
                isMap = false;
                continue;
            }

            if (isMap)
            {
                OutputMap.push_back(line);
            }
            else
            {
                OutputMoves.append(line);
            }
        }

        file.close();
    }
    else
    {
        cout << "File not opened, skill issue" << endl;
    }
}

void MoveTheRobot(vector<string>& MutableMap, pair<int64_t, int64_t>& MutablePosition, const char& Direction)
{
    static const map<char, pair<int64_t, int64_t>> DirectionMap = {
        { '^', make_pair(-1, 0) }, { 'v', make_pair(1, 0) },
        { '<', make_pair(0, -1) }, { '>', make_pair(0, 1) }
    };

    pair<int64_t, int64_t> _Position;
    _Position.first = MutablePosition.first;
    _Position.second = MutablePosition.second;

    const pair<int64_t, int64_t> _Direction = DirectionMap.find(Direction)->second;

    _Position.first += _Direction.first;
    _Position.second += _Direction.second;

    if (MutableMap[_Position.first][_Position.second] == '#')
        return;
    
    if (MutableMap[_Position.first][_Position.second] == '.')
    {
        MutablePosition = _Position;
        return;
    }

    while(MutableMap[_Position.first][_Position.second] != '#')
    {
        _Position.first += _Direction.first;
        _Position.second += _Direction.second;

        if (MutableMap[_Position.first][_Position.second] == '.')
        {
            while(_Position != MutablePosition)
            {
                MutableMap[_Position.first][_Position.second] = 
                MutableMap[_Position.first - _Direction.first][_Position.second - _Direction.second];

                _Position.first -= _Direction.first;
                _Position.second -= _Direction.second;        
            }

            MutablePosition.first += _Direction.first;
            MutablePosition.second += _Direction.second;

            return;
        }
    }
}

void PartOne()
{
    vector<string> Map;
    string Moves;
    ReadAndParseInput(Map, Moves);

    pair<int64_t, int64_t> Position;

    for (uint64_t i = 0; i < Map.size(); i++)
    {
        Position.second = Map[i].find('@');

        if (Position.second != string::npos)
        {
            Position.first = i;
            Map[Position.first][Position.second] = '.';
            break;
        }
    }

    char currentMove = '\0';

    while (!Moves.empty())
    {
        currentMove = Moves.front();
        Moves.erase(Moves.begin());

        MoveTheRobot(Map, Position, currentMove);
    }

    int64_t ans = 0;

    for (int64_t i = 0; i < Map.size(); i++)
    {
        for (int64_t j = 0; j < Map[i].length(); j++)
        {
            if (Map[i][j] == 'O')
            {
                ans += (100 * i) + j;
            }
        }
    }

    cout << "Part one answer " << ans << endl;
    // 1517819
}

// ============================================

string DoubleTheString(const string& str)
{
    string output = "";

    for (const char& ch : str)
    {
        output.push_back(ch);
        output.push_back(ch);
    }

    return output;
}

void MoveTheRobotButWider(vector<string>& MutableMap, pair<int64_t, int64_t>& MutablePosition, const char& Direction)
{
    static const map<char, pair<int64_t, int64_t>> DirectionMap = {
        { '^', make_pair(-1, 0) }, { 'v', make_pair(1, 0) },
        { '<', make_pair(0, -1) }, { '>', make_pair(0, 1) }
    };

    pair<int64_t, int64_t> _Position;
    _Position.first = MutablePosition.first;
    _Position.second = MutablePosition.second;

    const pair<int64_t, int64_t> _Direction = DirectionMap.find(Direction)->second;

    _Position.first += _Direction.first;
    _Position.second += _Direction.second;

    if (MutableMap[_Position.first][_Position.second] == '#')
        return;
    
    if (MutableMap[_Position.first][_Position.second] == '.')
    {
        MutablePosition = _Position;
        return;
    }

    while(MutableMap[_Position.first][_Position.second] != '#')
    {
        _Position.first += _Direction.first;
        _Position.second += _Direction.second;

        if (MutableMap[_Position.first][_Position.second] == '.')
        {
            while (_Position != MutablePosition)
            {
                
                _Position.first -= _Direction.first;
                _Position.second -= _Direction.second;        
            }

            MutablePosition.first += _Direction.first;
            MutablePosition.second += _Direction.second;

            return;
        }
    }
}

void PartTwo()
{
    // read input
    vector<string> Map;
    string Moves;
    ReadAndParseInput(Map, Moves);

    // double the width
    for (string& line : Map)
    {
        line = DoubleTheString(line);
    }

    // change every OO to [] and @@ to .. (also, find robot's initial position)
    pair<int64_t, int64_t> Position;

    for (int64_t i = 0; i < Map.size(); i++)
    {
        for (int64_t j = 0; j < Map[i].length(); j++)
        {
            if (Map[i][j] == 'O' && Map[i][j+1] == 'O')
            {
                Map[i][j] = '[';
                Map[i][j+1] = ']';
                j++;
            }

            if (Map[i][j] == '@' && Map[i][j+1] == '@')
            {
                Map[i][j] = '.';
                Map[i][j+1] = '.';
                Position.first = i;
                Position.second = j;
                j++;
            }
        }
    }

    // start moving d-.-b
    char currentMove = '\0';

    while (!Moves.empty())
    {
        currentMove = Moves.front();
        Moves.erase(Moves.begin());

        MoveTheRobotButWider(Map, Position, currentMove);
    }

    for (auto& x : Map)
    {
        std::cout << x << "\n";
    }

    return;

    // compute the answer 
    int64_t ans = 0;

    for (int64_t i = 0; i < Map.size(); i++)
    {
        for (int64_t j = 0; j < Map[i].length(); j++)
        {
            // check the boxes' GPS coordinates according to their closest edge

        }
    }

    cout << "Part two answer " << ans << endl;
    // 
}

int main()
{
    //PartOne();
    PartTwo();

    return 0;
}