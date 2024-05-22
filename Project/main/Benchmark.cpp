//
// Created by Ponanoix on 23.04.2023.
//

#include "../../Sdizo/main/Benchmark.h"
#include "../../Sdizo/input_output/CSVWriter.h"

using namespace std;

Benchmark::Benchmark(StructureType type, bool writeToFile, int initialSize, int step, float multiplier, int testNumber,
                     int maxSize): type(type), isWriteToFile(writeToFile), initialSize(initialSize), step(step), multiplier(multiplier), testNumber(testNumber), maxSize(maxSize) {
    cout << "Starting benchmark:" << endl;
    cout << "\ttype: " << type << endl;
    cout << "\twrite to file: " << writeToFile << endl;
    cout << "\tinitial size: " << initialSize << endl;
    cout << "\tstep: " << step << endl;
    cout << "\tmultiplier: " << multiplier << endl;
    cout << "\ttest number: " << testNumber << endl;
    cout << "\tmax size: " << maxSize << endl;

    performanceCounter = new LARGE_INTEGER;
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(-10000000, 10000000);
    randNumGen = mt;
    calcIterationNumber();
    switch (type) {
        case DynamicDoublyLinkedList_T: {
            testDynamicDoublyLinkedList();
            break;
        }
        case DynamicArray_T: {
            testDynamicArray();
            break;
        }
        case DynamicBinaryHeap_T: {
            testDynamicBinaryHeap();
            break;
        }
        case DynamicRBTree_T: {
            testRBTree();
        }
    }
}

