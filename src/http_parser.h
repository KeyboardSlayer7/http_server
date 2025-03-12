#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

#include <vector>
#include <string>
#include <unordered_map>

struct Http
{
    std::unordered_map<std::string, std::string> map;

    std::string get(std::string header);
};

std::vector<std::string> split(std::string& message, std::string separator);

Http parse(std::string& message);
// std::string createResponse(Http& http, std::vector<char>& content);

#endif