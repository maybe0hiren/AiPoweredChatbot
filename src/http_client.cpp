#include "http_client.hpp"
#include "nlohmann/json.hpp"
#include <iostream>
#include <curl/curl.h>
#include <sstream>
#include <iostream>

using json = nlohmann::json;

static size_t writeCallback(void* contents, size_t size, size_t elements, std::string* output) {
    size_t bytes = size * elements;
    output->append(static_cast<char*>(contents), bytes);
    return bytes;
}

std::string HttpClient::interact(const std::vector <Message> &convoHistory){

    json jsonTask;
    jsonTask["model"] = "llama3";

    for (const auto &msg : convoHistory){
        jsonTask["messages"].push_back({{"role", msg.role}, {"content", msg.content}});
    }
    std::string rawString4Llama = jsonTask.dump();
    std::string rawLlamaResponse;

    CURL* curl = curl_easy_init();
    if (!curl) {
        return "Error: Failed to initialize CURL.";
    }

    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:11434/api/chat"); //Tells libcurl where to send the HTTP request.
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, rawString4Llama.c_str()); //requestBody is a std::string containing JSON (like: {"model":"llama3", "messages":[...]}).

    // tell the server that you're sending JSON data.
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);



    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback); //When you get a response, send each chunk to writeCallback()
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rawLlamaResponse); //Pass in &rawLlamaResponse as the destination to collect it

    CURLcode res = curl_easy_perform(curl); //Sends your JSON to Ollama....Returns CURLE_OK on success, or an error code otherwise.
    //cleanup
    curl_slist_free_all(headers); //Frees up memory used by the header list.
    curl_easy_cleanup(curl); //Cleans up the CURL handle (avoids memory leaks).

    //Error Handeling
    if (res != CURLE_OK) {
        return "Error: Failed to send request to Ollama.";
    }
    std::istringstream stream(rawLlamaResponse);
    std::string line;
    std::string fullReply;
    while(std::getline(stream, line)){
        try {
            // auto responseJson = json::parse(rawLlamaResponse);
            // return responseJson["message"]["content"];
            auto lineJson = json::parse(line);
            if (lineJson.contains("message") && lineJson["message"].contains("content")){
                fullReply += lineJson["message"]["content"].get<std::string>();
            }
        } catch (...) {

        }
    }
    return fullReply.empty() ? "Error: Could not parse reply." : fullReply;
}