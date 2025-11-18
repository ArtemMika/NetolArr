#pragma once
#include "GroundTransport.h"

class Boots : public GroundTransport {
public:
    Boots();
    double getRestTime(int restCount) const override;
    std::string getName() const override;
};