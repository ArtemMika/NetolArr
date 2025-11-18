#pragma once
#include "GroundTransport.h"

class Centaur : public GroundTransport {
public:
    Centaur();
    double getRestTime(int restCount) const override;
    std::string getName() const override;
};