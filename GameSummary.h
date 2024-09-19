#ifndef GAMESUMMARY_H
#define GAMESUMMARY_H
#include "Grid.h"
#include "Leaderboard.h"
#include <vector>
#include <string>

class BattleshipGame;

class GameSummary {
private:
    BattleshipGame* battleshipGame;
public:
    void endGameSummary(bool isSinglePlayer, const Grid& player1Grid, const Grid& player2Grid, const std::vector<std::pair<int, int>>& player1Shots, const std::vector<std::pair<int, int>>& player2Shots, int player1HitCount, int player2HitCount, const std::vector<std::pair<int, int>>& userShots, const std::vector<std::pair<int, int>>& botShots, int userHitCount, int botHitCount, Leaderboard& leaderboard); // Завершення гри та підбиття підсумків
    void printLeaderboard(const std::vector<std::vector<std::string>>& table); // Виведення таблиці лідерів
};

#endif 
