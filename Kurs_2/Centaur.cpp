#include "Centaur.h"

Centaur::Centaur()
    : GroundTransport(25, 35) {
}

double Centaur::getRestTime(int restCount) const {
    return (restCount == 0) ? 4 : 6;
}

std::string Centaur::getName() const {
    return "Кентавр";
}