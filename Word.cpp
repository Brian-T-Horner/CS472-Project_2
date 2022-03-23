// Word Class Project Implementation
//
// Author: Brian Horner
// Edit History:
// 3/19/2022 - Initial Version
// 3/22/2022 - Added default constructor and get functions
// 3/23/2022 - Added overwriteData, displayWord, writeBackData and writeSingleData

// Standard Library Includes
#include <iostream>
// User Built Includes
#include "Word.h"


// --- Constructor ---
Word::Word() {}

Word::Word(unsigned short slotNumber) {
    for (unsigned int i{0}; i<0xF+0x1; i++){
        data[i] = 0;
    }
    this->slot = slotNumber;
}

// --- Calc Functions ---
void Word::overwriteData(short * mainMem, unsigned short address) {
    unsigned short blockMask = 0xFF0;
    unsigned short blockBegin = address & blockMask;
    unsigned short blockEnd = blockBegin + 0xF;
    unsigned int dataIndex = 0;
    for(unsigned short i = blockBegin; i< blockEnd+1; i++){
        this->data[dataIndex] = mainMem[i];
        dataIndex++;
    }
    this->dirtyBit = 1;
}

void Word::writeBackData(short *mainMem){
    unsigned short writeBackStart = (this->tag<<8) + (this->slot<<4) + 0x0;
    unsigned short writeBackEnd = writeBackStart + 0xF;
    unsigned int dataIndex{0};
    for(unsigned short i = writeBackStart; i<writeBackEnd +1; i++){
        mainMem[i] = this->data[dataIndex];
        dataIndex++;
    }
}

void Word::writeSingleData(unsigned short address, short data) {
    unsigned short dataOffset = 0x00F & address;
    this->data[dataOffset] = data;
}



// --- Get Functions ---
unsigned short Word::getSlotNumber() const {return this-> slot;}
unsigned short Word::getTag() const {return this->tag;}
unsigned short Word::getValidBit() const {return  this-> validBit;}
unsigned short Word::getDirtyBit() const {return this->dirtyBit;}



// --- Set Functions ---



// --- Print Function ---
void Word::printData() const{
    std::cout << "Printing array of data location at cache slot " <<std::hex
                 <<std::uppercase <<this->slot<<": "<<std::endl;
    for (unsigned int i{0}; i<16; i++){
        std::cout<< std::hex<<std::uppercase<< this->data[i] << std::endl;
    }
}

void Word::displayWord() const{
    std::cout << std::hex<<std::uppercase << this->slot << "\t\t";
    std::cout << this->validBit << "\t\t" <<this->dirtyBit <<"\t\t";
    std::cout << this->tag <<"\t\t";
    for(unsigned int i{0}; i<0xF+0x1; i++){
        std::cout << this->data[i] << "\t";
    }
    std::cout<<std::endl;
};

// --- Destructor ---
Word::~Word() {

}
// --- Data Members ---