//
// Created by wfs on 5/21/25.
//

#include "Directory.h"

Directory::Directory(const std::string &name): name(name) {}
Directory::~Directory() {
    name.clear();
    files.clear();
}


void Directory::addFile(const File &file) {
    for (const auto &entry : files) {
        if (entry.getName() == file.getName()) {
            std::cerr << "Ошибка: файл с таким именем уже существует.";
            return;
        }
    }
    files.push_back(file);
}
void Directory::removeFile(const std::string &) {
    for (auto item = files.begin(); item != files.end(); item++) {
        if (item->getName() == name) {
            files.erase(item);
            break;
        }
    }
}
void Directory::renameFile(const std::string &oldName, const std::string &newName) {
    for (File& file : files) {
        if (file.getName() == oldName) {
            file.rename(newName);
            return;
        }
    }
}
File *Directory::findFile(const std::string &name) {
    for (File& file : files) {
        if (file.getName() == name) {
            return &file;
        }
    }
    return nullptr;
}
void Directory::lsFiles() const {
    for (const auto &file : files) {
        std::cout << file.getName() << std::endl;
    }
}
void Directory::moveFile(const std::string &name, Directory &start, Directory &destinition) {
    File* filePtr = start.findFile(name);
    if (!filePtr) {
        std::cerr << "Файл не найден." << std::endl;
        return;
    }

    if (destinition.findFile(name)) {
        std::cerr << "В целевом катологе есть уже файл с таким именем." << std::endl;
        return;
    }

    destinition.addFile(*filePtr);
    start.removeFile(name);
    std::cout << "Файл успешно перемещен." << std::endl;
}

Directory Directory::operator+(const Directory &other) const {
    Directory res(this->name + "_" + other.name);
    res.files = this->files;
    res.files.insert(res.files.end(), other.files.begin(), other.files.end());
    return res;
}
std::ostream &operator<<(std::ostream &os, const Directory &dir) {
    os << "Директория: " << dir.name << std::endl;
    for (const auto &file : dir.files) {
        os << " " << file << std::endl;
    }
    return os;
}
