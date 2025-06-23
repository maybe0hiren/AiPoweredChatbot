#ifndef HTTP_CLIENT_HPP
#define HTTP_CLIENT_HPP

#include <vector>
#include "message.hpp"

class HttpClient{
    public:
        std::string interact(const std::vector <Message> &convoHistory);
};

#endif 