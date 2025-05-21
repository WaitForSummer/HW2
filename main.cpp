#include "Directory.h"
#include <iostream>
#include <thread>
#include <fstream>
#include <mutex>
#include <list>
#include <algorithm>
#include <exception>

std::mutex mtx;
Directory globalDir("home");

void saveToFile(const std::string& fileName) {
    std::lock_guard<std::mutex> lock(mtx);
    std::ofstream out(fileName);
    if (!out) throw std::runtime_error("Ошибка: не удалось открыть файл.");

    out << globalDir;
    std::cout << "Файлы успешно сохранены в " << fileName << std::endl;
}

void loadFromFile(const std::string& fileName) {
    std::lock_guard<std::mutex> lock(mtx);
    std::ifstream in(fileName);
    if (!in) throw std::runtime_error("Ошибка открытия файла для чтения.");

    std::string name, ext, content;
    size_t size;
    while (in >> name >> ext >> content) {
        in.ignore();
        std::getline(in, content);
        globalDir.addFile(File(name, ext, size, content));
    }
    std::cout << "Файлы успешно загружены из " << fileName << std::endl;
}

void addNewFile() {
    std::string name, ext, content;
    std::cout << "Имя файла: ";
    std::cin >> name;
    std::cout << "Расширение: ";
    std::cin >> ext;
    std::cin.ignore();
    std::cout << "Содержимое: ";
    std::getline(std::cin, content);

    File newFile(name, ext, content.size(), content);
    std::lock_guard<std::mutex> lock(mtx);
    globalDir.addFile(newFile);
    std::cout << "Файл успешно добавлен.\n";

}

void searchFile() {
    std::string name;
    std::cout << "Введите имя файла (с расширением): ";
    std::cin >> name;

    std::lock_guard<std::mutex> lock(mtx);
    File* found = globalDir.findFile(name);
    if (found) {
        std::cout << "Найден файл: " << *found << "\n";
    } else {
        std::cout << "Файл не найден.\n";
    }
}

void editFile() {
    std::string name;
    std::cout << "Введите имя файла: ";
    std::cin >> name;

    std::lock_guard<std::mutex> lock(mtx);
    File* file = globalDir.findFile(name);
    if (file) {
        std::string newContent;
        std::cin.ignore();
        std::cout << "Новое содержимое: ";
        std::getline(std::cin, newContent);
        file->edit(newContent);
        std::cout << "Файл обновлён.\n";
    } else {
        std::cout << "Файл не найден.\n";
    }
}

void deleteFile() {
    std::string name;
    std::cout << "Введите имя файла: ";
    std::cin >> name;

    std::lock_guard<std::mutex> lock(mtx);
    globalDir.removeFile(name);
    std::cout << "Файл удалён (если он был).\n";
}

void printAll() {
    std::lock_guard<std::mutex> lock(mtx);
    globalDir.lsFiles();
}

void sortFiles() {
    std::lock_guard<std::mutex> lock(mtx);
    globalDir.sortByName();
    std::cout << "Файлы успешно отсортированы по имени:\n";
    globalDir.lsFiles();
}

int main() {
    std::string command;
    bool running = true;

    while (running) {
        std::cout << "\nМеню:\n"
                  << "1. Добавить файл\n"
                  << "2. Найти файл\n"
                  << "3. Редактировать файл\n"
                  << "4. Удалить файл\n"
                  << "5. Сохранить в файл\n"
                  << "6. Загрузить из файла\n"
                  << "7. Показать все файлы\n"
                  << "8. Завершить\n"
                  << "9. Сортировать по имени\n"
                  << "Выбор: ";
        std::cin >> command;

        try {
            if (command == "1") {
                addNewFile();
            } else if (command == "2") {
                searchFile();
            } else if (command == "3") {
                editFile();
            } else if (command == "4") {
                deleteFile();
            } else if (command == "5") {
                std::thread saver(saveToFile, "files.txt");
                saver.join();
            } else if (command == "6") {
                std::thread loader(loadFromFile, "files.txt");
                loader.join();
            } else if (command == "7") {
                printAll();
            } else if (command == "8") {
                running = false;
            } else if (command == "9") {
                sortFiles();
            } else {
                std::cout << "Неверная команда\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
    }

    return 0;
}