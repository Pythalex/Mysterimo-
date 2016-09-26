#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include <fstream>

using namespace std;

bool is_in(int value, int table[], int table_size);

int dic_size(ifstream& stream);

#endif // TOOLS_H_INCLUDED
