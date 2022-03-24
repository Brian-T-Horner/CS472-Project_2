// Word Class Specification
//
// Author: Brian Horner
// Edit History:
// 3/19/2022 - Initial Version
// 3/19/2022 - Added methods and data member specifications
// 3/22/2022 - Added default constructor, get functions
// 3/23/2022 - Added overwriteData, displayWord, writeBackData and writeSingleData


#ifndef PROJECT2_WORD_H
#define PROJECT2_WORD_H


class Word {
public:

    // --- Constructor ---
    Word();
    Word(unsigned short slotNumber);

    // --- Calc Functions ---
    void loadData(short *, unsigned short);
    void overwriteData(short *, unsigned short);
    bool checkData(unsigned short, short);
    void writeSingleData(unsigned short, short);
    void writeBackData(short *);


    // --- Get Functions ---
    unsigned short getTag() const;
    unsigned short getValidBit() const;
    unsigned short getDirtyBit() const;
    unsigned short getSlotNumber() const;
//


    // --- Set Functions ---
   // TODO: Might be needed for tests?


    // --- Print Function ---
    void printData() const;
    void displayWord() const;
    // --- Destructor ---
    ~Word();

    // --- Data Members ---
private:
    unsigned short tag {0x0};
    unsigned short validBit{0x0};
    unsigned short dirtyBit{0x0};
    short data[0x10];
    unsigned short slot{0x0};
};


#endif //PROJECT2_WORD_H
