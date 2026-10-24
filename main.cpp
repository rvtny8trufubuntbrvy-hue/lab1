#include <iostream>
#include <clocale>
#include "Keeper.h"
#include "Student.h"
#include "Teacher.h"
#include "Admin.h"
#include <exception>

int main() {
    Keeper university;
    int choice = 0;

    while (true) {
        std::cout << "\n===== MENU (UNIVERSITY) =====\n"
                  << "1. Add object (Student / Teacher / Admin)\n"
                  << "2. Remove object by index\n"
                  << "3. Print all\n"
                  << "4. Save to file\n"
                  << "5. Load from file\n"
                  << "6. Exit\n"
                  << "Choose action: ";
        std::cin >> choice;

        try {
            if (choice == 1) {
                int typeChoice;
                std::cout << "Object type (1 - Student, 2 - Teacher, 3 - Admin): ";
                std::cin >> typeChoice;

                Base* person = nullptr;
                if (typeChoice == 1)      person = new Student();
                else if (typeChoice == 2) person = new Teacher();
                else if (typeChoice == 3) person = new Admin();
                else {
                    std::cout << "Invalid object type!" << std::endl;
                    continue;
                }

                person->input();
                university.add(person);
                std::cout << "Object added!" << std::endl;

            } else if (choice == 2) {
                int index;
                std::cout << "Enter index to remove: ";
                std::cin >> index;
                university.remove(index);
                std::cout << "Object removed!" << std::endl;

            } else if (choice == 3) {
                std::cout << "\n=== Current list ===" << std::endl;
                university.printAll();

            } else if (choice == 4) {
                university.saveToFile("university_data.bin");

            } else if (choice == 5) {
                university.loadFromFile("university_data.bin");

            } else if (choice == 6) {
                std::cout << "Exit." << std::endl;
                break;
            } else {
                std::cout << "Invalid menu item!" << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cout << "\n[EXCEPTION] Error: " << e.what() << std::endl;
        }
    }

    return 0;
}