#pragma warning(disable:4996)
#include "Student.h"
#include <fstream>
#include <cstring>
#include <iostream>
#include <limits> // Для защиты от букв

Student::Student() : Base(), group(nullptr), specialty(nullptr), course(0), rating(0.0) {
    std::cout << "[Student] Вызван конструктор без параметров" << std::endl;
}

Student::Student(const char* name, const char* grp, const char* spec, int crs, double rat)
    : Base(name), group(nullptr), specialty(nullptr), course(crs), rating(rat) {
    std::cout << "[Student] Вызван конструктор с параметрами" << std::endl;
    copyStr(group, grp);
    copyStr(specialty, spec);
}

Student::Student(const Student& src)
    : Base(src), group(nullptr), specialty(nullptr),
      course(src.course), rating(src.rating) {
    std::cout << "[Student] Вызван конструктор копирования" << std::endl;
    copyStr(group, src.group);
    copyStr(specialty, src.specialty);
}

Student::~Student() {
    std::cout << "[Student] Вызван деструктор" << std::endl;
    delete[] group;
    delete[] specialty;
}

Student& Student::operator=(const Student& r) {
    if (this == &r) return *this;
    setFio(r.getFio());
    copyStr(group, r.group);
    copyStr(specialty, r.specialty);
    course = r.course;
    rating = r.rating;
    return *this;
}

void Student::input() {
    char buf[256];
    std::cout << "Введите ФИО студента: ";
    std::cin.ignore();
    std::cin.getline(buf, 256);
    setFio(buf);

    std::cout << "Введите группу: ";
    std::cin.getline(buf, 256);
    copyStr(group, buf);

    std::cout << "Введите наименование специальности: ";
    std::cin.getline(buf, 256);
    copyStr(specialty, buf);

    std::cout << "Введите текущий курс: ";
    std::cin >> course;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка! Введите число (курс): ";
        std::cin >> course;
    }

    std::cout << "Введите средний балл: ";
    std::cin >> rating;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка! Введите число (балл): ";
        std::cin >> rating;
    }
    std::cin.ignore();
}

void Student::print() const {
    std::cout << "--- Студент ---\n"
              << "ФИО: " << getFio() << "\n"
              << "Группа: " << (group ? group : "") << "\n"
              << "Специальность: " << (specialty ? specialty : "") << "\n"
              << "Курс: " << course << "\n"
              << "Средний балл: " << rating << std::endl;
}

void Student::save(std::ofstream& out) const {
    int type = getType();
    out.write((char*)&type, sizeof(type));

    int len = (int)std::strlen(getFio());
    out.write((char*)&len, sizeof(len));
    out.write(getFio(), len);

    len = group ? (int)std::strlen(group) : 0;
    out.write((char*)&len, sizeof(len));
    if (len > 0) out.write(group, len);

    len = specialty ? (int)std::strlen(specialty) : 0;
    out.write((char*)&len, sizeof(len));
    if (len > 0) out.write(specialty, len);

    out.write((char*)&course, sizeof(course));
    out.write((char*)&rating, sizeof(rating));
}

void Student::load(std::ifstream& in) {
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
    copyStr(group, buf);
    delete[] buf;

    in.read((char*)&len, sizeof(len));
    buf = new char[len + 1];
    if (len > 0) in.read(buf, len);
    buf[len] = '\0';
    copyStr(specialty, buf);
    delete[] buf;

    in.read((char*)&course, sizeof(course));
    in.read((char*)&rating, sizeof(rating));
}