#include "parser.hpp"
#include "valute.hpp"

size_t cb(char* ptr, size_t size, size_t nmemb, std::string* str) 
{   
    str->append(ptr);
    return nmemb;
} 

void Parser::set_curl() 
{   
    curl_ = curl_easy_init();
    curl_easy_setopt(curl_, CURLOPT_URL, href_.c_str());
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, cb);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &json_);
}

nlohmann::json Parser::get_data() 
{   
    std::lock_guard<std::mutex> data_guard(json_mutex);
    nlohmann::json res = nlohmann::json::parse(json_);
    return res;
}

int Parser::perform() 
{   
    std::lock_guard<std::mutex> perform_guard(json_mutex);
    json_.clear();
    set_curl();
    curl_easy_perform(curl_);
    return 1;
}


std::stringstream & res_to_string(const nlohmann::json & res, std::stringstream & sstream, std::string valute) 
{   
    for_each(valute.begin(), valute.end(), helpfunc::upper);
    auto data_set = helpfunc::to_data_set(res);
    if (valute != "" && helpfunc::check_for_valute(data_set, valute) == false)
    {
        sstream << "Не существует валюты " << valute << ", Может поищешь что-нибудь другое?\n";
        return sstream;
    } 

    sstream << "Код    #  Тек. цена  " << std::setw(5) << std::right << " #  Пред. цена  #" << std::endl << std::endl; 
    auto it1 = data_set.begin();
    for (it1; it1 != data_set.end(); it1++) 
    {   
        std::string code((*it1)["CharCode"]);
        if ( (code == valute) || valute == "" ) 
        {   
            Valute v(it1, valute);
            sstream << v;
        }
    }

    return sstream;

}

std::ofstream & res_to_csv(const nlohmann::json & res, std::ofstream & csv) 
{
    csv << "Code,Current price,Previous price,Delta\n";
    auto data_set = helpfunc::to_data_set(res);
    for (auto it = data_set.begin(); it != data_set.end(); it++) 
    {
        Valute v(it, "");
        csv << v;
    }

    return csv;
}