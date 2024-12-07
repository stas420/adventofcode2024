#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

using EquationType = std::pair<std::int64_t, std::vector<std::int64_t>>; 

EquationType ParseInputEquation(const std::string& Line)
{
    EquationType out;
    std::int32_t i = 0;
    bool isTestValue = true;

    while(i < Line.length())
    {
        if (isdigit(Line[i]))
        {
            if (isTestValue)
            {
                out.first = atoll(&Line[i]);
                i += std::to_string(out.first).length();
                isTestValue = false;
            }
            else
            {
                out.second.push_back(atoll(&Line[i]));
                i += std::to_string(out.second.back()).length();
            }
        }
        else
        {
            i++;
        }
    }    

    return out;
}

enum class Operator{ ADD, MULT };

std::int64_t factorial(const std::int64_t& n)
{
    return ((n == 1) || (n == 0)) ? 1 : (factorial(n-1) * n);
}

std::int64_t Compute(const std::vector<std::int64_t>& Numbers, const std::vector<Operator>& Operators)
{
    std::cout << "[] ==== ";
    for (auto & x: Numbers)
    {
        std::cout << x << " ";
    }
    std::cout << "\nops ";

    for (auto& x: Operators)
    {
        if (x == Operator::ADD)
        {
            std::cout << "add ";
        }
        else
        {
            std::cout << "mul ";
        }
    }

    std::int64_t out = 0;
    std::int64_t mult = 0;
    std::int64_t n = 0;
    std::int64_t o = 0;

    mult = Numbers[0];

    while(n < Numbers.size() && o < Operators.size())
    {
        std::cout << "mult " << mult << "\n";

        if (Operators[o] == Operator::ADD)
        {
            std::cout << "add to prev\n";
            out += mult;
            o++;
            n++;
            mult = Numbers[n];
        }
        else
        {
            std::cout << "mult " << mult << "\n";
            n++;
            o++;
            mult *= Numbers[n];
        }
    }

    out += mult;

    std::cout << " -> " << out << std::endl;

    return out;
}

bool Check(const std::vector<std::int64_t>& Numbers, const std::int64_t& Value)
{
    const std::int64_t OperatorsNum = Numbers.size() - 1;
    std::vector<Operator> OperatorsSet(OperatorsNum, Operator::ADD);

    if (Value == Compute(Numbers, OperatorsSet))
    {
        std::cout << ">> yee\n";
        return true;
    }

    for (std::int64_t i = 0; i < OperatorsNum; i++)
    {
        std::fill(OperatorsSet.begin(), OperatorsSet.end(), Operator::ADD);

        for (std::int64_t j = 0; j <= i; j++)
        {
            OperatorsSet[j] = Operator::MULT;
        }

        if (Value == Compute(Numbers, OperatorsSet))
        {
            std::cout << ">> yee\n";
            return true;
        }

        auto operatorCompare = [](const Operator& f, const Operator& s) -> bool
        {
            if (f == Operator::ADD)
            {
                if (s == Operator::MULT)
                    return true;
                else
                    return false;
            }
            return false;
        };

        std::sort(OperatorsSet.begin(), OperatorsSet.end(), operatorCompare);
        
        while (
            std::next_permutation(OperatorsSet.begin(), OperatorsSet.end(), operatorCompare)
        )
        {
            std::cout << "perm\n";
            if (Value == Compute(Numbers, OperatorsSet))
            {
                std::cout << ">> yee\n";
                return true;
            }

            std::cout << "> nope\n";
        }
    }

    std::cout << "------------------------\n";

    return false;
}

void PartOne()
{
    std::fstream file("input.txt", std::ios::in);

    if (file.is_open())
    {
        std::vector<EquationType> Equations;
        std::string line;
        
        while(std::getline(file, line))
        {
            Equations.push_back(ParseInputEquation(line));
        }

        file.close();

        std::int64_t Result = 0;

        for (const EquationType& eq : Equations)
        {
            if (Check(eq.second, eq.first))
            {
                Result += eq.first;
            }
        }

        std::cout << "Part one result " << Result << std::endl;
        //
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
    // 19 * 34 + 22 * 4
    return 0;
}

        /*
        for (auto& x : Equations)
        {
            std::cout << x.first << " = ";

            for (auto& y : x.second)
            {
                std::cout << y << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        */
