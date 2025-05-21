#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "File.h"
#include <list>
#include <string>

class Directory {
    std::string name;
    std::list<File> files;

public:
    Directory(const std::string&);
    ~Directory();

    void addFile(const File&);
    bool contains(const std::string&) const;
    void printAll() const;
    File* find(const std::string&);
    void remove(const std::string&);
    void sortByName();

    friend std::ostream& operator<<(std::ostream&, const Directory&);
    friend std::istream& operator>>(std::istream&, Directory&);
};

#endif
