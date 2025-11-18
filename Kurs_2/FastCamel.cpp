#include "FastCamel.h"

FastCamel::FastCamel()
    : GroundTransport(20, 25) {
}

double FastCamel::getRestTime(int restCount) const {
    return (restCount == 0) ? 3 : 5;
}

std::string FastCamel::getName() const {
    return "Верблюд-быстроход";
}