#include "GameSummary.h"
#include "Utility.h"
#include "Leaderboard.h"
#include "BattleshipGame.h"
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>

void GameSummary::endGameSummary(bool isSinglePlayer, const Grid& player1Grid, const Grid& player2Grid,
                                 const std::vector<std::pair<int, int>>& player1Shots, const std::vector<std::pair<int, int>>& player2Shots,
                                 int player1HitCount, int player2HitCount,
                                 const std::vector<std::pair<int, int>>& userShots, const std::vector<std::pair<int, int>>& botShots,
                                 int userHitCount, int botHitCount, Leaderboard& leaderboard) {
    std::vector<std::vector<std::string>> table;
    table.push_back({"Player", "Shots", "Hits", "Accuracy (%)"});

    if (isSinglePlayer) {
        float userAccuracy = static_cast<float>(userHitCount) / userShots.size() * 100;
        float botAccuracy = static_cast<float>(botHitCount) / botShots.size() * 100;

        std::ostringstream userAccuracyStr, botAccuracyStr;
        userAccuracyStr << std::fixed << std::setprecision(2) << userAccuracy;
        botAccuracyStr << std::fixed << std::setprecision(2) << botAccuracy;

        table.push_back({"Player", std::to_string(userShots.size()), std::to_string(userHitCount), userAccuracyStr.str()});
        table.push_back({"Computer", std::to_string(botShots.size()), std::to_string(botHitCount), botAccuracyStr.str()});

        Utility::printTableCentered(table);

        char response;
        while (true) {
            Utility::printCentered("Would you like to save your result in the leaderboard? (y/n): ");
            response = Utility::readCentered()[0];
            Utility::clearInput();
            if (response == 'y' || response == 'Y' || response == 'n' || response == 'N') {
                break;
            } else {
                Utility::printCentered("Invalid input. Please enter 'y' or 'n'.\n");
            }
        }
        if (response == 'y' || response == 'Y') {
            leaderboard.saveResult(userShots.size(), userHitCount, userAccuracy);
        }

        while (true) {
            Utility::printCentered("Would you like to see the leaderboard? (y/n): ");
            response = Utility::readCentered()[0];
            Utility::clearInput();
            if (response == 'y' || response == 'Y' || response == 'n' || response == 'N') {
                break;
            } else {
                Utility::printCentered("Invalid input. Please enter 'y' or 'n'.\n");
            }
        }
        if (response == 'y' || response == 'Y') {
            leaderboard.display();
        }

    } else {
        float player1Accuracy = static_cast<float>(player1HitCount) / player1Shots.size() * 100;
        float player2Accuracy = static_cast<float>(player2HitCount) / player2Shots.size() * 100;

        std::ostringstream player1AccuracyStr, player2AccuracyStr;
        player1AccuracyStr << std::fixed << std::setprecision(2) << player1Accuracy;
        player2AccuracyStr << std::fixed << std::setprecision(2) << player2Accuracy;

        table.push_back({"Player 1", std::to_string(player1Shots.size()), std::to_string(player1HitCount), player1AccuracyStr.str()});
        table.push_back({"Player 2", std::to_string(player2Shots.size()), std::to_string(player2HitCount), player2AccuracyStr.str()});

        Utility::printTableCentered(table);

        char response;
        if (battleshipGame->checkWin(player2Grid)) {
            std::cout << "\n";
            while (true) {
                Utility::printCentered("Congratulations on Player 1 victory! Would you like to save your result in the leaderboard? (y/n): ");
                response = Utility::readCentered()[0];
                Utility::clearInput();
                if (response == 'y' || response == 'Y' || response == 'n' || response == 'N') {
                    break;
                } else {
                    Utility::printCentered("Invalid input. Please enter 'y' or 'n'.\n");
                }
            }
            if (response == 'y' || response == 'Y') {
                leaderboard.saveResult(player1Shots.size(), player1HitCount, player1Accuracy);
            }
        } else if (battleshipGame->checkWin(player1Grid)) {
            std::cout << "\n";
            while (true) {
                Utility::printCentered("Congratulations on Player 2 victory! Would you like to save your result in the leaderboard? (y/n): ");
                response = Utility::readCentered()[0];
                Utility::clearInput();
                if (response == 'y' || response == 'Y' || response == 'n' || response == 'N') {
                    break;
                } else {
                    Utility::printCentered("Invalid input. Please enter 'y' or 'n'.\n");
                }
            }
            if (response == 'y' || response == 'Y') {
                leaderboard.saveResult(player2Shots.size(), player2HitCount, player2Accuracy);
            }
        }

        while (true) {
            Utility::printCentered("Would you like to see the leaderboard? (y/n): ");
            response = Utility::readCentered()[0];
            Utility::clearInput();
            if (response == 'y' || response == 'Y' || response == 'n' || response == 'N') {
                break;
            } else {
                Utility::printCentered("Invalid input. Please enter 'y' or 'n'.\n");
            }
        }
        if (response == 'y' || response == 'Y') {
            leaderboard.display();
        }
    }
}

void GameSummary::printLeaderboard(const std::vector<std::vector<std::string>>& table) {
    Utility::printTableCentered(table);
}

