#ifndef TEACHER_H
#define TEACHER_H

#include "Base.h"

class Teacher : public Base {
private:
    char* groups;
    char* subjects;

public:
    Teacher();
    ~Teacher() override;

    void input() override;
    void print() const override;
    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
    int getType() const override { return 2; }
};

#endif // TEACHER_H