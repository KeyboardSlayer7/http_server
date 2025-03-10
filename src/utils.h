#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

#define BACKLOG 1
#define DEFAULT_BUFFER_LENGTH 8192

std::vector<char> get_content(const char* filename);

#endif 