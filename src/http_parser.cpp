#include <string>
#include <vector>
#include <iostream>

#include "http_parser.h"

std::vector<std::string> split(std::string& message, std::string separator)
{
    std::vector<std::string> split;
    std::string mutable_message = message;
    
    int index = mutable_message.find(separator);

    while(index != std::string::npos)
    {
        split.push_back(mutable_message.substr(0, index));
        mutable_message.erase(0, index + separator.size());

        index = mutable_message.find(separator);
    }

    if (mutable_message.size() > 0)
    {
        split.push_back(mutable_message);
    }

    return split;
}

Http parse(std::string& message)
{
    Http http;

    std::vector<std::string> array = split(message, "\r\n");
    
    for (int i = 0; i < array.size(); i++)
    {
        if (i == 0)
        {
            std::vector<std::string> request_line = split(array[i], " ");

            http.map["path"] = request_line[1];
            http.map["http_version"] = request_line[2];
        }
        else
        {
            std::string colon_space = ": ";
            int index = array[i].find(colon_space);
            
            if (index != std::string::npos)
            {
                http.map[array[i].substr(0, index)] = array[i].substr(index + colon_space.size(), array.size() - index);
            }            
        }
    }

    return http;
}

std::string Http::get(std::string header)
{
    return map[header];
}