#include "includes.hpp"

class Parser 
{
private:
    std::string href_;
    std::string json_;
    CURL * curl_;
    std::mutex json_mutex;
    typedef std::chrono::system_clock clock;

public:
    explicit Parser(const std::string & s) 
    {
        href_ = s;
    }
    int perform();
    void set_curl();
    friend size_t write_callback(char* ptr, size_t size, size_t nmemb, Parser* p);
    nlohmann::json get_data();
    friend int parse(Parser & p);
    ~Parser() 
    {
        curl_easy_cleanup(curl_);
        curl_global_cleanup();
    }


};

std::stringstream & res_to_string(const nlohmann::json & res, std::stringstream & sstream, std::string valute);
std::ofstream & res_to_csv(const nlohmann::json & res, std::ofstream & csv);