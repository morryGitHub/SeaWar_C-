#include "GamePlay.h"
#include "Utility.h"
#include "BattleshipGame.h"
#include "Turn.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <unordered_set>

void GamePlay:: displayMessages() {
    for (const auto& message : messages) {
        Utility::printCentered(message);
    }
}

void GamePlay::playTwoPlayerGame(Grid& player1Grid, Grid& player2Grid, std::vector<std::pair<int, int>>& player1Shots, std::vector<std::pair<int, int>>& player2Shots, int& player1HitCount, int& player2HitCount) {
    Utility::clearScreen(); // Очищення екрану
    printGrids(player1Grid, player2Grid, "Player 1", "Player 2", false); // Виведення сіток гравців без розкриття
    bool player1Turn = true; // Визначення, хто починає

    while (true) { // Основний ігровий цикл
        if (player1Turn) { // Хід гравця 1
            Utility::clearScreen();
            printCurrentPlayerGrid(player1Grid, player2Grid,"Player 1", "Player 2", player1Shots, false); // Виведення сіток
            Utility::printCentered("Player 1's turn:\n"); // Виведення інформації про хід
            Utility::delay(2000);
            Turn::userTurn(*this, player1Shots, player2Grid, player1HitCount, player1Turn, false); // Обробка ходу гравця 1
            if (battleshipGame->checkWin(player2Grid)) { // Перевірка на перемогу
                Utility::clearScreen(); // Очищення екрану
                printGrids(player1Grid, player2Grid, "Player 1", "Player 2", true); // Виведення сіток з розкриттям
                Utility::printSeparated(); // Виведення розділювальної лінії
                Utility::printCentered("Player 1 wins!\n"); // Повідомлення про перемогу гравця 1
                break; // Завершення циклу
            }
        } else { // Хід гравця 2
            Utility::clearScreen();
            printCurrentPlayerGrid(player2Grid, player1Grid, "Player 2", "Player 1", player2Shots, false); // Виведення сіток
            Utility::printCentered("Player 2's turn:\n"); // Виведення інформації про хід
            Utility::delay(2000);
            Turn::userTurn(*this, player2Shots, player1Grid, player2HitCount, player1Turn, false); // Обробка ходу гравця 2
            if (battleshipGame->checkWin(player2Grid)) { // Перевірка на перемогу
                Utility::clearScreen(); // Очищення екрану
                printGrids(player2Grid, player1Grid, "Player 2", "Player 1", true); // Виведення сіток з розкриттям
                Utility::printSeparated(); // Виведення розділювальної лінії
                Utility::printCentered("Player 2 wins!\n"); // Повідомлення про перемогу гравця 2
                break; // Завершення циклу
            }
        }
        player1Turn = !player1Turn; // Перемикання ходу між гравцями
    }
}

void GamePlay::playSinglePlayerGame(Grid& userGrid, Grid& botGrid, std::vector<std::pair<int, int>>& userShots, std::vector<std::pair<int, int>>& botShots, int& userHitCount, int& botHitCount, bool& revealBotGrid) {
    
    Utility::clearScreen();
    printGrids(userGrid, botGrid, "Player 1", "Bot", revealBotGrid);
    bool player1Turn = true;

    while (true) {
        Turn::userTurn(*this, userShots, botGrid, userHitCount, player1Turn, true);
        if (battleshipGame->checkWin(botGrid)) {
            Utility::clearScreen();
            printGrids(userGrid, botGrid, "Player 1", "Bot", revealBotGrid);
            Utility::printCentered("Congratulations! You have won!\n");
            break;
        }
        Turn::computerTurn(*this);
        if (battleshipGame->checkWin(userGrid)) {
            Utility::clearScreen();
            printGrids(userGrid, botGrid, "Player 1", "Bot", revealBotGrid);
            Utility::printCentered("Game over! The computer has won!\n");
            break;
        }
    }
}

