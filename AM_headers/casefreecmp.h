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
            int i = 0;
            for (; (lc = l[i]) != '\0'; i++)
            {
                char rc = r[i];
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
            if ('\0' < r[i])
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
            for (size_t i = 0; i < _Left.size(); i++)
            {
                char lc = l[i];
                char rc = r[i];
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
            for (size_t i = 0; i < str.size(); i++)
            {
                lower[i] = (char)tolower(str[i]);
            }
            return hasher()(lower);
        }
    };
}