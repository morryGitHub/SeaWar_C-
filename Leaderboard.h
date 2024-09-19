#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include <string>

class Leaderboard {
public:
    void saveResult(int shots, int hits, float accuracy); // Збереження результату гри в таблицю лідерів
    void display(); // Відображення таблиці лідерів
};

#endif 
