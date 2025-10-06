#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

size_t WriteCallback(void* contents, const size_t size, const size_t nmemb, std::string* output) {
    const size_t totalSize = size * nmemb;
    output->append(static_cast<char *>(contents), totalSize);
    return totalSize;
}

int main() {
    const std::string apiKey = "9ff0c523-4d02-4bd0-9a03-91c44aa2bcf2";
    const std::string url = "https://pro-api.coinmarketcap.com/v1/cryptocurrency/quotes/latest?id=1&convert=UAH";
    const std::string byc_url = "https://pro-api.coinmarketcap.com/v1/blockchain/statistics/latest";

    curl_global_init(CURL_GLOBAL_DEFAULT);
    if(CURL* curl = curl_easy_init()) {
        curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, ("X-CMC_PRO_API_KEY: " + apiKey).c_str());
        headers = curl_slist_append(headers, "Accept: application/json");

        std::string readBuffer;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        if (const CURLcode res = curl_easy_perform(curl); res != CURLE_OK) {
            std::cerr << "Ошибка curl (quotes): " << curl_easy_strerror(res) << std::endl;
        } else {
            try {
                json j = json::parse(readBuffer);
                auto quotes = j["data"]["1"]["quote"];
                std::cout << "Курс Bitcoin (BTC):\n";
                std::cout << "UAH: " << quotes["UAH"]["price"] << "\n";
            } catch (std::exception& e) {
                std::cerr << "Ошибка парсинга JSON (quotes): " << e.what() << std::endl;
            }
        }

        readBuffer.clear();

        curl_easy_setopt(curl, CURLOPT_URL, byc_url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        if (CURLcode res = curl_easy_perform(curl); res != CURLE_OK) {
            std::cerr << "Ошибка curl (blockchain stats): " << curl_easy_strerror(res) << std::endl;
        } else {
            try {
                json j2 = json::parse(readBuffer);
                std::cout << "\nБлокчейн статистика:\n";
                std::cout << j2.dump(2) << "\n";
            } catch (std::exception& e) {
                std::cerr << "Ошибка парсинга JSON (blockchain): " << e.what() << std::endl;
            }
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return 0;
}
