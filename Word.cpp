// Word Class Project Implementation
//
// Author: Brian Horner
// Edit History:
// 3/19/2022 - Initial Version
// 3/22/2022 - Added default constructor and get functions
// 3/23/2022 - Added overwriteData, displayWord, writeBackData and writeSingleData
// 3/24/2022 - Added getSingleData function

// Standard Library Includes
#include <iostream>
// User Built Includes
#include "Word.h"


// --- Constructor ---
Word::Word() = default;

Word::Word(unsigned short slotNumber) {
    for (unsigned int i{0}; i<0xF+0x1; i++){
        data[i] = 0;
    }
    this->slot = slotNumber;
}

// --- Calc Functions ---

void Word::loadData(short * mainMem, unsigned short address) {
    // Overwrite the data currently in the word with data from main mem
    unsigned short blockMask = 0b111111110000;
    //TODO: FIX ERROR WITH BLOCK BEGIN HERE
    unsigned short blockBegin = address & (blockMask);
    std::cout << "Block begin: " <<std::hex <<blockBegin <<std::endl;
    unsigned short blockEnd = blockBegin + 0xF;
    unsigned int dataIndex = 0;
    //    // Overwrite the data currently in the word with data from main mem
    //    unsigned short blockMask = 0xFF0;
    //    unsigned short blockBegin = address & blockMask;
    //    unsigned short blockEnd = blockBegin + 0xF;
    //    unsigned int dataIndex = 0;
    //    for(unsigned short i = blockBegin; i< blockEnd+1; i++){
    //        this->data[dataIndex] = mainMem[i];
    //        dataIndex++;
    //    }
    for(unsigned short i = blockBegin; i< blockEnd+0x1; i++){
        this->data[dataIndex] = mainMem[i];
        std::cout << mainMem[i] <<std::endl;
        dataIndex++;
    }
    unsigned short addressMask = 0x00F;
    this->validBit = 0x1;
    this->tag = ((addressMask<<8)&address)>>8;
}


void Word::writeBackData(short *mainMem){
    unsigned short writeBackStart = (this->tag<<8) + (this->slot<<4) + 0x0;
    unsigned short writeBackEnd = writeBackStart + 0xF;
    unsigned int dataIndex{0};
    for(unsigned short i = writeBackStart; i<writeBackEnd +1; i++){
        mainMem[i] = this->data[dataIndex];
        dataIndex++;
    }
    this->dirtyBit = 0x0;
}

void Word::writeSingleData(unsigned short address, short data) {
    unsigned short dataOffset = 0x00F & address;
    this->data[dataOffset] = data;
    this->dirtyBit = 1;
}


//void Word::overwriteData(short * mainMem, unsigned short address) {

//    unsigned short addressMask = 0x00F;
//
//    this->dirtyBit = 0x1;
//    this->validBit = 0x1;
//    this->tag = ((addressMask<<8)&address)>>8;
//}


// --- Get Functions ---
unsigned short Word::getSlotNumber() const {return this-> slot;}
unsigned short Word::getTag() const {return this->tag;}
unsigned short Word::getValidBit() const {return  this-> validBit;}
unsigned short Word::getDirtyBit() const {return this->dirtyBit;}

unsigned short Word::getSingleData(unsigned short address) const{
    unsigned short mask = 0x00F;
    unsigned short offset = address & mask;
    unsigned int returnValue = this->data[offset];
    return returnValue;
}




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
Word::~Word() {}
