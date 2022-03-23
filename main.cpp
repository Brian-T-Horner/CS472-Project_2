// CS472 Project 1 - MIPS Disassembler
//
// Author: Brian Horner
// Edit History:
// 2/5/2022 - Initial Version and Establishing Git Repo
// 3/22/2022 - Added populateMainMem and displayMainMem funcs
// 3/22/2022 - Fixed populateMainMem func
// 3/22/2022 - Added calcAddressValues func

// Standard Library Includes
#include <iostream>

// User Built Includes
#include "Word.h"

void populateMainMem(short *, short);
void displayMainMem(short *, short);
void calcAddressValues(short);


int main() {

    short main_mem[2048];
    populateMainMem(main_mem, 2048);
    displayMainMem(main_mem, 2048);

    short testAddress{0x14A};

    calcAddressValues(testAddress);

    return 0;
}

void calcAddressValues(short address){
    unsigned short mask = 0x00F;
    unsigned short offset = mask & address;
    unsigned short slot = ((mask <<4) & address)>>4;
    unsigned short tag = ((mask <<8) & address)>>8;

    std::cout << "Offset: " <<std::hex<<std::uppercase <<offset<<std::endl;
    std::cout << "Slot: " << slot <<std::endl;
    std::cout << "Tag: " << tag <<std::endl;
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
            b++;
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
