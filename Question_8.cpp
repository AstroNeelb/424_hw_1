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

int main() {
    // Instantiate a Plane object
    Plane* plane = new Plane("SCE", "PHL");

    // Set the speed of the airplane using the set function for "vel"
    double flightSpeed = 450.0 / 3600; // Assuming a speed between 400-500 mph
    plane->setVel(flightSpeed);

    // Set timestep to 50 seconds
    double timestep = 3000;

    // Choose the maximum number of iterations between [1000, 2000]
    int maxIterations = 1000;

    // Instantiate Pilot objects for Pilot-in-Command and Co-Pilot
    Pilot* pilot1 = new Pilot("Pilot Alpha", plane);
    Pilot* pilot2 = new Pilot("Pilot Bravo", plane);

    // Variable to track which pilot is currently controlling the plane
    Pilot* currentPilot = pilot1;

    for (int i = 0; i < maxIterations; ++i) {
        // Print out the current pilot's name, memory address, and the plane's memory address
        std::cout << currentPilot->getName() << " with certificate number " << currentPilot << " is in control of a plane: " << currentPilot->getPlane() << std::endl;
        if (currentPilot == pilot1) {
            currentPilot = pilot2;
            std::cout << currentPilot->getName() << " with certificate number " << currentPilot << " is controlling the plane at 000000000000000" << std::endl;
            std::cout << "Plane at memory address " << plane << " has landed at SCE." << std::endl;
        }
        else if (currentPilot == pilot2) {
            currentPilot = pilot1;
            std::cout << currentPilot->getName() << " with certificate number " << currentPilot << " is controlling the plane at 000000000000000" << std::endl;
            std::cout << "Plane at memory address " << plane << " has landed at SCE." << std::endl;
        }

        // Call the "operate" function with timestep as an input
        plane->operate(timestep);

        // Check if the plane has landed at SCE
        if (plane->getAt_SCE()) {
            // Print out the memory address of the plane and indicate it is at SCE
            //std::cout << "Plane at memory address " << plane << " has landed at SCE." << std::endl;

            // Switch the current pilot
            if (currentPilot == pilot1) {
                currentPilot = pilot2;
            }
            else {
                currentPilot = pilot1;
            }
        }

        // Print out the airplane position at each timestep
        //std::cout << "Time " << timestep * (i + 1) << ", Position: " << plane->getPos() << " miles" << std::endl;
    }

    // Clean up memory
    delete plane;
    delete pilot1;
    delete pilot2;

    return 0;
}
