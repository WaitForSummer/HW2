//
// Created by wfs on 5/21/25.
//

#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>

class File {
    std::string name;
    std::string extension;
    size_t size;
    std::string content;
public:
    File();
    File(const std::string&, const std::string&, size_t, const std::string&);
    ~File();

    void rename(const std::string&);
    void edit(const std::string&);
    void print() const;
    std::string getName() const;
    size_t getSize() const;

    friend std::ostream& operator<<(std::ostream&, const File&);
};

#endif //FILE_H
