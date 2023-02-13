// FileManager class
#include <iostream>
#include <string>
#include <vector>
#include <dirent.h> //Biblioteca para ler bibliotecas in linux
// #include <cassert>
#include <fstream>
#include <cstring>
#include "FileTree.h"

class FileManager {
  public:
    struct file_info {
      std::string name;
      std::string rname;
      bool is_dir;
    };

    FileManager(std::string path) {
      this->corePath = path;
    }

    void clear();

    void clear(std::string);

    void info();

    std::vector<file_info> list_files(std::vector<std::string> extensions = {}, bool ignore_extensions = false);

    void writeToFile(std::vector<std::string> ignore_dirs, std::vector<std::string> ignore_extensions, FileTree* tree);

  private:

    std::string corePath;

    void writeToFileIterated(int, std::vector<std::string>, std::vector<std::string>, FileTree* tree);

    bool itemInList(std::string, std::vector<std::string>);

    file_info make_file_info(std::string, std::string, bool);

};