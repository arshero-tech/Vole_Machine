//
// Created by mmh20 on 10/6/2024.
//


#ifndef CPU_H
#define CPU_H

#include <string>
#include "MainMemory.h"
#include "Register.h"
#include <iostream>
#include <format>
#include <iomanip>
#include <cmath>
#include "conversion.h"

class CPU {

    int programCounter{0};
    std::string instructionRegister;
    MainMemory mmry;
    Register rgstr;
    bool reachedTheEnd = false;

    void incrementProgramCounter() {

        programCounter+=2;
        if(programCounter==256) {
            reachedTheEnd = true;
            programCounter = 0;
        }
    }

    public:

    void setPC(const int& programCounter) {
        this -> programCounter = programCounter;
    }

    int getPC() {
        return programCounter;
    }

     void fetchInstruction() {

         std::cout<<"\nFetching the instruction in memory address "<< programCounter << " and " <<programCounter+1<<": ";
         int instruction = mmry.getCell(programCounter);
         std::string hexStr;
         std::string part1 = std::format("{:x}", instruction);

         if(part1.length()==1) {
             part1 = '0' + part1;
         }
         hexStr+=part1;

        instruction = mmry.getCell(programCounter+1);

         std::string part2 = std::format("{:x}", instruction);

         if(part2.length()==1) {
             part2 = '0' + part2;
         }

         hexStr+= part2;

         for(int i = 0;i<hexStr.length();i++) {
             if(isalpha(hexStr[i])) {
                 hexStr[i] = toupper(hexStr[i]);
             }
         }

        instructionRegister = hexStr;

        std::cout<<instructionRegister<<std::endl;
    }

    bool exectueInstruction() {


         std::string XY = instructionRegister.substr(2,2);

         switch (instructionRegister[0]) {
             case '1':
                 instruction1();
             break;
             case '2':
                 instruction2();
             break;
             case '3':
             if(XY == "00") {
                 instruction3R00();
             } else {
                 instruction3();

             }
             break;

             case '4':
                 instruction4();
             break;
             case '5':
                 instruction5();
             break;
             case '6':
                 instruction6();
             break;
             case '7':
                 instruction7();
             break;
             case '8':
                 instruction8();
             break;
             case '9':
                 instruction9();
             break;
             case 'A':
                 instructionA();
             break;
             case 'B':
                 instructionB();
             break;
             case 'C':
                 std::cout<<"\nHALT.\n";
             return false;
             default:
                 break;
         }
        incrementProgramCounter();
        if(reachedTheEnd) {
            std::cout << "\nYou have reached the end of the program.\n";
            return false;
        }
        return true;
    }


    void loadProgram(std::istream& cin, const int& startAddress = 0) {
        resetProgram();
        mmry.loadInstructions(cin, startAddress);
        programCounter = startAddress;
    }

    void runProgram() {

        fetchInstruction();
        while (exectueInstruction()) {
            fetchInstruction();

        }
    }

    void resetProgram() {
        programCounter = 0;
        mmry.clear();
        rgstr.clear();
        instructionRegister = "";
    }

    void displayMemory() {
        std::cout<<std::endl;
        std::cout<<"   ";
        for(int i = 0;i<16;i++) {
            std::cout<<std::right<<std::hex<<i;
            if(i!=15) {
                std::cout<<std::setw(6)<<std::setfill(' ');
            }
        }
        std::cout<<std::endl;

        for(int i = 0 ;i<16;i++) {
            std::cout<<std::hex<<i<<"  ";
            for(int j = i * 16;j<(i+1) * 16;j++) {
                std::cout<<std::setw(2)<<std::setfill('0')<<std::right<<std::hex<<mmry.getCell(j);
                std::cout<<"    ";
            }
            std::cout<<std::endl;
        }
    }

    void instruction1() {
         int r = std::stoi(instructionRegister.substr(1,1), nullptr, 16);
         int memoryAddress = std::stoi(instructionRegister.substr(2,2), nullptr, 16);
         int value = mmry.getCell(memoryAddress);


         rgstr.setCell(r,value);
     }

    void instruction2() {
         int r = std::stoi(instructionRegister.substr(1,1), nullptr, 16);
         int value = std::stoi(instructionRegister.substr(2,2), nullptr, 16);
         std::cout<<"\nRegister "<< r <<" = "<< value<<std::endl;
         rgstr.setCell(r,value);
     }

