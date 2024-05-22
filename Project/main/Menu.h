//
// Created by Ponanoix on 23.04.2023.
//

#ifndef SDIZO_MENU_H
#define SDIZO_MENU_H

#include "StructureType.h"
#include "../../Sdizo/header_files/DynamicDoublyLinkedList.h"
#include "../../Sdizo/header_files/DynamicArray.h"
#include "../../Sdizo/header_files/DynamicBinaryHeap.h"
#include "../../Sdizo/header_files/DynamicRBTree.h"

class Menu{
private:
    StructureType type;                                                                 // Types of structures in menu.
    DynamicDoublyLinkedList* dynamicDoublyLinkedList{};
    DynamicArray* dynamicArray{};
    DynamicBinaryHeap* dynamicBinaryHeap{};
    DynamicRBTree* dynamicRbTree{};

    void backToMainMenu();                                                              // The following 8 functions operate different menus.

    void printMainMenu();

    void printFileLoadMenu();

    void printDynamicDoublyLinkedListMenu();

    void printDynamicArrayMenu();

    void printDynamicBinaryHeapMenu();

    void printDynamicRBTreeMenu();

    void printBenchmarkMenu();

    void initDynamicDoublyLinkedList();                                                 // The following 4 functions initialise desired structures with details provided by the user.

    void initDynamicArray();

    void initHeap();

    void initRBTree();

    static int getIntegerInput(std::string message, bool mustPositive = false);         // The following two functions prompt the user with a request to print a certain number.

    static float getFloatInput(std::string message, bool mustPositive = false);

    static void printException(std::exception &e);                                      // Prints thrown exception.
public:
    Menu();
};

#endif //SDIZO_MENU_H
