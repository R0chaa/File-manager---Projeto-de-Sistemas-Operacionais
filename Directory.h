// Directory.h
#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__

#include <string>
#include <sstream>

class Directory {
public:
  Directory(Directory *parent, std::string path, std::string id, char tipo);
  ~Directory();

  std::string GetID();
  void SetID(std::string id);

  std::string GetPath();
  void SetPath(std::string, Directory *parent);

  char GetTipo();
  void SetTipo(char tipo);

  int GetSizeDir();
  void SetSizeDir(int index);
  void SetArq(Directory** file);
  Directory** GetArquivos();
  void AddArquivo(Directory *file);
  void RemoveArquivo(std::string id);

  int GetSizeArq();
  void SetSizeArq(int index);
  void SetDir(Directory** file);
  Directory** GetDiretorios();
  void AddDiretorio(Directory* file);
  void RemoveDiretorio(std::string id);

  Directory* GetAnterior();
  void SetAnterior(Directory *parent);

  void ListDir(Directory *current);
  void ListArq(Directory *current);
  void ListAll(Directory *current);

	bool IsRoot() const;
	bool IsLeaf();

	int GetDegree();
	int GetDepth();
	int GetHeight();

private:
	std::string m_ID; // Nome do diretório ou arquivo
  std::string m_Path; // Caminho a partir da raiz
  char m_Tipo; // Arquivo ‘a’ ou Diretório ‘d’
  Directory *m_Anterior; // Diretório anterior..
  Directory** m_Arquivos; // Lista de arquivos a partir do corrente
  int m_sizeArq; 
  Directory** m_Diretorios; // Lista de diretórios a partir do corrente
  int m_sizeDir;

  int GetDepthInternal(Directory* node) const;
	int GetHeightInternal(Directory *node) const;

};

#endif
