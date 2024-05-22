//
// Created by Ponanoix on 23.04.2023.
//

#ifndef SDIZO_DYNAMICBINARYHEAP_H
#define SDIZO_DYNAMICBINARYHEAP_H
#include "../../Sdizo/header_files/DynamicArray.h"

class DynamicBinaryHeap{
public:
    void add(int value);                        // Adds a new element and fixes the heap going up.

    int remove();                               // Removes the heap's root and returns it. Fixes the heap going down from the root.

    int getSize();                              // Returns the size of the heap.

    void print();                               // Prints the heap.

    ~DynamicBinaryHeap();                       // Deallocates all space taken by the heap.

    DynamicBinaryHeap();                        // Creates a new heap.

    bool search(int value);                     // Searches an element in the heap and tells if it exists or not.
private:
    DynamicArray * array;                       // Instance of an array which stores all heap data.

    void heapifyUp(int position);               // Fix the heap going up from given position.

    void heapifyDown(int position);             // Fix the heap going down from given position.

    bool findElement(int value, int position);  // Searches for the specified element, starting from the given position.
};

#endif //SDIZO_DYNAMICBINARYHEAP_H
