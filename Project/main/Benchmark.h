//
// Created by Ponanoix on 23.04.2023.
//

#ifndef SDIZO_BENCHMARK_H
#define SDIZO_BENCHMARK_H

#include "../../Sdizo/header_files/DynamicDoublyLinkedList.h"
#include "../../Sdizo/header_files/DynamicArray.h"
#include "../../Sdizo/header_files/DynamicBinaryHeap.h"
#include "../../Sdizo/header_files/DynamicRBTree.h"
#include "../../Sdizo/main/StructureType.h"
#include <windows.h>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

/*
 * The following class is used to benchmark given data structure and write output to stdout and CSV file.
 */

class Benchmark{
private:
    StructureType type;

    LARGE_INTEGER* performanceCounter;

    std::mt19937 randNumGen;

    std::uniform_int_distribution<int> numberDistribution;

    int testNumber;

    int initialSize;

    int step;

    int multiplier;

    int maxSize;

    int iterationNumber{};

    void testDynamicDoublyLinkedList();

    void testDynamicArray();

    void testDynamicBinaryHeap();

    void testRBTree();

    void generatePopulation(int* dataSet, int size, std::uniform_int_distribution<int> dist);

    bool isWriteToFile;

    void startTimer();

    double stopTimer();

    void calcIterationNumber();

    void writeToFile(std::string testName, const double *data, const int *size) const;

    int getNextRandom(std::uniform_int_distribution<int>& dist);

    static std::uniform_int_distribution<int> getRandomInRange(int a, int b);
public:
    explicit Benchmark(StructureType type, bool writeToFile, int initialSize, int step, float multiplier, int testNumber, int maxSize);
};

#endif //SDIZO_BENCHMARK_H
