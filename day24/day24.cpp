#include <optional>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <cstdint>
#include <cmath>

std::vector<std::string> ReadInput()
{
    std::fstream file("input.txt", std::ios::in);
    std::vector<std::string> Output;

    if (file.is_open())
    {        
        std::string line;

        while (std::getline(file, line))
            Output.push_back(line);

        file.close();
    }
    else
    {
        std::cout << "File not opened, skill issue" << std::endl;
    }

    return Output;
}

enum class Operator { AND, OR, XOR };

void PartOne()
{
    std::vector<std::string> Input = ReadInput();
    const std::uint64_t NameLen = 3; //< one sees it in the input, don't they?
    std::uint64_t i = 0;

    // wires will be stored as a map {name}->{value}
    std::map<std::string, bool> Wires;
    std::string tmpString = "";
    bool tmpBool = true;
    size_t pos = 0;

    // read every *given* value
    while (!Input[i].empty() && i < Input.size())
    {
        pos = Input[i].find(':', 0);
        tmpString = Input[i].substr(0, pos);
        pos += 2;

        if (Input[i][pos] == '0')
            tmpBool = false;
        else
            tmpBool = true;

        Wires.insert(std::make_pair(tmpString, tmpBool));
        Input.erase(Input.begin());
    }

    // now we're gonna read operations and compute them or push them back to the end
    // depending on having both values at the time or not
    Input.erase(Input.begin());
    pos = 0;
    std::map<std::string, bool>::iterator f, s, t;
    Operator op = Operator::AND;

    while (i < Input.size())
    {
        // read and find first wire
        tmpString = Input[i].substr(0, NameLen);
        f = Wires.find(tmpString);

        // if not found, push back the operation and read further
        if (f == Wires.end())
        {
            Input.push_back(Input[i]);
            Input.erase(Input.begin() + i);
            continue;
        }

        // read and parse the operation
        pos = NameLen + 1;

        if (Input[i][pos] == 'A')
            op = Operator::AND;

        else if (Input[i][pos] == 'O')
            op = Operator::OR;

        else if (Input[i][pos] == 'X')
            op = Operator::XOR;

        // read and find second wire
        pos = Input[i].find(' ', pos) + 1;
        tmpString = Input[i].substr(pos, NameLen);
        s = Wires.find(tmpString);

        // if not found, push back the operation and read further
        if (s == Wires.end())
        {
            Input.push_back(Input[i]);
            Input.erase(Input.begin() + i);
            continue;
        }
 
        // find the third one (it should not exist juust yet, but pro forma...)
        pos = Input[i].find('>', pos) + 2;
        tmpString = Input[i].substr(pos, NameLen);
        t = Wires.find(tmpString);

        // compute the value
        if (op == Operator::AND)
            tmpBool = (f->second && s->second);

        else if (op == Operator::OR)
            tmpBool = (f->second || s->second);

        else if (op == Operator::XOR)
            tmpBool = (f->second != s->second);


        if (t == Wires.end())
            Wires.insert(std::make_pair(tmpString, tmpBool));

        else
            t->second = tmpBool;

        Input.erase(Input.begin() + i);
    }

    f = Wires.find("z00");
    std::uint64_t ans = 0;
    i = 0;

    for (f; f != Wires.end(); f++)
    {
        if (f->second)
            ans += std::pow(2, i);
        
        i++;
    }

    std::cout << "Part one result " << ans << std::endl;
    // 64755511006320
}

void PartTwo()
{
    std::vector<std::string> Input = ReadInput();
}

int main()
{
    //PartOne();
    PartTwo();

    return 0;
}