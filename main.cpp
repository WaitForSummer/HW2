#include "Directory.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>

std::mutex mtx;
Directory globalDir("home");

void save(const std::string& filename) {
    std::lock_guard<std::mutex> lock(mtx);
    std::ofstream out(filename);
    if (!out) throw std::runtime_error("Не удалось открыть файл для записи.");
    out << globalDir;
    std::cout << "Сохранено в файл.\n";
}

void load(const std::string& filename) {
    std::lock_guard<std::mutex> lock(mtx);
    std::ifstream in(filename);
    if (!in) throw std::runtime_error("Не удалось открыть файл для чтения.");
    in >> globalDir;
    std::cout << "Загружено из файла.\n";
}

int main() {
    std::string command;
    while (true) {
        std::cout << "\n1. Добавить\n2. Найти\n3. Удалить\n4. Показать\n5. Сохранить\n6. Загрузить\n7. Сортировать\n0. Выход\nВыбор: ";
        std::cin >> command;

        try {
            if (command == "1") {
                std::string name, ext, cont;
                std::cout << "Имя: "; std::cin >> name;
                std::cout << "Расширение: "; std::cin >> ext;
                std::cin.ignore();
                std::cout << "Содержимое: "; std::getline(std::cin, cont);
                globalDir.addFile(File(name, ext, cont));
            } else if (command == "2") {
                std::string full;
                std::cout << "Имя с расширением: "; std::cin >> full;
                File* f = globalDir.find(full);
                if (f) f->print();
                else std::cout << "Не найдено.\n";
            } else if (command == "3") {
                std::string full;
                std::cout << "Имя: "; std::cin >> full;
                globalDir.remove(full);
            } else if (command == "4") {
                globalDir.printAll();
            } else if (command == "5") {
                std::thread t(save, "files.txt");
                t.join();
            } else if (command == "6") {
                std::thread t(load, "files.txt");
                t.join();
            } else if (command == "7") {
                globalDir.sortByName();
            } else if (command == "0") {
                break;
            } else {
                std::cout << "Неверная команда\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
    }
    return 0;
}