void Benchmark::testDynamicDoublyLinkedList() {
    cout << "Testing doubly linked list (max size: " << maxSize << ", iterations: " << iterationNumber << ", step: " << step << ", multiplier: " << multiplier << ", starting size: " << initialSize << endl;
    Sleep(2000);

    int *sizeArray = new int[iterationNumber];
    auto *resultsArray = new double[iterationNumber];

    int size = initialSize;
    for (int i = 0; i < iterationNumber; i++){
        double avg = 0;
        int* randomSet = new int[size + 1];
        for(int j = 0; j < testNumber; j++){
            auto* dynamicDoublyLinkedList = new DynamicDoublyLinkedList();
            generatePopulation(randomSet, size + 1, numberDistribution);
            for (int k = 0; k < size; k++) dynamicDoublyLinkedList -> backAdd(randomSet[k]);
            startTimer();
            dynamicDoublyLinkedList ->backAdd(randomSet[size]);
            avg += stopTimer();
            delete dynamicDoublyLinkedList;
        }
        delete[] randomSet;
        avg /= testNumber;
        sizeArray[i] = size;
        resultsArray[i] = avg;
        cout << "Dynamic Doubly Linked List back insertion: Done " << i + 1 << " out of " << iterationNumber << " size: " << size << " took " << resultsArray[i] << "us. " << endl;
        size *= multiplier;
        size += step;
    }
    if(isWriteToFile) {
        writeToFile("DOUBLY_LINKED_LIST_INSERT_BACK", resultsArray, sizeArray);
    }

    size = initialSize;
    for(int i = 0; i < iterationNumber; i++){
        double avg = 0;
        int* randomSet = new int[size + 1];
        for (int j = 0; j < testNumber; j++) {
            DynamicDoublyLinkedList *doublyLinkedList;
            doublyLinkedList = new DynamicDoublyLinkedList();
            generatePopulation(randomSet, size+1, numberDistribution);
            for (int k = 0; k < size; k++) doublyLinkedList->frontalAdd(randomSet[k]);
            startTimer();
            doublyLinkedList -> frontalAdd(randomSet[size]);
            avg += stopTimer();
            delete doublyLinkedList;
        }
        delete[] randomSet;
        avg /= testNumber;
        sizeArray[i] = size;
        resultsArray[i] = avg;
        cout << "Doubly linked list front insertion: Done " << i+1 << " out of " << iterationNumber << " size: " << size << " took "
             << resultsArray[i] << "us." << endl;
        size *= multiplier;
        size += step;
    }
    if (isWriteToFile) {
        writeToFile("DOUBLY_LINKED_LIST_INSERT_FRONT", resultsArray, sizeArray);
    }

    size = initialSize;
    for (int i = 0; i < iterationNumber; i++) {
        double avg = 0;
        int* randomSet = new int[size+1];
        for (int j = 0; j < testNumber; j++) {
            auto* doublyLinkedList = new DynamicDoublyLinkedList();
            generatePopulation(randomSet, size+1, numberDistribution);
            for (int k = 0; k < size; k++) {
                doublyLinkedList -> freeAdd(k, randomSet[k]);
            }
            startTimer();
            doublyLinkedList -> freeAdd(size, randomSet[size]);
            avg += stopTimer();
            delete doublyLinkedList;
        }
        delete[] randomSet;
        avg /= testNumber;
        sizeArray[i] = size;
        resultsArray[i] = avg;
        cout << "Doubly linked list at position insertion: Done " << i+1 << " out of " << iterationNumber << " size: " << size << " took "
             << resultsArray[i] << "us." << endl;
        size *= multiplier;
        size += step;
    }
    if (isWriteToFile) {
        writeToFile("DOUBLY_LINKED_LIST_INSERT_INDEX", resultsArray, sizeArray);
    }

    size = initialSize;
    for (int i = 0; i < iterationNumber; i++) {
        double avg = 0;
        int* randomSet = new int[size];
        for (int j = 0; j < testNumber; j++) {
            auto* doublyLinkedList = new DynamicDoublyLinkedList();
            generatePopulation(randomSet, size, numberDistribution);
            for (int k = 0; k < size; k++){
                doublyLinkedList -> backAdd(randomSet[k]);
            }
            shuffle(randomSet, &randomSet[size-1], std::mt19937(std::random_device()()));
            startTimer();
            doublyLinkedList->remove(randomSet[size-1]);
            avg += stopTimer();
            delete doublyLinkedList;
        }
        delete[] randomSet;
        avg /= testNumber;
        sizeArray[i] = size;
        resultsArray[i] = avg;
        cout << "Doubly linked list removal: Done " << i+1 << " out of " << iterationNumber << " size: " << size << " took "
             << resultsArray[i] << "us." << endl;
        size *= multiplier;
        size += step;
    }
    if (isWriteToFile) {
        writeToFile("DOUBLY_LINKED_LIST_REMOVE", resultsArray, sizeArray);
    }

    size = initialSize;
    for (int i = 0; i < iterationNumber; i++) {

        double avg = 0;
        int* randomSet = new int[size];
        for (int j = 0; j < testNumber; j++) {
            auto* doublyLinkedList = new DynamicDoublyLinkedList();
            generatePopulation(randomSet, size, numberDistribution);
            for (int k = 0; k < size; k++){
                doublyLinkedList -> backAdd(randomSet[k]);
            }
            shuffle(randomSet, &randomSet[size-1], std::mt19937(std::random_device()()));
            startTimer();
            doublyLinkedList -> positionOf(randomSet[size-1]);
            avg += stopTimer();
            delete doublyLinkedList;
        }
        delete[] randomSet;
        avg /= testNumber;
        sizeArray[i] = size;
        resultsArray[i] = avg;
        cout << "Doubly linked list at index retrieval: Done " << i+1 << " out of " << iterationNumber << " size: " << size << " took "
             << resultsArray[i] << "us." << endl;
        size *= multiplier;
        size += step;
    }
    if (isWriteToFile) {
        writeToFile("DOUBLY_LINKED_LIST_SEARCH", resultsArray, sizeArray);
    }
    delete[] resultsArray;
    delete[] sizeArray;
}

