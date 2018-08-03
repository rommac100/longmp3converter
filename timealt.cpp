#include "timealt.h"

TimeAlt::TimeAlt(int minutArg, int secArg)
{
    minutes = minutArg;
    seconds = secArg;
}

int TimeAlt::getSeconds()
{
    return seconds;
}

int TimeAlt::getMinutes()
{
    return minutes;
}


std::string TimeAlt::getCommandOut()
{
    return std::to_string(minutes)+"."+std::to_string(seconds);
}
