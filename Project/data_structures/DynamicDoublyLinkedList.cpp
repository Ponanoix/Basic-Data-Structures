//
// Created by Ponanoix on 22.04.2023.
//
#include "../../Sdizo/header_files/DynamicDoublyLinkedList.h"


DynamicDoublyLinkedList *DynamicDoublyLinkedList::frontalAdd(int value) {
    auto* element = new DynamicDoublyLinkedNode(value);                                             // Sets a new pointer (int type).
    if(head == nullptr){                                                                                // Checks whether the list is empty.
        head = element;
        tail = element;
    }
    else{                                                                                               // This part uses pointers to make the head of the list be preceded by the "element".
        DynamicDoublyLinkedNode* firstNode = head;
        firstNode -> setPreviousNode(element);
        element -> setNextNode(firstNode);
        head = element;
    }
    return this;                                                                                        // In the end, the pointer is returned to point at the current object.
}

DynamicDoublyLinkedList *DynamicDoublyLinkedList::backAdd(int value) {
    auto* element = new DynamicDoublyLinkedNode(value);                                             // Sets a new pointer (int type).
    if(head == nullptr){                                                                                // Checks whether the list is empty.
        head = element;
        tail = element;
    }
    else{                                                                                               // This part uses pointers to add an element in the back and make it the tail.
        DynamicDoublyLinkedNode* lastNode = tail;
        lastNode -> setNextNode(element);
        element -> setPreviousNode(lastNode);
        tail = element;
    }
    return this;                                                                                        // Returns the pointer to point at the current end of the list.
}

DynamicDoublyLinkedList *DynamicDoublyLinkedList::remove(int value) {
    DynamicDoublyLinkedNode* current = head;                                                            // Makes a pointer which points to the head.

    if(head -> getVal() == value){                                                                      // This part checks whether head represents the value.
        if(head -> getNextElem() != nullptr){                                                           // This part cues if there are nodes after the head.
            head = head -> getNextElem();
            head -> setPreviousNode(nullptr);                                                  // Removes head and makes the next element the new head
        }
        else {                                                                                          // This part cues when the list has single element and makes it empty.
            head = nullptr;
            tail = nullptr;
        }
        delete current;                                                                                 // This part deletes the pointer after removing an element.
    }
    else if (tail -> getVal() == value){                                                                // This part checks whether tail represents the value.
        if(tail -> getPrevElem() != nullptr){                                                           // This part checks if there are nodes before the tails.
            tail = tail -> getPrevElem();
            tail -> setNextNode(nullptr);                                                      // Removes the tail and makes the previous element the new tail
        }
        else{
            head = nullptr;                                                                             // This part cues when the list has single element and makes it empty.
            tail = nullptr;
        }
    }
    else{                                                                                                                                   // This part covers remaining scenarios.
        while(current != nullptr){
            if(current -> getVal() == value){                                                                                               // This part checks if current's value represents the one in parameter.
                current -> getPrevElem() -> setNextNode(current -> getNextElem());                                                 // This part makes the current node get the value of the following node, effectively deleting it.
                if(current -> getNextElem() != nullptr) current -> getNextElem() -> setPreviousNode(current -> getPrevElem());
                delete current;
                return this;
            }
            if(current -> getNextElem() != nullptr) current = current -> getNextElem();                                                     // This part makes the pointer point to the next element (While loop is still active)
            else throw std::invalid_argument("Element does not exist in the list.");                                                        // This part throws an error if the value in parameter doesn't exist
        }

    }
    return this;                                                                                                                            // Returns the pointer to point at the current end of the list.
}

int DynamicDoublyLinkedList::positionOf(int element) {
    if(head == nullptr) return -1;                                                                      // This part cues when the list is empty and returns -1
    else{                                                                                               // This part iterates through the list.
        DynamicDoublyLinkedNode* nextPointer = head;
        int i = 0;
        while (nextPointer != nullptr && nextPointer -> getVal() != element){
            nextPointer = nextPointer -> getNextElem();
            i++;
        }
        if (nextPointer == nullptr) return -1;                                                          // This part checks if the position exists in the end. If no - returns -1.
        return i;                                                                                       // The position is returned in the end.
    }
}

DynamicDoublyLinkedNode *DynamicDoublyLinkedList::getLastElem() {
    DynamicDoublyLinkedNode* node = head;                                                               // This method iterates through the entire list and returns the final node.
    while (node -> getNextElem() != nullptr){
        node = node -> getNextElem();
    }
    return node;
}

int DynamicDoublyLinkedList::getElem(int position) {
    DynamicDoublyLinkedNode* node = getPos(position);                                                // This method returns the value of the node at the specified position.
    return node -> getVal();
}

int DynamicDoublyLinkedList::getSize() {
    if (head == nullptr) return 0;                                                                      // This part checks if the list is empty. If so, returns 0.
    DynamicDoublyLinkedNode* node = head;
    int i = 1;                                                                                          // This part iterates through the list and increments i.
    while (node -> getNextElem() != nullptr){
        node = node -> getNextElem();
        i++;
    }
    return i;                                                                                           // Returns the final value of i, so the size of the list.
}

