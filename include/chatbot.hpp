#ifndef CHATBOT_HPP
#define CHATBOT_HPP

#include<string>
#include "message.hpp"
#include "conversation.hpp"
#include "http_client.hpp"
#include "storage.hpp"


class Chatbot{
    public:
        Chatbot();
        void start();
    private:
        Conversation convo;
        HttpClient cli;
        Storage store;

        void inputProcessing(const std::string &input);
        void commandProcessing(const std::string &command);
        void messageProcessing(const std::string &message);
};

#endif