    void instruction3() {
         int r = std::stoi(instructionRegister.substr(1,1), nullptr, 16);
         int value = rgstr.getCell(r);
         int memoryAddress = std::stoi(instructionRegister.substr(2,2), nullptr, 16);
         std::cout<<"\nMemory address "<<std::hex<<memoryAddress<<" = "<<"Register "<<r<<" = "<<value<<std::endl;
         mmry.setCell(memoryAddress,value);
     }

    void instruction3R00() {
         int r = std::stoi(instructionRegister.substr(1,1), nullptr, 16);
         int value = rgstr.getCell(r);
         std::cout<<"\nDisplaying to the screen: "<<value<<std::endl;

     }

    void instruction4() {
         int r1 = std::stoi(instructionRegister.substr(2,1), nullptr, 16);
         int r2 = std::stoi(instructionRegister.substr(3,1), nullptr, 16);
         rgstr.setCell(r2,rgstr.getCell(r1));
     }

    void instruction5() {
         int r1 = std::stoi(instructionRegister.substr(2,1), nullptr, 16);
         int r2 = std::stoi(instructionRegister.substr(3), nullptr, 16);
         int r3 = std::stoi(instructionRegister.substr(1,1), nullptr, 16);

         int num1 = rgstr.getCell(r1), num2 = rgstr.getCell(r2);
         int sum = decimalToTwosComp(num1) + decimalToTwosComp(num2);
        sum = twosCompToDecimal(sum);

         std::cout<<"\nRegister "<< r3 <<" = "<<"Register "<<r1<<" + Register "<<r2<<std::endl;

         rgstr.setCell(r3, sum);

     }

    void instruction6() {
        int r1 = std::stoi(instructionRegister.substr(2,1), nullptr, 16);
        int r2 = std::stoi(instructionRegister.substr(3), nullptr, 16);
        int r3 = std::stoi(instructionRegister.substr(1,1), nullptr, 16);
        double flt1 = decimalToFloat(rgstr.getCell(r1));
        double flt2 = decimalToFloat(rgstr.getCell(r2));
        double sum = flt1 + flt2;
        std::string fltString = floatToBinary(sum);
        int result = binaryToDecimal(fltString);
        rgstr.setCell(r3,result);

     }

    void instruction7() {
         int r1 = std::stoi(instructionRegister.substr(2,1), nullptr, 16);
         int r2 = std::stoi(instructionRegister.substr(3,1), nullptr, 16);
         int r3 = std::stoi(instructionRegister.substr(1,1), nullptr, 16);

         int sum = rgstr.getCell(r1) | rgstr.getCell(r2);

         rgstr.setCell(r3, sum);
     }
    void instruction8() {
         int r1 = std::stoi(instructionRegister.substr(2,1), nullptr, 16);
         int r2 = std::stoi(instructionRegister.substr(3,1), nullptr, 16);
         int r3 = std::stoi(instructionRegister.substr(1,1), nullptr, 16);

         int sum = rgstr.getCell(r1) & rgstr.getCell(r2);

         rgstr.setCell(r3, sum);
     }

    void instruction9() {
         int r1 = std::stoi(instructionRegister.substr(2,1), nullptr, 16);
         int r2 = std::stoi(instructionRegister.substr(3,1), nullptr, 16);
         int r3 = std::stoi(instructionRegister.substr(1,1), nullptr, 16);

         int sum = rgstr.getCell(r1) ^ rgstr.getCell(r2);

         rgstr.setCell(r3, sum);
     }

    void instructionA() {
         int r = std::stoi(instructionRegister.substr(1,1), nullptr, 16);
         int shift = std::stoi(instructionRegister.substr(3,1), nullptr, 16);

         int value = (rgstr.getCell(r) >> shift) | rgstr.getCell(r) << (8 - shift);
         rgstr.setCell(r, value);

     }

    void instructionB() {
         int r = std::stoi(instructionRegister.substr(1,1), nullptr, 16);
         int memoryAddress = std::stoi(instructionRegister.substr(2,2), nullptr, 16);

         if(rgstr.getCell(0) == rgstr.getCell(r)) {
             programCounter = memoryAddress;
             programCounter-=2;
         }

     }



};



#endif //CPU_H
