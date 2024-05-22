//
// Created by Ponanoix on 22.04.2023.
//
#include "../../header_files/helper_header_files/DynamicDoublyLinkedNode.h"

DynamicDoublyLinkedNode::DynamicDoublyLinkedNode(int val) {
    value = val;                                                                            // Assigns "value" as an initial value for the Node
}

void DynamicDoublyLinkedNode::setNextNode(DynamicDoublyLinkedNode *neighElem) {
    nextElem = neighElem;                                                                   // Sets a value pointed by the parameter for the following node.
}

void DynamicDoublyLinkedNode::setPreviousNode(DynamicDoublyLinkedNode *neighElem) {
    prevElem = neighElem;                                                                   // Sets a value pointed by the parameter for the previous node.
}

DynamicDoublyLinkedNode *DynamicDoublyLinkedNode::getNextElem() {
    return nextElem;                                                                        // Returns the following, pointed node.
}

DynamicDoublyLinkedNode *DynamicDoublyLinkedNode::getPrevElem() {
    return prevElem;                                                                        // Returns the previous, pointed node.
}

int DynamicDoublyLinkedNode::getVal() {
    return value;                                                                           // Returns the value of a specified node.
}
