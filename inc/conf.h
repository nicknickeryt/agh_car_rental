#ifndef CONF_H
#define CONF_H

#include <string>

using std::string;

// The slash used in your OS. Should be automatically set to '/' for Unix-like systems or '\\' for Windows.
inline string slash =
#if defined _WIN32 || defined __CYGWIN__
    "\\";
#else
    "/";
#endif  
                   
inline string resPath = "res" + slash;               // path of resources directory
inline string carsConf = resPath + "cars.yml";       // path of cars conf file
inline string clientsPath = resPath + "clients";     // path of client directory
inline string reportsPath = resPath + "reports.log"; // path of client reports log
inline int maxRentTime = 720;                        // max car rent time in minutes
inline int notReturnedFine = 250;                    // fine for not returning the car within maxRentTime

#endif // CONF_H