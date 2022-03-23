// Word Class Specification
//
// Author: Brian Horner
// Edit History:
// 3/19/2022 - Initial Version
// 3/19/2022 - Added methods and data member specifications
// 3/22/2022 - Added default constructor, get functions


#ifndef PROJECT2_WORD_H
#define PROJECT2_WORD_H


class Word {
public:

    // --- Constructor ---
    Word();
    Word(unsigned short slotNumber);

    // --- Calc Functions ---

    void calcOffset(short address);

    void calcSlot(short address);

    void calcTag(short address);

    bool validBitCheck();

    bool dirtyBitCheck();


    void writeCache(short address, short data);

    void readCache(short address);


    // --- Get Functions ---
    unsigned short getOffset() const;
    unsigned short getTag() const;
    unsigned short getValidBit() const;
    unsigned short getDirtyBit() const;
    unsigned short getSlotNumber() const;


    // --- Set Functions ---
   // TODO: Might be needed for tests?

    // --- Print Function ---
    void printData() const;
    // --- Destructor ---
    ~Word();

    // --- Data Members ---
private:
    unsigned short offset{0x0};
    unsigned short tag {0x0};
    unsigned short validBit{0x0};
    unsigned short dirtyBit{0x0};
    short data[16]{};
    unsigned short slot{0};
};


#endif //PROJECT2_WORD_H
