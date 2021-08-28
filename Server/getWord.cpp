#include "Server.class.hpp"

int ft_strlen(char **str)
{
    int i;

    i = 0;
    while (str[i] != 0)
        i++;
    return (i);
}

std::string toString(char *string)
{
    std::string word(string);
    return (word);
}

std::string parseString(std::istringstream &stringStream, int nLine, int nWord)
{
    char **tab;
    std::string line;
    std::string word;

    for (int number = 0; number <= nLine; number++)
        getline(stringStream, line);
    tab = ft_split(line, ' ');
    if(nWord >= ft_strlen(tab))
        return ("");
    word = toString(tab[nWord]);
    for (int i = 0; tab[i]; i++)
        delete tab[i];
    delete[] tab;
    return (word);
}
std::string getWord(char *str,  int nLine, int nWord)
{
    int r;
    // char *str;
    std::istringstream stringStream;
    std::string fileStr(str);

    // str = new char[100];
    r = 0;
    // fileStr = "";
    // while ((r = read(fd, str, 100)) > 0)
    // {
        // str[r] = '\0';
        // fileStr += str;
    // }
    // delete[] str;
    // std::cout << str << std::endl;
    stringStream.str(fileStr);
    return (parseString(stringStream, nLine, nWord));
}
