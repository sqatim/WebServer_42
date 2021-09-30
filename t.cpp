#include <iostream>
#include <vector>
std::string get_key_tab(std::string str)
{
    std::string ret;
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < str.length())
    {
        if (str[i] == ' ' || str[i] == '\t')
            i++;
        else
            break;
    }
    j = 0;
    k = i;
    while (k < str.length())
    {
        if (str[k] != '\t')
        {
            j++;
            k++;
        }
        else
            break;
    }
    ret = str.substr(i, j);
    return ret;
}

std::string get_value(std::string str)
{
    std::string ret;
    std::string key = get_key_tab(str);
    int found = str.find(key);
    found += key.length();
    ret = str.substr(found, str.length() - found);
    return ret;
}

std::vector<std::string> splitstring(std::string str, std::string to_split_with)
{
    std::vector<std::string> vect_str;
    int start = 0;
    while (start < str.size())
    {
        if (str[start] != '\t' && str[start] != ' ')
            break;
        start++;
    }
    std::string _str = str.substr(start, str.length());
    // std::cout << _str << std::endl;
    to_split_with = " ";
    start = 0;
    int end = _str.find(to_split_with);
    while (end != -1)
    {
        if (_str.substr(start, end - start).length() > 0)
            vect_str.push_back(_str.substr(start, end - start));
        start = end + to_split_with.size();
        end = _str.find(to_split_with, start);
    }
    vect_str.push_back(_str.substr(start, end - start));
    int i = 0;
    while (i < vect_str.size())
    {
        if (vect_str[i].length() == 0 )
            vect_str.erase(vect_str.begin() + i);
        i++;
    }
    return vect_str;
}

int main()
{
    std::vector<std::string> vect_str = splitstring(" \t \t[\t \t \t", " ");
    int i = 0;
    std::string str;
    while (i < vect_str.size())
    {
        str = get_key_tab(vect_str[i]);
        std::cout << "{" << str << "}" << std::endl;
        i++;
    }
    return 0;
}