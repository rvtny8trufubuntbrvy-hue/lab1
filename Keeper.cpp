#include "Keeper.h"
#include "Student.h"
#include "Teacher.h"
#include "Admin.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

Keeper::Keeper() : head(nullptr), count(0) {}

Keeper::~Keeper() { clear(); }

void Keeper::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current->data;
        delete current;
        current = next;
    }
    head = nullptr;
    count = 0;
}

void Keeper::add(Base* item) {
    Node* newNode = new Node{ item, nullptr };
    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
    count++;
}

void Keeper::remove(int index) {
    if (index < 0 || index >= count || !head) {
        throw std::out_of_range("Индекс за пределами допустимого диапазона контейнера Keeper!");
    }

    Node* temp = head;
    if (index == 0) {
        head = head->next;
        delete temp->data;
        delete temp;
    } else {
        Node* prev = nullptr;
        for (int i = 0; i < index; i++) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
        delete temp->data;
        delete temp;
    }
    count--;
}

void Keeper::printAll() const {
    if (count == 0) {
        std::cout << "Контейнер пуст." << std::endl;
        return;
    }
    Node* temp = head;
    int idx = 0;
    while (temp) {
        std::cout << "[" << idx++ << "] ";
        temp->data->print();
        std::cout << "-----------------------" << std::endl;
        temp = temp->next;
    }
}

void Keeper::saveToFile(const char* filename) const {
    std::ofstream out(filename, std::ios::binary);
    if (!out.is_open()) throw std::runtime_error("Не удалось открыть файл для сохранения!");

    out.write((char*)&count, sizeof(count));
    Node* temp = head;
    while (temp) {
        temp->data->save(out);
        temp = temp->next;
    }
    out.close();
    std::cout << "Данные успешно сохранены в файл: " << filename << std::endl;
}

void Keeper::loadFromFile(const char* filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open()) throw std::runtime_error("Не удалось открыть файл для загрузки!");

    clear();

    int total = 0;
    in.read((char*)&total, sizeof(total));

    for (int i = 0; i < total; i++) {
        int type = 0;
        in.read((char*)&type, sizeof(type));
        Base* item = nullptr;

        if (type == 1)      item = new Student();
        else if (type == 2) item = new Teacher();
        else if (type == 3) item = new Admin();

        if (item) {
            item->load(in);
            add(item);
        }
    }
    in.close();
    std::cout << "Данные успешно восстановлены из файла: " << filename << std::endl;
}