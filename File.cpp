#include "File.h"

File::File() : name("unnamed"), extension("txt"), content("") {}
File::File(const std::string& n, const std::string& e, const std::string& c)
    : name(n), extension(e), content(c) {}

File::~File() {}

std::string File::getFullName() const {
    return name + "." + extension;
}

std::string File::getContent() const {
    return content;
}

void File::edit(const std::string& newContent) {
    content = newContent;
}

void File::print() const {
    std::cout << *this << std::endl;
}

std::ostream& operator<<(std::ostream& os, const File& file) {
    os << file.name << "." << file.extension << "\n"
       << file.content.length() << "\n"
       << file.content << "\n";
    return os;
}

std::istream& operator>>(std::istream& is, File& file) {
    is >> file.name >> file.extension;
    size_t size;
    is >> size;
    is.ignore();
    std::getline(is, file.content);
    return is;
}
