#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include "Grid.h"
#include <vector>
#include <string>

class BattleshipGame;

class GamePlay {
private:
    void printCurrentPlayerGrid(const Grid& playerGrid, const Grid& opponentGrid,const std::string& label1, const std::string& label2, const std::vector<std::pair<int, int>>& shots, bool revealBotGrid); // Виведення сітки поточного гравця
public:
    GamePlay(BattleshipGame* game) : battleshipGame(game) {} // Конструктор, що приймає вказівник на гру
    void playTwoPlayerGame(Grid& player1Grid, Grid& player2Grid, std::vector<std::pair<int, int>>& player1Shots, std::vector<std::pair<int, int>>& player2Shots, int& player1HitCount, int& player2HitCount); // Метод для гри між двома гравцями
    void playSinglePlayerGame(Grid& userGrid, Grid& botGrid, std::vector<std::pair<int, int>>& userShots, std::vector<std::pair<int, int>>& botShots, int& userHitCount, int& botHitCount, bool& revealBotGrid); // Метод для гри між гравцем і ботом
    void displayMessages();
    void printGrids(const Grid& grid1, const Grid& grid2, const std::string& label1, const std::string& label2, bool revealGrid2); // Виведення двох сіток з мітками
    std::vector<std::string> messages; // Додавання вектора повідомлень
    BattleshipGame* battleshipGame; // Вказівник на гру
    GamePlay* gamePlay;
};

#endif 
