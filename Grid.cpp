#include "Grid.h"
#include <iostream>
#include <algorithm>
using std::cout;

Grid::Grid() { // Конструктор для ініціалізації сітки
    grid.resize(GRID_SIZE, std::vector<CellState>(GRID_SIZE, WATER)); // Заповнює сітку водою
}

void Grid::print() const { // Метод для виведення сітки на екран
    int terminalWidth = 210; // Ширина терміналу
    int gridWidth = 10; // Ширина сітки
    int cellWidth = 2; // Ширина однієї клітинки
    int padding = (terminalWidth - (gridWidth * cellWidth + gridWidth - 1)) / 2 + 3; // Розрахунок відступу для центрування

    for (int i = 0; i < 10; i++) { // Виводимо порожні рядки для відступу
        cout << "\n";
    }

    for (int i = 0; i < padding; i++) { // Відступ перед сіткою
        cout << " ";
    }

    std::cout << "  ";
    for (int j = 0; j < 10; j++) // Виводимо індекси стовпців
        cout << j << " ";
    cout << "\n";

    for (int i = 0; i < padding; i++) { // Відступ перед рядками сітки
        cout << " ";
    }

    for (int i = 0; i < 10; i++) {
        cout << i << " "; // Виводимо індекси рядків
        for (int j = 0; j < 10; j++) {
            switch (grid[i][j]) { // Виводимо стан кожної клітинки
                case WATER: std::cout << "· "; break;
                case SHIP: std::cout << "# "; break;
                case HIT: std::cout << "H "; break;
                case DESTROYED: std::cout << "X "; break;
                case BOOM: std::cout << "^ "; break;
                case MISS: std::cout << "* "; break;
            }
        }
        cout << "\n";
        for (int k = 0; k < padding; k++) { // Відступ між рядками сітки
            cout << " ";
        }
    }
    cout << "\n" << std::endl;
}

bool Grid::canPlaceShip(int x, int y, int size, char orientation) { // Перевірка можливості розміщення корабля
    for (int i = 0; i < size; ++i) {
        int xi = x + (orientation == 'v' ? i : 0); // Координата x для вертикальної орієнтації
        int yi = y + (orientation == 'h' ? i : 0); // Координата y для горизонтальної орієнтації

        if (xi >= GRID_SIZE || yi >= GRID_SIZE || grid[xi][yi] != WATER) // Перевірка виходу за межі сітки та наявності іншого об'єкта
            return false;

        for (int dx = -1; dx <= 1; ++dx) { // Перевірка сусідніх клітинок
            for (int dy = -1; dy <= 1; ++dy) {
                int nx = xi + dx, ny = yi + dy;
                if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE && grid[nx][ny] != WATER)
                    return false;
            }
        }
    }
    return true; // Корабель можна розмістити
}

void Grid::placeShip(char shipSymbol, int size, char orientation, int x, int y) { // Розміщення корабля на сітці
    ShipInfo ship(shipSymbol, size); // Створення об'єкта ShipInfo
    for (int i = 0; i < size; ++i) {
        int xi = x + (orientation == 'v' ? i : 0); // Координата x для вертикальної орієнтації
        int yi = y + (orientation == 'h' ? i : 0); // Координата y для горизонтальної орієнтації
        grid[xi][yi] = SHIP; // Розміщення частини корабля на сітці
        ship.coordinates.push_back({xi, yi}); // Додавання координат до списку координат корабля
    }
    ships.push_back(ship); // Додавання корабля до списку кораблів
}

bool Grid::hit(int x, int y) {
    for (auto& ship : ships) {
        for (auto& coord : ship.coordinates) {
            if (coord.first == x && coord.second == y) {
                ship.hit();
                if (ship.isDestroyed()) {
                    for (auto& coord : ship.coordinates) {
                        grid[coord.first][coord.second] = DESTROYED;
                    }
                    markSurroundingAsMiss(ship);
                } else {
                    grid[x][y] = HIT;
                }
                return true;
            }
        }
    }
    grid[x][y] = MISS;
    return false;
}

void Grid::markSurroundingAsMiss(const ShipInfo& ship) {
    for (const auto& coord : ship.coordinates) {
        int x = coord.first;
        int y = coord.second;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE) {
                    if (grid[nx][ny] == WATER) {
                        grid[nx][ny] = BOOM;
                    } else if (grid[nx][ny] == DESTROYED) {
                        // Skip if already marked as destroyed
                        continue;
                    }
                }
            }
        }
    }
}
