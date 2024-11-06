#include <iostream>
#include <string>
#include <format>
#include <iomanip>
#include "CPU.h"
#include <cmath>
using namespace std;

enum choice{ LOAD = 1, RUN, DISPLAY, RESET, EXIT};

int getChoice() {
    cout<<"\n1- Load new program\n2- Run program\n3- Display memory\n4- Clear memory\n5- Exit\n\n-";
    int n;
    do {
        cin>>n;
    } while (n < 1 || n > 5);
    return n;
}
int main() {

    int choice = getChoice();
    CPU prg;
    while (choice!=choice::EXIT) {

        switch (choice) {
            case 1:
                cin.ignore();
            prg.loadProgram(cin);
            break;
            case 2:
                prg.runProgram();
            break;
            case 3:
                prg.displayMemory();
            break;
            case 4:
                prg.resetProgram();
            break;
            default:
                break;
        }
        choice = getChoice();
    }





    return 0;
}
