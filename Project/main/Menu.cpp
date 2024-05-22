//
// Created by Ponanoix on 23.04.2023.
//

#include "../../Sdizo/main/Menu.h"
#include "../../Sdizo/input_output/FileReader.h"
#include "../../Sdizo/main/Benchmark.h"

using namespace std;

Menu::Menu() {
    printMainMenu();
}

void Menu::printMainMenu() {

    while (true) {
        cout << "Choose the command: " << endl;
        cout << "\t1. Initiate the tests." << endl;
        cout << "\t2. Load a structure from the file." << endl;
        cout << "\t0. Turn off the program" << endl;
        cout << "\n";
        int input = getIntegerInput("Your choice:");
        cout << "\n";
        switch (input) {
            case 1: {
                printBenchmarkMenu();
                break;
            }
            case 2: {
                printFileLoadMenu();
                break;
            }
            case 0: {
                cout << "Turning off..." << endl;
                exit(0);
            }
            default: {
                cout << "Unknown command" << endl;
                break;
            }
        }
    }
}

void Menu::printFileLoadMenu() {
    cout << "Enter the type of structure: " << endl;
    cout << "\t1. DynamicArray" << endl;
    cout << "\t2. DynamicDoublyLinkedList" << endl;
    cout << "\t3. DynamicBinaryHeap" << endl;
    cout << "\t4. DynamicRBTree" << endl;
    cout << "\t0. Return" << endl;
    cout << "\n";
    int input = getIntegerInput("Your choice:");
    cout << "\n";
    bool isPicked = false;
    while (!isPicked){
        switch (input) {
            case 1: {
                type = DynamicArray_T;
                initDynamicArray();
                isPicked = true;
                break;
            }
            case 2: {
                type = DynamicDoublyLinkedList_T;
                initDynamicDoublyLinkedList();
                isPicked = true;
                break;
            }
            case 3: {
                type = DynamicBinaryHeap_T;
                initHeap();
                isPicked = true;
                break;
            }
            case 4: {
                type = DynamicRBTree_T;
                initRBTree();
                isPicked = true;
                break;
            }
            default: {
                cout << "Unknown choice." << endl;
            }
        }
    }
}

void Menu::initDynamicDoublyLinkedList() {
    cout << "Enter the name of the file, from which you desire to download the data: ";
    string input;
    cin >> input;
    cout << "Loading data..." << endl;
    try {
        FileReader reader(input);
        dynamicDoublyLinkedList = new DynamicDoublyLinkedList();
        reader.readToDynamicDoublyLinkedList(dynamicDoublyLinkedList, BACK);
        printDynamicDoublyLinkedListMenu();
    } catch (runtime_error& e){
        printException(e);
        initDynamicDoublyLinkedList();
        return;
    }
}

void Menu::initDynamicArray() {
    cout << "Enter the name of a file, from which you desire to download the data: ";
    string input;
    cin >> input;
    cout << "Loading..." << endl;
    try {
        FileReader reader(input);
        dynamicArray = new DynamicArray();
        reader.readToDynamicArray(dynamicArray, BACK);
        printDynamicArrayMenu();
    } catch (runtime_error& e){
        printException(e);
        initDynamicArray();
        return;
    }
}

void Menu::initHeap() {
    cout << "Enter the name of the file, from which you desire to download data: ";
    string input;
    cin >> input;
    cout << "Loading..." << endl;
    try {
        FileReader reader(input);
        dynamicBinaryHeap = new DynamicBinaryHeap();
        reader.readToHeap(dynamicBinaryHeap);
        printDynamicBinaryHeapMenu();
    } catch (runtime_error& e){
        printException(e);
        initHeap();
        return;
    }
}

void Menu::initRBTree() {
    cout << "Enter the name of the file, from which you desire to download data: ";
    string input;
    cin >> input;
    cout << "Loading..." << endl;
    try{
        FileReader reader(input);
        dynamicRbTree = new DynamicRBTree();
        reader.readToRBTree(dynamicRbTree);
        printDynamicRBTreeMenu();
    } catch (runtime_error& e){
        printException(e);
        initRBTree();
        return;
    }
}

