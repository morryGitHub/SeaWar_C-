#include "Utility.h"
#include <thread>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <sstream>
using std::cout;
using std::endl;

void Utility::delay(int milliseconds) { // Затримка на вказану кількість мілісекунд
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void Utility::clearScreen() { // Очищення екрану
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
    std::cout << "\033[2J\033[1;1H";
}

void Utility::printCentered(const char* s) { // Виведення тексту по центру екрану (для рядків типу char*)
    int len = strlen(s);
    int centre = (210 - len) / 2;
    for (int i = 0; i < centre; ++i) {
        cout << " ";
    }
    cout << s << endl;
}

void Utility::printCentered(const std::string& message) { // Виведення тексту по центру екрану (для рядків типу std::string)
    const int consoleWidth = 210;
    int padding = (consoleWidth - message.size()) / 2;
    if (padding > 0) {
        std::cout << std::setw(padding) << "" << message;
    } else {
        std::cout << message;
    }
}

void Utility::printSeparated() { // Виведення розділювальної лінії
    for (int i = 0; i < 5; i++){
        cout << "\n";
    }
}

void Utility::printTableCentered(const std::vector<std::vector<std::string>>& table) { // Виведення таблиці по центру екрану
    const int width = 210;
    int maxCellWidth = 0;
    for (const auto& row : table) {
        for (const auto& cell : row) {
            maxCellWidth = std::max(maxCellWidth, static_cast<int>(cell.length()));
        }
    }
    maxCellWidth += 2; // Додаємо відступ

    int tableWidth = table[0].size() * (maxCellWidth + 1) + 3;
    int padding = (width - tableWidth) / 2;

    std::string topBottomBorder(tableWidth, '-');

    for (int i = 0; i < padding; ++i) {
        std::cout << " ";
    }
    std::cout << "+" << topBottomBorder << "+" << std::endl;

    for (const auto& row : table) {
        for (int i = 0; i < padding; ++i) {
            std::cout << " ";
        }
        std::cout << "|";
        for (const auto& cell : row) {
            std::cout << " " << std::setw(maxCellWidth) << std::left << cell << "|";
        }
        std::cout << std::endl;
        for (int i = 0; i < padding; ++i) {
            std::cout << " ";
        }
        std::cout << "+" << topBottomBorder << "+" << std::endl;
    }
}

std::string Utility::readCentered() { // Читання введеного тексту по центру екрану
    std::string input;
    int centre = 210 / 2 - 2;
    for (int i = 0; i < centre; ++i) {
        cout << " ";
    }
    std::getline(std::cin, input);
    return input;
}

void Utility::clearInput() { // Очищення введення
    std::cout << "\033[A\033[2K";
}

void Utility::printTableInBox(const std::vector<std::string>& lines) { // Виведення тексту у вигляді таблиці
    const int width = 208; // Ширина рамки
    const int padding = 4; // Відступ від межі
    std::string topBottomBorder(width, '-');
    std::cout << "+" << topBottomBorder << "+" << std::endl; // Вивести верхню межу рамки
    std::cout << "| " << std::setw(width) << " |" << std::endl;
    for (const auto& line : lines) { // Вивести кожен рядок тексту всередині рамки
        std::cout << "| " << std::setw(padding) << "" // Лівий відступ
                  << std::setw(width - 2 * padding - 2) << std::left << line // Текст з відступом
                  << std::setw(padding) << "" << " |" << std::endl; // Правий відступ
    }
    std::cout << "| " << std::setw(width-1) << " " << "|" << std::endl; // Вивести нижню межу рамки
    std::cout << "+" << topBottomBorder << "+" << std::endl;
}