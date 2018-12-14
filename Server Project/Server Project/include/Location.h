#ifndef LOCATION_H
#define LOCATION_H
#include <iostream>


class Location
{
    public:
        Location(char name[], char type[], char value, char activityLevel, char safe);
        Location(std::string);
        virtual ~Location();
        friend std::ostream& operator<<(std::ostream &strm, const Location &a);
        bool isCompromised(), isUnCompromised();
        int activitylevel(), value();
        float getMultiplier();
        std::string getName(), getType();
        std::string getFullSite();
    protected:

    private:
        char m_name[18], m_type[11];
        char m_value, m_activity, m_safe;
        std::string fullSite;
};

#endif // LOCATION_H
