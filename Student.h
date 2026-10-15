#ifndef STUDENT_H
#define STUDENT_H

#include "Base.h"

class Student : public Base {
private:
    char* group;
    char* specialty;
    int course;
    double rating;

public:
    Student();
    Student(const char* name, const char* grp, const char* spec, int crs, double rat);
    Student(const Student& src);
    ~Student() override;

    Student& operator=(const Student& r);

    void input() override;
    void print() const override;
    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
    int getType() const override { return 1; }
};

#endif // STUDENT_H