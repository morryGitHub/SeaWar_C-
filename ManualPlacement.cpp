#include "ManualPlacement.h"
#include <iostream>
#include <sstream>
using std::cout;

void ManualPlacement::placeShips(Grid& grid) { // Реалізує розміщення кораблів вручну
    placeShipManually(grid, 'A', 4); // Розміщує Aircraft Carrier
    for (int i = 0; i < 2; i++) // Розміщує два Battleship
        placeShipManually(grid, 'B', 3);
    for (int i = 0; i < 3; i++) // Розміщує три Destroyer
        placeShipManually(grid, 'D', 2);
    for (int i = 0; i < 4; i++) // Розміщує чотири Corvette
        placeShipManually(grid, 'C', 1);
}

void ManualPlacement::placeShipManually(Grid& grid, char shipSymbol, int size) { // Ручне розміщення одного корабля
    int x, y;
    while (true) {
        Utility::clearScreen(); // Очищає екран
        std::stringstream ss;
        Utility::printSeparated(); // Друкує розділову лінію
        ss << "Placement of the " << getShipName(shipSymbol) << " (" << size << " decks).";
        Utility::printCentered(ss.str()); // Друкує повідомлення про розміщення корабля
        cout << "\n";

        grid.print(); // Друкує поточний стан сітки
        char orientation = 'h';
        if (size > 1) { // Запитує орієнтацію корабля, якщо його розмір більше 1
            std::string orientationStr;
            while (true) {
                Utility::printCentered("Enter orientation (h/v): ");
                orientationStr = Utility::readCentered();
                if (orientationStr.size() == 1 && (orientationStr[0] == 'h' || orientationStr[0] == 'v')) {
                    orientation = orientationStr[0];
                    break; // Вихід з циклу, якщо орієнтація введена коректно
                } else {
                    Utility::printCentered("Invalid orientation. Please enter 'h' for horizontal or 'v' for vertical.");
                }
            }
        }

        Utility::printCentered("Enter x and y coordinates (space-separated): ");
        std::string coordinates = Utility::readCentered();
        std::istringstream iss(coordinates);
        iss >> x >> y;

        if (orientation == 'h') { 
            if (y + size > GRID_SIZE || !grid.canPlaceShip(x, y, size, orientation)) { // Перевірка, чи можна розмістити корабель
                Utility::printCentered("Can't place here. Please try again.");
                continue;
            }
            grid.placeShip(shipSymbol, size, orientation, x, y); // Розміщення корабля на сітці
            break;
        } else {
            if (x + size > GRID_SIZE || !grid.canPlaceShip(x, y, size, orientation)) { // Перевірка, чи можна розмістити корабель
                Utility::printCentered("Can't place here. Please try again.");
                continue;
            }
            grid.placeShip(shipSymbol, size, orientation, x, y); // Розміщення корабля на сітці
            break;
        }
    }
}

std::string ManualPlacement::getShipName(char shipSymbol) { // Повертає назву корабля за його символом
    switch (shipSymbol) {
        case 'A': return "Aircraft Carrier"; // Символ 'A' відповідає Aircraft Carrier
        case 'B': return "Battleship"; // Символ 'B' відповідає Battleship
        case 'D': return "Destroyer"; // Символ 'D' відповідає Destroyer
        case 'C': return "Corvette"; // Символ 'C' відповідає Corvette
        default: return ""; // Повертає порожній рядок, якщо символ не відповідає жодному кораблю
    }
}
