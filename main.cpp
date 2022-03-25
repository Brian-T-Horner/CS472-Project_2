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
// 3/24/2022 - Added basic run function and read function
// 3/24/2022 - Added read and write functions
// 3/24/2022 - Added comments
// 3/24/2022 - Added command, data, and address vectors
// 3/24/2022 - Added loop to read through command, data and address vectors
// and preform functions




// Standard Library Includes
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// User Built Includes
#include "Word.h"

void populateMainMem(short *, short);
void displayMainMem(short *, short);
unsigned short calcAddressValues(short);
void initializeCache(std::vector<Word> &); //used for print test statements
void printMainMemData(short *, unsigned short);
void readCache(short *, std::vector<Word>&, unsigned short);
void writeCache(short *, std::vector<Word> &, unsigned short address, short
data);
void displayCache(std::vector<Word> &);
void run(short *, std::vector<Word> &, std::vector<char> &,
        std::vector<unsigned short> &, std::vector<short> &);



int main() {

    // Command, address and data vectors
    std::vector<char> commands = {'R',  'R',  'R',  'R',
                                       'R',  'R',  'R', 'R',
                                       'R',  'R', 'R',  'D',
                                       'W', 'W', 'R',  'D',
                                      'R',  'R',  'D', 'R',
                                      'R',  'R',  'R', 'D'};
    std::vector<unsigned short> addressInputs = {0x5, 0x6, 0x7, 0x14c,
                                                 0x14d,0x14e, 0x14f, 0x150,
                                                 0x151, 0x3A6, 0x4C3, 0x14C,
                                                 0x63B,  0x582, 0x348, 0x3F,
                                                 0x14b, 0x14c, 0x63F,0x83,};
    std::vector<short> dataInputs = {0x99, 0x7};


    short main_mem[2048]; // set up main mem
    populateMainMem(main_mem, 2048);

    std::vector<Word> cache; // set up cache
    initializeCache(cache);
    std::string file = "test.txt";
    run(main_mem, cache, commands, addressInputs, dataInputs); // run standard reads
    return 0;
}

void run(short * main_mem, std::vector<Word> &cache, std::vector<char>
& commands, std::vector<unsigned short> & addressInput, std::vector<short>
        & dataInput){
    char inputChar;
    int commandsIndex{0};
    int addressIndex{0};
    int dataIndex{0};
    while(commandsIndex < commands.size()){
        std::cout << "(R)ead, (W)rite, or (D)isplay Cache?" <<std::endl;
        inputChar = commands[commandsIndex];
        std::cout <<inputChar <<std::endl;
        commandsIndex ++;

        // Switch statements for read, write and display cache
        switch (inputChar){
            case 'R':
            {
                std::cout << "What address would you like to read?" <<std::endl;
                unsigned short readInput = addressInput[addressIndex];
                addressIndex++;
                std::cout << readInput <<std::endl;

                readCache(main_mem, cache, readInput);


                break;
            }
            case 'W': {
                std::cout << "What address would you like to write to?"
                <<std::endl;
                unsigned short writeInput = addressInput[addressIndex];
                addressIndex++;
                std::cout << writeInput <<std::endl;
                std::cout << "What data would you like to write at that "
                             "address?" <<std::endl;
                short writeData = dataInput[dataIndex];
                dataIndex++;
                std::cout <<writeData <<std::endl;

                writeCache(main_mem, cache, writeInput, writeData);
                break;
                }
            case 'D': {
                displayCache(cache);
                std::cout << "\n"<<std::endl;
                std::cout << "\n---------------------------------------------------\n"
                <<std::endl;
                break;
            }
            default: {
                std::cout << "Error: Should not reach here." <<std::endl;
            }
        }
    }
}


void displayCache(std::vector<Word> &cache){
    // Function to display cache
    std::cout<< "Slot\tValid\tDirty\tTag\t\tData"<<std::endl;
    for (unsigned int i{0}; i<0xF+1; i++){
        cache[i].displayWord();
    }
    std::cout<<std::endl;
}



void readCache(short *mainMem, std::vector<Word> &cache, unsigned short
 address){
    //Function to do cache reads

    // Calculate the offset, tag, and slot from address
    unsigned short mask = 0x00F;
    unsigned short offset = address & mask;
    unsigned short slot = (address & (mask<<4))>>4;
    unsigned short tag = (address & (mask<<8))>>8;

    if(cache[slot].getValidBit() == 0){
        // If cache slot has not been used
        cache[slot].loadData(mainMem,address);
        std::cout << "At that byte there is the value ";
        std::cout << std::hex <<std::uppercase<<cache[slot].getSingleData
        (address)<<" (Cache Miss)\n"<<std::endl;
        std::cout << "\n---------------------------------------------------\n"
        <<std::endl;
    }else if (cache[slot].getValidBit() == 1){
        // If cache slot has been used
        if(cache[slot].getTag() != tag){
            // If cache slot has been used and tag is different
            if(cache[slot].getDirtyBit() == 0){
                // If cache slot is used, different tag and not dirty
                cache[slot].loadData(mainMem,address);
                std::cout << "At that byte there is the value ";
                std::cout << std::hex <<std::uppercase<< cache[slot]
                .getSingleData(offset)<< " (Cache Miss)\n" <<std::endl;
                std::cout << "\n---------------------------------------------------\n"
                <<std::endl;
            } else if (cache[slot].getDirtyBit() == 1){
                // If cache slot is used, different tag and dirty
                cache[slot].writeBackData(mainMem);
                cache[slot].loadData(mainMem,address);
                std::cout << "At that byte there is the value ";
                std::cout << std::hex <<std::uppercase<< cache[slot]
                .getSingleData(address)<< " (Cache Miss)\n" <<std::endl;
                std::cout << "\n---------------------------------------------------\n"
                <<std::endl;
            }
        } else if (cache[slot].getTag() == tag){
            // If cache tag is the same
            std::cout << "At that byte there is the value ";
            std::cout << std::hex <<std::uppercase<< cache[slot]
            .getSingleData(address)<< " (Cache Hit)\n"
            <<std::endl;
            std::cout << "\n---------------------------------------------------\n"
            <<std::endl;
        }
    }
}


