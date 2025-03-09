#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "utils.h"

std::vector<char> get_content(const char* filename)
{
    std::vector<char> output;
    
    std::ifstream file = std::ifstream(filename, std::ios::binary | std::ios::in);

    file.seekg(0, file.end);
    int size = file.tellg();
    file.seekg(0, file.beg);
    
    // output.contents = new char[size + 1];
    output.resize(size + 1); 

    file.read(output.data(), size);
    output[size] = '\0';

    // output.size = size;

    file.close();
        
    return output;
}
