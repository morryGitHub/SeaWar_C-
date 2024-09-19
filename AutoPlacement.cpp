#include "AutoPlacement.h"
#include <cstdlib>

void AutoPlacement::placeShips(Grid& grid) { // Метод для автоматичного розміщення кораблів на сітці
    placeShip(grid, 'A', 4); // Розміщує Aircraft Carrier
    for (int i = 0; i < 2; i++) // Розміщує два Battleship
        placeShip(grid, 'B', 3);
    for (int i = 0; i < 3; i++) // Розміщує три Destroyer
        placeShip(grid, 'D', 2);
    for (int i = 0; i < 4; i++) // Розміщує чотири Corvette
        placeShip(grid, 'C', 1);
}

void AutoPlacement::placeShip(Grid& grid, char shipSymbol, int size) { // Приватний метод для розміщення одного корабля на сітці
    int x, y, orientation;
    bool validPlacement = false;
    while (!validPlacement) { // Повторюємо, поки не знайдемо допустиме місце для розміщення
        x = rand() % GRID_SIZE; // Випадкове значення для координати x
        y = rand() % GRID_SIZE; // Випадкове значення для координати y
        orientation = rand() % 2; // Випадкове значення для орієнтації (0 для горизонтальної, 1 для вертикальної)

        if (grid.canPlaceShip(x, y, size, orientation == 0 ? 'h' : 'v')) { // Перевіряємо, чи можна розмістити корабель
            validPlacement = true; // Якщо можна, то встановлюємо прапорець
            grid.placeShip(shipSymbol, size, orientation == 0 ? 'h' : 'v', x, y); // Розміщуємо корабель на сітці
        }
    }
}
