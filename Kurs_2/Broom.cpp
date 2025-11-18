#include "Broom.h"

Broom::Broom()
    : AirTransport(35) {
}

double Broom::getDistanceReduction(double distance) const {
    if (distance < 1000) return 0.02;
    if (distance < 5000) return 0.05;
    return 0.08;
}

std::string Broom::getName() const {
    return "Метла";
}