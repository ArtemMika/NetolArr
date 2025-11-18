#pragma once
#include "AirTransport.h"

class Broom : public AirTransport {
public:
    Broom();
    double getDistanceReduction(double distance) const override;
    std::string getName() const override;
};