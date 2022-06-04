
#include "includes.hpp"

void helpfunc::upper(char & c) 
{
    c = toupper(c);
}

bool helpfunc::check_for_valute(const nlohmann::json & set, const std::string & valute)
{   
    auto it = set.begin();
    while (it != set.end() && valute != "")
    { 
        
        if (valute == (*it)["CharCode"]) 
        {
            return true;
        }
        it++;

    } 
    return false;
}

nlohmann::basic_json<> helpfunc::to_data_set(const nlohmann::json & res) 
{
    auto it = res.begin();
    for (int i = 0; i < 4; i++) 
    {
        it++;
    }
    return (*it);
}