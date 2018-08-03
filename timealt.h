#ifndef TIMEALT_H
#define TIMEALT_H
#include <iostream>
#include <string>

class TimeAlt
{
private:
    int minutes;
    int seconds;

public:
    TimeAlt(int minutArg, int secArg);
    std::string getCommandOut();
    int getMinutes();
    int getSeconds();

};

#endif // TIMEALT_H
