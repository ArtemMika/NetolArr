#pragma once
#include <vector>
#include <string>
#include "Transport.h"
#include <algorithm>

enum class RaceType {
    GROUND,
    AIR,
    MIXED
};

class Race {
private:
    std::vector<Transport*> participants;
    double distance;
    RaceType type;

public:
    Race(RaceType type, double distance);
    void addParticipant(Transport* transport);
    std::vector<std::pair<std::string, double>> startRace() const;
    bool canAdd(Transport* transport) const;
    RaceType getType() const;

    // Добавляем новый метод
    int getParticipantsCount() const;
};