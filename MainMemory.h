//
// Created by mmh20 on 10/6/2024.
//
#ifndef MAINMEMORY_H
#define MAINMEMORY_H

#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <exception>


class MainMemory {
    int memoryCells[256]{0};


public:

    void setCell(const int& address, const int& value) {

        memoryCells[address] = value;
    }

    int getCell(const int& address) {
        return memoryCells[address];
    }

    void clear() {
        for( auto& cell : memoryCells) {
            cell = 0;
        }
    }

    void loadInstructions(std::istream& cin,const int& startAddress) {
        std::string instruction;
        int currentAddress = startAddress;
        std::string line;
        getline(cin,line);
        std::istringstream streamLine(line);
        while (streamLine>>instruction) {
            if(!validateInstruction(instruction)) {
                continue;
            }
            std::string part1,part2;
            part1 = instruction.substr(0,2);
            part2 = instruction.substr(2,2);

            setCell(currentAddress, stoi(part1, nullptr, 16));
            currentAddress++;
            setCell(currentAddress, stoi(part2, nullptr, 16));
            currentAddress++;
        }
        std::cout<<"\nProgram has been loaded successfully!\n";
    }

    bool validateInstruction(std::string instruction) {
        if(instruction.length()!=4) {
            return false;
        }

        int op;

        try {
            op = stoi(instruction.substr(0,1), nullptr, 16);
            stoi(instruction.substr(1), nullptr, 16);
            stoi(instruction.substr(2), nullptr, 16);
            stoi(instruction.substr(3), nullptr, 16);

        } catch (std::exception e) {

            return false;
        }



        if(op<1 || op> 12) {
            return false;
        }

        return true;


    }


};



#endif //MAINMEMORY_H