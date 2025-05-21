#include "Directory.h"
#include <algorithm>
#include <iostream>

Directory::Directory(const std::string& n) : name(n) {}
Directory::~Directory() {}

void Directory::addFile(const File& f) {
    if (contains(f.getFullName()))
        throw std::runtime_error("Файл уже существует!");
    files.push_back(f);
}

bool Directory::contains(const std::string& fullName) const {
    for (const auto& f : files)
        if (f.getFullName() == fullName) return true;
    return false;
}

void Directory::printAll() const {
    std::cout << "Директория: " << name << "\n";
    for (const auto& f : files)
        f.print();
}

File* Directory::find(const std::string& fullName) {
    for (auto& f : files)
        if (f.getFullName() == fullName)
            return &f;
    return nullptr;
}

void Directory::remove(const std::string& fullName) {
    files.remove_if([&](const File& f) {
        return f.getFullName() == fullName;
    });
}

void Directory::sortByName() {
    files.sort([](const File& a, const File& b) {
        return a.getFullName() < b.getFullName();
    });
}

std::ostream& operator<<(std::ostream& os, const Directory& dir) {
    os << dir.name << "\n" << dir.files.size() << "\n";
    for (const auto& f : dir.files)
        os << f;
    return os;
}

std::istream& operator>>(std::istream& is, Directory& dir) {
    dir.files.clear();
    std::getline(is, dir.name);
    size_t count;
    is >> count;
    is.ignore();
    for (size_t i = 0; i < count; ++i) {
        File f;
        is >> f;
        dir.files.push_back(f);
    }
    return is;
}
