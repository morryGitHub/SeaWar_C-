#include "ShipInfo.h"

ShipInfo::ShipInfo(char s, int sz) : symbol(s), size(sz), hits(0) {} // Ініціалізація символу, розміру і попадань

void ShipInfo::hit() { // Метод для обробки попадання в корабель
    hits++; // Збільшує кількість попадань
}

bool ShipInfo::isDestroyed() const { // Метод для перевірки, чи знищений корабель
    return hits >= size; // Повертає true, якщо кількість попадань дорівнює або перевищує розмір корабля
}
