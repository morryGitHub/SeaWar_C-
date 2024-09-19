#ifndef BATTLESHIPGAME_H
#define BATTLESHIPGAME_H
#include "Grid.h"
#include "GameSetup.h"
#include "GamePlay.h"
#include "GameSummary.h"
#include "Leaderboard.h"
#include <vector>
#include <string>

class BattleshipGame {
private:
    void resetGame(); // Метод для скидання стану гри
    void addMessage(const std::string& message); // Метод для додавання повідомлення
    void clearMessages(); // Метод для очищення повідомлень  
public:
    BattleshipGame() : gamePlay(this) {} // Конструктор для ініціалізації гри, передає себе в GamePlay
    void play(); // Основний метод для запуску гри
    void displayMessages() const; // Метод для відображення повідомлень
    bool userSurrendered; // Флаг для показу здачі гравця
    bool checkWin(const Grid& grid); // Метод для перевірки перемоги

    Grid player1Grid; // Сітка для гравця 1
    Grid player2Grid; // Сітка для гравця 2
    Grid userGrid; // Сітка для користувача
    Grid botGrid;  // Сітка для бота
    int player1HitCount = 0; // Лічильники попадань для гравця 1
    int player2HitCount = 0; // Лічильники попадань для гравця 2
    int userHitCount = 0; // Лічильники попадань для користувача
    int botHitCount = 0; // Лічильники попадань для бота
    bool revealBotGrid = false; // Флаг для показу сітки бота

    std::vector<std::pair<int, int>> player1Shots; // Вектори для зберігання ходів гравця 1
    std::vector<std::pair<int, int>> player2Shots; // Вектори для зберігання ходів гравця 2
    std::vector<std::pair<int, int>> userShots; // Вектори для зберігання ходів користувача
    std::vector<std::pair<int, int>> botShots; // Вектори для зберігання ходів бота
    std::vector<std::string> messages; // Вектор для зберігання повідомлень

    GameSetup gameSetup; // Об'єкт для налаштування гри
    GamePlay gamePlay; // Об'єкт для ігрового процесу
    GameSummary gameSummary; // Об'єкт для підбиття підсумків гри
    Leaderboard leaderboard; // Об'єкт для роботи з таблицею лідерів
};

#endif 
