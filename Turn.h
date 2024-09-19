#ifndef TURN_H
#define TURN_H
#include "BattleshipGame.h"


class Turn {
private:
    static bool checkWin(const Grid& grid); // Метод для перевірки перемоги
public:
    static void userTurn(GamePlay& gamePlay, std::vector<std::pair<int, int>>& playerShots, Grid& opponentGrid, int& playerHitCount, bool& player1Turn, bool isSinglePlay); // Метод для обробки ходу користувача
    static void computerTurn(GamePlay& gamePlay); // Метод для обробки ходу комп'ютера
    
};

#endif 
