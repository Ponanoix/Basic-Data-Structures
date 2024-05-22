//
// Created by Ponanoix on 22.04.2023.
//

#ifndef SDIZO_DYNAMICDOUBLYLINKEDNODE_H
#define SDIZO_DYNAMICDOUBLYLINKEDNODE_H

class DynamicDoublyLinkedNode{
public:
    explicit DynamicDoublyLinkedNode(int val);                           // Creates a new node with a value.

    void setNextNode(DynamicDoublyLinkedNode* neighElem);                // Sets next node pointed by this node.

    void setPreviousNode(DynamicDoublyLinkedNode* neighElem);            // Sets previous node pointed by this node.

    DynamicDoublyLinkedNode* getNextElem();                              // Returns the next node.

    DynamicDoublyLinkedNode* getPrevElem();                              // Returns the previous node.

    int getVal();                                                        // Returns the value of the node.
private:
    DynamicDoublyLinkedNode* nextElem = nullptr;                         // Points to the next node.

    DynamicDoublyLinkedNode* prevElem = nullptr;                         // Points to the previous node.

    int value;                                                           // Node's value
};

#endif //SDIZO_DYNAMICDOUBLYLINKEDNODE_H
