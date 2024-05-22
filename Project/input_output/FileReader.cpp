//
// Created by Ponanoix on 23.04.2023.
//

#include "../../Sdizo/input_output/FileReader.h"

void FileReader::readToDynamicDoublyLinkedList(DynamicDoublyLinkedList *dest, PushType type) {
    if(type == BACK){
        for(int i = 0; i < structureSize; i++){
            dest -> backAdd(readNextValue());
        }
    }
    else if (type == FRONT){
        for(int i = 0; i < structureSize; i++){
            dest -> frontalAdd(readNextValue());
        }
    }
}

void FileReader::readToDynamicArray(DynamicArray *dest, PushType type) {
    if (type == BACK){
        for(int i = 0; i < structureSize; i++){
            dest -> backAdd(readNextValue());
        }
    }
}

void FileReader::readToHeap(DynamicBinaryHeap *dest) {
    for (int i = 0; i < structureSize; i++){
        dest -> add(readNextValue());
    }
}

void FileReader::readToRBTree(DynamicRBTree *dest) {
    for(int i = 0; i < structureSize; i++){
        dest -> add(readNextValue());
    }
}

int FileReader::readNextValue() {
    int nextVal;
    if (input.is_open()){
        input >> nextVal;
        if (input.fail()){
            throw std::runtime_error("File error - stopping program");
        }
        if(input.eof()){
            input.close();
        }
        return nextVal;
    }
    throw std::runtime_error("File not opened - maybe it was already closed?");
    return 0;
}

FileReader::FileReader(const std::string &fileName):fileName(fileName), input(fileName) {
    input >> structureSize;
    if(!input.is_open()){
        throw std::runtime_error("Could not read the file");
    }
    std::cout << "Structure size is " << structureSize;
    printf("%s", "\n\n");
}

int FileReader::getStructureSize() const {
    return structureSize;
}