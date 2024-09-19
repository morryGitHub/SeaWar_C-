#include "Leaderboard.h"
#include "Utility.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

void Leaderboard::saveResult(int shots, int hits, float accuracy) { // Збереження результату гри
    std::ofstream leaderboard("leaderboard.txt", std::ios::app); // Відкриття файлу для додавання
    if (!leaderboard) { // Перевірка на помилку відкриття файлу
        std::cerr << "Error opening leaderboard file.\n"; // Виведення повідомлення про помилку
        return; // Вихід з функції
    }

    std::string name; // Ім'я гравця
    while (true) { // Цикл для введення правильного імені
        Utility::printCentered("Enter your name (at least one word): "); // Запит на введення імені
        name = Utility::readCentered(); // Читання імені

        if (!name.empty()) { // Якщо ім'я не пусте
            break; // Вихід з циклу
        } else { // Якщо ім'я пусте
            std::cerr << "Invalid name. Please enter your name correctly.\n"; // Виведення повідомлення про помилку
        }
    }

    leaderboard << name << " " << shots << " " << hits << " " << accuracy << "\n"; // Запис результату в файл
    leaderboard.close(); // Закриття файлу
}

void Leaderboard::display() { // Відображення таблиці лідерів
    std::ifstream leaderboardFile("leaderboard.txt"); // Відкриття файлу для читання
    if (!leaderboardFile) { // Перевірка на помилку відкриття файлу
        std::cerr << "Error opening leaderboard file.\n"; // Виведення повідомлення про помилку
        return; // Вихід з функції
    }

    struct Player { // Структура для зберігання даних гравця
        std::string name; // Ім'я гравця
        int shots; // Кількість пострілів
        int hits; // Кількість попадань
        float accuracy; // Точність
    };

    std::vector<Player> players; // Вектор для зберігання даних гравців
    std::string line; // Рядок для читання з файлу

    while (std::getline(leaderboardFile, line)) { // Читання файлу по рядках
        std::istringstream iss(line); // Потік для читання з рядка
        Player player; // Об'єкт гравця
        if (iss >> std::quoted(player.name) >> player.shots >> player.hits >> player.accuracy) { // Читання даних гравця
            players.push_back(player); // Додавання гравця у вектор
        }
    }
    leaderboardFile.close(); // Закриття файлу

    // Сортування гравців за кількістю попадань, а у випадку однакової кількості попадань - за точністю
    std::sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
        if (a.hits == b.hits) {
            return a.accuracy > b.accuracy; // Сортування за точністю
        }
        return a.hits > b.hits; // Сортування за кількістю попадань
    });

    std::vector<std::vector<std::string>> table; // Вектор для зберігання таблиці
    table.push_back({"Name", "Shots", "Hits", "Accuracy (%)"}); // Заголовки таблиці

    for (const auto& player : players) { // Перебір гравців
        std::ostringstream oss; // Потік для форматування точності
        oss << std::fixed << std::setprecision(2) << player.accuracy; // Форматування точності
        table.push_back({player.name, std::to_string(player.shots), std::to_string(player.hits), oss.str()}); // Додавання даних гравця у таблицю
    }

    Utility::printTableCentered(table); // Виведення таблиці
}
