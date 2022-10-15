#include <curl/curl.h>
#include <json/json.h>
#include <iostream>
#include "http.h"

namespace ServerConnection {
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
    {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }
	std::string getIp(std::string url) {
        CURL* curl;
        CURLcode res;
        std::string string_buffer;
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &string_buffer);
            res = curl_easy_perform(curl);

            curl_easy_cleanup(curl);
        }

        Json::Value root;
        Json::Reader reader;

        bool parsed = reader.parse(string_buffer.c_str(), root);

        std::string ip = root["ip"].asString();

        return ip;
	}
}