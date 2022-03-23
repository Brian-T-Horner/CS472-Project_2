// CS472 Project 1 - MIPS Disassembler
//
// Author: Brian Horner
// Edit History:
// 2/5/2022 - Initial Version and Establishing Git Repo
// 3/19/2022 -

// Standard Library Includes
#include <iostream>

// User Built Includes
#include "Word.h"

void populateMainMem(short *, short);
void displayMainMem(short *, short);

int main() {

    short main_mem[2048];
    populateMainMem(main_mem, 2048);
    displayMainMem(main_mem, 2048);

    return 0;
}

void populateMainMem(short *mainMem, short mainMemSize){
    short b{0};
    for (short i {0}; i<mainMemSize; i ++){
        if (b <= 0xFF){
            mainMem[i] = b;
            b++;
        }else{
            b = 0;
            mainMem[i] = b;
        }
    }
}

void displayMainMem(short *mainMem, short mainMemSize){
    for(unsigned int b{0}; b < mainMemSize; b++){
        std::cout << "Array element " << std::hex<<std::uppercase<< b << " is "
        <<mainMem[b]
        <<std::endl;
    }
}