void Menu::printDynamicDoublyLinkedListMenu() {
    bool goBack = false;
    while (!goBack){
        cout << "---DOUBLY LINKED LIST--- " << endl;
        cout << "Print: ";
        dynamicDoublyLinkedList -> printList();
        cout << "\nChoose one of the following:" << endl;
        cout << "\t1. Add an element at the beginning." << endl;
        cout << "\t2. Add an element in the end." << endl;
        cout << "\t3. Add an element at a position." << endl;
        cout << "\t4. Delete an element at the beginning." << endl;
        cout << "\t5. Delete an element at the end." << endl;
        cout << "\t6. Delete an element at the position." << endl;
        cout << "\t7. Search for an element." << endl;
        cout << "\t0. Return to the main menu." << endl;
        cout << "\t-1 Leave." << endl;
        int input;
        input = getIntegerInput("\nYour choice: ");
        switch (input) {
            case 1: {
                int input2;
                input2 = getIntegerInput("Enter the element to be added: ");
                dynamicDoublyLinkedList -> frontalAdd(input2);
                cout << "Successfully added the element" << endl << endl;
                break;
            }
            case 2: {
                int input2;
                input2 = getIntegerInput("Enter the element to be added: ");
                dynamicDoublyLinkedList -> backAdd(input2);
                cout << "Successfully added the element" << endl << endl;
                break;
            }
            case 3: {
                int input2;
                input2 = getIntegerInput("Enter the element to be added: ");
                int input3;
                input3 = getIntegerInput("Enter the element's position: ");
                try {
                    dynamicDoublyLinkedList -> freeAdd(input3, input2);
                }
                catch (invalid_argument& e) {
                    printException(e);
                }
                break;
            }
            case 4: {
                if(dynamicDoublyLinkedList -> getSize() > 0) {
                    dynamicDoublyLinkedList -> frontalRemove();
                    cout << "The element was successfully deleted." << endl;
                }
                else {
                    cout << "\nThe list is empty." << endl << endl;
                }
                break;
            }
            case 5: {
                if(dynamicDoublyLinkedList -> getSize() > 0) {
                    dynamicDoublyLinkedList -> backRemove();
                    cout << "The element was successfully deleted." << endl;
                }
                else {
                    cout << "\nThe list is empty." << endl << endl;
                }
                break;
            }
            case 6: {
                int input2;
                input2 = getIntegerInput("Position of the element to delete: ");
                if (input2 >= 0 && input2 < dynamicDoublyLinkedList -> getSize()){
                    try {
                        dynamicDoublyLinkedList -> freeRemove(input2);
                        cout << "The element was deleted." << endl;
                    }
                    catch (invalid_argument& e) {
                        printException(e);
                    }
                }
                else {
                    cout << "\nInvalid argument." << endl << endl;
                }
                break;
            }
            case 7: {
                int input2 = getIntegerInput("Enter the element to find: ");
                if (dynamicDoublyLinkedList -> positionOf(input2) != -1){
                    cout << "The element exists. Its address: ";
                    DynamicDoublyLinkedNode* node = dynamicDoublyLinkedList -> getPos(dynamicDoublyLinkedList -> positionOf(input2));
                    cout << dynamicDoublyLinkedList -> positionOf(input2) << endl;
                    if (node -> getPrevElem() != nullptr) cout << "The previous element: " << node -> getPrevElem()-> getVal() << "." << endl;
                    if (node -> getNextElem() != nullptr) cout << "The next element: " << node -> getNextElem() -> getVal() << "." << endl;
                }
                else {
                    cout << "This element does not exist!" << endl;
                }
                break;
            }
            case 0: {
                backToMainMenu();
                goBack = true;
                break;
            }
            case -1: {
                cout << "Shutting down..." << endl;
                exit(0);
            }
            default: {
                cout << "Unknown argument." << endl;
            }
        }
    }
}

