//
// Created by Ponanoix on 25.04.2023.
//

#ifndef SDIZO_DYNAMICRBTREENODE_H
#define SDIZO_DYNAMICRBTREENODE_H

#include<iostream>
#include<string>

enum Colour { RED, BLACK};

class DynamicRBTreeNode{
private:
    Colour colour = RED;                    // Colour of the node.

    DynamicRBTreeNode* right = nullptr;     // Pointer to the right son.

    DynamicRBTreeNode* left = nullptr;      // Pointer to the left son.

    DynamicRBTreeNode* parent = nullptr;    // Pointer to the father.

    int data;                               // Value carried by the node.
public:
    DynamicRBTreeNode(int data, Colour colour):data(data), colour(colour){}; // Creates a new node with initial colour and data.

    Colour getColour() const;                                               // Returns the colour.

    void setColour(Colour colour);                                          // Sets the colour of the node.

    DynamicRBTreeNode *getRight() const;                                    // Returns node representing the right son.

    DynamicRBTreeNode *getLeft() const;                                     // Returns node representing the left son.

    void setRight(DynamicRBTreeNode *right);                                // Sets the right son of the node.

    void setLeft(DynamicRBTreeNode *left);                                  // Sets the left son of the node.

    DynamicRBTreeNode *getParent() const;                                   // Returns node representing the father.

    void setParent(DynamicRBTreeNode *parent);                              // Sets the parent of the node.

    int getData() const;                                                    // Returns the value of the node.

    void setData(int data);                                                 // Sets the value of the node.

    void printInOrder();                                                    // Recursive function to print in order (non-descending).

    std::string toString();                                                 // Returns string representation of the node.
};

#endif //SDIZO_DYNAMICRBTREENODE_H
