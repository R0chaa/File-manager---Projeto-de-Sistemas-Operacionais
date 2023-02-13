#include "FileManager.hpp"

void FileManager::clear() {
  corePath.clear();
}

void FileManager::clear(std::string newPath) {
  corePath = newPath;
}

void FileManager::info() {
  std::cout << "Current path is set to: " << corePath << "\n";
}

FileManager::file_info FileManager::make_file_info(std::string filename, std::string relative_filename, bool is_dir) {
  // f.name é o nome da pasta/arquivo
  // f.rname é o caminho da pasta/arquivo
  // f.is_dir é uma variavel boolean
  file_info f;
  f.name = filename;
  f.rname = relative_filename;
  f.is_dir = is_dir;
  return f;
}

std::vector<FileManager::file_info> FileManager::list_files(std::vector<std::string> extensions, bool ignore_extensions) {
  // Retorna a lista dos arquivos presentes em corePath

  std::vector<file_info> list_files;
  std::string base_name;

  if(*corePath.rbegin() != '/') base_name = corePath + "/";
  else base_name = corePath;

  DIR* dir;
  struct dirent *ent;
  bool is_dir;
  if((dir = opendir(base_name.c_str())) != NULL) {
    while((ent = readdir(dir)) != NULL) {
      bool include = false;
      std::string relative_filename = ent->d_name;
      if(relative_filename == "." || relative_filename == "..") {
        continue;
      }
      std::string filename = base_name + relative_filename;
      if(opendir(filename.c_str()) == NULL) {
        // Checka extensão do arq
        const char* const_relative_filename = relative_filename.c_str();
        auto pos = std::strrchr(const_relative_filename, '.');

        if (pos) {
        
          std::string file_extension = relative_filename.substr(pos - relative_filename.c_str());
          if (extensions.size() == 0) include = true;
          if (itemInList(file_extension, extensions) != ignore_extensions) {
            include = true;
          }
        }
        is_dir = false;
      }
      else {
        is_dir = true;
        include = true;
      }
      if (include) {
        list_files.push_back(make_file_info(filename, relative_filename, is_dir));
      }
    }
    closedir(dir);
  } else {
    std::cout << "Could not open directory " << base_name.c_str() << std::endl;
  }
  return list_files;
}

std::string spaces(int s) {
  std::string out;
  for (size_t i = 0; i < s; i++) {
    out += "    ";
  }
  return out;
}

void FileManager::writeToFileIterated(int depth, std::vector<std::string> ignore_dirs, std::vector<std::string> extensions_to_ignore, FileTree* tree) {
  std::vector<file_info> out_dir = this->list_files(extensions_to_ignore, true);
  ++depth;
  Directory** temp = tree->GetCurrent()->GetDiretorios();
  int pos = tree->GetCurrent()->GetSizeDir()-1;
  Directory* atual = tree->GetCurrent();
  
  for (auto const& iterating_entry: out_dir) {
    if (!iterating_entry.is_dir) {
      // é arq
      tree->Insert(iterating_entry.rname, 'a');
      std::cout << spaces(depth) << iterating_entry.rname + "\n";
    } else {
      // é dir
      tree->Insert(iterating_entry.rname, 'd');
      std::cout << spaces(depth) + "/" << iterating_entry.rname + "\n";
      if (itemInList(iterating_entry.rname, ignore_dirs)) {
#ifdef DEBUG
        std::cout << "Ignoring dir: " << iterating_entry.name << "\n";
#endif
        continue;
      }
      temp = tree->GetCurrent()->GetDiretorios();
      pos = tree->GetCurrent()->GetSizeDir()-1;
      atual = tree->GetCurrent();
      tree->SetCurrent(temp[pos]);
      this->clear(iterating_entry.name);
      this->writeToFileIterated(depth, ignore_dirs, extensions_to_ignore, tree);
      tree->SetCurrent(atual);
    }
  }   
}

bool FileManager::itemInList(std::string item, std::vector<std::string> list) {
  for(auto const& _item: list) {
    if (_item == item) {
      return true;
    }
  }
  return false;
}

void FileManager::writeToFile(std::vector<std::string> ignore_dirs, std::vector<std::string> ignore_extensions, FileTree* tree) { 
  Directory** temp = tree->GetCurrent()->GetDiretorios();
  int pos = tree->GetCurrent()->GetSizeDir()-1;
  Directory* atual = tree->GetCurrent();
  int depth = 0;
  
  std::vector<file_info> out = this->list_files(ignore_extensions, true);
  std::cout << std::endl;
  
  if (out.size() == 0) {
    return;
  }

  for (auto const& entry: out) {
    if (!entry.is_dir) {
      // entry é arquivo
      tree->Insert(entry.rname, 'a');
      std::cout << " " << entry.rname + "\n";
    } else {
      // entry é dir
      tree->Insert(entry.rname, 'd');
      std::cout << " " << entry.rname + "\n";
      
      if (itemInList(entry.rname, ignore_dirs)) { //Se o diretorio tem o nome do diretorio que pedimos pra ignorar a função ignora ele
        continue;
      } else {
        temp = tree->GetCurrent()->GetDiretorios();
        pos = tree->GetCurrent()->GetSizeDir()-1;
        atual = tree->GetCurrent();
        tree->SetCurrent(temp[pos]);
        this->clear(entry.name);
        this->writeToFileIterated(depth, ignore_dirs, ignore_extensions, tree);
        tree->SetCurrent(atual);
      }
    }
  }
}