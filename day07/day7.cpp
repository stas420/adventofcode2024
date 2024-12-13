#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

struct Equation
{
    std::uint64_t testValue;
    std::vector<std::uint64_t> numbers;
};

std::vector<Equation> ParseInput()
{
    std::fstream file("input.txt", std::ios::in);
    std::vector<Equation> Output;

    if (file.is_open())
    {
        std::string line;
        bool isTestValue = true;
        std::uint64_t i = 0;
        Equation tmp;

        while(std::getline(file, line))
        {
            isTestValue = true;
            tmp.numbers.clear();

            for (i = 0; i < line.length(); i++)
            {
                if (isdigit((line[i])))
                {
                    if (isTestValue)
                    {
                        tmp.testValue = atoll(&line[i]);
                        i += std::to_string(tmp.testValue).length();
                        isTestValue = false;
                    }
                    else
                    {
                        tmp.numbers.push_back(atoll(&line[i]));
                        i += std::to_string(tmp.numbers.back()).length();
                    }
                }
            }

            Output.push_back(tmp);
        }
    }
    else
    {
        std::cout << "File not opened, skill issue" << std::endl;
    }

    return Output;
}

enum class Operator { ADD, MULT, CONCAT };

auto OperatorCompare = [](const Operator& first, const Operator& second) -> bool
{
    if (second == Operator::MULT)
    {
        if (first == Operator::ADD)
            return true;
    }

    return false;
};

bool CheckPossibility(const Equation& equation, const std::vector<Operator>& operators)
{
    //for (auto& x : equation.numbers)
    //{
        //std::cout << x << " ";
    //}

    std::uint64_t value = equation.numbers[0];

    //std::cout << "\nchecking : " << value << " ";

    for (std::uint64_t i = 0; i < equation.numbers.size() - 1; i++)
    {
        if (operators[i] == Operator::ADD)
        {
            //std::cout << "add -> ";
            value += equation.numbers[i+1];
        }
        else if (operators[i] == Operator::MULT)
        {
            //std::cout << "mult -> ";
            value *= equation.numbers[i+1];
        }
        else
        {
            //std::cout << "concat -> ";
            value = std::stoll(std::to_string(value).append(
                std::to_string(equation.numbers[i+1])
            ));
        }

        //std::cout << value << " ; ";
    }

    //std::cout << std::endl;

    return value == equation.testValue;
}

void PartOne()
{
    std::vector<Equation> Equations = ParseInput();
    std::vector<Operator> Operators;
    std::uint64_t p = 0;
    std::uint64_t q = 0;
    std::int64_t answer = 0;

    bool ifGood = false;

    for (Equation& e : Equations)
    {
        ifGood = false;

        Operators.resize(e.numbers.size() - 1);
        std::fill(Operators.begin(), Operators.end(), Operator::ADD);

        if (CheckPossibility(e, Operators))
        {
            answer += e.testValue;
            continue;
        }

        for (p = 0; p < Operators.size(); p++)
        {
            std::fill(Operators.begin(), Operators.end(), Operator::ADD);
            
            for (q = 0; q <= p; q++)
            {
                Operators[q] = Operator::MULT;
            }

            std::sort(Operators.begin(), Operators.end(), OperatorCompare);

            if (CheckPossibility(e, Operators))
            {
                ifGood = true;
                break;
            }

            while (std::next_permutation(Operators.begin(), Operators.end(), OperatorCompare))
            {
                if (CheckPossibility(e, Operators))
                {
                    ifGood = true;
                    break;
                }
            }

            if (ifGood)
                break;
        }

        if (ifGood)
            answer += e.testValue;
    }

    std::cout << "Part one answer " << answer << std::endl;
    // 267566105056
}

void GeneratePermsWithReps(const std::vector<Operator>& Ops, std::vector<Operator> Vec, 
                           const std::uint32_t& Len, std::vector<std::vector<Operator>>& Output)
{
    std::vector<Operator> copy = Vec;

    if (Vec.size() == Len)
    {
        Output.push_back(Vec);
        return;
    }

    for (const Operator& o : Ops)
    {
        copy = Vec;
        copy.push_back(o);
        GeneratePermsWithReps(Ops, copy, Len, Output);
    }
}

void PartTwo()
{
    std::vector<Equation> Equations = ParseInput();
    std::vector<std::vector<Operator>> AllPermsWithReps;

    GeneratePermsWithReps(std::vector<Operator>({ 
        Operator::ADD, Operator::CONCAT, Operator::MULT 
    }), std::vector<Operator>(), 3, AllPermsWithReps);

    std::uint64_t ans = 0;

    for (Equation& e : Equations)
    {
        for (std::vector<Operator>& p : AllPermsWithReps)
        {
            if (CheckPossibility(e, p))
            {
                ans += e.testValue;
                break;
            }
        }
    }

    std::cout << "Part two answer " << ans << std::endl;
}

int main()
{
    //PartOne();
    PartTwo();

/*
    Equation p;
    p.numbers = { 6, 8, 6, 15 };
    p.testValue = 7290;
    std::vector<Operator> o = { Operator::MULT, Operator::CONCAT, Operator::MULT };

    if (CheckPossibility(p, o))
        std::cout << "llll\n";
    else
        std::cout << ":(\n";

    std::vector<Operator> AllOps = { Operator::ADD, Operator::MULT, Operator::CONCAT };
    std::vector<std::vector<Operator>> x;
    x.clear();
    GeneratePermsWithReps(AllOps, std::vector<Operator>(), AllOps.size(), x);

    for (auto& y : x)
    {
        for (auto& z : y)
        {
            if (z == Operator::ADD)
            {
                std::cout << "add ";
            }
            if (z == Operator::MULT)
            {
                std::cout << "mul ";
            }
            if (z == Operator::CONCAT)
            {
                std::cout << "con ";
            }
        }

        std::cout << std::endl;
    }

    std::cout << x.size() << std::endl;
*/
    return 0;
}