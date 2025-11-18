#include "Eagle.h"

Eagle::Eagle()
    : AirTransport(40) {
}

double Eagle::getDistanceReduction(double distance) const {
    if (distance < 1000) return 0.05;
    if (distance < 5000) return 0.10;
    return 0.15;
}

std::string Eagle::getName() const {
    return "Îð¸ë";
}