#ifndef KEEPER_H
#define KEEPER_H

#include "Base.h"

class Keeper {
private:
    struct Node {
        Base* data;
        Node* next;
    };
    Node* head;
    int count;

    void clear();   // добавлено: нормальная очистка контейнера

public:
    Keeper();
    ~Keeper();

    void add(Base* item);
    void remove(int index);
    void printAll() const;
    int getCount() const { return count; }

    void saveToFile(const char* filename) const;
    void loadFromFile(const char* filename);
};

#endif // KEEPER_H