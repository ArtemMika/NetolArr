#include "GroundTransport.h"

GroundTransport::GroundTransport(int speed, int maxMoveTime)
    : speed(speed), maxMoveTime(maxMoveTime) {
}

double GroundTransport::getSpeed() const {
    return speed;
}

std::string GroundTransport::getType() const {
    return "ground";
}

double GroundTransport::calculateTime(double distance) const {
    double movingTime = distance / speed;
    int fullCycles = static_cast<int>(movingTime / maxMoveTime);
    double remainingTime = movingTime - fullCycles * maxMoveTime;

    double totalRestTime = 0;
    for (int i = 0; i < fullCycles; ++i) {
        totalRestTime += getRestTime(i);
    }

    return movingTime + totalRestTime;
}