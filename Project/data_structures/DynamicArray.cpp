//
// Created by Ponanoix on 21.04.2023.
//
#include<cstdio>
#include "..\..\Sdizo\header_files\DynamicArray.h"
#include<stdexcept>
#include <iostream>

void DynamicArray::frontalAdd(int element) {
    if(numOfElem >= size) increaseSize();         // Increases the size, just in case.

    for(int i = numOfElem; i >= 1; i--){
        arrayPointer[i] = arrayPointer[i - 1];    // Shifts the array to the left (5 becomes 4 etc.).
    }
    arrayPointer[0] = element;                    // Sets the value of the front position.

    numOfElem++;                                  // Updates the number of the elements.
}

void DynamicArray::backAdd(int element) {
    if (numOfElem >= size) increaseSize();        // Increases the size, just in case.

    arrayPointer[numOfElem] = element;            // Adds a new value at the back.

    numOfElem++;                                  // Updates the number of the elements.
}

void DynamicArray::freeAdd(int element, int position) {
    if (position > numOfElem || position < 0){
        throw std::invalid_argument("There is no such position!");  // Checks if the typed position exists.
    }

    if(position == numOfElem){
        backAdd(element);                                           // If the position is the last one - use the backAdd
        return;
    }

    if(position == 0 && numOfElem > 0){
        frontalAdd(element);                                        // If the position is the first one - use the frontalAdd.
        return;
    }

    if(numOfElem >= size) increaseSize();                           // Increases the size, just in case.
    for(int i = numOfElem; i > position; i--){
        arrayPointer[i] = arrayPointer[i - 1];                      // Shifts all the elements before the position to the left.
    }
    arrayPointer[position] = element;                               // Sets the value of the specified position.
    numOfElem++;                                                    // Updates the number of the elements.
}

int DynamicArray::frontalRemove() {
    if(numOfElem <= 0){
        std::cout << "The array is empty.";
        return -1;
    }
    for(int i = 1; i < numOfElem; i++){
        arrayPointer[i - 1] = arrayPointer[i];
    }
    arrayPointer[numOfElem - 1] = 0;
    numOfElem--;
    if(numOfElem < size/2) decreaseSize();
    return numOfElem;
}

int DynamicArray::backRemove() {
    if (numOfElem <= 0) {
        std::cout << "The array is empty.";
        return -1;
    }
    arrayPointer[numOfElem - 1] = 0;
    numOfElem--;
    if (numOfElem < size / 2) decreaseSize();
    return numOfElem;
}

int DynamicArray::freeRemove(int position) {
    if (position >= size) return -1;                                // Checks if the typed position exists.
    int j = 0;
    for(int i = 0; i < size; i++){
        if(i == position) continue;
        arrayPointer[j++] = arrayPointer[i];
    }
    arrayPointer[numOfElem - 1] = 0;                                // Removes the pointed element.
    numOfElem--;
    if(numOfElem < size/2) decreaseSize();                          // Updates the space.
    return numOfElem;
}

void DynamicArray::initArray() {
    this -> arrayPointer = new int[1];                              // Initialises a new array with a single element space.
    size = 1;                                                       // Sets the size to 1.
    numOfElem = 0;                                                  // Sets the number of elements to 0.
}

int DynamicArray::getSize() const {
    return this -> numOfElem;                                       // Returns the size (number of elements) of the array.
}

int DynamicArray::getElem(int position) {
    if(position >= size || position < 0) throw std::invalid_argument("There is no such position!");     // Checks whether the position exists.
    return arrayPointer[position];                                                                      // Returns the element's position.
}

void DynamicArray::setElem(int position, int value) {
    if(position < size) arrayPointer[position] = value;             // Gives the element on a position a new value.
}

void DynamicArray::swapElem(int pos1, int pos2) {
    int temp = getElem(pos1);
    setElem(pos1, getElem(pos2));              // This method creates a temporary int value to swap to elements.
    setElem(pos2, temp);
}

DynamicArray::DynamicArray() {
    initArray();                                                   // Creates a new array.
}

DynamicArray::~DynamicArray() {
    delete[] arrayPointer;                                         // Deletes the array and frees up memory
}

void DynamicArray::increaseSize() {
    size *= 2;                                                     // Doubles the size of the array
    int * temp = new int[size];

    for(int i = 0; i < numOfElem; i++){                            // Iterates through all the elements in order to place them properly.
        temp[i] = arrayPointer[i];
    }
    delete[] arrayPointer;                                         // Deletes the temporary pointer.

    arrayPointer = temp;
}

void DynamicArray::decreaseSize() {
    if(numOfElem < size/2){                                        // Halves the size of the array.
        size /= 2;
        int *temp = new int[size];

        for(int i = 0; i < numOfElem; i++){                        // Iterates through all the elements to place them properly.
            temp[i] = arrayPointer[i];
        }
        delete[] arrayPointer;                                         // Deletes the temporary pointer.

        arrayPointer = temp;
    }
}

int DynamicArray::checkElem(int value) {
    if(arrayPointer[0] == value) return 0;
    for(int i = 0; i < size; i++){
        if(arrayPointer[i] == value) return i;                     // Iterates through elements and returns searched one's position. In other case -> returns -1.
    }
    return -1;
}

void DynamicArray::printArray() {
    if(this -> size == 0) return;                                  // If size == 0, return 0.
    for(int i = 0; i < numOfElem; i++) {
        printf("%d", arrayPointer[i]);                      // Using pointer, print every position's number
        printf(" ");
    }
    printf("%s", "\n\n");
}

bool DynamicArray::contains(int val) {
    for (int i = 0; i < size; i++) {
        if (arrayPointer[i] == val) return true;
    }
    return false;
}