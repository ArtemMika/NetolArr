#include "Camel.h"

Camel::Camel()
    : GroundTransport(10, 30) {
}

double Camel::getRestTime(int restCount) const {
    return (restCount == 0) ? 5 : 8;
}

std::string Camel::getName() const {
    return "Верблюд";
}