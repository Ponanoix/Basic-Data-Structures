//
// Created by Ponanoix on 25.04.2023.
//

#include "../../Sdizo/header_files/DynamicRBTree.h"
#include<iostream>
#include<iomanip>

DynamicRBTree::DynamicRBTree(int value) {
    this -> root = new DynamicRBTreeNode(value, BLACK);
}

DynamicRBTree::DynamicRBTree(DynamicRBTreeNode *node) {
    this -> root = node;
}

void DynamicRBTree::add(int value) {
    auto* newNode = new DynamicRBTreeNode(value, RED);
    if(root == nullptr){
        root = newNode;
        root ->setColour(BLACK);
        return;
    }
    insert(newNode, root);
    fixTree(newNode);
}

void DynamicRBTree::remove(int value) {
    remove(search(value));
}

void DynamicRBTree::remove(DynamicRBTreeNode* node) {
    if (node == nullptr) return;

    if (node->getColour() == BLACK) restoreDelete(node);

    DynamicRBTreeNode* parent = node->getParent();
    DynamicRBTreeNode* child = nullptr;

    if (node->getLeft() == nullptr || node->getRight() == nullptr) {
        // The node has at most one child
        if (node->getLeft() != nullptr) {
            child = node->getLeft();
        } else if (node->getRight() != nullptr) {
            child = node->getRight();
        }

        if (parent == nullptr) {
            // The node to be deleted is the root
            root = child;
            if (child != nullptr) {
                child->setParent(nullptr);
                child->setColour(BLACK);
            }
        } else if (node == parent->getLeft()) {
            parent->setLeft(child);
            if (child != nullptr) {
                child->setParent(parent);
            }
        } else {
            parent->setRight(child);
            if (child != nullptr) {
                child->setParent(parent);
            }
        }

        delete node;
    } else {
        // The node has both left and right children
        DynamicRBTreeNode* successor = getNext(node);
        node->setData(successor->getData());

        // Update parent's pointer to the successor
        if (successor->getParent()->getLeft() == successor) {
            successor->getParent()->setLeft(successor->getRight());
        } else {
            successor->getParent()->setRight(successor->getRight());
        }

        if (successor->getRight() != nullptr) {
            successor->getRight()->setParent(successor->getParent());
        }

        delete successor;
    }
}

DynamicRBTreeNode *DynamicRBTree::search(int value) {
    DynamicRBTreeNode* node = root;

    while(node != nullptr && node -> getData() != value){
        if(node -> getData() > value){
            node = node -> getLeft();
        }
        else{
            node = node -> getRight();
        }
    }
    if(node == nullptr) return nullptr;
    if(node -> getData() == value) return node;
    return nullptr;
}

void DynamicRBTree::rotateRight(DynamicRBTreeNode *node) {
    if(node != nullptr && node -> getLeft() != nullptr){
        DynamicRBTreeNode* left = node -> getLeft();
        if(node -> getParent() != nullptr){
            if(node -> getParent() -> getLeft() == node){
                node -> getParent() -> setLeft(left);
                left -> setParent(node -> getParent());
            }
            else{
                node -> getParent() ->setRight(left);
                left -> setParent(node -> getParent());
            }
        }
        else left -> setParent(nullptr);
        node -> setLeft(left -> getRight());
        if(left -> getRight() != nullptr) left -> getRight() ->setParent(node);
        left -> setRight(node);
        if(node == root){
            root == left;
        }
        node -> setParent(left);
    }
}

void DynamicRBTree::rotateLeft(DynamicRBTreeNode *node) {
    if(node != nullptr && node -> getRight() != nullptr){
        DynamicRBTreeNode* right = node -> getRight();
        if(node -> getParent() != nullptr){
            if(node -> getParent() -> getLeft() == node){
                node -> getParent() -> setLeft(right);
                right -> setParent(node -> getParent());
            }
            else {
                node -> getParent() -> setRight(right);
                right -> setParent(node -> getParent());
            }
        }
        else right -> setParent(nullptr);

        node -> setRight(right -> getLeft());
        if(right -> getLeft() != nullptr) right -> getLeft() -> setParent(node);

        right -> setLeft(node);
        if(node == root){
            root = right;
        }
        node -> setParent(right);
    }
}

