#include "GameSetup.h"
#include "Utility.h"
#include <iostream>
#include <ctime>

void GameSetup::setupGrids(Grid& player1Grid, Grid& player2Grid) { // Налаштування сіток для двох гравців
    initializeGrid(player1Grid); // Ініціалізація сітки гравця 1
    initializeGrid(player2Grid); // Ініціалізація сітки гравця 2

    Utility::clearScreen(); // Очищення екрану
    Utility::printSeparated(); // Виведення розділювальної лінії

    Utility::printCentered("Player 1: Choose placement method: "); // Запит на вибір методу розміщення для гравця 1
    Utility::printCentered("1. Automatic"); // Автоматичне розміщення
    Utility::printCentered("2. Manual"); // Ручне розміщення
    choosePlacement(player1Grid, "Player 1"); // Виклик функції вибору розміщення

    Utility::clearScreen(); // Очищення екрану
    Utility::printSeparated(); // Виведення розділювальної лінії

    Utility::printCentered("Player 2: Choose placement method: "); // Запит на вибір методу розміщення для гравця 2
    Utility::printCentered("1. Automatic"); // Автоматичне розміщення
    Utility::printCentered("2. Manual"); // Ручне розміщення
    choosePlacement(player2Grid, "Player 2"); // Виклик функції вибору розміщення

    Utility::clearScreen(); // Очищення екрану
}

void GameSetup::setupSinglePlayer(Grid& userGrid, Grid& botGrid) { // Налаштування сіток для одного гравця і бота
    initializeGrid(userGrid); // Ініціалізація сітки користувача
    initializeGrid(botGrid); // Ініціалізація сітки бота

    Utility::printSeparated(); // Виведення розділювальної лінії
    Utility::printCentered("Choose placement method: "); // Запит на вибір методу розміщення
    Utility::printCentered("1. Automatic"); // Автоматичне розміщення
    Utility::printCentered("2. Manual"); // Ручне розміщення

    choosePlacement(userGrid, "Player"); // Виклик функції вибору розміщення для користувача

    AutoPlacement autoPlacement; // Створення об'єкту автоматичного розміщення
    autoPlacement.placeShips(botGrid); // Автоматичне розміщення кораблів для бота
}

void GameSetup::choosePlacement(Grid& grid, const std::string& playerName) { // Функція вибору методу розміщення
    int choice = std::stoi(Utility::readCentered()); // Читання вибору користувача
    Utility::clearInput(); // Очищення введення

    if (choice == 1) { // Якщо вибрано автоматичне розміщення
        bool satisfied = false; // Прапорець задоволення розміщенням
        AutoPlacement autoPlacement; // Створення об'єкту автоматичного розміщення

        while (!satisfied) { // Поки не задоволені розміщенням
            Utility::clearScreen(); // Очищення екрану
            initializeGrid(grid); // Ініціалізація сітки
            autoPlacement.placeShips(grid); // Автоматичне розміщення кораблів
            grid.print(); // Виведення сітки

            Utility::printCentered(playerName + ": Are you satisfied with the ship placement? (y/n):\n "); // Запит на задоволення розміщенням
            char response = Utility::readCentered()[0]; // Читання відповіді користувача
            Utility::clearInput(); // Очищення введення
            if (response == 'y' || response == 'Y') { // Якщо задоволені
                satisfied = true; // Встановлення прапорця задоволення
            }
        }
    } else { // Якщо вибрано ручне розміщення
        ManualPlacement manualPlacement; // Створення об'єкту ручного розміщення
        manualPlacement.placeShips(grid); // Ручне розміщення кораблів
    }
}

void GameSetup::initializeGrid(Grid& grid) { // Ініціалізація сітки
    for (int i = 0; i < GRID_SIZE; ++i) { // Перебір рядків сітки
        for (int j = 0; j < GRID_SIZE; ++j) { // Перебір стовпців сітки
            grid.grid[i][j] = WATER; // Встановлення стану "Вода" для кожної клітинки
        }
    }
}
