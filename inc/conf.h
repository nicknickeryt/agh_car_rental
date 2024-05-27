#pragma once

#include <string>

using std::string;

inline string slash = "/";                           // the slash used in your OS. Should be set to '/' for Linux or '\\' for Windows.
inline string resPath = "res" + slash;               // path of resources directory
inline string carsConf = resPath + "cars.yml";       // path of cars conf file
inline string clientsPath = resPath + "clients";     // path of client directory
inline string reportsPath = resPath + "reports.log"; // path of client reports log
inline int maxRentTime = 720;                        // max car rent time in minutes
inline int notReturnedFine = 250;                    // fine for not returning the car within maxRentTime