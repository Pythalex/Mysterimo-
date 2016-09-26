#include <fstream>
#include "tools.h"

using namespace std;

bool is_in(int value, int table[], int table_size)
/***************************************************
* Finds if an int value exists in an int array,
* returns boolean.
* @param  : value      - Int value you want to check
*                          the existence
*           table      - List you want to check the
*                          value existence in.
*           table_size - Size of the list
*
* @return : true/false
****************************************************/
{
    bool exist (false);
    for (int i (0); i < table_size; i++)
    {
        exist = exist || (table[i] == value);
    }
    return exist;
}

int dic_size(ifstream& stream)
/**************************************************
* Returns the number of words in the dictionnary
* text file of the game folder : '~\dic.txt'
* Each word MUST take one line, no more no less.
* Words can be added everywhere, as long as they
* take one line.
*
* @param  : stream - Stream of the dictionnary file
*
* @return : Int number of words in the dictionnary
****************************************************/
{
    int line_num (0);
    string line;

    while (getline(stream, line))
    {
        line_num += 1;
    }
    stream.clear();
    stream.seekg(0, ios::beg);
    // On revient au début du fichier

    return line_num;
}
