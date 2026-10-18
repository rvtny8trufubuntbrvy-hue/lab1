#pragma warning(disable:4996)
#include "Teacher.h"
#include <fstream>
#include <cstring>
#include <iostream>

Teacher::Teacher() : Base(), groups(nullptr), subjects(nullptr) {
    std::cout << "[Teacher] constructor (no args)" << std::endl;
}

Teacher::~Teacher() {
    std::cout << "[Teacher] destructor" << std::endl;
    delete[] groups;
    delete[] subjects;
}

void Teacher::input() {
    char buf[256];
    std::cout << "Vvedite FIO prepodavatelya: ";
    std::cin.ignore();
    std::cin.getline(buf, 256);
    setFio(buf);

    std::cout << "Vvedite gruppy (cherez zapyatuyu): ";
    std::cin.getline(buf, 256);
    copyStr(groups, buf);

    std::cout << "Vvedite predmety (cherez zapyatuyu): ";
    std::cin.getline(buf, 256);
    copyStr(subjects, buf);
}

void Teacher::print() const {
    std::cout << "--- Prepodavatel ---\n"
              << "FIO: " << getFio() << "\n"
              << "Vedet gruppy: " << (groups ? groups : "") << "\n"
              << "Predmety: " << (subjects ? subjects : "") << std::endl;
}

void Teacher::save(std::ofstream& out) const {
    int type = getType();
    out.write((char*)&type, sizeof(type));

    int len = (int)std::strlen(getFio());
    out.write((char*)&len, sizeof(len));
    out.write(getFio(), len);

    len = groups ? (int)std::strlen(groups) : 0;
    out.write((char*)&len, sizeof(len));
    if (len > 0) out.write(groups, len);

    len = subjects ? (int)std::strlen(subjects) : 0;
    out.write((char*)&len, sizeof(len));
    if (len > 0) out.write(subjects, len);
}

void Teacher::load(std::ifstream& in) {
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
    copyStr(groups, buf);
    delete[] buf;

    in.read((char*)&len, sizeof(len));
    buf = new char[len + 1];
    if (len > 0) in.read(buf, len);
    buf[len] = '\0';
    copyStr(subjects, buf);
    delete[] buf;
}