#pragma once
#include "GroundTransport.h"

class FastCamel : public GroundTransport {
public:
    FastCamel();
    double getRestTime(int restCount) const override;
    std::string getName() const override;
};