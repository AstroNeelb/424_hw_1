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
    std::map<std::string, std::map<std::string, int>> flightDistances;

public:
    // Constructor
    Plane(const std::string& from, const std::string& to) {
        flightDistances["SCE"]["PHL"] = 160;
        flightDistances["SCE"]["ORD"] = 640;
        flightDistances["SCE"]["EWR"] = 220;

        origin = from;
        destination = to;
        distance = flightDistances[origin][destination];

        pos = 0;
        vel = 0;
        at_SCE = false;

        std::cout << "Plane Created at " << this << std::endl;
    }

    // Destructor
    ~Plane() {
        std::cout << "Plane Destroyed" << std::endl;
    }

    // Function to operate the plane
    void operate(double dt) {
        if (pos < distance) {
            pos += vel * dt;
            if (pos < 0) pos = 0;
            at_SCE = false;
        }
        else {
            if (destination == "SCE") {
                at_SCE = true;
                std::swap(origin, destination);
                pos = 0.0;
                distance = flightDistances[origin][destination];
            }
            else {
                std::cout << "Plane at " << this << " has landed at SCE." << std::endl;
                std::swap(origin, destination);
                pos = 0.0;
                distance = flightDistances[origin][destination];
            }
        }
    }

    // Getter functions
    double getPos() const {
        return pos;
    }

    double getVel() const {
        return vel;
    }

    double getDistance() const {
        return distance;
    }

    bool getAt_SCE() const {
        return at_SCE;
    }

    std::string getOrigin() const {
        return origin;
    }

    std::string getDestination() const {
        return destination;
    }

    // Setter function for velocity
    void setVel(double newVel) {
        vel = newVel;
    }
};