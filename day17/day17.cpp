#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <fstream>

// this class is poorly written (in terms of beauty and formatting, naturally)
// well, I was too lazy to make separate header and source file for it lol
class Computer
{
    public:
        Computer()
        {
            if (!ReadProgram())
            {
                this->Program.clear();
            }
        }

        std::int64_t GetOperandValue(const std::int64_t& Operand)
        {
            if (Operand == 4)
                return this->regA;
            if (Operand == 5)
                return this->regB;
            if (Operand == 6)
                return this->regC;
            
            if (Operand > 6 || Operand < 0)
            {
                std::cout << "Wrong operand value: " << Operand << std::endl;
                return -1;
            }

            return Operand;
        }

    //private:
        std::int64_t regA, regB, regC;
        std::vector<std::uint8_t> Program;

        bool ReadProgram()
        {
            std::fstream file("input.txt", std::ios::in);

            if (file.is_open())
            {
                std::string line;
                std::int64_t tmp;

                std::getline(file, line);
                tmp = line.find(':');
                tmp++;
                this->regA = atoll(&line[tmp]);

                std::getline(file, line);
                tmp = line.find(':');
                tmp++;
                this->regB = atoll(&line[tmp]);

                std::getline(file, line);
                tmp = line.find(':');
                tmp++;
                this->regC = atoll(&line[tmp]);

                std::getline(file, line);
                std::getline(file, line);
                tmp = line.find(':');
                tmp++;

                for (std::int64_t i = tmp; i < line.length();)
                {
                    if (isdigit(line[i]))
                    {
                        std::cout << " >> push back " << atoi(&line[i]);
                        this->Program.push_back(atoi(&line[i]));
                        i += std::to_string(Program.back()).length();
                    }
                    else
                    {
                        i++;
                    }

                    std::cout << std::endl;
                }

                file.close();

                return true;
            }
            else
            {
                std::cout << "File not opened, skill issue" << std::endl;
            }

            return false;
        }

};


int main()
{
    Computer bob;
    
    std::cout << "Program:\n";

    for (auto& x : bob.Program)
    {
        std::cout << x << " ";
    }

    std::cout << std::endl;

    return 0;
}