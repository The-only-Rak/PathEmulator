#ifndef CBB96FCC_7B6D_4E41_93C9_794A44546D1C
#define CBB96FCC_7B6D_4E41_93C9_794A44546D1C
#include "rapidjson/document.h"
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

class path_value_allready_exist : public std::exception
{
  public:
    const char *what() const noexcept override;
    virtual ~path_value_allready_exist() = default;
};
class Path
{
    rapidjson::Document doc;
    std::string str;
    std::ostream &log;

  public:
    Path(const std::string_view file, std::ostream &logger);
    /**
     * It adds a new array to the document
     *
     * @param name The name of the key.
     * @param vals The values to add to the array.
     */
    void Add(const std::string_view name, const std::vector<std::string> &vals);
    /**
     * It removes a member from the document
     *
     * @param name The name of the element to remove.
     * @param vals The values to remove from the array. If this is empty, the entire array is removed.
     */
    void Remove(const std::string_view name, const std::vector<std::string> &vals);
    /**
     * It appends a vector of strings to a JSON array
     *
     * @param name The name of the array.
     * @param vals The values to append to the array.
     */
    void Append(const std::string_view name, const std::vector<std::string> &vals);
    /**
     * It prints out the contents of the JSON file
     *
     * @param name The name of the path to get. If empty, all paths will be printed.
     */
    void Get(const std::string_view name = "");
    /**
     * It removes the existing value for the given name, and then adds the new value
     *
     * @param name The name of the parameter to set.
     * @param vals The values to set.
     */
    void Set(const std::string_view name, const std::vector<std::string> &vals);
    /**
     * > Change the value of a path variable
     *
     * @param name The name of the environment variable to change.
     * @param old_val The old value to be replaced.
     * @param new_val The new value to be added to the path.
     */
    void Change(const std::string_view name, const std::string_view old_val, const std::string_view new_val);
    /**
     * > The destructor of the Path class writes the JSON document to the file specified in the constructor
     */
    ~Path();
};

#endif /* CBB96FCC_7B6D_4E41_93C9_794A44546D1C */
