#ifndef GRID_H
#define GRID_H
#include "ShipInfo.h"
#include <vector>

enum CellState { 
    WATER, // Вода
    SHIP, // Корабель
    HIT, // Попадання
    DESTROYED, // Знищений корабель
    MISS, // Промах
    BOOM // Підірвана 
};

const int GRID_SIZE = 10; // Розмір поля

class Grid {
    private:
    void markSurroundingAsMiss(const ShipInfo& ship);
public:
    Grid(); // Конструктор для ініціалізації сітки
    void print() const; // Метод для виведення сітки
    bool canPlaceShip(int x, int y, int size, char orientation); // Перевірка можливості розміщення корабля
    void placeShip(char shipSymbol, int size, char orientation, int x, int y); // Метод для розміщення корабля
    bool hit(int x, int y); // Метод для обробки попадання
    std::vector<std::vector<CellState>> grid; // Сітка поля
    std::vector<ShipInfo> ships; // Інформація про кораблі
};

#endif
