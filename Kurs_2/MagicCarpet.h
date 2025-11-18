#pragma once
#include "AirTransport.h"

class MagicCarpet : public AirTransport
{
public:
    MagicCarpet();
    double getDistanceReduction(double distance) const override;
    std::string getName() const override;
};