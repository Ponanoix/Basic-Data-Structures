//
// Created by Ponanoix on 23.04.2023.
//

#ifndef SDIZO_CSVWRITER_H
#define SDIZO_CSVWRITER_H

#include<fstream>
#include "../../Sdizo/header_files/DynamicArray.h"

class CSVWriter{
private:
    const std::string fileName;

    int dataSize;

    int columnWidth;

    double** data;

    std::string * headers;

    std::ofstream stream;

    void writeData();
public:
    CSVWriter(std::string fileName, int dataSize, int columnWidth, std::string* headers, double** data);
};

#endif //SDIZO_CSVWRITER_H
