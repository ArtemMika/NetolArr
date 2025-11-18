#pragma once
#include "AirTransport.h"

class Eagle : public AirTransport {
public:
    Eagle();
    double getDistanceReduction(double distance) const override;
    std::string getName() const override;
};