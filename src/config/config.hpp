#ifndef B06E2B2C_A12D_4E90_A344_D0CA9C58C845
#define B06E2B2C_A12D_4E90_A344_D0CA9C58C845
#include <string>
#include <string_view>
class Config
{
    std::string _default_file_name;

  public:
    Config(std::string_view str = std::string_view());
    std::string_view path_file_name();

    ~Config();
};
#endif /* B06E2B2C_A12D_4E90_A344_D0CA9C58C845 */
