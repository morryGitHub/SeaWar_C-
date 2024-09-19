#ifndef MANUALPLACEMENT_H
#define MANUALPLACEMENT_H
#include "Placement.h"
#include "Utility.h"

class ManualPlacement : public Placement { //клас для розміщення кораблів вручну
private:
    void placeShipManually(Grid& grid, char shipSymbol, int size); // Метод для ручного розміщення одного корабля на сітці
    std::string getShipName(char shipSymbol); // Метод для отримання назви корабля за його символом
public:
    void placeShips(Grid& grid) override; // Метод для розміщення кораблів на сітці
};

#endif 
