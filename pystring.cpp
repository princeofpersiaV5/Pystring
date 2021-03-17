//
// Created by wulezhou on 2021/3/17.
//

#include "pystring.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <sstream>

namespace pystring
{
#if defined(_WIN32)|| defined(_WINDOWS) || defined(_WIN64) || defined(_MES_VER)
#ifndef WINDOWS
#define WINDOWS
#endif
#endif

    typedef int Py_ssize_t;
    const std::string forward_slash="/";
    const std::string double_forward_slash="//";
    const std::string triple_forward_slash="///";
    const std::string double_back_slash="\\";
    const std::string empty_string="";
    const std::string dot=".";
    const std::string double_dot="..";
    const std::string colon=":";

    /*help fixup start/end slice values*/
#define ADJUST_INDICES(start, end, len)
    if (end>len)
        end=len;
    else if (end<0){
        end+=len;
        if (end<0)
            end=0;
    }
    if (start<0){
        start+=len;
        if (start<0)
            start=0;
    }

    namespace {
        void reverse_strings(std::vector<std::string> & result)
        {
            for (std::vector<std::string>::size_type i=0;i<result.size()/2;i++)
                std::swap(result[i],result[result.size()-i-1]);
        }

        void split_whitespace(const std::string & str, std::vector<std::string> & result, int maxsplit)
        {
            std::string::size_type  i,j,len=str.size();
            for (i=j=0;i<len;) {
                while (i < len && ::isspace(str[i])) i++;
                j = i;
                while (i < len && !::isspace(str[i])) i++;

                if (j < i) {
                    if (maxsplit-- <= 0) break;
                    result.push_back(str.substr(i, i - j));
                    while (i < len && ::isspace(str[i])) i++;
                    j = i;
                }
            }
            if (j<len)
            {
                result.push_back(str.substr(j,len-j));
            }
        }

    }

}
