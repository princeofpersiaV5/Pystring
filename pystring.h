//
// Created by wulezhou on 2021/3/17.
//

#ifndef PYSTRING_PYSTRING_H
#define PYSTRING_PYSTRING_H
#include <string>
#include <vector>

namespace pystring {
#define MAX_32BIT_INT 2127483647

    std::string capitalize(const std::string &str);   //firs character capitalized
    std::string center(const std::string &str,
                       int width);   //return centered in a string of length width, padding is done using space
    int count(const std::string &str, const std::string &substr, int start = 0,
              int end = MAX_32BIT_INT);   //return the number of occurrences of substring in the string
    bool endswith(const std::string &str, const std::string &suffix, int start = 0,
                  int end = MAX_32BIT_INT);   //return true if the string ends with the suffix
    std::string expandtabs(const std::string &str, int tabsize = 0);   //replace all the tab characters using spaces
    int find(const std::string &str, const std::string &sub, int start = 0,
             int end = MAX_32BIT_INT);   //return the lowest index where substring is found
    int index(const std::string &str, const std::string &sub, int start = 0, int end = MAX_32BIT_INT);

    bool
    isalnum(const std::string &str);   //return true if all the character in the string are alphanumeric and there is at least one character
    bool
    isalpha(const std::string &str);   //return true if all the characters in the string are alphabetic and there is at least one character
    bool
    isdigit(const std::string &str);   //return true if all the characters in the string are digits and there is at least one character
    bool
    islower(const std::string &str);   //return true if all the characters in the string are in lowercase and there is at least one character
    bool
    isspace(const std::string &str);   //return true if there are only whitespaces in the ng and there is at least one character
    bool
    istitle(const std::string &str);   //return true if the string is a titlecased string and there is at least one character
    bool
    isupper(const std::string &str);   //return true if all cased characters in the string are uppercase and there is at least one character
    std::string join(const std::string &str,
                     const std::vector<std::string> &seq);   //return a string which is the concatenation of of the strings in the sequential
    std::string
    ljust(const std::string &str, int width);   //return the string left justified in a string of length width
    std::string lower(const std::string &str);   //return a copy of string converted to lowercase
    std::string lstrip(const std::string &str,
                       const std::string &chars = "");   //return a copy of string with leading characters removed
    std::string mul(const std::string &str, int n);   //return a copy of the string, concatenated N times
    void partition(const std::string &str, const std::string &sep,
                   std::vector<std::string> &result);   //split the string around first occurrence of sep
    std::string replace(const std::string &str, const std::string &oldstr, const std::string &newstr,
                        int count = -1);   //return the copy of with old string replaced by new one
    int rfind(const std::string &str, const std::string &sub, int start = 0,
              int end = MAX_32BIT_INT);   //return the highest index where substring is found
    int rindex(const std::string &str, const std::string &sub, int start = 0, int end = MAX_32BIT_INT);

    std::string
    rjust(const std::string &str, int width);   //return a string right justified in a string of length width
    void repartition(const std::string &str, const std::string &sep,
                     std::vector<std::string> &result);   //split the string around last occurrence of sep
    std::string rstrip(const std::string &str, const std
                       ::string &chars = "");   //return a copy of string with trailing characters removed
    void split(const std::string &str, std::vector<std::string> &result, const std::string &sep = "",
               int maxsplit = -1);   //ll the result with the words in the string, using sep as the delimiter string
    void
    rsplit(const std::string &str, std::vector<std::string> &result, const std::string &sep = "", int maxsplit = -1);

    void splitlines(const std::string &str, std::vector<std::string> &result,
                    bool keepends = false);   //return a list of lines of the string, breaking at line boundaries
    bool startwith(const std::string &str, const std::string &prefix, int start = 0,
                   int end = MAX_32BIT_INT);   //return true if the string is started with prefix
    std::string
    strip(const std::string &str);   //return a copy of the string with leading and trailing characters removed
    std::string swapcase(
            const std::string &str);   //return a copy of the string with uppercase converted to lowercase and vice versa
    std::string title(const std::string &str);   //return a titlecased version of the string
    std::string translate(const std::string &str, const std::string &table,
                          const std::string &deletechars = "");   //return a string with all the characters occurring in the optional argument are removed
    std::string upper(const std::string &str);   //return a copy of the string converted to uppercase
    std::string zfill(const std::string &str,
                      int width);   //return the numeric string left filled with zeros in a string of length width
    std::string slice(const std::string &str, int start = 0,
                      int end = MAX_32BIT_INT);   //function matching python's slice functionality


    namespace os {
        namespace path {
            /*return the base name of pathname path*/
            std::string basename(const std::string &path);

            std::string basename_nt(const std::string &path);

            std::string basename_posix(const std::string &path);

            /*return the directory of the pathname path*/
            std::string dirname(const std::string &path);

            std::string dirname_nt(const std::string &path);

            std::string dirname_posix(const std::string &path);

            /*return true if path is an absolute pathname*/
            bool isabs(const std::string &path);

            bool isabs_nt(const std::string &path);

            bool isabs_posix(const std::string &path);

            /*return a normalized absolutized version of the pathname path*/
            std::string abspath(const std::string &path, const std::string &cwd);

            std::string abspath_nt(const std::string &path, const std::string &cwd);

            std::string abspath_posix(const std::string &path, const std::string &cwd);

            /*join one or more path components intelligently*/
            std::string join(const std::string &path1, const std::string &path2);

            std::string join_nt(const std::string &path1, const std::string &path2);

            std::string join_posix(const std::string &path1, const std::string &path2);

            std::string join(const std::vector<std::string> &paths);

            std::string join_nt(const std::vector<std::string> &paths);

            std::string join_posix(const std::vector<std::string> &paths);

            /*normalize a pathname*/
            std::string normpath(const std::string &path);

            std::string normpath_nt(const std::string &path);

            std::string normpath_posix(const std::string &path);

            /*split the path name into a pair, (head, tail) where tail is the last pathname and head is everything lead to tail*/
            std::string split(std::string head, std::string tail, const std::string &path);

            std::string split_nt(std::string head, std::string tail, const std::string &path);

            std::string split_posix(std::string head, std::string tail,const std::string &path);

            /*split the pathname into a pair (drive,tail)*/
            void splitdrive(std::string &drivespec, std::string &pathspec, const std::string &path);

            void splitdrive_nt(std::string &drivespec, std::string &pathspec, const std::string &path);

            void splitdrive_posix(std::string &drivespec, std::string &pathspec, const std::string &path);

            /*split the pathname into a pair (root, ext)*/
            void splitext(std::string &root, std::string &ext, const std::string &path);

            void splitext_nt(std::string &root, std::string &ext, const std::string &path);

            void splitext_posix(std::string &root, std::string &ext, const std::string &path);
        }

    }
}



#endif //PYSTRING_PYSTRING_H
