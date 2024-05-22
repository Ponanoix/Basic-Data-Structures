//
// Created by Ponanoix on 23.04.2023.
//

#include<iostream>
#include "cmath"
#include "../../Sdizo/header_files/DynamicBinaryHeap.h"
#include<cstdio>

void DynamicBinaryHeap::add(int value) {
    array -> backAdd(value);                                                                                    // Adds a new element to the end of an array, to be later used by the heap.
    heapifyUp(array -> getSize() - 1);                                                                          // Maintains the binary heap property by moving the newly added element.
}

void DynamicBinaryHeap::heapifyUp(int position) {
    if(position == 0) return;                                                                                           // Checks if the element isn't in the root already.
    if(array -> getElem(position) > array -> getElem((position - 1) / 2)){                                      // Checks if the element in latter position is smaller. If no, swaps them. Does this until the heap is fixed.
        array -> swapElem(position, (position - 1) / 2);
        heapifyUp((position - 1) / 2);
    }
}

void DynamicBinaryHeap::heapifyDown(int position) {
    int maxPosition = position;
    for(int i = 1; i <= 2; i++){                                                                                                                                               // This begins the loop which iterates over two child nodes of the "position" element.
        if(2 * position + i < array -> getSize() && array -> getElem(2 * position + i) > array -> getElem(maxPosition)) maxPosition = 2 * position + i;         // This line compares the value of the child node with the current maxPosition. If the child node is larger, it becomes the new maximum position.
    }
    if(maxPosition != position){                                                                                                                                               // This part checks if the maxPosition has changed and if yes, it moves it down the heap.
        array -> swapElem(position, maxPosition);
        heapifyDown(maxPosition);
    }
}

int DynamicBinaryHeap::remove() {
    if(array -> getSize() > 0){                                                                                         // This part removes the root of the heap and then fixes the new heap.
        int toReturn = array -> getElem(0);
        array -> setElem(0, array -> getElem(array -> getSize() - 1));
        array -> freeRemove(array -> getSize() - 1);
        heapifyDown(0);
        return toReturn;
    }
    else throw std::length_error("Heap is empty!");                                                                     // In case the heap is empty, this is thrown.
}

int DynamicBinaryHeap::getSize() {
    return array -> getSize();                                                                                          // This function returns the size of the heap.
}

void DynamicBinaryHeap::print() {
    if(array -> getSize() == 0) return;                                                                                 // Checks if the heap is empty first.
    int height = (int) log2(array -> getSize());                                                                        // Counts the height, knowing its |_ log_n _|.
    for (int i = 0; i <= height; i++){                                                                                  // Outer loop jumps between levels
        for(int j = 0; j < pow(2, i) && j + pow(2, i) <= array -> getSize(); j++){                          // Inner loop uses the j + pow(2, i) - 1 formula to calculate the position of each node on the level
            printf("%d", array -> getElem(j + (int) pow(2, i) - 1));                                // This part of the function prints the nodes from the current level.
            printf(" ");
        }
        printf("%s", " \n\n");                                                                                   // Here, the function prints two blank lines in order to prepare for the next level.
    }
}

DynamicBinaryHeap::~DynamicBinaryHeap() {
    delete array;                                                                                                       // This function deletes the heap and deallocates space.
}

DynamicBinaryHeap::DynamicBinaryHeap() {
    array = new DynamicArray();                                                                                         // This function creates a new heap.
}

bool DynamicBinaryHeap::search(int value) {
    return findElement(value, 0);                                                                               // This function returns "1" if desired element exists in the heap. In other case it returns "0".
}

bool DynamicBinaryHeap::findElement(int value, int position) {                                                          // This function performs the actual search.
    if (value == array -> getElem(position)) return true;                                                               // In the beginning, if the value exists in the initial position, simply return true.
    bool res = false;                                                                                                   // Initiate two bool variables for later uses.
    bool res2 = false;
    if (array -> getSize() > 2 * position + 1 && value <= array ->getElem(2 * position + 1)){                   // This part checks the children of given position and either returns true or checks their children etc.
        res = findElement(value, 2 * position + 1);
    }
    if (array -> getSize() > 2 * position + 2 && value <= array ->getElem(2 * position + 2)){
        res2 = findElement(value, 2 * position + 2);
    }
    return res || res2;
}
