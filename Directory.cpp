// Directory.cpp
#include "Directory.h"
#include <iostream>

Directory::Directory(Directory *parent,std::string path, std::string id, char tipo)
	: m_ID(id)
  , m_Path(path)
	, m_Tipo(tipo)
	, m_Anterior(parent)
	, m_Arquivos(nullptr)
  , m_Diretorios(nullptr)
  ,m_sizeDir(0)
  ,m_sizeArq(0)
{
}

Directory::~Directory()
{
	m_Anterior = nullptr;
  
  delete [] m_Arquivos;
  
  delete[] m_Diretorios;
}

std::string Directory::GetID() 
{
	return m_ID;
}

void Directory::SetTipo(char tipo){
  m_Tipo = tipo;
}


void Directory::ListDir(Directory *current){
  if(current->GetAnterior() != nullptr) std::cout << "\n"<< current->GetAnterior()->GetID();
  std::cout << "\n\t" << current->GetID();
  Directory** temp = current->GetDiretorios(); 
  for(int i = 0; i < GetSizeDir(); i++){
    std::cout <<"\n\t | "  << temp[i]->GetID() << " (Directory)";
  }
}

void Directory::ListArq(Directory *current){
  Directory** temp = GetArquivos();
  for(int i = 0; i < GetSizeArq(); i++){
    std::cout <<"\n\t | " << temp[i]->GetID() << " (Archive)";
  }
}

void Directory::ListAll(Directory *current){
  ListDir(current);
  ListArq(current);
}

void Directory::SetID(std::string id)
{
	m_ID = id;
}

std::string Directory::GetPath() 
{
	return m_Path;
}

void Directory::SetPath(std::string path, Directory *parent)
{
	m_Path = parent->GetPath() + '/' + path;
}

Directory* Directory::GetAnterior() 
{
	return m_Anterior;
}

void Directory::SetAnterior(Directory* parent)
{
	m_Anterior = parent;
}

int Directory::GetSizeArq()
{
  return m_sizeArq;  
}

void Directory::SetSizeArq(int index)
{
  m_sizeArq = index;
}

int Directory::GetSizeDir()
{
  return m_sizeDir;  
}

void Directory::SetSizeDir(int index)
{
  m_sizeDir = index;
}

Directory** Directory::GetArquivos() 
{
	return m_Arquivos;
}

void Directory::SetArq(Directory** file)
{
  m_Arquivos = file;
}

void Directory::AddArquivo(Directory* file)
{
  int i;
  Directory** temp = new Directory*[GetSizeArq()+1];
  Directory** current = GetArquivos();
	for(i = 0; i < GetSizeArq();++i){
    temp[i] = current[i];
  }
  temp[i]= file;
  delete [] GetArquivos();
  SetSizeArq(GetSizeArq()+1);  
  SetArq(temp);
}

void Directory::RemoveArquivo(std::string id)
{
  int j = 0, key = 0;
  Directory** temp = new Directory*[GetSizeArq()-1];
  Directory** current = GetArquivos();
  for(int i = 0; i < GetSizeArq();++i){
    if (current[i]->GetID() == id){
      delete current[i];
      key = 1;
    }
    else temp[j++] = current[i];
  }
  if (key == 1){
    delete [] GetArquivos();
    SetSizeArq(GetSizeArq()-1); 
    SetArq(temp);
  }
  else delete [] temp;
  return;
}

Directory** Directory::GetDiretorios() 
{
	return m_Diretorios;
}
void Directory::SetDir(Directory** file){
  m_Diretorios = file;
}
void Directory::AddDiretorio(Directory* file)
{
	int i;
  Directory** temp = new Directory*[GetSizeDir()+1];
  Directory** current = GetDiretorios();
	for(i = 0; i < GetSizeDir();++i){
    temp[i] = current[i];
  }
  temp[i]= file;
  delete [] GetDiretorios();
  SetSizeDir(GetSizeDir()+1);  
  SetDir(temp);
}

void Directory::RemoveDiretorio(std::string id)
{
  int j = 0, key = 0;
  Directory** temp = new Directory*[GetSizeDir()-1];
  Directory** current = GetDiretorios();

	for(int i = 0; i < GetSizeDir();++i){
    if (current[i]->GetID() == id){
      delete current[i];
      key = 1;
    }
    else temp[j++] = current[i];
  }
  if (key == 1){
    delete [] GetDiretorios();
    SetSizeDir(GetSizeDir()-1); 
    SetDir(temp);
  }
  else delete [] temp;
  
  return;
}

bool Directory::IsRoot() const
{
	return m_Anterior == nullptr;
}

bool Directory::IsLeaf()
{
  if (m_Tipo == 'a') return true;
	else return GetSizeArq() == 0 && GetSizeDir() == 0;
}

int Directory::GetDegree() 
{
	return GetSizeArq() + GetSizeDir();
}

int Directory::GetDepth() 
{
	return GetDepthInternal(this);
}

int Directory::GetDepthInternal(Directory* node) const
{
	if (node->IsRoot())
	{
		return 0;
	}
	else
	{
		return 1 + GetDepthInternal(node->GetAnterior());
	}
}

int Directory::GetHeight() 
{
	return GetHeightInternal(this);
}

int Directory::GetHeightInternal(Directory* node) const
{
  int maxheight = 0, currentheight;
	if (node == nullptr || node->IsLeaf())
	{
		return 0;
	}
	else
	{
    for(int i = 0; i < node->GetSizeDir(); ++i){
      currentheight = GetHeightInternal(m_Diretorios[i]);
      if(currentheight > maxheight) maxheight = currentheight;
    }
		return maxheight;
	}
}

char Directory::GetTipo()  
{
  return m_Tipo;
}