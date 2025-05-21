#ifndef FILE_H
#define FILE_H

#include <string>
#include <iostream>

class File {
    std::string name;
    std::string extension;
    std::string content;

public:
    File();
    File(const std::string&, const std::string&, const std::string&);
    ~File();

    std::string getFullName() const;
    std::string getContent() const;
    void edit(const std::string&);
    void print() const;

    friend std::ostream& operator<<(std::ostream&, const File&);
    friend std::istream& operator>>(std::istream&, File&);
};

#endif
