#include "BattleshipGame.h"
#include "Utility.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>

void BattleshipGame::play() { 
    while (true) {
        resetGame(); // Скидання стану гри
        Utility::clearScreen(); // Очищення екрану
        Utility::printSeparated(); // Виведення розділювальної лінії

        Utility::printCentered("Welcome to the Battleship!"); // Привітання гравця
        Utility::delay(1500); // Затримка

        std::cout << "\n\n";
        Utility::printCentered("Prepare for the Battle!"); // Підготовка до гри
        Utility::delay(1500); // Затримка

        for (;;) { // Меню вибору дії
            Utility::printSeparated();

            Utility::printCentered("1. Play Battleship Game!"); // Вибір гри
            Utility::printCentered("2. See rules"); // Перегляд правил
            Utility::printCentered("3. Exit"); // Вихід

            int choice;
            std::string input = Utility::readCentered(); // Читання вибору користувача
            Utility::clearInput(); // Очищення введення

            std::istringstream iss(input);
            if (iss >> choice && (choice == 1 || choice == 2 || choice == 3)) {
                if (choice == 1) break; // Якщо вибрано гру, вихід з циклу
                if (choice == 2) { // Якщо вибрано перегляд правил
                    for (int i = 0; i < 3; i++) std::cout << "\n";
                    Utility::printCentered("“Oorah!” Get ready for the war!"); // Повідомлення
                    std::vector<std::string> rules = { // Правила гри
                        "1. You have to destroy your opponent's war ships before he destroys yours.",
                        "2. The battlefield is of 10x10 grid size in which you place your ships.",
                        "3. You can place your ships by entering its orientation, i.e horizontal or vertical. For horizontal orientation, type 'h' in the orientation option and type 'v' for vertical.",
                        "4. You have a fleet of 4 battle ships: Aircraft Carrier (4 units long), Battleship (3 units long), Destroyer (2 units long) and Corvette (1 unit long).",
                        "5. The first coordinate is vertical, the second one - horizontal.",
                        "6. Attack hit to the enemy ship is denoted and you get an extra turn.",
                        "7. Attack miss is denoted by a '*' and your turn ends.",
                        "8. To end the game earlier, enter the word 'surrender' during the game process.",
                        "9. At the end your results will be placed on the leaderboard and you can view it.",
                        "10. After placing your ships, you can attack the enemy area. To attack an area, enter its x y coordinate (separated by a space)."
                    };
                    Utility::printTableInBox(rules); // Виведення правил у вигляді таблиці

                    Utility::printCentered("Press ENTER to continue!"); // Запит на продовження
                    std::cin.get(); // Очікування введення користувача
                    Utility::clearInput(); // Очищення введення

                    Utility::clearScreen(); // Очищення екрану
                    continue; // Повернення до меню
                } else {
                    Utility::printCentered("See you next time!");
                    exit(1); // Вихід з гри
                }
            } else {
                Utility::printCentered("Invalid choice. Please enter 1, 2, or 3.\n"); // Повідомлення про недійсне введення
            }
        }

        srand(static_cast<unsigned int>(time(nullptr))); // Ініціалізація генератора випадкових чисел

        Utility::clearScreen(); // Очищення екрану
        Utility::printSeparated(); // Виведення розділювальної лінії

        int opponentChoice;
        while (true) {
            Utility::printCentered("Choose your opponent:"); // Вибір супротивника
            Utility::printCentered("1. Play against another player"); // Гра проти іншого гравця
            Utility::printCentered("2. Play against the bot\n"); // Гра проти бота

            std::string input = Utility::readCentered(); // Читання вибору користувача
            Utility::clearInput(); // Очищення введення

            std::istringstream iss(input);
            if (iss >> opponentChoice && (opponentChoice == 1 || opponentChoice == 2)) {
                break; // Valid input received
            } else {
                std::cout << "\n";
                Utility::printCentered("Invalid choice. Please enter 1 or 2.\n"); // Повідомлення про недійсне введення
            }
        }

        if (opponentChoice == 1) { // Гра проти іншого гравця
            gameSetup.setupGrids(player1Grid, player2Grid); // Налаштування сіток
            gamePlay.playTwoPlayerGame(player1Grid, player2Grid, player1Shots, player2Shots, player1HitCount, player2HitCount); // Запуск гри для двох гравців
        } else { // Гра проти бота
            gameSetup.setupSinglePlayer(userGrid, botGrid); // Налаштування сіток
            gamePlay.playSinglePlayerGame(userGrid, botGrid, userShots, botShots, userHitCount, botHitCount, revealBotGrid); // Запуск гри для одного гравця проти бота
        }

        gameSummary.endGameSummary(opponentChoice == 2, player1Grid, player2Grid, player1Shots, player2Shots, player1HitCount, player2HitCount, userShots, botShots, userHitCount, botHitCount, leaderboard); // Підбиття підсумків гри

        Utility::printSeparated();

        char rematchResponse;
        while (true) {
            Utility::printCentered("Would you like to play a rematch? (y/n): "); // Запит на перегравання
            rematchResponse = Utility::readCentered()[0]; // Читання відповіді користувача
            Utility::clearInput(); // Очищення введення
            if (rematchResponse == 'y' || rematchResponse == 'Y' || rematchResponse == 'n' || rematchResponse == 'N') {
                break; // Valid input received
            } else {
                std::cout << "\n";
                Utility::printCentered("Invalid input. Please enter 'y' or 'n'.\n"); // Повідомлення про недійсне введення
            }
        }
        if (rematchResponse != 'y' && rematchResponse != 'Y') { // Якщо користувач не хоче перегравати
            Utility::printSeparated();
            Utility::printCentered("See you next time!");
            break; // Вихід з основного ігрового циклу
        }
    }
}

void BattleshipGame::resetGame() { // Скидання стану гри
    player1Shots.clear(); // Очищення ходів гравця 1
    player2Shots.clear(); // Очищення ходів гравця 2
    userShots.clear(); // Очищення ходів користувача
    botShots.clear(); // Очищення ходів бота
    player1HitCount = 0; // Скидання лічильника попадань гравця 1
    player2HitCount = 0; // Скидання лічильника попадань гравця 2
    userHitCount = 0; // Скидання лічильника попадань користувача
    botHitCount = 0; // Скидання лічильника попадань бота
    revealBotGrid = false; // Скидання прапора показу сітки бота
    userSurrendered = false; // Флаг для показу здачі гравця
    gameSetup.initializeGrid(player1Grid); // Ініціалізація сітки гравця 1
    gameSetup.initializeGrid(player2Grid); // Ініціалізація сітки гравця 2
    gameSetup.initializeGrid(userGrid); // Ініціалізація сітки користувача
    gameSetup.initializeGrid(botGrid); // Ініціалізація сітки бота
}

void BattleshipGame::addMessage(const std::string& message) {
    messages.push_back(message);
}

void BattleshipGame::displayMessages() const {
    for (const auto& message : messages) {
        std::cout << message << std::endl;
    }
}

void BattleshipGame::clearMessages() {
    messages.clear();
}

bool BattleshipGame::checkWin(const Grid& grid) { // Перевірка перемоги
    for (const auto& row : grid.grid) { // Перебір усіх рядків сітки
        for (CellState cell : row) { // Перебір усіх клітинок у рядку
            if (cell == SHIP) { // Якщо знайдено клітинку з кораблем
                return false; // Повернути false, гра ще не виграна
            }
        }
    }
    return true; // Повернути true, якщо всі кораблі знищені
}
