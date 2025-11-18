#include "Boots.h"

Boots::Boots()
    : GroundTransport(30, 40) {
}

double Boots::getRestTime(int restCount) const {
    return (restCount == 0) ? 2 : 4;
}

std::string Boots::getName() const {
    return "Ботинки-вездеходы";
}