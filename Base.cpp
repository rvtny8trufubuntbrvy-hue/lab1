#pragma warning(disable:4996)
#include "Base.h"

void Base::copyStr(char*& dest, const char* src) {
    if (dest) {
        delete[] dest;
        dest = nullptr;
    }
    if (src) {
        dest = new char[std::strlen(src) + 1];
        std::strcpy(dest, src);
    }
}

Base::Base() : fio(nullptr) {
    std::cout << "[Base] Вызван конструктор без параметров" << std::endl;
}

Base::Base(const char* name) : fio(nullptr) {
    std::cout << "[Base] Вызван конструктор с параметрами" << std::endl;
    copyStr(fio, name);
}

Base::Base(const Base& src) : fio(nullptr) {
    std::cout << "[Base] Вызван конструктор копирования" << std::endl;
    copyStr(fio, src.fio);
}

Base::~Base() {
    std::cout << "[Base] Вызван деструктор" << std::endl;
    delete[] fio;
}

void Base::setFio(const char* name) { copyStr(fio, name); }
const char* Base::getFio() const { return fio ? fio : ""; }