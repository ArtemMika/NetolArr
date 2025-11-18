#include "Race.h"
#include "Transport.h"
#include <algorithm>

Race::Race(RaceType type, double distance)
    : type(type), distance(distance) {
}

void Race::addParticipant(Transport* transport) {
    participants.push_back(transport);
}

std::vector<std::pair<std::string, double>> Race::startRace() const {
    std::vector<std::pair<std::string, double>> results;
    for (const auto& participant : participants) {
        results.emplace_back(participant->getName(), participant->calculateTime(distance));
    }
    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
        });
    return results;
}

bool Race::canAdd(Transport* transport) const {
    if (getType() == RaceType::GROUND && transport->getType() != "ground") return false;
    if (getType() == RaceType::AIR && transport->getType() != "air") return false;
    for (const auto& participant : participants) {
        if (participant->getName() == transport->getName()) return false;
    }
    return true;
}

RaceType Race::getType() const {
    return type;
}

// Добавляем реализацию нового метода
int Race::getParticipantsCount() const {
    return participants.size();
}