//
// Created by Ponanoix on 22.04.2023.
//

#ifndef SDIZO_DYNAMICDOUBLYLINKEDLIST_H
#define SDIZO_DYNAMICDOUBLYLINKEDLIST_H

#include<iostream>
#include "..\..\Sdizo\header_files\helper_header_files\DynamicDoublyLinkedNode.h"

class DynamicDoublyLinkedList{
public:
    int positionOf(int element);                                // Returns position of the element. -1 if not present.

    DynamicDoublyLinkedList* frontalAdd(int value);             // Adds element at the front of the list. Returns instance of the list.

    DynamicDoublyLinkedList* backAdd(int value);                // Adds element at the back of the list. Returns instance of the list.

    DynamicDoublyLinkedList* freeAdd(int position, int value);  // Adds element at the specified point on the list. Returns instance of the list.

    DynamicDoublyLinkedList* remove(int value);                 // Removes the specified element from the list. Returns the instance of the list.

    int getElem(int position);                                  // Returns the value from the specified position, returns nullptr if index is incorrect.

    int getSize();                                              // Returns the size of the list.

    ~DynamicDoublyLinkedList();                                 // Deallocates the entire space taken by the list.

    void printList();                                           // Prints the list.

    DynamicDoublyLinkedNode * getPos(int i);                    // Returns the node located at this position.

    void freeRemove(int position);                              // Removes the element at the specified position.

    void frontalRemove();                                       // Removes the frontal element.

    void backRemove();                                          // Removes the back element.
private:
   DynamicDoublyLinkedNode* head = nullptr;                     // This symbolises the first element.

   DynamicDoublyLinkedNode* tail = nullptr;                     // This symbolises the last element.

   DynamicDoublyLinkedNode* getLastElem();                      // Get last element in the list.

   void deleteAll(DynamicDoublyLinkedNode* node);               // Delete all nodes, starting from this one.
};

#endif //SDIZO_DYNAMICDOUBLYLINKEDLIST_H
