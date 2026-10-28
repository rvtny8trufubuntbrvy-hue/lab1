#include <iostream>
#include <clocale>
#include <windows.h> 
#include <limits> 
#include "Keeper.h"
#include "Student.h"
#include "Teacher.h"
#include "Admin.h"
#include <exception>

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Keeper university;
    int choice = 0;

    while (true) {
        std::cout << "\n===== ПОЛЬЗОВАТЕЛЬСКОЕ МЕНЮ (ВУЗ) =====\n"
                  << "1. Добавить объект (Студент / Преподаватель / Администратор)\n"
                  << "2. Удалить объект по индексу\n"
                  << "3. Вывести всю базу на экран\n"
                  << "4. Сохранить базу в файл\n"
                  << "5. Восстановить базу из файла\n"
                  << "6. Выход\n"
                  << "Выберите действие: ";
        
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: нужно ввести число (1-6)!" << std::endl;
            continue;
        }

        try {
            if (choice == 1) {
                int typeChoice;
                std::cout << "Какой тип объекта добавить? (1 - Студент, 2 - Преподаватель, 3 - Админ): ";
                std::cin >> typeChoice;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ошибка: нужно ввести число (1-3)!" << std::endl;
                    continue;
                }

                Base* person = nullptr;
                if (typeChoice == 1)      person = new Student();
                else if (typeChoice == 2) person = new Teacher();
                else if (typeChoice == 3) person = new Admin();
                else {
                    std::cout << "Неверный тип объекта!" << std::endl;
                    continue;
                }

                person->input();
                university.add(person);
                std::cout << "Объект успешно добавлен!" << std::endl;

            } else if (choice == 2) {
                int index;
                std::cout << "Введите индекс для удаления: ";
                std::cin >> index;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ошибка: индекс должен быть числом!" << std::endl;
                    continue;
                }

                university.remove(index);
                std::cout << "Объект успешно удален!" << std::endl;

            } else if (choice == 3) {
                std::cout << "\n=== Текущий список объектов ===" << std::endl;
                university.printAll();

            } else if (choice == 4) {
                university.saveToFile("university_data.bin");

            } else if (choice == 5) {
                university.loadFromFile("university_data.bin");

            } else if (choice == 6) {
                std::cout << "Выход из программы." << std::endl;
                break;
            } else {
                std::cout << "Неверный пункт меню!" << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cout << "\n[ИСКЛЮЧЕНИЕ] Произошла ошибка: " << e.what() << std::endl;
        }
    }

    return 0;
}