void Benchmark::testDynamicArray() {
    cout << "Testing dynamic array (max size: " << maxSize << ", iterations: " << iterationNumber << ", step: " << step
         << ", multiplier: " << multiplier << ", starting size: " << initialSize << endl;
    Sleep(2000);

    int *sizeArray = new int[iterationNumber];
    auto *resultsArray = new double[iterationNumber];

    int size = initialSize;
    for (int i = 0; i < iterationNumber; i++) {
        double avg = 0;
        int* randomSet = new int[size+1];
        for (int j = 0; j < testNumber; j++) {
            auto* dynamicArray = new DynamicArray();
            generatePopulation(randomSet, size+1, numberDistribution);
            for (int k = 0; k < size; k++) {
                dynamicArray->backAdd(randomSet[k]);
            }
            startTimer();
            dynamicArray->backAdd(randomSet[size]);
            avg += stopTimer();
            delete dynamicArray;
        }
        delete[] randomSet;
        avg /= testNumber;
        sizeArray[i] = size;
        resultsArray[i] = avg;
        cout << "Dynamic array back insertion: Done " << i+1 << " out of " << iterationNumber << " size: " << size << " took "
             << resultsArray[i] << "us." << endl;
        size *= multiplier;
        size += step;
    }
    if (isWriteToFile) {
        writeToFile("DYNAMIC_ARRAY_INSERT_BACK", resultsArray, sizeArray);
    }

    size = initialSize;
    for (int i = 0; i < iterationNumber; i++) {
        double avg = 0;
        int* randomSet = new int[size+1];
        for (int j = 0; j < testNumber; j++) {
            auto* dynamicArray = new DynamicArray();
            generatePopulation(randomSet, size+1, numberDistribution);
            for (int k = 0; k < size; k++) {
                dynamicArray -> frontalAdd(randomSet[k]);
            }
            startTimer();
            dynamicArray -> frontalAdd(randomSet[size]);
            avg += stopTimer();
            delete dynamicArray;
        }
        delete[] randomSet;
        avg /= testNumber;
        sizeArray[i] = size;
        resultsArray[i] = avg;
        cout << "Dynamic array front insertion: Done " << i+1 << " out of " << iterationNumber << " size: " << size << " took "
             << resultsArray[i] << "us." << endl;
        size *= multiplier;
        size += step;
    }
    if (isWriteToFile) {
        writeToFile("DYNAMIC_ARRAY_INSERT_FRONT", resultsArray, sizeArray);
    }


    size = initialSize;
    for (int i = 0; i < iterationNumber; i++) {
        double avg = 0;
        int* randomSet = new int[size+1];
        for (int j = 0; j < testNumber; j++) {
            auto* dynamicArray = new DynamicArray();
            generatePopulation(randomSet, size+1, numberDistribution);
            for (int k = 0; k < size; k++) {
                dynamicArray -> freeAdd(randomSet[k], k);
            }
            startTimer();
            dynamicArray -> freeAdd(randomSet[size], size);
            avg += stopTimer();
            delete dynamicArray;
        }
        delete[] randomSet;
        avg /= testNumber;
        resultsArray[i] = avg;
        sizeArray[i] = size;
        cout << "Dynamic array at index insertion: Done " << i+1 << " out of " << iterationNumber << " size: " << size << " took "
             << resultsArray[i] << "us." << endl;
        size *= multiplier;
        size += step;
    }
    if (isWriteToFile) {
        writeToFile("DYNAMIC_ARRAY_INSERT_INDEX", resultsArray, sizeArray);
    }

    size = initialSize;
    for (int i = 0; i < iterationNumber; i++) {
        double avg = 0;
        int* randomSet = new int[size];
        for (int j = 0; j < testNumber; j++) {
            auto* dynamicArray = new DynamicArray();
            generatePopulation(randomSet, size, numberDistribution);
            for (int k = 0; k < size; k++){
                dynamicArray -> backAdd(randomSet[k]);
            }
            shuffle(randomSet, &randomSet[size-1], std::mt19937(std::random_device()()));
            startTimer();
            dynamicArray -> freeRemove(randomSet[size-1]);
            avg += stopTimer();
            delete dynamicArray;
        }
        delete[] randomSet;
        avg /= testNumber;
        sizeArray[i] = size;
        resultsArray[i] = avg;
        cout << "Dynamic array removal: Done " << i+1 << " out of " << iterationNumber << " size: " << size << " took "
             << resultsArray[i] << "us." << endl;
        size *= multiplier;
        size += step;
    }
    if (isWriteToFile) {
        writeToFile("DYNAMIC_ARRAY_REMOVE", resultsArray, sizeArray);
    }
    delete[] resultsArray;
    delete[] sizeArray;
}

