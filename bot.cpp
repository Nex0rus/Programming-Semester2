#ifndef MAIN_CPP_
#define MAIN_CPP_
#define CURL_STATICLIB
#include <iostream>
#include <cstring>
#include <random>
#include "tgbot/tgbot.h"
#include "parser.hpp"
#include "valute.hpp"
#include <thread>
#include <sstream>

int parse(Parser & p) 
{   
    while (true) 
    {   
        p.perform();
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    return 1;
}


static Parser p("https://www.cbr-xml-daily.ru/daily_json.js");


void bot_start() 
{   
    std::stringstream s;
    std::ifstream f("token.txt");
    std::string token;
    f >> token;
    TgBot::Bot bot(token);
    f.close();
    std::string valute = "";

    auto data_wrapper = [&bot, &s, &valute](TgBot::Message::Ptr message) 
    {   
        auto res = p.get_data();
        res_to_string(res, s, valute);
        std::string output(s.str());
        bot.getApi().sendMessage(message->chat->id, output);
        valute = "";
        s.str("");
    };

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) 
    {
        bot.getApi().sendMessage(message->chat->id, "Добро пожаловать! Курсы, валюты, информация? Это все твое друг мой!\nВот что может бот:\n/currencies - Выводит список валют с базовой информацией, названий нет, если нужно получить информацию по конкретной валюте, используй\n/show <валюта> - более конкретная информация.\n/get_file <название> - кинет файлик с той же информацией но с разделителями по запятой формата csv");
        bot.getApi().sendAnimation(message->chat->id, TgBot::InputFile::fromFile("morshu.gif", "image/gif"));
    });

    bot.getEvents().onCommand("currencies", [&bot, &s, &valute, &data_wrapper](TgBot::Message::Ptr message) {
        data_wrapper(message);
    });

    bot.getEvents().onCommand("show", [&bot, &s, &valute, &data_wrapper](TgBot::Message::Ptr message) {
        std::string arg(message->text);
        auto it = std::find(arg.begin(), arg.end(), ' ');
        if (it != arg.end() ) 
        {   
            ++it;
            auto temp = it + 3;
            valute = std::string(it, temp);
            data_wrapper(message);        
        }
        else 
        {
            bot.getApi().sendMessage(message->chat->id, "Такой валюты у меня нет, поищи что-нибудь другое\n");
        }
    
    });
    bot.getEvents().onCommand("get_file", [&bot](TgBot::Message::Ptr message) 
    {   
        std::ofstream file;
        std::string arg(message->text);
        std::string file_name;
        std::string format(".csv");
        auto it = std::find(arg.begin(), arg.end(), ' ');
        if (it != arg.end()) 
        {   
            arg = std::move( std::string(++it, arg.end()) );
            auto format_pos = arg.find(format);
            if (format_pos == std::string::npos) 
            {
                bot.getApi().sendMessage(message->chat->id, "Ты хочешь получить файл, но не указываешь расширение, просто ошибся или пытаешься испортить логику программы?\n");
                return;
            }
            format_pos += 4;
            file_name = std::move(std::string(arg.begin(), arg.begin() + format_pos));
            file.open(file_name);
        }

        else 
        {   file_name = "cringe.csv";
            file.open("cringe.csv");
        }
        auto res = p.get_data();
        res_to_csv(res, file);
        file.flush();
        file.close();
        std::cout << file_name << std::endl;
        bot.getApi().sendDocument(message->chat->id, TgBot::InputFile::fromFile(file_name, "text/csv"));
        remove(file_name.c_str());
    });

    try {
        auto temp = bot.getEventHandler();
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }

    } 
    catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
}


int main()
{   
    auto b_parse = std::async(std::launch::async, bot_start);
    auto f_parse = std::async(std::launch::async, parse, std::ref(p));
    return 0;
}



#endif