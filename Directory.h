//
// Created by wfs on 5/21/25.
//

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "File.h"
#include <list>

class Directory {
    std::string name;
    std::list<File> files;
public:
    Directory(const std::string&);
    ~Directory();

    void moveFile(const std::string&, Directory&, Directory&);
    void addFile(const File&);
    void removeFile(const std::string&);
    void renameFile(const std::string&, const std::string&);
    File* findFile(const std::string&);
    void lsFiles() const;

    Directory operator+(const Directory&) const;
    friend std::ostream& operator<<(std::ostream&, const Directory&);
};

#endif //DIRECTORY_H