void Menu::printDynamicArrayMenu() {
    bool goBack = false;
    while (!goBack){
        cout << "---DYNAMIC ARRAY---" << endl;
        cout << "Print: ";
        dynamicArray -> printArray();
        cout << "Choose one of the following:" << endl;
        cout << "\t1. Add an element at the beginning." << endl;
        cout << "\t2. Add an element at the end." << endl;
        cout << "\t3. Add an element at the position." << endl;
        cout << "\t4. Delete an element at the beginning." << endl;
        cout << "\t5. Delete an element at the end." << endl;
        cout << "\t6. Delete an element at the position." << endl;
        cout << "\t7. Search for an element." << endl;
        cout << "\t0. Return to main menu." << endl;
        cout << "\t-1. Leave." << endl;
        int input;
        input = getIntegerInput("\nYour choice: ");
        switch (input) {
            case 1: {
                int input2 = getIntegerInput("Enter the element to be added: ");
                dynamicArray -> frontalAdd(input2);
                cout << "Successfully added the element." << endl << endl;
                break;
            }
            case 2: {
                int input2 = getIntegerInput("Enter the element to be added: ");
                dynamicArray -> backAdd(input2);
                cout << "Successfully added the element." << endl << endl;
                break;
            }
            case 3: {
                int input2 = getIntegerInput("Enter the element to be added: ");
                int input3 = getIntegerInput("Enter the element's position: ");
                try {
                    dynamicArray -> freeAdd(input2, input3);
                }
                catch (invalid_argument& e){
                    printException(e);
                }
                cout << "Successfully added the element." << endl << endl;
                break;
            }
            case 4: {
                if(dynamicArray -> getSize() > 0) {
                    dynamicArray -> frontalRemove();
                    cout << "The element was successfully deleted." << endl;
                }
                else{
                    cout << "The array is empty." << endl << endl;
                }
                break;
            }
            case 5: {
                if(dynamicArray -> getSize() > 0) {
                    dynamicArray -> backRemove();
                    cout << "The element was successfully deleted." << endl;
                }
                else{
                    cout << "The array is empty." << endl << endl;
                }
                break;
            }
            case 6: {
                int input2 = getIntegerInput("The position of the element to delete: ");
                if (dynamicArray -> getSize() > input2){
                    dynamicArray -> freeRemove(input2);
                    cout << "The element was successfully deleted." << endl;
                }
                else {
                    cout << "The element does not exist." << endl << endl;
                }
                break;
            }
            case 7: {
                int input2 = getIntegerInput("Enter the element to find: ");
                if (dynamicArray -> contains(input2)){
                    cout << "The element exists. Its address: " << dynamicArray -> checkElem(input2) << endl;
                }
                else {
                    cout << "The element does not exist." << endl << endl;
                }
                break;
            }
            case 0: {
                backToMainMenu();
                goBack = true;
                break;
            }
            case -1: {
                cout << "Shutting down..." << endl << endl;
                exit(0);
            }
            default: {
                cout << "Unknown argument." << endl << endl;
            }
        }
    }
}

void Menu::printDynamicBinaryHeapMenu() {
    bool goBack = false;
    while (!goBack){
        cout << "---BINARY HEAP---" << endl;
        dynamicBinaryHeap -> print();
        cout << "Choose one of the following:" << endl;
        cout << "\t1. Add an element." << endl;
        cout << "\t2. Delete an element." << endl;
        cout << "\t3. Search through the heap." << endl;
        cout << "\t4. Show the heap" << endl;
        cout << "\t0. Return to the main menu." << endl;
        cout << "\t-1. Leave." << endl;
        int input = getIntegerInput("\nYour choice: ");
        switch (input) {
            case 1: {
                int input2 = getIntegerInput("Type an element to add: ");
                dynamicBinaryHeap -> add(input2);
                break;
            }
            case 2: {
                cout << "Deleting the root element...\n";
                try {
                    dynamicBinaryHeap -> remove();
                } catch (length_error& e) {
                    printException(e);
                }
                break;
            }
            case 3 : {
                cout << "Searching through the heap...\n";
                int input2 = getIntegerInput("Type the element to search for: ");
                bool result = dynamicBinaryHeap -> search(input2);
                if (result) cout << "The element is in the heap." << endl;
                else cout << "The element is not in the heap." << endl;
            }
            case 4: {
                dynamicBinaryHeap -> print();
                break;
            }
            case 0: {
                backToMainMenu();
                goBack = true;
                break;
            }
            case -1: {
                cout << "Shutting down..." << endl << endl;
                exit(0);
            }
            default: {
                cout << "Unknown argument." << endl << endl;
            }
        }
    }
}

void Menu::printDynamicRBTreeMenu() {
    bool goBack = false;
    while (!goBack){
        cout << "---RED-BLACK TREE---" << endl;
        dynamicRbTree -> postOrder(dynamicRbTree -> getRoot(), 0);
        cout << "\n WARNING: Tree is printed from left to right - not from up to down!\n";
        cout << "\nIn-order: " << endl;
        dynamicRbTree -> printInOrder();
        cout << "\nWhat do you want to do? " << endl;
        cout << "\t1. Add an element" << endl;
        cout << "\t2. Delete an element" << endl;
        cout << "\t3. Find an element" << endl;
        cout << "\t0. Return to main menu" << endl;
        cout << "\t-1 Exit" << endl;
        int input = getIntegerInput("Your choice: ");
        switch (input) {
            case 1: {
                int input2 = getIntegerInput("Type an element to add: ");
                dynamicRbTree -> add(input2);
                break;
            }
            case 2: {
                int input2 = getIntegerInput("Type an element to delete: ");
                if (dynamicRbTree -> search(input2) != nullptr){
                    dynamicRbTree -> remove(input2);
                }
                else cout << "This element does not exist." << endl << endl;
                break;
            }
            case 3: {
                int input2 = getIntegerInput("Type an element to find: ");
                DynamicRBTreeNode* found = dynamicRbTree -> search(input2);
                if (found != nullptr){
                    cout << "Such element was found!";
                    if (found->getParent() != nullptr) cout << "\n\tIts father: " << found -> getParent() -> getData() << ".";
                    if (found->getLeft() != nullptr) cout << "\n\tLeft son: " << found -> getLeft() -> getData();
                    if (found->getRight() != nullptr) cout << "\n\tRight son: " << found -> getRight() -> getData();
                    cout << "\n";

                }
                else cout << "This element does not exist." << endl << endl;
                break;
            }
            case 0: {
                backToMainMenu();
                goBack = true;
                break;
            }
            case -1: {
                cout << "Shutting down..." << endl << endl;
                exit(0);
            }
            default:{
                cout << "Unknown argument." << endl << endl;

            }
        }
    }
}

