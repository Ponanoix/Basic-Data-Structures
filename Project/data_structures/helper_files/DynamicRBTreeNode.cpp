//
// Created by Ponanoix on 25.04.2023.
//

#include "../../header_files/helper_header_files/DynamicRBTreeNode.h"

Colour DynamicRBTreeNode::getColour() const {
    return colour;
}

void DynamicRBTreeNode::setColour(Colour colour) {
    DynamicRBTreeNode::colour = colour;
}

DynamicRBTreeNode *DynamicRBTreeNode::getRight() const {
    return right;
}

void DynamicRBTreeNode::setRight(DynamicRBTreeNode *right) {
    DynamicRBTreeNode::right = right;
}

DynamicRBTreeNode *DynamicRBTreeNode::getLeft() const {
    return left;
}

void DynamicRBTreeNode::setLeft(DynamicRBTreeNode *left) {
    DynamicRBTreeNode::left = left;
}

DynamicRBTreeNode *DynamicRBTreeNode::getParent() const {
    return parent;
}

void DynamicRBTreeNode::setParent(DynamicRBTreeNode *parent) {
    DynamicRBTreeNode::parent = parent;
}

int DynamicRBTreeNode::getData() const {
    return data;
}

void DynamicRBTreeNode::setData(int data) {
    DynamicRBTreeNode::data = data;
}

void DynamicRBTreeNode::printInOrder() {
    if(this -> left != nullptr) this -> left -> printInOrder();
    std::cout << this -> toString() + " ";
    if (this -> right != nullptr) this -> right -> printInOrder();
}

std::string DynamicRBTreeNode::toString() {
    std::string charColour;
    switch (colour) {
        case BLACK:{
            charColour = "B";
            break;
        }
        case RED:{
            charColour = "R";
            break;
        }
    }
    std::string value = std::to_string(this -> data) + "(" + charColour + ")";
    return value;
}