void DynamicRBTree::insert(DynamicRBTreeNode *node, DynamicRBTreeNode *startingNode) {
    if(startingNode -> getData() > node -> getData()){
        if(startingNode -> getLeft() != nullptr) insert(node, startingNode -> getLeft());
        else{
            startingNode -> setLeft(node);
            node -> setParent(startingNode);
        }
    }
    else{
        if(startingNode -> getRight() != nullptr) insert(node, startingNode -> getRight());
        else{
            startingNode -> setRight(node);
            node ->setParent(startingNode);
        }
    }
}

void DynamicRBTree::fixTree(DynamicRBTreeNode *startNode) {
    auto currentNode = startNode;
    if(startNode == root){
        startNode -> setColour(BLACK);
        return;
    }
    while(currentNode != root && currentNode -> getColour() != BLACK && currentNode -> getParent() -> getColour() == RED){
        DynamicRBTreeNode* parent = currentNode -> getParent();
        DynamicRBTreeNode* gParent = parent -> getParent();
        if(!isRightSon(parent)){
            DynamicRBTreeNode* uncle = getUncle(currentNode);
            if(uncle != nullptr && uncle -> getColour() == RED){
                gParent -> setColour(RED);
                parent -> setColour(BLACK);
                uncle -> setColour(BLACK);
                currentNode = gParent;
            }
            else{
                if(isRightSon(currentNode)){
                    rotateLeft(parent);
                    currentNode = parent;
                    parent = currentNode -> getParent();
                }
                rotateRight(gParent);
                Colour colour = parent -> getColour();
                parent -> setColour(gParent -> getColour());
                gParent -> setColour(colour);
                currentNode = parent;
            }
        }
        else{
            DynamicRBTreeNode* uncle = getUncle(currentNode);
            if(uncle != nullptr && uncle -> getColour() == RED){
                gParent -> setColour(RED);
                parent -> setColour(BLACK);
                uncle -> setColour(BLACK);
                currentNode = gParent;
            }
            else{
                if(!isRightSon(currentNode)){
                    rotateRight(parent);
                    currentNode = parent;
                    parent = currentNode -> getParent();
                }
                rotateLeft(gParent);
                Colour colour = parent -> getColour();
                parent -> setColour(gParent -> getColour());
                gParent -> setColour(colour);
            }
        }
        root -> setColour(BLACK);
    }
}

DynamicRBTreeNode *DynamicRBTree::getUncle(DynamicRBTreeNode *node) {
    if(node == root) return nullptr;
    if (node -> getParent() == nullptr) return nullptr;
    if (node -> getParent() -> getParent() == nullptr) return nullptr;
    if (node -> getParent() -> getParent() -> getLeft() == node -> getParent() &&
        node -> getParent() -> getParent() -> getRight() != nullptr) return node -> getParent() -> getParent() -> getRight();
    if (node -> getParent() -> getParent() -> getRight() == node -> getParent() &&
        node -> getParent() -> getParent() -> getLeft() != nullptr) return node -> getParent() -> getParent() -> getLeft();
    return nullptr;
}

bool DynamicRBTree::isRightSon(DynamicRBTreeNode *node) {
    if (node -> getParent() == nullptr) return false;
    if (node -> getParent()->getLeft() == node) return false;
    return true;
}

DynamicRBTreeNode *DynamicRBTree::getRoot() const {
    return root;
}

DynamicRBTreeNode *DynamicRBTree::getNext(DynamicRBTreeNode *node) {
    if(node -> getRight() != nullptr){
        DynamicRBTreeNode* minNode = node -> getRight();
        while (minNode -> getLeft() != nullptr){
            minNode = minNode -> getLeft();
        }
        return minNode;
    }
    return nullptr;
}

