// CS472 Project 1 - MIPS Disassembler
//
// Author: Brian Horner
// Edit History:
// 2/5/2022 - Initial Version and Establishing Git Repo
// 3/22/2022 - Added populateMainMem and displayMainMem funcs
// 3/22/2022 - Fixed populateMainMem func
// 3/22/2022 - Added calcAddressValues func
// 3/22/2022 - Changed cache to contain dynamic objects
// 3/22/2022 - Added initialize cache function for setting tag and data
// 3/22/2022 - Added todos for write and read for progress tomorrow
// 3/23/2022 - Added printMainMem and displayCache functions
// 3/24/2022 - Added basic run function adn read function


//TODO: WriteByte function
//TODO: ReadByte function
//TODO: set tag
//TODO: get slot
//TODO: check data for reads to see if it hit



// Standard Library Includes
#include <iostream>
#include <string>
#include <fstream>

// User Built Includes
#include "Word.h"

void populateMainMem(short *, short);
void displayMainMem(short *, short);
unsigned short calcAddressValues(short);
void initializeCache(Word cache[]); //used for print test statements
void printMainMemData(short *, unsigned short);
void readCache(short *, Word cache[], short);
//void writeCache(Word cache[], short address, short data);
void displayCache(Word cache[]);
void run();

// TODO: Add file read function, readCache, writeCache, update
//  word, and all writes needed to file

int main() {

    short main_mem[2048];
    Word *cache = new Word[16];
    initializeCache(cache);
    populateMainMem(main_mem, 2048);


    unsigned short testAddress{0x14A};
    unsigned short slot = (0x0F0 & testAddress)>>4;
    cache[slot].loadData(main_mem, testAddress);
    displayCache(cache);
    cache[slot].writeSingleData(0x14D, 0xCD);
    displayCache(cache);
    cache[slot].writeBackData(main_mem);
    displayCache(cache);
    cache[slot].overwriteData(main_mem, 0x24C);
    displayCache(cache);



    delete [] cache;
    return 0;
}

void run(){
    short main_mem[2048];
    Word *cache = new Word[16];
    initializeCache(cache);
    populateMainMem(main_mem, 2048);
    char inputChar;
    bool invalidInput = false;
    //TODO: File reading
    std::cout << "(R)ead, (W)rite, or (D)isplay Cache?" <<std::endl;
    while(!invalidInput){
        std::cin >> inputChar;
        switch (inputChar){
            case 'R':
                std::cout << "What address would you like to read?" <<std::endl;
            case 'W':
                std::cout << "What address would you like to write to?"
                <<std::endl;
            case 'D':
                std::cout<< "Display" <<std::endl;
            default:
                invalidInput = true;

        }
    }
}
void displayCache(Word cache[]){
    std::cout<< "Slot\tValid\tDirty\tTag\t\tData"<<std::endl;
    for (unsigned int i{0}; i<0xF+1; i++){
        cache[i].displayWord();
    }
    std::cout<<std::endl;
}

void printMainMemData(short *mainMem, unsigned short address){
    unsigned short blockMask = 0xFF0;
    unsigned short blockBegin = address & blockMask;
    unsigned short blockEnd = blockBegin + 0xF;
    for(unsigned short i = blockBegin; i< blockEnd+1; i++){
        std::cout << "Data at memory location " <<std::hex<<std::uppercase<<i << " is " << mainMem[i]<<std::endl;
    }
}


void readCache(short *mainMem, Word cache[], short address){
    unsigned short mask = 0xF;
    unsigned short offset = address & mask;
    unsigned short slot = address & (mask<<4);
    unsigned short tag = address & (mask<<8);

    if(cache[slot].getValidBit() == 0){
        cache[slot].loadData(mainMem,address);
        std::cout << "At that byte there is the value ";
        std::cout << cache[slot].getSingleData(address)<< " (Cache Miss)"
        <<std::endl;
    }

        // miss grab from main
    // else if valid == 1
       // if tag & slot != ==
            // if dirty == 0
                // miss grab from main
            // else if dirty == 1
                // write back
                // grab from main
        // if tag and slot ==
            // hit read from cache

}


void writeCache(Word cache[], short address, short data){
    unsigned short standardMask = 0xF;

    // if valid  == 0
        //get data
        // overwrite slot
        // update dirty bit, tag
    // else if valid == 1
        // if tag & slot != ==
            // if dirty == 0
                // get data
                // overwrite slot
                // update dirty bit,tag
            // else if dirty == 1
                // write back data
                // grab data
                // overwrite slot
                // update dirty bit & tag
        // if tag & slot ==
            // if dirty bit == 1
                // write back data
                // grab data again?
                // overwrite slot
                //update dirty bit & tag
            // if dirty bit == 0
                // overwrite data
                // update dirty bit and tag
}



unsigned short calcAddressValues(short address){
    unsigned short mask = 0x00F;
    unsigned short offset = mask & address;
    unsigned short slot = ((mask <<4) & address)>>4;
    unsigned short tag = ((mask <<8) & address)>>8;
    return slot;
}

void initializeCache(Word cache[]){
    for (unsigned short i{0}; i<0xF+1; i++){
        cache[i] = Word(i);
    }
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

