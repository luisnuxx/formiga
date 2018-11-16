//
// Created by Luis Rodrigues on 25/02/2018.
//

#ifndef FORMIGA_CONFIG_HPP
#define FORMIGA_CONFIG_HPP
#include <boost/iostreams/device/mapped_file.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace boost::iostreams;
using json = nlohmann::json;

class Config {

    private:
        json cfg;
        std::string filename = "./config/settings.json";
    public:
        Config();
        Config(std::string filename);
        std::string loadFromFile();
        json get();
        virtual ~Config() {
            std::cout << "Destructor called:: ~Config" << std::endl;
        }
};
Config::Config() {
    cfg = json::parse(this->loadFromFile());
}

Config::Config(std::string filename) {
    this->filename = filename;
    cfg = json::parse(this->loadFromFile());
}


std::string Config::loadFromFile() {
    //Initialize the memory-mapped file
    mapped_file_source file(this->filename);
    //Read the entire file into a string
    std::string fileContent(file.data(), file.size());
    //Print the string
    std::cout << fileContent;
    //Cleanup
    file.close();
    return fileContent;
}

json Config::get() {
    return cfg;
}
#endif //FORMIGA_CONFIG_HPP


//Compile like this: g++ -o mmap mmap.cpp -lboost_iostreams


