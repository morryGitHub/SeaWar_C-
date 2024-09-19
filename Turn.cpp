#include "Turn.h"
#include "Utility.h"
#include "Surrender.h"
#include "BattleshipGame.h"
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <unordered_set>

void Turn::userTurn(GamePlay& gamePlay, std::vector<std::pair<int, int>>& playerShots, Grid& opponentGrid, int& playerHitCount, bool& player1Turn, bool isSinglePlay) {
    int userX, userY;
    std::string input;
    bool validMove = false;
    std::ostringstream oss;
    std::unordered_set<std::string> uniqueMessages;

    while (!validMove) {
        std::cout << "\n";
        Utility::printCentered("Enter coordinates to attack (x y): "); 
        input = Utility::readCentered();
        Utility::clearInput();

        if (input == "surrender") { 
            Surrender::handleSurrenderAndRematch(*gamePlay.battleshipGame, isSinglePlay);
            return;
        }

        if (input == "SHOW") {
            gamePlay.battleshipGame->revealBotGrid = !gamePlay.battleshipGame->revealBotGrid;
            Utility::clearScreen();
            if (isSinglePlay) {
                gamePlay.printGrids(gamePlay.battleshipGame->userGrid, gamePlay.battleshipGame->botGrid, "Player 1", "Bot", gamePlay.battleshipGame->revealBotGrid);
            } else {
                gamePlay.printGrids(gamePlay.battleshipGame->player1Grid, gamePlay.battleshipGame->player2Grid, "Player 1", "Player 2", true);
            }
            continue;
        }

        std::istringstream iss(input); 
        if (!(iss >> userX >> userY) || userX < 0 || userX >= GRID_SIZE || userY < 0 || userY >= GRID_SIZE) {
            Utility::printCentered("Invalid input. Please enter valid coordinates or 'surrender'.\n");
            continue;
        }

        if (opponentGrid.grid[userX][userY] == DESTROYED || opponentGrid.grid[userX][userY] == BOOM) {
            Utility::printCentered("This field has been destroyed, please choose another location.\n");
            continue; 
        } else if(std::find(playerShots.begin(), playerShots.end(), std::make_pair(userX, userY)) != playerShots.end()) {
            Utility::printCentered("You've already shot at this position. Try again.\n");
            continue; 
        }

        playerShots.push_back(std::make_pair(userX, userY));

        if (opponentGrid.grid[userX][userY] == SHIP) { 
            opponentGrid.hit(userX, userY);
            playerHitCount++;
            oss.str(""); 
            oss.clear(); 
            oss << "Hit! Ship at (" << userX << ", " << userY << ")!";
            uniqueMessages.insert(oss.str());

            bool shipDestroyed = false;
            for (const auto& ship : opponentGrid.ships) {
                if (std::find(ship.coordinates.begin(), ship.coordinates.end(), std::make_pair(userX, userY)) != ship.coordinates.end()) {
                    if (ship.isDestroyed()) {
                        shipDestroyed = true;
                        break;
                    }
                }
            }
            if (shipDestroyed) {
                oss.str(""); 
                oss.clear(); 
                oss << "Ship destroyed!\n";
                uniqueMessages.insert(oss.str());
            }

            if (checkWin(opponentGrid)) { 
                break;
            }
        } else { 
            opponentGrid.grid[userX][userY] = MISS;
            oss.str(""); 
            oss.clear(); 

            oss << "Missed! No ship at (" << userX << ", " << userY << ").";
            uniqueMessages.insert(oss.str());
            validMove = true;
        }

        Utility::clearScreen();

        if (isSinglePlay) { 
            gamePlay.printGrids(gamePlay.battleshipGame->userGrid, gamePlay.battleshipGame->botGrid, "Player 1", "Bot", gamePlay.battleshipGame->revealBotGrid);
        } else { 
            if (player1Turn) {
                gamePlay.printGrids(gamePlay.battleshipGame->player1Grid, gamePlay.battleshipGame->player2Grid, "Player 1", "Player 2", false);
            } else {
                gamePlay.printGrids(gamePlay.battleshipGame->player2Grid, gamePlay.battleshipGame->player1Grid, "Player 2", "Player 1", false);
            }
        }
        std::cout << std::flush;
        
        for (const auto& message : uniqueMessages) {
            Utility::printCentered(message);
        }
        uniqueMessages.clear(); 
    }
}

void Turn::computerTurn(GamePlay& gamePlay) {
    int x, y;
    bool validMove = false;
    std::stringstream ss;
    std::unordered_set<std::string> uniqueMessages;
    
    while (!validMove) {
        Utility::delay(1500);
        x = rand() % GRID_SIZE;
        y = rand() % GRID_SIZE;

        if (std::find(gamePlay.battleshipGame->botShots.begin(), gamePlay.battleshipGame->botShots.end(), std::make_pair(x, y)) != gamePlay.battleshipGame->botShots.end()) {
            continue;
        }

        gamePlay.battleshipGame->botShots.push_back(std::make_pair(x, y));

        if (gamePlay.battleshipGame->userGrid.grid[x][y] == HIT || gamePlay.battleshipGame->userGrid.grid[x][y] == MISS) {
            continue;
        }

        if (gamePlay.battleshipGame->userGrid.grid[x][y] == DESTROYED) {
            ss.str("");
            ss << "This field has been destroyed, please choose another location.\n";
            uniqueMessages.insert(ss.str());
            continue;
        }   

        if (gamePlay.battleshipGame->userGrid.grid[x][y] == SHIP) {
            gamePlay.battleshipGame->userGrid.hit(x, y);
            gamePlay.battleshipGame->botHitCount++;
            ss.str("");
            ss << "Computer hit! Ship at (" << x << ", " << y << ")!";
            uniqueMessages.insert(ss.str());

            // Check if ship is destroyed
            bool shipDestroyed = false;
            for (const auto& ship : gamePlay.battleshipGame->userGrid.ships) {
                if (std::find(ship.coordinates.begin(), ship.coordinates.end(), std::make_pair(x, y)) != ship.coordinates.end()) {
                    if (ship.isDestroyed()) {
                        shipDestroyed = true;
                        break;
                    }
                }
            }
            if (shipDestroyed) {
                ss.str("");
                ss << "Ship destroyed !\n";
                uniqueMessages.insert(ss.str());
            }

            if (checkWin(gamePlay.battleshipGame->userGrid)) {
                gamePlay.battleshipGame->messages.push_back(ss.str());
                break;
            }
        } else {
            gamePlay.battleshipGame->userGrid.grid[x][y] = MISS;
            ss.str("");
            ss << "Computer missed! No ship at (" << x << ", " << y << ").";
            uniqueMessages.insert(ss.str());
            validMove = true;
        }

        Utility::clearScreen();
        gamePlay.printGrids(gamePlay.battleshipGame->userGrid, gamePlay.battleshipGame->botGrid, "Player 1", "Bot", gamePlay.battleshipGame->revealBotGrid);
        
        // Відображення унікальних повідомлень
        for (const auto& message : uniqueMessages) {
            Utility::printCentered(message);
        }
        uniqueMessages.clear();
    }
}
bool Turn::checkWin(const Grid& grid) { // Перевірка перемоги
    for (const auto& row : grid.grid) { // Перебір усіх рядків сітки
        for (CellState cell : row) { // Перебір усіх клітинок у рядку
            if (cell == SHIP) { // Якщо знайдено клітинку з кораблем
                return false; // Повернути false, гра ще не виграна
            }
        }
    }
    return true; // Повернути true, якщо всі кораблі знищені
}

