//
// Created by mmh20 on 10/6/2024.
//

#ifndef REGISTER_H
#define REGISTER_H



class Register {

    int registerCells[16]{0};

public:

    void setCell(const int& address, const int& value) {

        registerCells[address] = value;
    }

    int getCell(const int& address) {
        return registerCells[address];
    }

    void clear() {
        for( auto& cell : registerCells) {
            cell = 0;
        }
    }


};



#endif //REGISTER_H
