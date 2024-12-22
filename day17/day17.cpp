#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

// this class is poorly written (in terms of beauty and formatting, naturally)
// well, I was too lazy to make separate header and source file for it lol
class Computer
{
    public:
        Computer()
        {
            this->regA = 0;
            this->regB = 0;
            this->regC = 0;
            this->InstructionPtr = 0;
            this->Output.clear();

            if (!ReadProgram())
            {
                this->Program.clear();
            }
        }

        std::string GetOutput()
        {
            if (this->Output.size() == 0)
                return "[No output available]";

            std::string _output = "";
            std::uint64_t i = 0;

            for (i = 0; i < this->Output.size() - 1; i++)
            {
                _output.append(std::to_string(this->Output[i]));
                _output.append(",");
            }

            _output.append(std::to_string(this->Output[i]));
            return _output;
        }

        void GetComputerState()
        {
            std::cout << "-----------------------------------\n"
                      << "Computer:\n" 
                      << "Register A: " << this->regA << "\n"           
                      << "Register B: " << this->regB << "\n"                       
                      << "Register C: " << this->regC << "\n"
                      << "Instruction pointer: " << this->InstructionPtr << "\n"
                      << "Next command(operand): " << static_cast<unsigned int>(this->Program[this->InstructionPtr]) << "("
                      << static_cast<unsigned int>(this->Program[this->InstructionPtr + 1]) << ")\n"
                      << "Program: ";

            for (auto& x : this->Program)
                std::cout << static_cast<unsigned int>(x) << " ";

            std::cout << "\n-----------------------------------\n";
        }

        void RunProgram(const bool& ifReload)
        {
            this->InstructionPtr = 0;
            this->Output.clear();

            if (ifReload)
                this->ReadProgram();

            const std::uint64_t programLen = this->Program.size();

            //this->GetComputerState();

            while (InstructionPtr < (programLen - 1) && InstructionPtr >= 0)
            {
                if (RunCommand(this->Program[this->InstructionPtr], 
                               this->Program[this->InstructionPtr + 1]))
                {
                    this->InstructionPtr += 2;
                }

                //this->GetComputerState();
            }
        }

        void SetRegisterA(const std::int64_t& newRegisterA)
        {
            this->regA = newRegisterA;
        }

        std::int64_t FindRegisterA()
        {
            this->GetComputerState();

            this->RunProgram(true);

            this->GetComputerState();

            if (this->Output == this->Program)
                return this->regA;
            
            while (this->Output.size() != this->Program.size())
            {
                this->GetComputerState();

                if (this->Output.size() < this->Program.size())
                    this->regA += 1;
                else if (this->Output.size() > this->Program.size())
                    this->regA -= 1;                

                this->RunProgram(false);

                std::cin.get();
            }

            //if (this->Output == this->Program)
                return this->regA;


        }

    private:
        std::uint64_t InstructionPtr;
        std::int64_t regA, regB, regC;
        std::vector<std::uint8_t> Program;
        std::vector<std::uint8_t> Output;

        bool ReadProgram()
        {
            std::fstream file("input.txt", std::ios::in);

            if (file.is_open())
            {
                std::string line;
                std::int64_t tmp;
                this->Program.clear();

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

                for (std::int64_t i = tmp; i < line.length(); i++)
                {
                    if (isdigit(line[i]))
                    {
                        this->Program.push_back(std::stoi(line.substr(i, 1)));
                    }
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

        std::int64_t GetComboOperand(const std::int64_t& Operand)
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

        bool RunCommand(const std::int64_t& Opcode, const std::int64_t& Operand)
        {
            bool output = true;
            
            switch(Opcode)
            {
                case 0: // adv
                {
                    this->regA = static_cast<std::int64_t>(this->regA / std::pow(2, this->GetComboOperand(Operand)));
                    break;
                }
                case 1: // bxl
                {
                    this->regB = (this->regB ^ Operand);
                    break;
                }
                case 2: // bst
                {
                    this->regB = GetComboOperand(Operand) % 8;
                    break;
                }
                case 3: // jnz
                {
                    if (this->regA != 0)
                    {
                        this->InstructionPtr = Operand;
                        output = false;
                    }

                    break;
                }
                case 4: // bxc
                {
                    this->regB = (this->regB ^ this->regC);
                    break;
                }
                case 5: // out
                {
                    this->Output.push_back(GetComboOperand(Operand) % 8);
                    break;
                }
                case 6: // bdv
                {
                    this->regB = static_cast<std::int64_t>(this->regA / std::pow(2, this->GetComboOperand(Operand)));
                    break;
                }
                case 7: // cdv
                {
                    this->regC = static_cast<std::int64_t>(this->regA / std::pow(2, this->GetComboOperand(Operand)));
                    break;
                }
                default:
                {
                    std::cout << "Computer::RunCommand | Unknown Opcode: " << Opcode << std::endl;
                    break;
                }
            }

            return output;
        }
};


int main()
{
    Computer bob;
    //bob.RunProgram(true); //< Part one: 2,3,4,7,5,7,3,0,7
    //std::cout << "Part one output: " << bob.GetOutput() << std::endl;

    //bob.SetRegisterA(1);
    //bob.RunProgram(false);

    //bob.SetRegisterA(117440);
    //bob.RunProgram(false);

    std::cout << "what I found " << bob.FindRegisterA() << std::endl;

    return 0;
}

/*

    std::cout << "Program:\n";

    for (std::int8_t x : bob.Program)
    {
        std::cout << static_cast<unsigned int> (x) << " ";
    }

    std::cout << std::endl;

*/