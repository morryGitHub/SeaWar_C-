#include "Surrender.h"
#include "BattleshipGame.h"
#include "Utility.h"
#include "GameSummary.h"

void Surrender::handleSurrenderAndRematch(BattleshipGame& battleshipGame, bool isSinglePlay) {
    Utility::clearScreen();
    Utility::printSeparated();
    Utility::printCentered("You have surrendered. Game over.\n"); // Повідомлення про капітуляцію

    if (!isSinglePlay) {
        // Якщо грає проти іншого гравця, підбиваємо підсумки гри
        battleshipGame.gameSummary.endGameSummary(
            isSinglePlay, 
            battleshipGame.player1Grid, battleshipGame.player2Grid, 
            battleshipGame.player1Shots, battleshipGame.player2Shots, 
            battleshipGame.player1HitCount, battleshipGame.player2HitCount, 
            battleshipGame.userShots, battleshipGame.botShots, 
            battleshipGame.userHitCount, battleshipGame.botHitCount, 
            battleshipGame.leaderboard
        );
    }

    Utility::printSeparated();


    char viewLeaderboardResponse;
    while (true) {
        Utility::printCentered("Would you like to view the leaderboard? (y/n): "); // Запит на перегляд таблиці лідерів
        viewLeaderboardResponse = Utility::readCentered()[0]; // Читання відповіді користувача
        Utility::clearInput(); // Очищення введення
        if (viewLeaderboardResponse == 'y' || viewLeaderboardResponse == 'Y' || viewLeaderboardResponse == 'n' || viewLeaderboardResponse == 'N') {
            break; // Valid input received
        } else {
            Utility::printCentered("Invalid input. Please enter 'y' or 'n'.\n"); // Повідомлення про недійсне введення
        }
    }

    if (viewLeaderboardResponse == 'y' || viewLeaderboardResponse == 'Y') {
        battleshipGame.leaderboard.display(); // Відображення таблиці лідерів
    }

    Utility::printSeparated();

    char rematchResponse;
    while (true) {
        Utility::printCentered("Would you like to play a rematch? (y/n): "); // Запит на перегравання
        rematchResponse = Utility::readCentered()[0]; // Читання відповіді користувача
        Utility::clearInput(); // Очищення введення
        if (rematchResponse == 'y' || rematchResponse == 'Y' || rematchResponse == 'n' || rematchResponse == 'N') {
            break; // Valid input received
        } else {
            Utility::printCentered("Invalid input. Please enter 'y' or 'n'.\n"); // Повідомлення про недійсне введення
        }
    }

    if (rematchResponse == 'y' || rematchResponse == 'Y') { // Якщо користувач погоджується на перегравання
        battleshipGame.play(); // Запуск нової гри
    } else { // Якщо користувач не хоче перегравати
        Utility::printCentered("We believe you would do better next time!!"); // Повідомлення про завершення гри
        exit(1); // Вихід з гри
    }
}