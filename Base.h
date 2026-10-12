#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <fstream>
#include <cstring>

class Base {
protected:
    char* fio;

    void copyStr(char*& dest, const char* src);

public:
    Base();
    Base(const char* name);
    Base(const Base& src);
    virtual ~Base();

    void setFio(const char* name);
    const char* getFio() const;

    virtual void input() = 0;
    virtual void print() const = 0;
    virtual void save(std::ofstream& out) const = 0;
    virtual void load(std::ifstream& in) = 0;
    virtual int getType() const = 0;
};

#endif // BASE_H