void Menu::printBenchmarkMenu() {
    StructureType toTest;
    bool writeToFile;
    int initialSize;
    int step;
    float multiplier;
    int testNumber;
    int maxSize;

    cout << "Type the data structure to test: " << endl;
    cout << "\t1. DynamicDoublyLinkedList" << endl;
    cout << "\t2. DynamicArray" << endl;
    cout << "\t3. DynamicBinaryHeap" << endl;
    cout << "\t4. DynamicRBTree" << endl;
    cout << "\n";
    bool isPicked = false;
    while (!isPicked) {
        int input = getIntegerInput("Your choice: ");
        switch (input) {
            case 1: {
                toTest = DynamicDoublyLinkedList_T;
                isPicked = true;
                break;
            }
            case 2: {
                toTest = DynamicArray_T;
                isPicked = true;
                break;
            }
            case 3: {
                toTest = DynamicBinaryHeap_T;
                isPicked = true;
                break;
            }
            case 4: {
                toTest = DynamicRBTree_T;
                isPicked = true;
                break;
            }
            default: {
                cout << "Unknown choice." << endl;
            }
        }
    }

    cout << "Do you wish for the data to be saved in .csv? (Y/N): ";
    string odp;
    cin >> odp;
    if (odp[0] == 'Y' || odp[0] == 'y') writeToFile = true;
    else writeToFile = false;

    initialSize= getIntegerInput("Initial structure's size: ", true);

    multiplier = getFloatInput("Magnitude multiplier (advised is 1): ", true);

    step = getIntegerInput("Step (Amount by which should it be increased after each iteration): ", true);

    testNumber = getIntegerInput("How many times should the tests be repeated: ", true);

    maxSize = getIntegerInput("What should be the maximum size of the structure: ", true);

    Benchmark benchmark(toTest, writeToFile, initialSize, step, multiplier, testNumber, maxSize);

    cout << "Test is finished" << endl;
    backToMainMenu();
}

void Menu::backToMainMenu() {
    switch (type) {
        case DynamicDoublyLinkedList_T: {
            delete dynamicDoublyLinkedList;
            break;
        }
        case DynamicArray_T: {
            delete dynamicArray;
            break;
        }
        case DynamicBinaryHeap_T: {
            delete dynamicBinaryHeap;
            break;
        }
        case DynamicRBTree_T: {
            delete dynamicRbTree;
            break;
        }
    }
}

int Menu::getIntegerInput(string message, bool mustPositive) {
    bool isNum = false;
    bool isPositive = false;
    int val;
    while (!isNum) {
        cout << message;
        string input;
        cin.clear();
        cin.sync();
        getline(cin, input);
        try {
            val = stoi(input);
            if (val > 0) isPositive = true;
            if (!mustPositive) isNum = true;
            else if (isPositive) isNum = true;
            else isNum = false;
        } catch (invalid_argument &e) {
            cout << "The input data is not a number!" << endl;
            continue;
        }
        catch (out_of_range &e) {
            cout << "The input number is too large!" << endl;
            continue;
        }
    }
    return val;
}
float Menu::getFloatInput(string message, bool mustPositive) {
    bool isNum = false;
    bool isPositive = false;
    float val;
    while (!isNum) {
        cout << message;
        string input;
        cin.clear();
        cin.sync();
        getline(cin, input);
        try {
            val = stof(input);
            if (val > 0) isPositive = true;
            if (!mustPositive) isNum = true;
            else if (isPositive) isNum = true;
            else isNum = false;
        } catch (invalid_argument &e) {
            cout << "The input data is not a number!" << endl;
            continue;
        }
        catch (out_of_range &e) {
            cout << "The input number is too large!" << endl;
            continue;
        }
    }
    return val;
}

void Menu::printException(exception &e) {
    cout << "-------------------------------------------\n";
    cout << endl << endl << "WARNING: An error has occurred";
    cerr << e.what() << "\n\n\n";
    cout << " -------------------------------------------\n";
}
