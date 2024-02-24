#include <iostream>
#include <string>
#include <map>

using namespace std;

class Plane {
private:
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    string origin;
    string destination;
    map<string, map<string, int>> flightDistances;

public:
    Plane(const string& from, const string& to);
    ~Plane();
    void operate(double dt);
    double getPos() const;
    double getVel() const;
    double getDistance() const;
    bool getAt_SCE() const;
    string getOrigin() const;
    string getDestination() const;
    void setVel(double velocity);
};

Plane::Plane(const string& from, const string& to) {
    flightDistances["SCE"]["PHL"] = 160;
    flightDistances["SCE"]["ORD"] = 640;
    flightDistances["SCE"]["EWR"] = 220;

    origin = from;
    destination = to;
    distance = flightDistances[origin][destination];

    pos = 0;
    vel = 0;
    at_SCE = false;

    cout << "Plane Created at " << this << endl;
}

Plane::~Plane() {
    cout << "Plane Destroyed" << endl;
}

void Plane::operate(double dt) {
    if (pos < distance) {
        pos += vel * dt;
        if (pos < 0) pos = 0;
        at_SCE = false;
    }
    else if (destination == "SCE") {
        at_SCE = true;
        swap(origin, destination);
        pos = 0.0;
        distance = flightDistances[origin][destination];
    }
    else {
        swap(origin, destination);
        pos = 0.0;
        distance = flightDistances[origin][destination];
    }
}

double Plane::getPos() const {
    return pos;
}

double Plane::getVel() const {
    return vel;
}

double Plane::getDistance() const {
    return distance;
}

bool Plane::getAt_SCE() const {
    return at_SCE;
}

string Plane::getOrigin() const {
    return origin;
}

string Plane::getDestination() const {
    return destination;
}

void Plane::setVel(double velocity) {
    vel = velocity;
}


class Pilot {
private:
    std::string name;
    Plane* myPlane;

public:
    // Constructor
    Pilot(const std::string& pilotName, Plane* planePtr) : name(pilotName), myPlane(planePtr) {
        std::cout << "Pilot " << name << " at " << this << " is at the gate, ready to board the plane." << std::endl;
    }

    // Destructor
    ~Pilot() {
        std::cout << "Pilot " << name << " is out of the plane." << std::endl;
    }

    // Getter function for name
    std::string getName() const {
        return name;
    }

    // Getter function to access the plane object
    Plane* getPlane() {
        return myPlane;
    }
};


