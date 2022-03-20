// Word Class Specification
//
// Author: Brian Horner
// Edit History:
// 3/19/2022 - Initial Version
// 3/19/2022 Added methods and data member specifications


#ifndef PROJECT2_WORD_H
#define PROJECT2_WORD_H


class Word {
public:

    // --- Constructor ---
    Word();

    // --- Calc Functions ---

    void calcOffset(short address);

    void calcSlot(short address);

    void calcTag(short address);

    bool validBitCheck();

    bool dirtyBitCheck();


    void writeCache(short address, short data);

    void readCache(short address);


    // --- Get Functions ---
    short getOffset() const;
    short getSlot() const;
    short getTag() const;
    short getValidBit() const;
    short getDirtyBit() const;

    // --- Set Functions ---
   // TODO: Might be needed for tests?

    // --- Print Function ---

    // --- Destructor ---
    ~Word();

    // --- Data Members ---
private:
    short offset{0x0};
    short slot {0x0};
    short tag {0x0};
    short validBit{0x0};
    short dirtyBit{0x0};
};


#endif //PROJECT2_WORD_H
