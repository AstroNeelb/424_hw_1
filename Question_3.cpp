#include <iostream>
#include <string>
#include <map>

class Plane {
private:
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    std::string origin;
    std::string destination;
    // Define the container to store flight distances
    std::map<std::string, std::map<std::string, int>> flightDistances = {
        {"SCE", {{"PHL", 160}, {"ORD", 640}, {"EWR", 220}}},
        {"PHL", {{"SCE", 160}}},
        {"ORD", {{"SCE", 640}}},
        {"EWR", {{"SCE", 220}}}
    };

public:
    Plane(const std::string& from, const std::string& to);
    ~Plane();
    void operate(double dt);
    // Getter functions
    double getPos() const;
    double getVel() const;
    std::string getOrigin() const;
    std::string getDestination() const;
    bool isAtSCE() const;
    // Setter functions
    void setVel(double newVel);
};
