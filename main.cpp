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


//TODO: WriteByte function
//TODO: ReadByte function
//TODO: set tag
//TODO: get slot
//TODO: check data for reads to see if it hit



// Standard Library Includes
#include <iostream>

// User Built Includes
#include "Word.h"

void populateMainMem(short *, short);
void displayMainMem(short *, short);
unsigned short calcAddressValues(short);
void initializeCache(Word cache[]); //used for print test statements
void printMainMemData(short *, unsigned short);
//void readCache(Word cache[], short);
//void writeCache(Word cache[], short address, short data);
void displayCache(Word cache[]);

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


//void readCache(Word cache[], short address){
//    unsigned short mask = 0x00F;
//    unsigned short dataMask = 0x0FF;
//    unsigned short blockMask = 0xFF0;
//    unsigned short offset = mask & address;
//    unsigned short slot = ((mask <<4) & address)>>4;
//    unsigned short tag = ((mask <<8) & address)>>8;
//    unsigned short data = mask & address;
//    if(cache[slot].getValidBit() == 1){
//        if(cache[slot].getTag() == tag){
//            if (cache[slot].getDirtyBit() != 1){
//                for(unsigned int i{0}; i<16; i++){
//                    if(cache->getData()[i] == data){
//                        //TODO: Cache hit
//                    }else{
//                        // MISS
//                        //TODO: Load into cache
//                        //TODO: update data members
//                    }
//                }
//            }else{
//                //MISS
//                //TODO: write to main mem
//                //TODO: load into cache
//                //TODO: update data members
//            }
//        }else{
//            if(cache[slot].getDirtyBit()!= 1){
//                //MISS
//                //TODO: load into cache
//                //TODO: update data members
//            }else{
//                //MISS
//                //TODO: write back to main mem
//                //TODO: load into cache
//                //TODO: update data members
//            }
//        }
//    }else{
//        //MISS
//        //TODO: load into cache
//        //TODO: update data members
//    }

//}


//void writeCache(Word cache[], short address, short data){
//    unsigned short mask = 0x00F;
//    unsigned short offset = mask & address;
//    unsigned short slot = ((mask <<4) & address)>>4;
//    unsigned short tag = ((mask <<8) & address)>>8;
//    if(cache[slot].getValidBit() == 1){
//        if(cache[slot].getTag() == tag){
//            if (cache[slot].getDirtyBit() != 1){
//                for(unsigned int i{0}; i<16; i++){
//                    if(cache->getData()[i] == data){
//                        //TODO: Cache hit
//                        //TODO: Write to cache
//                    }else{
//                        // MISS
//                        //TODO: Load into cache
//                        //TODO: update data members
//                        //TODO: write to cache
//                    }
//                }
//            }else{
//                //MISS
//                //TODO: write to main mem
//                //TODO: load into cache
//                //TODO: write to cache
//                //TODO: update data members
//            }
//        }else{
//            if(cache[slot].getDirtyBit()!= 1){
//                //MISS
//                //TODO: load into cache
//                //TODO: write to cache
//                //TODO: update data members
//            }else{
//                //MISS
//                //TODO: write back to main mem
//                //TODO: load into cache
//                //TODO: write to cache
//                //TODO: update data members
//            }
//        }
//    }else{
//        //MISS
//        //TODO: load into cache
//        //TODO: write to cache
//        //TODO: update data members
//    }
//}



unsigned short calcAddressValues(short address){
    unsigned short mask = 0x00F;
    unsigned short offset = mask & address;
    unsigned short slot = ((mask <<4) & address)>>4;
    unsigned short tag = ((mask <<8) & address)>>8;
    return slot;

//    std::cout << "Offset: " <<std::hex<<std::uppercase <<offset<<std::endl;
//    std::cout << "Slot: " << slot <<std::endl;
//    std::cout << "Tag: " << tag <<std::endl;
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

