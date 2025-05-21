//
// Created by wfs on 5/21/25.
//

#include "File.h"

File::File() {
    this->name = "unnamed";
    this->extension = "txt";
    this->size = 0;
    this->content = "";
}
File::File(const std::string &name, const std::string &ext, size_t size, const std::string &content) {
    this->name = name;
    this->extension = ext;
    this->size = size;
    this->content = content;
}
File::~File() {
    name.clear();
    content.clear();
    extension.clear();
    size = 0;
}

void File::rename(const std::string &newName) {
    this->name = newName;
}
void File::edit(const std::string &newContent) {
    this->content = newContent;
    this->size = newContent.size();
}
void File::print() const {
    std::cout << *this << std::endl;
}
std::string File::getName() const {
    return name + '.' + extension;
}
size_t File::getSize() const {
    return size;
}

std::ostream &operator<<(std::ostream &os, const File &file) {
    os << "Файл: " << file.name << '.' << file.extension << "\nРазмер файла: " << file.size << "\nСодержимое файла: "
    << file.content;
    return os;
}