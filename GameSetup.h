#ifndef GAMESETUP_H
#define GAMESETUP_H
#include "Grid.h"
#include "AutoPlacement.h"
#include "ManualPlacement.h"
#include <string>

class GameSetup {
private:
    void choosePlacement(Grid& grid, const std::string& playerName); // Вибір способу розміщення кораблів
public:
    void setupGrids(Grid& player1Grid, Grid& player2Grid); // Налаштування сіток для двох гравців
    void setupSinglePlayer(Grid& userGrid, Grid& botGrid); // Налаштування сіток для одного гравця і бота
    void initializeGrid(Grid& grid); // Ініціалізація сітки
};

#endif 
