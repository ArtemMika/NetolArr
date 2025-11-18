#include <iostream>
#include <vector>
#include <string>
#include "Race.h"
#include "Camel.h"
#include "MagicCarpet.h"
#include "FastCamel.h"
#include "Centaur.h"
#include "Boots.h"
#include "Eagle.h"
#include "Broom.h"
#include <algorithm>
#include <windows.h>

void displayRaceTypeMenu() {
    std::cout << "Выберите тип гонки:\n";
    std::cout << "1. Наземная гонка\n";
    std::cout << "2. Воздушная гонка\n";
    std::cout << "3. Смешанная гонка\n";
}

RaceType getRaceType() {
    int choice;
    do {
        displayRaceTypeMenu();
        std::cin >> choice;
    } while (choice < 1 || choice > 3);
    return static_cast<RaceType>(choice - 1);
}

double getDistance() {
    double distance;
    do {
        std::cout << "Введите дистанцию (км): ";
        std::cin >> distance;
    } while (distance <= 0);
    return distance;
}

void registerParticipants(Race& race) {
    std::vector<Transport*> availableTransports;

    switch (race.getType()) {
    case RaceType::GROUND:
        availableTransports.push_back(new Camel());
        availableTransports.push_back(new FastCamel());
        availableTransports.push_back(new Centaur());
        availableTransports.push_back(new Boots());
        break;
    case RaceType::AIR:
        availableTransports.push_back(new MagicCarpet());
        availableTransports.push_back(new Eagle());
        availableTransports.push_back(new Broom());
        break;
    case RaceType::MIXED:
        availableTransports.push_back(new Camel());
        availableTransports.push_back(new FastCamel());
        availableTransports.push_back(new Centaur());
        availableTransports.push_back(new Boots());
        availableTransports.push_back(new MagicCarpet());
        availableTransports.push_back(new Eagle());
        availableTransports.push_back(new Broom());
        break;
    }

    std::cout << "Доступные транспортные средства:\n";
    for (size_t i = 0; i < availableTransports.size(); ++i) {
        std::cout << i + 1 << ". " << availableTransports[i]->getName() << "\n";
    }
    std::cout << "0. Закончить регистрацию\n";

    int selectedCount = 0;
    while (selectedCount < 2) {
        int choice;
        std::cout << "Выберите транспортное средство (0 — закончить регистрацию): ";
        std::cin >> choice;

        if (choice == 0) {
            if (selectedCount < 2) {
                std::cout << "Необходимо зарегистрировать минимум 2 участника!\n";
                continue;
            }
            break;
        }

        if (choice > 0 && choice <= availableTransports.size()) {
            Transport* selectedTransport = availableTransports[choice - 1];

            if (race.canAdd(selectedTransport)) {
                race.addParticipant(selectedTransport);
                selectedCount++;
                std::cout << "Ваше транспортное средство " << selectedTransport->getName() << " успешно зарегистрировано!\n";
                availableTransports.erase(availableTransports.begin() + (choice - 1));
            }
            else {
                std::cout << "Невозможно добавить это транспортное средство\n";
            }
        }
        else {
            std::cout << "Неверный выбор!\n";
        }
    }

    for (auto& transport : availableTransports) {
        delete transport;
    }
}

void chooseActionMenu() {
    std::cout << "\nВыберите действие:\n";
    std::cout << "1. Зарегистрировать транспорт\n";
    std::cout << "2. Начать гонку\n";
}

int getActionChoice() {
    int choice;
    do {
        chooseActionMenu();
        std::cin >> choice;
    } while (choice < 1 || choice > 2);
    return choice;
}

void runRace() {
    RaceType raceType = getRaceType();
    double distance = getDistance();
    Race race(raceType, distance);

    int action;
    do {
        action = getActionChoice();
        if (action == 1) {
            registerParticipants(race);
        }
    } while (action == 1); // Повторяем регистрацию, пока не выберут «начать гонку»

    // Проверка на количество зарегистрированных участников
    if (race.getParticipantsCount() < 2) {
        std::cout << "Ошибка: необходимо зарегистрировать минимум 2 участника для гонки!\n";
        std::cout << "Пожалуйста, вернитесь к регистрации транспортных средств.\n";
        return; // Возвращаемся без запуска гонки
    }

    // Запуск гонки и вывод результатов, если участников достаточно
    auto results = race.startRace();
    std::cout << "\nРезультаты гонки:\n";
    for (const auto& result : results) {
        std::cout << result.first << ": " << result.second << " часов\n";
    }
}

void endGameMenu() {
    std::cout << "\nВыберите действие:\n";
    std::cout << "1. Провести ещё одну гонку\n";
    std::cout << "2. Выйти\n";
}

int getEndGameChoice() {
    int choice;
    do {
        endGameMenu();
        std::cin >> choice;
    } while (choice < 1 || choice > 2);
    return choice;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    bool continueGame = true;
    while (continueGame) {
        runRace();

        int endChoice = getEndGameChoice();
        if (endChoice == 2) {
            continueGame = false;
        }
    }

    return 0;
}