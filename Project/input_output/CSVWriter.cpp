//
// Created by Ponanoix on 23.04.2023.
//

#include "../../Sdizo/input_output/CSVWriter.h"

CSVWriter::CSVWriter(std::string fileName, int dataSize, int columnWidth, std::string *headers, double **data) :fileName(fileName), dataSize(dataSize),
                                                                                                                columnWidth(columnWidth), headers(headers), data(data), stream(fileName) {
    writeData();
}

void CSVWriter::writeData() {
    for(int i = 0; i < columnWidth; i++){
        stream << headers[i];
        if(i+1 < columnWidth) stream << ",";
    }
    stream << std::endl;
    for(int i = 0; i < dataSize; i++){
        for (int j = 0; j < columnWidth; j++){
            stream << data[j][i];
            if (j+1 < columnWidth) stream << ",";
        }
        stream << std::endl;
    }
}
