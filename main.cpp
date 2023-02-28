#include <config.hpp>
#include <cxxopts.hpp>
#include <exception>
#include <iostream>
#include <path.hpp>
#include <string>
#include <vector>
int main(int argc, char **argv)
{
    Config cfg("{\"default file name\": \"path\"}");
    Path path(cfg.path_file_name(), std::cout);
    cxxopts::Options opts("Path emulator", "Emulate the path of win os");
    opts.add_options()("a,add", "add new variable at path,only unique name")(
        "r,remove", "remove variable from path or values from variable if it not empty")("s,set", "set path variable")(
        "g,get", "get all variable if not name,or all values from variable")("p,append", "add new values to variable")(
        "c,change", "change value of varible")("n,name", "name of path variable",
                                               cxxopts::value<std::string>()->default_value(""))(
        "v,value", "value of path variable",
        cxxopts::value<std::vector<std::string>>()->default_value(""))("h,help", "help command");
    // opts.parse_positional({"command", "name", "value"});
    auto res = opts.parse(argc, argv);
    {
        if (res["h"].count())
        {
            std::cout << opts.help();
        }
        if (res["a"].count())
        {
            try
            {
                path.Add(res["name"].as<std::string>(), res["v"].as<std::vector<std::string>>());
            }
            catch (const path_value_allready_exist &ex)
            {
                std::cout << "Value already exist,try another name";
            }
            catch (const cxxopts::exceptions::option_has_no_value &ex)
            {
                std::cout << "";
            }
        }
        if (res["s"].count())
        {
            path.Set(res["name"].as<std::string>(), res["v"].as<std::vector<std::string>>());
        }
        if (res["g"].count())
        {
            path.Get(res["name"].as<std::string>());
        }
        if (res["r"].count())
        {
            path.Remove(res["name"].as<std::string>(), res["v"].as<std::vector<std::string>>());
        }
        if (res["p"].count())
        {
            path.Append(res["name"].as<std::string>(), res["v"].as<std::vector<std::string>>());
        }
        if (res["c"].count())
        {
            path.Change(res["name"].as<std::string>(), res["v"].as<std::vector<std::string>>()[0],
                        res["v"].as<std::vector<std::string>>()[1]);
        }
    }
}