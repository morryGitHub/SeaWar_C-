#ifndef PLACEMENT_H
#define PLACEMENT_H
#include "Grid.h"

class Placement { // Абстрактний клас Placement, який визначає інтерфейс для розміщення кораблів
public:
    virtual void placeShips(Grid& grid) = 0; //Віртуальний метод для розміщення кораблів на сітці
};

#endif 
