#pragma once
#include <string>

class Transport {
public:
    virtual ~Transport() = default;
    virtual double getSpeed() const = 0;
    virtual double calculateTime(double distance) const = 0;
    virtual std::string getType() const = 0;
    virtual std::string getName() const = 0;
};