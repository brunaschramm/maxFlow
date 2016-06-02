#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>

using namespace std;

void split(const string& s, char c, set<string>& v)
{
   string::size_type i = 0;
   string::size_type j = s.find(c);

   if(!s.empty() && j == string::npos)
   {
        v.insert(s);
   }
   else
   {
       while (j != string::npos)
       {
          v.insert(s.substr(i, j-i));
          i = ++j;
          j = s.find(c, j);

          if (j == string::npos)
             v.insert(s.substr(i, s.length()));
       }
   }
}

//Retorna UNIX epoch, com preciso at nanossegundos
double getUnixTime()
{
    struct timespec tv;
    if(clock_gettime(CLOCK_REALTIME, &tv) != 0) return 0;
    return (((double) tv.tv_sec) + (double) (tv.tv_nsec / 1000000000.0));
}
