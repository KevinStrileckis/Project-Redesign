#include "../include/Location.h"
#include "string.h"
#include <iostream>
using namespace std;

Location::Location(std::string s)
{
    int i, j;
    for(i=0; i<18; ++i){
        m_name[i] = s[i];
    }
    m_name[i] = '\0';
    cout<<s.length();
    for(j=0, i=18; j<11; ++i,j++){
        m_type[j] = s[i];
    }
    m_type[j] = '\0';
    m_value = s[29];
    m_activity = s[30];
    m_safe = s[31];
    cout<<"::"<<*this<<endl;
}

Location::Location(char name[], char type[], char value, char activityLevel, char safe)
{
    int i=0;
    //int namelength = 17; //+1 for null terminator
    //int typelength = 11; //+1 for null terminator
    //m_name[18], m_type[11];
    for(i=0; i<10; ++i){
        m_name[i] = name[i];
        m_type[i] = type[i];
    }
    m_type[i] = '\0';
    for(;i<17;++i){
        m_name[i] = name[i];
    }
    m_name[i] = '\0';
    m_value = value;
    m_activity = activityLevel;
    m_safe = safe;

    char *buffer = (char*)(malloc(32));

    buffer = strcpy(m_name,m_type);
    buffer = (buffer+m_value);
    buffer = (buffer+m_activity);
    buffer = (buffer+m_safe);

    fullSite = buffer;
}
std::ostream& operator<<(std::ostream &strm, const Location &a) {
    //std::cout<<"friend method accessed"<<std::endl;
    //std::cout<< "Location(" << a.m_name <<".";//<< a.m_type<<a.m_value<<a.m_activity<<a.m_safe << ")"
  return strm << "" << a.m_name<<"\n\t\t" << a.m_type<<"," <<a.m_value<<"," <<a.m_activity<<"," <<a.m_safe << "";
}
std::string Location::getFullSite(){
    return fullSite;
}

Location::~Location()
{
    //dtor
}

bool Location::isCompromised(){
    if(m_safe == 's'){
        return false;
    }
    return true;
}
bool Location::isUnCompromised(){
    if(m_safe == 'c'){
        return false;
    }
    return true;
}
int Location::activitylevel(){
    return m_activity - ' ';
}
int Location::value(){
    return m_value - ' ';
}
float Location::getMultiplier(){
    //Personal or public
    if((m_type[2] == 'P' && m_type[3] == 'e' && m_type[4] == 'r')
       || (m_type[4] == 'P' && m_type[5] == 'u' && m_type[6] == 'b') ){
            //"  Personal  s"
            //"    Public  s"
        return 1.0;
    }
    //Darkweb
    else if(m_type[3] == 'D' && m_type[4] == 'a' && m_type[5] == 'r'){
            //"   Darkweb  s"
        return 1.3;
    }
    std::cout<<"Invalid type, value multiplier will be zero\n";
    return 0;
}

std::string Location::getName(){
    std::string ret = "";
    for(int i=0; i<18; ++i){
        if(m_name[i] != ' '){
            ret += m_name[i];
        }
    }
    return ret;
}
std::string Location::getType(){
    std::string ret = "";
    for(int i=0; i<11; ++i){
        if(m_type[i] != ' '){
            ret += m_type[i];
        }
    }
    return ret;
}
