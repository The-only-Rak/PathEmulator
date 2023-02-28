#include "path.hpp"
#include "rapidjson/rapidjson.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <sstream>
#include <vector>
using namespace rapidjson;

/**
 * It takes a string, opens a file with that string, and parses the file into a JSON document
 *
 * @param file The file to open.
 */
Path::Path(std::string_view file, std::ostream &logger) : log(logger)
{
    str = file;
    std::ifstream ifs(str);
    IStreamWrapper isw(ifs);
    doc.ParseStream(isw);
}

void Path::Add(std::string_view name, const std::vector<std::string> &vals)
{
    Value val(kArrayType);
    auto &alloc = doc.GetAllocator();
    if (doc.FindMember(name.data()) == doc.MemberEnd())
    {
        for (auto &i : vals)
        {
            val.PushBack(Value().SetString(i.c_str(), i.size()), alloc);
        }
        doc.AddMember(StringRef(name.data()), val, alloc);
    }
    else
    {
        throw path_value_allready_exist();
    }
}

void Path::Remove(std::string_view name, const std::vector<std::string> &vals = std::vector<std::string>())
{
    if (vals.empty())
    {
        doc.RemoveMember(StringRef(name.data()));
    }
    else
    {
        for (auto &elem : vals)
        {
            auto arr = doc[name.data()].GetArray();
            arr.Erase(std::find(arr.begin(), arr.end(), elem.data()));
        }
    }
}

void Path::Append(std::string_view name, const std::vector<std::string> &vals)
{
    auto arr = doc[name.data()].GetArray();
    auto &alloc = doc.GetAllocator();
    for (auto &i : vals)
    {
        arr.PushBack(Value().SetString(i.c_str(), i.size()), alloc);
    }
}

void Path::Get(std::string_view name)
{
    if (name.empty())
    {
        for (auto i = doc.MemberBegin(); i != doc.MemberEnd(); ++i)
        {
            auto tmp = i->value.GetArray();
            log << i->name.GetString() << ":";
            for (auto &i : tmp)
            {
                log << ' ' << i.GetString();
            }
        }
    }
    else
    {
        auto arr = doc[name.data()].GetArray();
        for (auto &i : arr)
        {
            std::cout << ' ' << i.GetString();
        }
    }
}

void Path::Set(std::string_view name, const std::vector<std::string> &vals)
{
    Remove(name);
    Add(name, vals);
}

void Path::Change(std::string_view name, std::string_view old_val, std::string_view new_val)
{
    std::vector<std::string> tmp{new_val.data()};
    Remove(name, {old_val.data()});
    Append(name, tmp);
}

Path::~Path()
{
    std::ofstream ofs(str);
    OStreamWrapper osw(ofs);
    Writer<OStreamWrapper> writer(osw);
    doc.Accept(writer);
}

const char *path_value_allready_exist::what() const noexcept
{
    return "Path variable exist already";
}
