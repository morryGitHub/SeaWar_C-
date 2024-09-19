#ifndef UTILITY_H
#define UTILITY_H
#include <iostream>
#include <vector>
#include <string>

class Utility {
public:
    static void delay(int milliseconds); // Затримка на вказану кількість мілісекунд
    static void clearScreen(); // Очищення екрану
    static void printCentered(const char* s); // Виведення тексту по центру екрану (для рядків типу char*)
    static void printCentered(const std::string& message); // Виведення тексту по центру екрану (для рядків типу std::string)
    static void printSeparated(); // Виведення розділювальної лінії
    static void printTableCentered(const std::vector<std::vector<std::string>>& table); // Виведення таблиці по центру екрану
    static std::string readCentered(); // Читання введеного тексту по центру екрану
    static void clearInput(); // Очищення введення
    static void printTableInBox(const std::vector<std::string>& lines); // Виведення тексту у вигляді таблиці
};

#endif 
