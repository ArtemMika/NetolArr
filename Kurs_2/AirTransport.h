#pragma once
#include "Transport.h"

class AirTransport : public Transport {
protected:
    int speed;

    virtual double getDistanceReduction(double distance) const = 0;

public:
    AirTransport(int speed);
    double getSpeed() const override;
    std::string getType() const override;
    double calculateTime(double distance) const override;
};