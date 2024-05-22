//
// Created by Ponanoix on 23.04.2023.
//

#ifndef SDIZO_FILEREADER_H
#define SDIZO_FILEREADER_H

#include "../../Sdizo/header_files/DynamicArray.h"
#include "../../Sdizo/header_files/DynamicBinaryHeap.h"
#include "../../Sdizo/header_files/DynamicDoublyLinkedList.h"
#include "../../Sdizo/header_files/DynamicRBTree.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

enum PushType{
    FRONT,
    BACK
};

/*
 * This class is used to read and push data from files and into data structures.
 * Data needs to be delimited with white characters.
 * First value represents the amount of values stored in the file.
 */

class FileReader{
private:
    std::string fileName;                                                               // Name of the input file.

    std::ifstream input;                                                                // File input stream.

    int structureSize = 0;                                                              // Amount of data to be read.

    int readNextValue();                                                                // Returns the next value read from the file.
public:
    explicit FileReader(const std::string& fileName);                                   // Creates a new instance of this class with name of file to read from. Reads the first value.

    void readToDynamicDoublyLinkedList(DynamicDoublyLinkedList* dest, PushType type);   // Reads data stored in the file into linked list.

    void readToDynamicArray(DynamicArray* dest, PushType type);                         // Reads data stored in the file into table.

    void readToHeap(DynamicBinaryHeap* dest);                                           // Reads data stored in the file into binary heap.

    void readToRBTree(DynamicRBTree* dest);                                             // Reads data stored in the file into RBTree.

    int getStructureSize() const;                                                       // Gets the amount of items stored in the input file.
};

#endif //SDIZO_FILEREADER_H
