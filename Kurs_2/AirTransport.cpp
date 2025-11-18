#include "AirTransport.h"

AirTransport::AirTransport(int speed)
    : speed(speed) {
}

double AirTransport::getSpeed() const {
    return speed;
}

std::string AirTransport::getType() const {
    return "air";
}

double AirTransport::calculateTime(double distance) const {
    double reducedDistance = distance * (1 - getDistanceReduction(distance));
    return reducedDistance / speed;
}