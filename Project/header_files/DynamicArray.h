//
// Created by Ponanoix on 21.04.2023.
//

#ifndef SDIZO_DYNAMICARRAY_H
#define SDIZO_DYNAMICARRAY_H

class DynamicArray{
private:
    int* arrayPointer = nullptr;                 // Points to the array.

    int size = 0;                                // Sets the size of the array.

    int numOfElem = 0;                           // Sets the number of elements.

    void initArray();                            // Initialise a new array.

    void increaseSize();                         // Increases the size of the array.

    void decreaseSize();                         // Decreases the size of the array.
public:
    DynamicArray();                              // Creates a new array.

    void frontalAdd(int element);                // Adds an element to the front of the array.

    void backAdd(int element);                   // Adds an element to the back of the array.

    void freeAdd(int element, int position);     // Adds an element on the specified position.

    int frontalRemove();                         // Removes the element at the front of the array.

    int backRemove();                            // Removes the element at the back of the array.

    int freeRemove(int position);                // Removes an element. Returns size.

    [[nodiscard]] int getSize() const;           // Gets and returns the current size.

    int getElem(int position);                   // Gets and returns element on the specified position.

    void setElem(int position, int value);       // Replaces the specified value on the specified position.

    void swapElem(int pos1, int pos2);           // Swaps two elements.

    int checkElem(int value);                    // Checks if the array contains specified value. If yes - returns its position.

    void printArray();                           // Prints the contents of the array.

    ~DynamicArray();                             // Deallocates all space.

    bool contains(int val);
};

#endif //SDIZO_DYNAMICARRAY_H
