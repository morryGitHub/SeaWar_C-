#ifndef SHIPINFO_H
#define SHIPINFO_H
#include <vector>
#include <utility>

class ShipInfo {
public:
    char symbol; // Символ, що позначає корабель
    int size; // Розмір корабля
    int hits; // Кількість попадань у корабель
    std::vector<std::pair<int, int>> coordinates; // Координати клітинок, зайнятих кораблем

    ShipInfo(char s, int sz); // Конструктор для ініціалізації корабля
    void hit(); // Метод для обробки попадання в корабель
    bool isDestroyed() const; // Метод для перевірки, чи знищений корабель
};

#endif 
