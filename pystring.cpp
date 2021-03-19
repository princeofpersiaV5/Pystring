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

        if (charslen==0) {
            i = 0;
            if (striptype != RIGHTSTRIP) {
                while (i < len && ::isspace(str[i]))
                    i++;
            }

            j = len;
            if (striptype != LEFTSTRIP) {
                do {
                    j--;
                } while (j >= i && ::isspace(str[j]));

                j++;
            }
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

    void partition(const std::string & str, const std::string & sep, std::vector<std::string> & result)
    {
        result.resize(3);
        int index=find(str,sep);
        if (index<0)
        {
            result[0]=str;
            result[1]=empty_string;
            result[2]=empty_string;
        }
        else
        {
            result[0]=str.substr(0,index);
            result[1]=sep;
            result[2]=str.substr(index+sep.size(),str.size());
        }


    }

    void rpartition(const std::string & str, const std::string & sep, std::vector<std::string> & result)
    {
        result.resize(3);
        int index=rfind(str,sep);
        if (index<0)
        {
            result[0]=empty_string;
            result[1]=empty_string;
            result[2]=str;
        }
        else
        {
            result[0]=str.substr(0,index);
            result[1]=sep;
            result[2]=str.substr(index+sep.size(),str.size());
        }
    }

    std::string strip(const std::string & str, const std::string & chars)
    {
        return do_strip(str,BOTHSTRIP,chars);
    }

    std::string lstrip(const std::string & str,const std::string & chars)
    {
        return do_strip(str,LEFTSTRIP,chars);
    }

    std::string rstrip(const std::string & str, const std::string & chars)
    {
        return do_strip(str,RIGHTSTRIP,chars);
    }

    std::string join(const std::string & str,const std::vector<std::string> & seq)
    {
        std::vector<std::string>::size_type seqlen=seq.size();
        if(seqlen==0) return empty_string;
        if(seqlen==1) return seq[0];

        std::string result(seq[0]);

        for(int i=1;i<seqlen;++i)
        {
            result+=str+seq[i];
        }

        return result;
    }

    namespace
    {
        int _string_tailmatch(const std::string & self, const std::string & substr, Py_ssize_t start, Py_ssize_t end, int direction)
        {
            Py_ssize_t len=(Py_ssize_t) self.size();
            Py_ssize_t slen=(Py_ssize_t) substr.size();

            const char* sub=substr.c_str();
            const char* str=self.c_str();

            ADJUST_INDICES(start,end,len);

            if (direction<0)
            {
                if(start+slen>len)
                    return 0;
            }
            else
            {
                if(end-start<slen || start>len)
                    return 0;
                if (end-slen>start)
                    start=end-slen;
            }
            if (end-start>=slen)
                return (!std::memcmp(str+start,sub,slen));

            return 0;
        }
    }

    bool endswith(const std::string & str, const std::string & suffix, int start, int end)
    {
        int result=_string_tailmatch(str,suffix,(Py_ssize_t) start, (Py_ssize_t) end, +1);

        return static_cast<bool>(result);
    }

    bool startswith(const std::string & str, const std::string & prefix, int start, int end)
    {
        int result=_string_tailmatch(str,prefix,(Py_ssize_t) start, (Py_ssize_t) end,-1);

        return static_cast<bool>(result);
    }

    bool isalnum(const std::string & str)
    {
        std::string::size_type len=str.size(),i;
        if(len==0) return false;

        if(len==1)
        {
            return ::isalnum(str[0]);
        }

        for(i=0;i<len;++i)
        {
            if(!::isalnum(str[i])) return false;
        }

        return true;
    }

    bool isalpha(const std::string & str)
    {
        std::string::size_type len=str.size(),i;
        if(len==0) return false;
        if(len==1) return ::isalpha((int) str[0]);

        for (i=0;i<len;++i)
        {
            if (!::isalpha((int) str[i])) return false;
        }

        return true;
    }

    bool isdigit(const std::string & str)
    {
        std::string::size_type len=str.size(),i;
        if (len==0) return false;
        if (len==1) return ::isdigit((str[0]));

        for (i=0;i<len;++i)
        {
            if (!::isdigit(str[i])) return false;
        }

        return true;
    }

    bool islower(const std::string & str)
    {
        std::string::size_type len=str.size(),i;
        if(len==0) return false;
        if (len==1) return ::islower(str[0]);

        for(i=0;i<len;++i)
        {
            if (!::islower(str[i])) return false;
        }

        return true;
    }

    bool isspace(const std::string & str)
    {
        std::string::size_type len=str.size(),i;
        if(len==0) return false;
        if(len==1) return ::isspace(str[0]);

        for(i=0;i<len;++i)
        {
            if(!::isspace(str[i])) return false;
        }

        return true;
    }

    bool istitle(const std::string & str)
    {
        std::string::size_type len=str.size(),i;
        if(len==0) return false;
        if(len==1) return ::isupper(str[0]);

        bool cased=false, previous_is_cased=false;

        for (i=0;i<len;++i)
        {
            if(::isupper(str[i]))
            {
                if(previous_is_cased)
                    return false;

                previous_is_cased=true;
                cased=true;
            }
            else if (::islower(str[i]))
            {
                if(!previous_is_cased)
                    return false;

                previous_is_cased=true;
                cased=true;
            }

            else
            {
                previous_is_cased=false;
            }
        }

        return cased;
    }

    bool isupper(const std::string & str)
    {
        std::string::size_type len=str.size(),i;
        if(len==0) return false;
        if(len==1) return ::isupper(str[0]);

        for (i=0;i<len;++i)
        {
            if(!::isupper(str[i])) return false;
        }

        return  true;
    }

    std::string capitalize(const std::string & str)
    {
        std::string s(str);
        std::string::size_type len=s.size(),i;

        if(len>0)
        {
            if (::islower(s[0])) s[0]=(char) ::toupper(s[0]);
        }

        for (i=1;i<len;++i)
        {
            if(::isupper(s[i])) s[i]=(char) ::toupper(s[i]);
        }

        return s;
    }

    std::string lower(const std::string & str)
    {
        std::string s(str);
        std::string::size_type len=s.size(),i;

        for(i=0;i<len;++i)
        {
            if(::isupper(str[i])) s[i]=(char) ::tolower(s[i]);
        }
        return s;
    }

    std::string upper(const std::string & str)
    {
        std::string s(str);
        std::string::size_type len=s.size(),i;

        for(i=0;i<len;++i)
        {
            if(::islower(s[i])) s[i]=(char) ::toupper(s[i]);
        }

        return s;
    }

    std::string swapcase(const std::string & str)
    {
        std::string s(str);
        std::string::size_type len=s.size(),i;

        for(i=0;i<len;++i)
        {
            if(::islower(s[i])) s[i]=(char) ::toupper(s[i]);
            else if(::isupper(s[i])) s[i]=(char) ::tolower(s[i]);
        }

        return s;
    }

    std::string title(const std::string & str)
    {
        std::string s(str);
        std::string::size_type len=s.size(),i;
        bool previous_is_cased=false;

        for(i=0;i<len;++i)
        {
            int c=s[i];
            if(::islower(c))
            {
                if(!previous_is_cased)
                {
                    s[i]=(char) ::toupper(c);
                }
                previous_is_cased=true;
            }
            else if(::isupper(c))
            {
                if(previous_is_cased)
                {
                    s[i]=(char) ::tolower(c);
                }
                previous_is_cased=true;
            }
            else
                previous_is_cased=false;
        }
        return s;
    }

    std::string translate(const std::string & str, const std::string & table, const std::string & deletechars)
    {
        std::string s;
        std::string::size_type len=str.size(),dellen=deletechars.size();

        if(table.size()!=256)
        {
            return str;
        }
        if (dellen==0)
        {
            s=str;
            for(std::string::size_type i=0;i<len;++i)
            {
                s[i]=table[s[i]];
            }
            return s;
        }

        int trans_table[256];
        for(int i=0;i<256;i++)
        {
            trans_table[i]=table[i];
        }

        for(std::string::size_type i=0;i<dellen;i++)
        {
            trans_table[(int)deletechars[i]]=-1;
        }

        for(std::string::size_type i=0;i<len;++i)
        {
            if(trans_table[(int) str[i]]!=-1)
            {
                s+=table[str[i]];
            }
        }

        return s;
    }

    std::string zfill(const std::string & str,int width)
    {
        int len=(int) str.size();
        if (len>=width)
        {
            return str;
        }

        std::string s(str);

        int fill=width-len;
        s=std::string(fill,'0')+s;

        if (s[fill]=='+' || s[fill]=='-')
        {
            s[0]=s[fill];
            s[fill]='0';
        }

        return s;
    }

    std::string ljust(const std::string & str,int width)
    {
        std::string::size_type len=str.size();
        if(((int)len)>=width) return str;
        return std::string(width-len,' ')+str;
    }

    std::string rjust(const std::string & str,int width)
    {
        std::string::size_type len=str.size();
        if(((int)len)>=width) return str;
        return std::string(width-len,' ')+str;
    }

    std::string center(const std::string & str, int width)
    {
        int len=(int) str.size();
        int marg,left;

        marg=width-len;   //recording the white part
        left=marg/2+(marg&width&1);

        return std::string(left,' ')+str+std::string(marg-left,' ');
    }

    std::string slice(const std::string & str, int start, int end)
    {
        ADJUST_INDICES(start,end,(int) str.size());
        if (start>=end) return empty_string;
        return str.substr(start,end-start);
    }

    int find(const std::string & str, const std::string & sub,int start, int end)
    {
        ADJUST_INDICES(start,end,(int)str.size());
        std::string::size_type result=str.find(sub,start);

        if(result==std::string::npos || (result+sub.size()>(std::string::size_type) end))
        {
            return -1;
        }

        return (int) result;
    }

    int index(const std::string & str, const std::string & sub, int start, int end)
    {
        return find(str,sub,start,end);
    }

    int rfine(const std::string & str, const std::string & sub, int start, int end)
    {
        ADJUST_INDICES(start,end,(int) str.size());

        std::string::size_type result=str.rfind(sub,end);

        if(result==std::string::npos || result<(std::string::size_type) start || (result+sub.size()>(std::string::size_type) end))
        {
            return (int) -1;
        }

        return result;
    }

    int rindex(const std::string & str, const std::string & sub, int start, int end)
    {
        return rfind(str, sub,start,end);
    }

    std::string expandtabs(const std::string & str, int tabsize)
    {
        std::string s(str);

        std::string::size_type len=str.size(),i=0;
        int offset=0;
        int j=0;
        for (i=0;i<len;++i)
        {
            if (str[i]=='\t')
            {
                if (tabsize>0)
                {
                    int fillsize=tabsize-(j%tabsize);
                    j+=fillsize;
                    s.replace(i+offset,1,std::string(fillsize,' '));
                    offset+=fillsize-1;
                }
                else
                {
                    s.replace(i+offset,1,empty_string);
                    offset-=1;
                }
            }
            else
            {
                j++;
                if(str[i]=='\n' || str[i]=='\r')
                {
                    j=0;
                }
            }
        }

        return s;
    }

    int count(const std::string & str, const std::string & substr, int start, int end)
    {
        int nummatches=0;
        int cursor=start;

        while (1)
        {
            cursor=find(str,substr,cursor,end);
            if(cursor<0) break;

            cursor+=(int) substr.size();
            nummatches+=1;
        }

        return nummatches;
    }

    std::string replace(const std::string & str, const std::string & oldstr, const std::string & newstr, int count)
    {
        int sofar=0;
        int cursor=0;
        std::string s(str);

        std::string::size_type oldlen=oldstr.size(),newlen=newstr.size();
        cursor=find(s,oldstr,cursor);   //find the location of the old string
        while (cursor!=-1 && cursor<=(int) s.size())
        {
            if(count>-1 && sofar >=count)
            {
                break;
            }

            s.replace(cursor,oldlen,newstr);
            cursor+=(int) newlen;

            if (oldlen!=0)
            {
                cursor=find(s,oldstr,cursor);;
            }
            else
            {
                ++cursor;
            }

            ++sofar;
        }

        return s;
    }

    void splitlines(const std::string & str, std::vector<std::string> & result, bool keepends)
    {
        result.clear();
        std::string::size_type len=str.size(),i,j,eol;

        for (i=j=0;i<len;)
        {
            while (i<len && str[i] != '\n' && str[i]!='\r') i++;

            eol=i;
            if (i<len)
            {
                if (str[i]=='\r' && i+1<len && str[i+1] == '\n')
                {
                    i+=2;
                }
                else
                {
                    i++;
                }
                if (keepends)
                    eol=i;
            }

            result.push_back(str.substr(j,eol-j));
            j=i;
        }

        if (j<len)
            result.push_back(str.substr(j,len-j));
    }

    std::string mul(const std::string & str, int n)
    {
        if (n<=0) return empty_string;
        if (n==1) return str;

        std::ostringstream os;
        for(int i=0;i<n;++i)
        {
            os<<str;
        }
        return os.str();
    }






}


