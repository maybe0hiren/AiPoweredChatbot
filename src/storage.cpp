#include "storage.hpp"
#include "nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

const std::string permanentDataFile = "saved/savedData.json";

void Storage::save(const std::vector <Message> &convoHistory){
    json j;
    for (const auto &msg : convoHistory){
        j.push_back({{"role", msg.role}, {"content", msg.content}});
    }

    std::ofstream outFile(permanentDataFile);
    if (outFile.is_open()){
        outFile << j.dump(4);
    }
}

std::vector <Message> Storage::load(){
    std::vector <Message> convoHistory;
    std::ifstream inFile(permanentDataFile);

    if(!inFile.is_open()){
        return convoHistory;
    }
    try{
        json j;
        inFile >> j;
        
        for (const auto &item : j){
            if (item.contains("role") && item.contains("content")){
                convoHistory.push_back({item["role"], item["content"]});
            }
        }
    }
    catch(...){

    }
    return convoHistory;
}

void Storage::clear(){
    std::ofstream outFile(permanentDataFile, std::ios::trunc);
    if (outFile.is_open()){
        outFile << "[]";
    }
}