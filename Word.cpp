// Word Class Project Implementation
//
// Author: Brian Horner
// Edit History:
// 3/19/2022 - Initial Version
// 3/22/2022 - Added default constructor and get functions

// Standard Library Includes
#include <iostream>
// User Built Includes
#include "Word.h"


// --- Constructor ---
Word::Word() {}

Word::Word(unsigned short slotNumber) {
    for (unsigned int i{0}; i<16; i++){
        data[i] = 0x00;
    }
    this->slot = slotNumber;
}

// --- Calc Functions ---



// --- Get Functions ---
unsigned short Word::getOffset() const {return this->offset;}
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
// --- Destructor ---
Word::~Word() {

}
// --- Data Members ---