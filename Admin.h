#ifndef ADMIN_H
#define ADMIN_H

#include "Base.h"

class Admin : public Base {
private:
    char* position;
    char* phone;
    char* responsibility;

public:
    Admin();
    ~Admin() override;

    void input() override;
    void print() const override;
    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
    int getType() const override { return 3; }
};

#endif // ADMIN_H