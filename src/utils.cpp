#include <string>
#include <fstream>
#include <iostream>

#include "utils.h"

Body get_content(const char* filename)
{
    Body output;
    
    std::ifstream file = std::ifstream(filename, std::ios::binary | std::ios::in);

    file.seekg(0, file.end);
    int size = file.tellg();
    file.seekg(0, file.beg);
    
    output.contents = new char[size + 1];

    file.read(output.contents, size);
    output.contents[size] = '\0';

    output.size = size;

    file.close();
        
    return output;
}