void writeCache(short *mainMem, std::vector<Word> &cache, unsigned short
address,
 short data){
    // Function to write to cache

    // Calculate offset, tag, and slot
    unsigned short mask = 0x00F;
    unsigned short slot = (address & (mask<<4))>>4;
    unsigned short tag = (address & (mask<<8))>>8;

    if(cache[slot].getValidBit() == 0){
        // If cache slot has not been used
        cache[slot].loadData(mainMem, address);
        cache[slot].writeSingleData(address, data);
        std::cout << "Value " <<cache[slot].getSingleData(address)
        <<" has been written to address " <<address <<".(Cache Miss)\n"
        <<std::endl;
        std::cout << "\n---------------------------------------------------\n"
        <<std::endl;
    } else if (cache[slot].getValidBit() == 1){
        // If cache slot has been used
        if (cache[slot].getTag() != tag){
            // If cache slot has a different tag
            if (cache[slot].getDirtyBit() == 0){
                // If cache slot with different tag and not dirty
                cache[slot].loadData(mainMem, address);
                cache[slot].writeSingleData(address, data);
                std::cout << "Value " <<cache[slot].getSingleData(address)
                <<" has been written to address " <<address <<".(Cache Miss)"
                "\n" <<std::endl;
                std::cout << "\n---------------------------------------------------\n"
                <<std::endl;
            } else if (cache[slot].getDirtyBit() == 1){
                // If cache slot with different tag hand dirty
                cache[slot].writeBackData(mainMem);
                cache[slot].loadData(mainMem, address);
                cache[slot].writeSingleData(address, data);
                std::cout << "Value " <<cache[slot].getSingleData(address)
                <<" has been written to address " <<address <<".(Cache Miss)"
                                                              "\n" <<std::endl;
                std::cout << "\n---------------------------------------------------\n"
                <<std::endl;
            }
        } else if (cache[slot].getTag() == tag){
            // If cache slot tag has the same tag
            if (cache[slot].getDirtyBit() == 1){
                // If cache slot with same tag and dirty
                cache[slot].writeBackData(mainMem);
                cache[slot].writeSingleData(address, data);
                std::cout << "Value " <<cache[slot].getSingleData(address)
                <<" has been written to address " <<address <<".(Cache Hit)\n"
                <<std::endl;
                std::cout << "\n---------------------------------------------------\n"
                <<std::endl;
            }else if (cache[slot].getDirtyBit() == 0){
                // If cache slot with same tag and not dirty
                cache[slot].writeSingleData(address, data);
                std::cout << "Value " <<cache[slot].getSingleData(address)
                <<" has been written to address " <<address <<".(Cache Hit)\n"
                <<std::endl;
                std::cout << "\n---------------------------------------------------\n"
                <<std::endl;
            }
        }
    }
}





void initializeCache(std::vector<Word> &cache){
    // Function to set up cache with correct slots
    for (unsigned int i{0}; i<0xF+1; i++){
        cache.push_back(Word(i));
    }
}

void populateMainMem(short *mainMem, short mainMemSize){
    // Populate main mem with default values
    short b{0};
    for (short i {0}; i<mainMemSize; i ++){
        // Loop from 0x00-0xFF then restart
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



// --- CURRENTLY UNUSED FUNCTIONS ---

void printMainMemData(short *mainMem, unsigned short address){
    // Print main memory address for tests
    unsigned short blockMask = 0xFF0;
    unsigned short blockBegin = address & blockMask;
    unsigned short blockEnd = blockBegin + 0xF;
    for(unsigned short i = blockBegin; i< blockEnd+1; i++){
        std::cout << "Data at memory location " <<std::hex<<std::uppercase<<i << " is " << mainMem[i]<<std::endl;
    }
}

unsigned short calcAddressValues(short address){
    // Calculate address tag, offset and slot for tests
    unsigned short mask = 0x00F;
    unsigned short offset = mask & address;
    unsigned short slot = ((mask <<4) & address)>>4;
    unsigned short tag = ((mask <<8) & address)>>8;
    return slot;
}

void displayMainMem(short *mainMem, short mainMemSize){
    // Print all of main mem for tests
    for(unsigned int b{0}; b < mainMemSize; b++){
        std::cout << "Array element " << std::hex<<std::uppercase<< b << " is "
        <<mainMem[b]
        <<std::endl;
    }
}

