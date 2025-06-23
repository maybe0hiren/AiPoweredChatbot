#include "chatbot.hpp"
#include <iostream>


Chatbot::Chatbot(){

}

void Chatbot::start(){
    std::cout << "Jokshumadhini Initiated....(type '/exit' to quit, '/save' to store this conversation)";

    std::vector <Message> convoHistory = store.load();
    for (const auto &msg : convoHistory){
        convo.addMessage(msg.role, msg.content);
    }

    while (true){
        std::cout << "\nHiren: ";
        std::string userInput;
        std::getline(std::cin, userInput);

        if (userInput == "/exit"){
            std::cout << "Bye....\n";
            break;
        }
        else if (userInput == "/save"){
            store.save(convo.getHistory());
            std::cout << "Conversation saved....";
            continue;
        }

        convo.addMessage("user", userInput);
        std::string aiResponse = cli.interact(convo.getHistory());
        convo.addMessage("assistant", aiResponse);
        std::cout << "\nJokshumadhini: " << aiResponse;
    }
}