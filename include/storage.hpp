#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <string>
#include <vector>
#include "message.hpp"

class Storage{
    public:
        void save(const std::vector <Message> &convoHistory);
        std::vector <Message> load();
        void clear();
};

#endif