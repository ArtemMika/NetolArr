#include "MagicCarpet.h"

MagicCarpet::MagicCarpet() : AirTransport(10) { }

double MagicCarpet::getDistanceReduction(double distance) const 
{
    if (distance < 1000) return 0;
    if (distance < 5000) return 0.03;
    if (distance < 10000) return 0.10;
    return 0.05;
}

std::string MagicCarpet::getName() const
{
    return "Ковёр-самолёт";
}