void Benchmark::testDynamicBinaryHeap() {
    cout << "Testing Heap (max size: " << maxSize << ", iterations: " << iterationNumber << ", step: " << step
         << ", multiplier: " << multiplier << ", starting size: " << initialSize << endl;
    Sleep(2000);
    //Test adding
    int *sizeArray = new int[iterationNumber];
    auto *resultsArray = new double[iterationNumber];
    //Adding benchmark
    int size = initialSize;
    for (int i = 0; i < iterationNumber; i++) {
        double avg = 0;
        int* randomSet = new int[size+1];
        for (int j = 0; j < testNumber; j++) {
            auto* heap = new DynamicBinaryHeap();
            generatePopulation(randomSet, size+1, numberDistribution);
            for (int k = 0; k < size; k++) {
                heap->add(randomSet[k]);
            }
            startTimer();
            heap->add(randomSet[size]);
            avg += stopTimer();
            delete heap;
        }
        delete[] randomSet;
        avg /= testNumber;
        sizeArray[i] = size;
        resultsArray[i] = avg;
        cout << "Heap insertion: Done " << i+1 << " out of " << iterationNumber << " size: " << size << " took "
             << resultsArray[i] << "us." << endl;
        size *= multiplier;
        size += step;
    }
    if (isWriteToFile) {
        writeToFile("HEAP_ADD", resultsArray, sizeArray);
    }

    // Remove
    size = initialSize;
    for (int i = 0; i < iterationNumber; i++) {
        double avg = 0;
        int* randomSet = new int[size+1];
        for (int j = 0; j < testNumber; j++) {
            auto* heap = new DynamicBinaryHeap();
            generatePopulation(randomSet, size+1, numberDistribution);
            for (int k = 0; k < size; k++){
                heap->add(randomSet[k]);
            }
            startTimer();
            heap-> remove();
            avg += stopTimer();
            delete heap;
        }
        delete[] randomSet;
        avg /= testNumber;
        sizeArray[i] = size;
        resultsArray[i] = avg;
        cout << "Heap removal: Done " << i+1 << " out of " << iterationNumber << " size: " << size << " took "
             << resultsArray[i] << "us." << endl;
        size *= multiplier;
        size += step;
    }
    if (isWriteToFile) {
        writeToFile("HEAP_REMOVE", resultsArray, sizeArray);
    }
    delete[] resultsArray;
    delete[] sizeArray;
}

