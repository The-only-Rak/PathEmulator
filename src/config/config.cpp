#include "config.hpp"
#include <filesystem>
#include <fstream>
#include <rapidjson/document.h>
Config::Config(std::string_view str)
{
    rapidjson::Document file;
    file.Parse(str.data());
    _default_file_name = file["default file name"].GetString();
    if (!std::filesystem::exists(_default_file_name))
    {
        std::ofstream ofs(_default_file_name.data());
        ofs.write("{}", 2);
        ofs.close();
    }
}

std::string_view Config::path_file_name()
{
    return _default_file_name;
}

Config::~Config()
{
}
