#ifndef AUTOPLACEMENT_H
#define AUTOPLACEMENT_H
#include "Placement.h"

class AutoPlacement : public Placement { //Клас для розміщення кораблів автоматично
private:
    void placeShip(Grid& grid, char shipSymbol, int size);  // Метод для розміщення одного корабля на сітці
public:
    void placeShips(Grid& grid) override; // Метод для розміщення кораблів на сітці
};

#endif 