void Benchmark::testRBTree() {
    cout << "Testing RBTree (max size: " << maxSize << ", iterations: " << iterationNumber << ", step: " << step << ", multiplier: " << multiplier << ", starting size: " << initialSize << endl;
    Sleep(2000);

    int *sizeArray = new int[iterationNumber];
    auto *resultsArray = new double[iterationNumber];
    // Adding
    int size = initialSize;
    for(int i = 0; i < iterationNumber; i++){
        double avg = 0;
        int* randomSet = new int[size + 1];
        for(int j = 0; j < testNumber; j++){
            auto* rbTree = new DynamicRBTree();
            generatePopulation(randomSet, size + 1, numberDistribution);
            for(int k = 0; k < size; k++){
                rbTree -> add(randomSet[k]);
            }
            startTimer();
            rbTree -> add(randomSet[size]);
            avg += stopTimer();
            delete rbTree;
        }
        delete[] randomSet;
        avg /= testNumber;
        sizeArray[i] = size;
        resultsArray[i] = avg;
        cout << "RBTree insertion: Done " << i+1 << " out of " << iterationNumber << " size: " << size << " took " << resultsArray[i] << "us. " << endl;
        size *= multiplier;
        size += step;
    }
    if(isWriteToFile){
        writeToFile("RB_TREE_ADD", resultsArray, sizeArray);
    }
    // Searching
    size = initialSize;
    for(int i = 0; i < iterationNumber; i++){
        // Sizes
        double avg = 0;
        int* randomSet = new int[size];
        for(int j = 0; j < testNumber; j++){
            auto* rbTree = new DynamicRBTree();
            generatePopulation(randomSet, size, numberDistribution);
            for(int k = 0; k < size; k++){
                rbTree -> add(randomSet[k]);
            }
            shuffle(randomSet, &randomSet[size - 1], mt19937(random_device()()));
            startTimer();
            rbTree -> search(randomSet[size - 1]);
            avg += stopTimer();
            delete rbTree;
        }
        delete[] randomSet;
        avg /= testNumber;
        sizeArray[i] = size;
        resultsArray[i] = avg;
        cout << "RBTree search: Done " << i + 1 << " out of " << iterationNumber << " size: " << size << " took " << resultsArray[i] << "us. " << endl;
        size *= multiplier;
        size += step;
    }
    if(isWriteToFile){
        writeToFile("RB_TREE_SEARCH", resultsArray, sizeArray);
    }
    // Removing
    size = initialSize;
    for (int i = 0; i < iterationNumber; i++) {
        // Sizes
        double avg = 0;
        int* randomSet = new int[size];
        for (int j = 0; j < testNumber; j++) {
            auto* rbTree = new DynamicRBTree();
            generatePopulation(randomSet, size, numberDistribution);
            for (int k = 0; k < size; k++) {
                rbTree->add(randomSet[k]);
            }
            shuffle(randomSet, &randomSet[size-1], std::mt19937(std::random_device()()));
            startTimer();
            rbTree-> remove(randomSet[size-1]);
            avg += stopTimer();
            delete rbTree;
        }
        delete[] randomSet;
        avg /= testNumber;
        sizeArray[i] = size;
        resultsArray[i] = avg;
        cout << "RB tree deletion: Done " << i+1 << " out of " << iterationNumber << " size: " << size << " took "
             << resultsArray[i] << "us." << endl;
        size *= multiplier;
        size += step;
    }
    if (isWriteToFile) {
        writeToFile("RB_TREE_REMOVE", resultsArray, sizeArray);
    }
    delete[] resultsArray;
    delete[] sizeArray;
}

void Benchmark::calcIterationNumber() {
    int size = initialSize;

    int itNumber = 0;

    while (size < maxSize) {
        size *= multiplier;
        size += step;
        itNumber++;
    }
    if (size > maxSize) itNumber--;
    this->iterationNumber = itNumber;
}

void Benchmark::writeToFile(string testName, const double *data, const int *size) const {
    auto **toWrite = new double *[2];
    toWrite[0] = new double[iterationNumber];
    toWrite[1] = new double[iterationNumber];

    for (int i = 0; i < iterationNumber; i++) {
        toWrite[0][i] = size[i];
        toWrite[1][i] = data[i];
    }
    string headers[2];
    headers[0] = "Struct size";
    headers[1] = "Time [us]";
    CSVWriter writer(testName.append(".csv"), iterationNumber, 2, headers, toWrite);

}

int Benchmark::getNextRandom(uniform_int_distribution<int>& dist) {
    return dist(randNumGen);
}

void Benchmark::generatePopulation(int *dataSet, int size, uniform_int_distribution<int> dist) {
    for (int i = 0; i < size; i++) {
        dataSet[i] = getNextRandom(dist);
    }
}

void Benchmark::startTimer() {
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    *performanceCounter = count;
}

double Benchmark::stopTimer() {
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    uint64_t elapsed = count.QuadPart - (*performanceCounter).QuadPart;
    double timeInNs;
    timeInNs = 1000000.0 * elapsed / freq.QuadPart;
    return timeInNs;

}

uniform_int_distribution<int> Benchmark::getRandomInRange(int a, int b) {
    uniform_int_distribution<int> dist(a, b);
    return dist;
}
