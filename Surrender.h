#ifndef SURRENDER_H
#define SURRENDER_H

class BattleshipGame; // Оголошення класу BattleshipGame

class Surrender {
public:
    static void handleSurrenderAndRematch(BattleshipGame& battleshipGame, bool isSinglePlay); // Статичний метод для обробки капітуляції і запиту на перегравання
};

#endif 
