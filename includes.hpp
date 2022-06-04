#include <curl/curl.h>
#include </home/nex0rus/Code/json/single_include/nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <future>
#include <atomic>
#include <cstdlib>

typedef const nlohmann::detail::iter_impl<nlohmann::json> json_iterator;

namespace helpfunc 
{
    void upper(char & c);
    bool check_for_valute(const nlohmann::json & set, const std::string & valute);
    nlohmann::basic_json<> to_data_set(const nlohmann::json & res);
}