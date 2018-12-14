#ifndef LOCATIONLIST_H
#define LOCATIONLIST_H
#include <map>
#include "Location.h"
std::map<std::string,int> makeList(std::map<std::string,int>);
std::map<std::string,int> makeLocationList(std::map<std::string,int>, bool);
std::map<Location *,int> makeLocationList(std::map<Location *,int>);
void writeLocationListToFile(std::map<Location *, int> , std::string );
#endif // LOCATIONLIST_H
