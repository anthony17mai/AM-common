#pragma once

#include <string>

namespace AM_common
{
    //casefree less
    struct casefreeless {
        typedef std::string first_argument_type;
        typedef std::string second_argument_type;
        typedef bool result_type;

        bool operator()(const first_argument_type& _Left, const second_argument_type& _Right) const
        {
            const char* l = _Left.c_str();
            const char* r = _Right.c_str();
            char lc = '\0';
            int id = 0;
            for (; (lc = l[id]) != '\0'; id++)
            {
                char rc = r[id];
                if (isupper(lc)) lc = (char)tolower(lc);
                if (isupper(rc)) rc = (char)tolower(rc);
                if (lc != rc)
                {
                    if (lc < rc)
                        return true;
                    else
                        return false;
                }
            }
            if ('\0' < r[id])
                return true;
            else
                return false;
        }
    };

    //casefree equal
    struct casefreeeqq
    {
        typedef std::string first_argument_type;
        typedef std::string second_argument_type;
        typedef bool result_type;

        bool operator()(const first_argument_type& _Left, const second_argument_type& _Right) const
        {
            const char* l = _Left.c_str();
            const char* r = _Right.c_str();

            if (_Left.size() != _Right.size()) return false;

            bool eq = true;
            for (size_t id = 0; id < _Left.size(); id++)
            {
                char lc = l[id];
                char rc = r[id];
                lc = (char)tolower(lc);
                rc = (char)tolower(rc);

                if (lc != rc)
                {
                    eq = false;
                    break;
                }
                else
                {
                    //equals
                    continue;
                }
            }
            return eq;
        }
    };

    //casefree hash
    template<typename hasher = std::hash<std::string>>
    struct casefreehash
    {
        inline size_t operator()(const std::string& str)
        {
            std::string lower(str.size(), 0);
            for (size_t id = 0; id < str.size(); id++)
            {
                lower[id] = (char)tolower(str[id]);
            }
            return hasher()(lower);
        }
    };
}