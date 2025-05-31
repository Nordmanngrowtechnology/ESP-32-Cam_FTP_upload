//
// Created by Asie on 05.04.2025.
//

#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <fstream>

void parseConfigFile(FILENAME, const char *path){
  std::ifstream file(FILENAME.path);
if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
        // using printf() in all tests for consistency
        printf("%s", line.c_str());
    }
    file.close();
}
else{
  std::cout << "Error opening file";
}

};

#endif //CONFIGFILE_H


