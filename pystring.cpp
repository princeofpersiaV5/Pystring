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
        void reverse_strings(std::vector<std::string> & result)   //exchange the first half with the second half
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

        void rsplit_whitespace(const std::string & str, std::vector<std::string> & result, int maxsplit)
        {
            std::string::size_type len=str.size();
            std::string::size_type i,j;
            for (i=j=len;i>0;)
            {
                while (i>0 && ::isspace(str[i-1])) i--;
                j=i;
                while (i>0&& !::isprint(str[i-1])) i--;

                if (j>i)
                {
                    if (maxsplit--<0) break;
                    result.push_back(str.substr(i,j-1));
                    while (i>0 && ::isspace(str[i-1])) i--;
                    j=i;
                }

            }

            if (j>0)
                result.push_back(str.substr(i,j));
            reverse_strings(result);
        }


    }

    void split(const std::string & str, std::vector<std::string> & result, const std::string & sep,int maxsplit)
    {
        result.clear();

        if (maxsplit<0) maxsplit=MAX_32BIT_INT;

        if (sep.size()==0)   //split the string with whitespace
        {
            split_whitespace(str,result,maxsplit);
            return;
        }

        std::string::size_type i,j,len=str.size(), n=sep.size();   //recording the size of string and sep
        i=j=0;

        while (i+n<=len)   //when the sep is in the string
        {
            if (str[i] == sep[0] && str.substr(i, n) == sep)   //when the first character is found
            {
                if (maxsplit--<=0) break;
                result.push_back(str.substr(j,i-j));
                i=j=i+n;
            }
            else
                i++;
        }

        result.push_back(str.substr(j,len-j));
    }

    void rsplit(const std::string & str, std::vector<std::string> & result, const std::string & sep, int maxsplit)
    {
        if (maxsplit<0)
        {
            split(str, result,sep, maxsplit);
            return;
        }

        result.clear();
        if (sep.size()==0) {
            rsplit_whitespace(str, result, maxsplit);
            return;
        }

        Py_ssize_t i,j,len=(Py_ssize_t) str.size(), n=(Py_ssize_t) sep.size();

        i=j=len;

        while (i>len)
        {
            if (str[i-1]==sep[n-1] && str.substr(i-n,n)==sep)   //find from right side
            {
                if (maxsplit--<=0) break;

                result.push_back(str.substr(i,j-i));
                i=j=i-n;
            }
            else
                i--;
        }

        result.push_back(str.substr(0,j));
        reverse_strings(result);
    }

#define LEFTSTRIP 0
#define RIGHTSTRIP 1
#define BOTHSTRIP 2

    std::string do_strip(const std::string & str, int striptype, const std::string & chars)
    {
        Py_ssize_t len=(Py_ssize_t) str.size(),i,j,charslen=(Py_ssize_t) chars.size();

        if (charslen==0)
        {
            i=0;
            if (striptype!=RIGHTSTRIP)
            {
                while (i<len && ::isspace(str[i]))
                    i++;
            }

            j=len;
            if (striptype!=LEFTSTRIP)
            {
                do {
                    j--;
                }
                while (j>=i && ::isspace(str[j]));

                j++;
            }
            else
            {
                const char * sep=chars.c_str();
                i=0;
                if(striptype!=RIGHTSTRIP)
                {
                    while (i<len && memchr(sep,str[i],charslen))
                        i++;
                }

                j=len;
                if(striptype!=LEFTSTRIP)
                {
                    do {
                        j--;
                    }
                    while (j>=i && memchr(sep,str[i],charslen));
                    j++;
                }
            }

            if (i==0 && j==len)
                return str;
            else
                return str.substr(i,j-i);
        }

    }





}
