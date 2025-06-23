#ifndef CONVERSATION_HPP
#define CONVERSATION_HPP

#include <vector>
#include "message.hpp"

class Conversation {
private:
    std::vector<Message> convoHistory;

public:
    void addMessage(const std::string &role, const std::string &content);
    void clearHistory();
    const std::vector<Message>& getHistory();
    bool emptyCheck() const;
};

#endif