void GamePlay::printCurrentPlayerGrid(const Grid& playerGrid, const Grid& opponentGrid,const std::string& label1, const std::string& label2, const std::vector<std::pair<int, int>>& shots, bool revealBotGrid) {
    int terminalWidth = 210;
    int gridWidth = 10;
    int cellWidth = 2;
    int padding = (terminalWidth - (4 * gridWidth * cellWidth + 4 * gridWidth) - 6);

    for (int i = 0; i < 10; i++) {
        std::cout << "\n";
    }

    std::cout << std::setw(padding + 8) << "" << label1 << std::setw(15) << "" << label2 << "\n" << std::endl;

    for (int i = 0; i < padding; i++) {
        std::cout << " ";
    }
    std::cout << "  ";
    for (int j = 0; j < 10; j++) {
        std::cout << j << " ";
    }
    std::cout << "    ";
    for (int j = 0; j < 10; j++) {
        std::cout << j << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < 10; i++) {
        for (int k = 0; k < padding; k++) {
            std::cout << " ";
        }

        std::cout << i << " ";
        for (int j = 0; j < 10; j++) {
            switch (playerGrid.grid[i][j]) {
                case WATER: std::cout << "· "; break;
                case SHIP: std::cout << "# "; break;
                case HIT: std::cout << "H "; break;
                case DESTROYED: std::cout << "X "; break;
                case MISS: std::cout << "* "; break;
                case BOOM: std::cout << "~ "; break;
            }
        }

        std::cout << "  " << i << " ";
        for (int j = 0; j < 10; j++) {
            if (revealBotGrid) {
                switch (opponentGrid.grid[i][j]) {
                    case WATER: std::cout << "· "; break;
                    case SHIP: std::cout << "# "; break;
                    case HIT: std::cout << "H "; break;
                    case DESTROYED: std::cout << "X "; break;
                    case MISS: std::cout << "* "; break;
                    case BOOM: std::cout << "~ "; break;
                }
            } else {
                switch (opponentGrid.grid[i][j]) {
                    case WATER: std::cout << "· "; break;
                    case HIT: std::cout << "H "; break;
                    case MISS: std::cout << "* "; break;
                    case DESTROYED: std::cout << "X "; break;
                    case BOOM: std::cout << "~ "; break;
                    default: std::cout << "· "; break;
                }
            }
        }
        std::cout << "\n";
    }

    for (int i = 0; i < 3; i++) {
        std::cout << "\n";
    }
}


void GamePlay::printGrids(const Grid& grid1, const Grid& grid2, const std::string& label1, const std::string& label2, bool revealGrid2) {
    int terminalWidth = 210;
    int gridWidth = 10;
    int cellWidth = 2;
    int padding = (terminalWidth - (4 * gridWidth * cellWidth + 4 * gridWidth) - 6);

    for (int i = 0; i < 10; i++) {
        std::cout << "\n";
    }
    std::cout << std::setw(padding + 9) << "" << label1 << std::setw(16) << "" << label2 << "\n" << std::endl;
    for (int i = 0; i < padding; i++) {
        std::cout << " ";
    }

    std::cout << "  ";
    for (int j = 0; j < 10; j++) {
        std::cout << j << " ";
    }
    std::cout << "    ";
    for (int j = 0; j < 10; j++) {
        std::cout << j << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < padding; i++) {
        std::cout << " ";
    }

    for (int i = 0; i < 10; i++) {
        std::cout << i << " ";
        for (int j = 0; j < 10; j++) {
            switch (grid1.grid[i][j]) {
                case WATER: std::cout << "· "; break;
                case SHIP: std::cout << "# "; break;
                case HIT: std::cout << "H "; break;
                case DESTROYED: std::cout << "X "; break;
                case MISS: std::cout << "* "; break;
                case BOOM: std::cout << "~ "; break;
            }
        }
        std::cout << "  " << i << " ";
        for (int j = 0; j < 10; j++) {
            if (revealGrid2) {
                switch (grid2.grid[i][j]) {
                    case WATER: std::cout << "· "; break;
                    case SHIP: std::cout << "# "; break;
                    case HIT: std::cout << "H "; break;
                    case DESTROYED: std::cout << "X "; break;
                    case MISS: std::cout << "* "; break;
                    case BOOM: std::cout << "~ "; break;
                }
            } else {
                switch (grid2.grid[i][j]) {
                    case WATER: std::cout << "· "; break;
                    case HIT: std::cout << "H "; break;
                    case DESTROYED: std::cout << "X "; break;
                    case MISS: std::cout << "* "; break;
                    case BOOM: std::cout << "~ "; break;
                    default: std::cout << "· "; break;
                }
            }
        }
        std::cout << "\n";
        for (int i = 0; i < padding; i++) {
            std::cout << " ";
        }
    }
    std::cout << "\n" << std::endl;
}

