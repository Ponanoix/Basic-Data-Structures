//
// Created by Ponanoix on 25.04.2023.
//

#ifndef SDIZO_DYNAMICRBTREE_H
#define SDIZO_DYNAMICRBTREE_H

#include "../../Sdizo/header_files/helper_header_files/DynamicRBTreeNode.h"

class DynamicRBTree{
private:
    DynamicRBTreeNode *root = nullptr;                              // Pointer to the tree's root.

    void hardDelete(DynamicRBTreeNode *node);                           // Deletes all given nodes and its sub-nodes.

    void fixTree(DynamicRBTreeNode* startNode);                     // Fixes tree starting from given node.

    DynamicRBTreeNode* getUncle(DynamicRBTreeNode* node);           // Returns either node's uncle or nullptr.

    static bool isRightSon(DynamicRBTreeNode* node);                // Checks if the node is father's right child.

    void remove(DynamicRBTreeNode* node);                           // Removes the given node.

    static DynamicRBTreeNode* getNext(DynamicRBTreeNode* node);     // Returns the node's successor.

    void restoreDelete(DynamicRBTreeNode* node);                    // Restores RBTree's properties after removal.

    static DynamicRBTreeNode* getBrother(DynamicRBTreeNode* node);  // Returns the node's brother.

    void fixDoubleBlack(DynamicRBTreeNode* node);                   // Fixes instance of two black nodes during deletion.
public:
    [[nodiscard]] DynamicRBTreeNode *getRoot() const;               // Returns the tree's root.

    ~DynamicRBTree();

    explicit DynamicRBTree(int value);                              // Constructor to create a new RBTree.

    DynamicRBTree() = default;;

    explicit DynamicRBTree(DynamicRBTreeNode* node);                // Creates a new instance of this class with initial node as a root.

    void add(int value);                                            // Inserts new element and recolours tree.

    void remove(int value);                                         // Removes the node with specified value from this tree.

    DynamicRBTreeNode* search(int value);                           // Returns the node which carries the value.

    void rotateLeft(DynamicRBTreeNode *node);                       // Performs left rotation on this node.

    void rotateRight(DynamicRBTreeNode *node);                      // Performs right rotation on this node.

    void printInOrder();                                            // Prints the tree in non-descending order.

    void insert(DynamicRBTreeNode *node, DynamicRBTreeNode *startingNode);

    void postOrder(DynamicRBTreeNode *node, int indent);

};

#endif //SDIZO_DYNAMICRBTREE_H
