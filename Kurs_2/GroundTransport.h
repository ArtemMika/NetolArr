#pragma once
#include "Transport.h"

class GroundTransport : public Transport {
protected:
    int speed;
    int maxMoveTime;

    virtual double getRestTime(int restCount) const = 0;

public:
    GroundTransport(int speed, int maxMoveTime);
    double getSpeed() const override;
    std::string getType() const override;
    double calculateTime(double distance) const override;
};