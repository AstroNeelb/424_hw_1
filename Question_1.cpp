#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Seat {
    double weight;
    double arm;
};

int main() {
    // Receive inputs from the user
    double empty_weight, empty_weight_moment, front_arm, rear_arm, fuel_arm, baggage_arm, fuel_per_gallon, baggage_weight;
    int num_front_occupants, num_rear_occupants;
    vector<Seat> front_seats, rear_seats;
    double total_weight = 0, total_moment = 0;

    cout << "Enter airplane empty weight (pounds): ";
    cin >> empty_weight;
    cout << "Enter airplane empty-weight moment (pounds-inches): ";
    cin >> empty_weight_moment;

    cout << "Enter the number of front seat occupants: ";
    cin >> num_front_occupants;
    front_seats.resize(num_front_occupants);
    for (int i = 0; i < num_front_occupants; ++i) {
        cout << "Enter weight of front seat occupant " << i + 1 << " (pounds): ";
        cin >> front_seats[i].weight;
        cout << "Enter moment arm for front seat occupant " << i + 1 << " (inches): ";
        cin >> front_seats[i].arm;
    }

    cout << "Enter the number of rear seat occupants: ";
    cin >> num_rear_occupants;
    rear_seats.resize(num_rear_occupants);
    for (int i = 0; i < num_rear_occupants; ++i) {
        cout << "Enter weight of rear seat occupant " << i + 1 << " (pounds): ";
        cin >> rear_seats[i].weight;
        cout << "Enter moment arm for rear seat occupant " << i + 1 << " (inches): ";
        cin >> rear_seats[i].arm;
    }

    cout << "Enter the number of gallons of usable fuel (gallons): ";
    int num_gallons;
    cin >> num_gallons;
    cout << "Enter usable fuel weights per gallon (pounds): ";
    cin >> fuel_per_gallon;
    cout << "Enter fuel tank moment arm (inches): ";
    cin >> fuel_arm;

    cout << "Enter baggage weight (pounds): ";
    cin >> baggage_weight;
    cout << "Enter baggage moment arm (inches): ";
    cin >> baggage_arm;

    // Calculate total weight and moment
    total_weight += empty_weight;
    total_moment += empty_weight_moment;

    // Calculate total weight and moment for front seats
    for (const auto& front_seat : front_seats) {
        total_weight += front_seat.weight;
        total_moment += front_seat.weight * front_seat.arm;
    }

    // Calculate total weight and moment for rear seats
    for (const auto& rear_seat : rear_seats) {
        total_weight += rear_seat.weight;
        total_moment += rear_seat.weight * rear_seat.arm;
    }

    total_weight += num_gallons * fuel_per_gallon;
    total_moment += num_gallons * fuel_per_gallon * fuel_arm;
    total_weight += baggage_weight;
    total_moment += baggage_weight * baggage_arm;

    // Check if within design limits
    bool within_limits = total_weight <= 2950 && total_moment / total_weight >= 82.1 && total_moment / total_weight <= 84.7;

    if (!within_limits) {
        // Calculate required fuel adjustment
        double max_weight = 2950;
        double max_cg = 84.7;
        double min_cg = 82.1;
        double current_cg = total_moment / total_weight;

        double additional_fuel_needed = 0;
        if (total_weight > max_weight) {
            additional_fuel_needed = (total_weight - max_weight) / fuel_per_gallon;
        }
        double adjusted_cg = current_cg;
        if (current_cg > max_cg) {
            adjusted_cg = max_cg;
        }
        else if (current_cg < min_cg) {
            adjusted_cg = min_cg;
        }

        double adjusted_weight = total_moment / adjusted_cg;

        cout << "Total weight exceeds design limits." << endl;
        cout << "Additional fuel needed: " << fixed << setprecision(2) << additional_fuel_needed << " gallons" << endl;
        cout << "Adjusted gross weight: " << adjusted_weight << " lbs" << endl;
        cout << "Adjusted C.G. location: " << adjusted_cg << " inches" << endl;
    }
    else {
        cout << "Total weight and C.G. location are within design limits." << endl;
        cout << "Gross weight: " << total_weight << " lbs" << endl;
        cout << "C.G. location: " << total_moment / total_weight << " inches" << endl;
    }

    return 0;
}
