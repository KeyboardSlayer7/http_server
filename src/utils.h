#ifndef UTILS_H
#define UTILS_H

#include <string>

struct Body
{
    int size = 0;
    char* contents;
};

Body get_content(const char* filename);

#endif 