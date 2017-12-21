#include <sstream>
#include <stdlib.h>
#include "StringOp.h"
using namespace std;

void splitString(const string& s, vector<string>& v, const string& c)
{
  string::size_type pos1, pos2;
  pos2 = s.find(c);
  pos1 = 0;
  while(string::npos != pos2)
  {
    v.push_back(s.substr(pos1, pos2-pos1));
 
    pos1 = pos2 + c.size();
    pos2 = s.find(c, pos1);
  }
  if(pos1 != s.length())
    v.push_back(s.substr(pos1));
}

float stringToFloat(const string& str)
{
    istringstream iss(str);
    float num;
    iss >> num;
    return num;
}