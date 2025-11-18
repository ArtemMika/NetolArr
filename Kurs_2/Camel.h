#pragma once
#include "GroundTransport.h"

class Camel : public GroundTransport {
public:
    Camel();
    double getRestTime(int restCount) const override;
    std::string getName() const override;
};