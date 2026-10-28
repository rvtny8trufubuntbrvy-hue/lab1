#pragma warning(disable:4996)
#include "Admin.h"
#include <fstream>
#include <cstring>
#include <iostream>

Admin::Admin() : Base(), position(nullptr), phone(nullptr), responsibility(nullptr) {
    std::cout << "[Admin] Вызван конструктор без параметров" << std::endl;
}

Admin::~Admin() {
    std::cout << "[Admin] Вызван деструктор" << std::endl;
    delete[] position;
    delete[] phone;
    delete[] responsibility;
}

void Admin::input() {
    char buf[256];
    std::cout << "Введите ФИО сотрудника: ";
    std::cin.ignore();
    std::cin.getline(buf, 256);
    setFio(buf);

    std::cout << "Введите должность: ";
    std::cin.getline(buf, 256);
    copyStr(position, buf);

    std::cout << "Введите телефон: ";
    std::cin.getline(buf, 256);
    copyStr(phone, buf);

    std::cout << "Введите область ответственности: ";
    std::cin.getline(buf, 256);
    copyStr(responsibility, buf);
}

void Admin::print() const {
    std::cout << "--- Административный персонал ---\n"
              << "ФИО: " << getFio() << "\n"
              << "Должность: " << (position ? position : "") << "\n"
              << "Телефон: " << (phone ? phone : "") << "\n"
              << "Область ответственности: " << (responsibility ? responsibility : "") << std::endl;
}

void Admin::save(std::ofstream& out) const {
    int type = getType();
    out.write((char*)&type, sizeof(type));

    int len = (int)std::strlen(getFio());
    out.write((char*)&len, sizeof(len));
    out.write(getFio(), len);

    len = position ? (int)std::strlen(position) : 0;
    out.write((char*)&len, sizeof(len));
    if (len > 0) out.write(position, len);

    len = phone ? (int)std::strlen(phone) : 0;
    out.write((char*)&len, sizeof(len));
    if (len > 0) out.write(phone, len);

    len = responsibility ? (int)std::strlen(responsibility) : 0;
    out.write((char*)&len, sizeof(len));
    if (len > 0) out.write(responsibility, len);
}

void Admin::load(std::ifstream& in) {
    int len = 0;
    in.read((char*)&len, sizeof(len));
    char* buf = new char[len + 1];
    in.read(buf, len);
    buf[len] = '\0';
    setFio(buf);
    delete[] buf;

    in.read((char*)&len, sizeof(len));
    buf = new char[len + 1];
    if (len > 0) in.read(buf, len);
    buf[len] = '\0';
    copyStr(position, buf);
    delete[] buf;

    in.read((char*)&len, sizeof(len));
    buf = new char[len + 1];
    if (len > 0) in.read(buf, len);
    buf[len] = '\0';
    copyStr(phone, buf);
    delete[] buf;

    in.read((char*)&len, sizeof(len));
    buf = new char[len + 1];
    if (len > 0) in.read(buf, len);
    buf[len] = '\0';
    copyStr(responsibility, buf);
    delete[] buf;
}