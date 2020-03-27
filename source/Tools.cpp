#include "cpputil/Tools.h"
#include "cpputil/StringHelper.h"

#include <vector>
#include <cctype>

namespace cpputil
{

std::string UnderscoreToCamelCase(const std::string& str)
{
    std::vector<std::string> tokens;
    StringHelper::Split(str, "_", tokens);

    std::string ret;
    for (auto& sub : tokens)
    {
        if (sub.empty()) {
            continue;
        }
        sub[0] = std::toupper(sub[0]);
        if (!ret.empty()) {
            ret += " ";
        }
        ret += sub;
    }
    return ret;
}

std::string CamelCaseToUnderscore(const std::string& str)
{
    std::vector<std::string> tokens;
    StringHelper::Split(str, " ", tokens);



    std::string ret;
    for (auto& sub : tokens)
    {
        if (sub.empty()) {
            continue;
        }

        bool first = true;
        //bool begin = ret.empty();
        for (auto& c : sub)
        {
            if (std::isupper(c))
            {
                if (!first) {
                    ret.append("_");
                }
                ret += std::tolower(c);
                first = false;
            }
            else
            {
                ret += c;
            }
        }
    }
    return ret;
}

}