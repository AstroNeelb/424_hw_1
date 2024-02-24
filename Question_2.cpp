#include <map>
#include <string>

// Define the container to store flight distances
std::map<std::string, std::map<std::string, int>> flightDistances = {
    {"SCE", {{"PHL", 160}, {"ORD", 640}, {"EWR", 220}}},
    {"PHL", {{"SCE", 160}}},
    {"ORD", {{"SCE", 640}}},
    {"EWR", {{"SCE", 220}}}
};