DynamicDoublyLinkedList *DynamicDoublyLinkedList::freeAdd(int position, int value) {
    auto* newElement = new DynamicDoublyLinkedNode(value);
    if (position < 0 || position > getSize()) throw std::invalid_argument("Wrong position given!");     // This part checks if the position inside parameters is correct.
    if (position == 0){                                                                                 // This part checks if the position is "0". If so, uses the dedicated method.
        frontalAdd(value);
        return this;
    }
    if (position == getSize()){                                                                         // This part checks if the position is the last one. If so, uses the dedicated method.
        backAdd(value);
        return this;
    }
    if (head == nullptr){                                                                               // This part checks if the list is empty. If so, adds a single element.
        backAdd(value);
        return this;
    }
    DynamicDoublyLinkedNode* prev = head;
    prev = getPos(position - 1);                                                                      // This part assigns "prev" the value which is earlier.
    if (prev != nullptr){                                                                               // This part cues when prev has an assigned value.
        DynamicDoublyLinkedNode* nodeAtPos = prev -> getNextElem();
        if (nodeAtPos == nullptr){                                                                      // This part cues when "prev" is the final node. It adds a new element after it.
            prev -> setNextNode(newElement);
            newElement -> setPreviousNode(prev);
            return this;
        }
        else{
            if (nodeAtPos == head){                                                                     // This part cues when the value after the "prev" is the head.
                newElement -> setNextNode(head -> getNextElem());                              // It makes the function add a new node before the head.
                head -> setPreviousNode(newElement);
                head = newElement;
                return this;
            }
            newElement -> setPreviousNode(nodeAtPos -> getPrevElem());                         // This part of the method inserts a new node between "nodeAtPos" and the node before "nodeAtPos"
            newElement -> setNextNode(nodeAtPos);
            nodeAtPos -> getPrevElem() -> setNextNode(newElement);
            nodeAtPos -> setPreviousNode(newElement);
            return this;
        }
    }
    return nullptr;                                                                                     // In the end, the function returns the "empty" pointer.
}

DynamicDoublyLinkedNode *DynamicDoublyLinkedList::getPos(int i) {
    DynamicDoublyLinkedNode* node = head;
    int in = 0;
    while (node -> getNextElem() != nullptr && in != i){                                                // This part iterates through the list until in's value becomes equal to i's.
        node = node -> getNextElem();
        in++;
    }
    if (in == i){                                                                                       // When in and i become equal, the current node is returned.
        return node;
    }
    return nullptr;
}

DynamicDoublyLinkedList::~DynamicDoublyLinkedList() {
    deleteAll(head);                                                                              // This method deletes the entire list and frees the memory.
}

void DynamicDoublyLinkedList::deleteAll(DynamicDoublyLinkedNode *node) {
    if (node == nullptr) return;                                                                       // This part checks if the list is empty already.
    DynamicDoublyLinkedNode *element = getLastElem();
    while (element != head){                                                                           // This part iterates through the list from behind and leaves the elements empty
        element -> getPrevElem() ->setNextNode(nullptr);
        delete element;
        element = getLastElem();
    }
    delete head;                                                                                       // In the end, head is also deleted.
}

void DynamicDoublyLinkedList::printList() {
    if(this -> head == nullptr) return;                                                                // This part checks if the list is empty.
    DynamicDoublyLinkedNode * node = head;

    while(node -> getNextElem() != nullptr){                                                           // This part iterates through the list and prints its nodes' values.
        printf("%d", node -> getVal());
        printf(" ");
        node = node -> getNextElem();
    }
    printf("%d", node -> getVal());
    printf("%s", "\n\n");
}

void DynamicDoublyLinkedList::freeRemove(int position) {
    if(position < 0 || position >= getSize()) throw std::invalid_argument("Invalid position given!");                   // This parts checks if the position is correct.
    int i = 0;

    DynamicDoublyLinkedNode* node = head;

    while(i < position){                                                                                                // This part iterates through the list. If it reaches end, returns.
        if(node -> getNextElem() == nullptr) return;
        node = node -> getNextElem();
        i++;
    }
    if(node == head) head = node -> getNextElem();                                                                      // This part assigns new values in different scenarios, effectively removing nodes.
    if(node == tail) tail = node -> getPrevElem();
    if(node -> getPrevElem() != nullptr) node -> getPrevElem() ->setNextNode(node -> getNextElem());
    if(node -> getNextElem() != nullptr) node -> getNextElem() ->setPreviousNode(node -> getPrevElem());
    delete node;
}

void DynamicDoublyLinkedList::frontalRemove() {
    if(head == nullptr) return;
    DynamicDoublyLinkedNode* nodeToRemove = head;

    head = head -> getNextElem();                                                                                       // Update the head to the next node

    if (head != nullptr) head -> setPreviousNode(nullptr);                                                     // Update the previous node of the new head

    else tail = nullptr;                                                                                                // List became empty, update the tail

    delete nodeToRemove;
}

void DynamicDoublyLinkedList::backRemove() {
    if(head == nullptr) return;
    DynamicDoublyLinkedNode* nodeToRemove = tail;

    tail = tail -> getPrevElem();                                                                                       // Update the head to the next node

    if (tail != nullptr) tail -> setNextNode(nullptr);                                                         // Update the previous node of the new head

    else head = nullptr;                                                                                                // List became empty, update the tail

    delete nodeToRemove;
}