void DynamicRBTree::restoreDelete(DynamicRBTreeNode *node) {
    DynamicRBTreeNode* onlyChild = nullptr;
    if(node -> getLeft() != nullptr) onlyChild = node -> getLeft();
    else if (node -> getRight() != nullptr) onlyChild = node -> getRight();
    if (onlyChild != nullptr){
        if (node -> getColour() == RED || onlyChild -> getColour() == RED){
            onlyChild -> setColour(BLACK);
            return;
        }
    }
    if(node -> getColour() == BLACK && (onlyChild == nullptr || onlyChild -> getColour() == BLACK)){
        fixDoubleBlack(node);
    }
}

DynamicRBTreeNode *DynamicRBTree::getBrother(DynamicRBTreeNode *node) {
    if(isRightSon(node)) return node -> getParent() -> getLeft();
    return node -> getParent() -> getRight();
}

void DynamicRBTree::fixDoubleBlack(DynamicRBTreeNode *node) {
    if(node == root) return;
    DynamicRBTreeNode* brother = getBrother(node);
    DynamicRBTreeNode* father = node -> getParent();
    if(brother == nullptr) fixDoubleBlack(node -> getParent());
    else if(brother -> getColour() == BLACK){
        DynamicRBTreeNode* rightSonSibling = brother -> getRight();
        DynamicRBTreeNode* leftSonSibling = brother -> getLeft();
        if((rightSonSibling != nullptr && rightSonSibling -> getColour() == RED) || (leftSonSibling != nullptr && leftSonSibling -> getColour() == RED)){
            DynamicRBTreeNode* redSon = nullptr;
            bool bothRed = (rightSonSibling != nullptr && rightSonSibling -> getColour() == RED) && (leftSonSibling !=
                    nullptr && leftSonSibling -> getColour() == RED);
            if(rightSonSibling != nullptr && rightSonSibling -> getColour() == RED) redSon = rightSonSibling;
            else redSon = leftSonSibling;
            if(!isRightSon(brother)){
                if(redSon == leftSonSibling || bothRed){
                    leftSonSibling ->setColour(brother -> getColour());
                    rotateRight(node -> getParent());
                }
                else if(redSon == rightSonSibling){
                    rightSonSibling -> setColour(father -> getColour());
                    rotateLeft(brother);
                    rotateRight(node -> getParent());
                }
            }
            else{
                if(redSon == rightSonSibling || bothRed){
                    rightSonSibling -> setColour(brother -> getColour());
                    rotateLeft(node -> getParent());
                    brother -> setColour(father -> getColour());
                }
                else if(redSon == leftSonSibling){
                    leftSonSibling -> setColour(father -> getColour());
                    rotateRight(brother);
                    rotateLeft(node -> getParent());
                }
            }
        }
        else{
            brother ->setColour(RED);
            if(node -> getParent() -> getColour() == BLACK) fixDoubleBlack(node -> getParent());
            else node -> getParent() -> setColour(BLACK);
        }
    }
    else if(brother != nullptr && brother -> getColour() == RED){
        if(!isRightSon(brother)){
            brother -> getParent() ->setColour(RED);
            rotateRight(brother -> getParent());
            brother -> setColour(BLACK);
            fixDoubleBlack(node);
        }
        else{
            brother -> getParent() -> setColour(RED);
            rotateLeft(brother -> getParent());
            brother -> setColour(BLACK);
            fixDoubleBlack(node);
        }
    }
}

DynamicRBTree::~DynamicRBTree(){
    hardDelete(root);
}

void DynamicRBTree::hardDelete(DynamicRBTreeNode *node) {
    if(node == nullptr) return;
    hardDelete(node -> getLeft());
    hardDelete(node -> getRight());
    delete node;
}

void DynamicRBTree::printInOrder() {
    root -> printInOrder();
}

void DynamicRBTree::postOrder(DynamicRBTreeNode *node, int indent) {
    if(node != nullptr){
        if(node -> getRight()){
            postOrder(node -> getRight(), indent + 4);
        }
        if(indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if(node -> getRight()) std::cout << " /\n" << std::setw(indent) << ' ';
        std::cout << node -> toString() << "\n ";
        if(node -> getLeft()) {
            std::cout << std::setw(indent) << ' ' << " \\\n";
            postOrder(node -> getLeft(), indent + 4);
        }
    }
}
