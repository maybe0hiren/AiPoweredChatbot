#include "conversation.hpp"

void Conversation::addMessage(const std::string &role, const std::string &content){
    convoHistory.push_back({role, content});
}

void Conversation::clearHistory(){
    convoHistory.clear();
}

const std::vector <Message> &Conversation::getHistory(){
    return convoHistory;
}

bool Conversation::emptyCheck() const{
    return convoHistory.empty();
}