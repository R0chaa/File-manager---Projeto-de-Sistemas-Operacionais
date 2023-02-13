// BST.cpp

#include "FileTree.h"
#include <queue> // TraverseDepthOrderInternal
#include <iostream>

FileTree::FileTree()
	: m_Root(nullptr)
  , m_Current(nullptr)
{
}

FileTree::~FileTree()
{
	Clear();
}

Directory* FileTree::GetRoot() const
{
	return m_Root;
}

Directory* FileTree::GetCurrent() const
{
	return m_Current;
}

void FileTree::SetCurrent(Directory* node){
  m_Current = node;
}

bool FileTree::IsEmpty() const
{
	return m_Root == nullptr;
}

void FileTree::Clear()
{
	Destroy(m_Root);
	m_Root = nullptr;
  m_Current = nullptr;
}

void FileTree::Destroy(Directory* node)
{
	if (node != nullptr)
	{
    Directory** temp1 = node->GetDiretorios();
    Directory** temp2 = node->GetArquivos();
    
    for(int i = 0; i < node->GetSizeDir();i++){
      Destroy(temp1[i]);
    }
    for(int i = 0; i < node->GetSizeArq(); i++){
      Destroy(temp2[i]);
    }
		delete node;
		node = nullptr;
	}
}


int FileTree::GetHeight() const
{
	if (m_Root == nullptr)
		return -1;

	return m_Root->GetHeight();
}


std::string FileTree::TraversePreOrder() const
{
	return TraversePreOrderInternal(m_Root, 0);
}

std::string FileTree::TraversePreOrderInternal(Directory* node, int index) const
{
	if (node != nullptr)
	{
		std::ostringstream oss;
    for(int i = 0; i < index; i++){
      oss << "\t";
    }
		oss << node->GetID() << (node->GetTipo() != 'a' ? " (Directory)" : " (Archive)") << std::endl;
    Directory** temp1 = node->GetDiretorios();
    Directory** temp2 = node->GetArquivos();
    for(int i = 0; i < node->GetSizeArq(); i++){
      oss << TraversePreOrderInternal(temp2[i], index+1);
    }
    for(int i = 0; i < node->GetSizeDir(); i++){
      oss << TraversePreOrderInternal(temp1[i], index+1);
    }
		return oss.str();
	}
	return "";
}

std::string FileTree::TraverseDepthOrder() const
{
	return TraverseDepthOrderInternal(m_Root);
}

std::string FileTree::TraverseDepthOrderInternal(Directory* node) const
{
	if (node != nullptr)
	{
		std::ostringstream oss;
		std::queue<Directory*> queue;
		queue.push(node);
		while (!queue.empty())
		{
			Directory* n = queue.front();
			queue.pop();
			oss << n->GetID() << "\n";
      Directory** temp1 = n->GetDiretorios();
      Directory** temp2 = n->GetArquivos();
      for(int i = 0; i < n->GetSizeDir(); i++){
        if (temp1[i] != nullptr)
				  queue.push(temp1[i]);
      }
      for(int i = 0; i < n->GetSizeArq(); i++){
        if (temp2[i] != nullptr)
				  queue.push(temp2[i]);
      }
		}
		return oss.str();
	}
	return "";
}

Directory* FileTree::Search(std::string id) const
{
	return SearchInternal(m_Root, id);
}

Directory* FileTree::SearchInternal(Directory* node, std::string &id) const
{
	if (node == nullptr)
		return nullptr;
	else if (node->GetID() == id)
		return node;
	else{
    Directory** temp1 = node->GetArquivos();
		Directory** temp2 = node->GetDiretorios();
    for(int i = 0; i < node->GetSizeDir(); i++){
      return SearchInternal(temp1[i], id);
    }
    for(int i = 0; i < node->GetSizeArq(); i++){
      return SearchInternal(temp2[i], id);
    }
  }
  return nullptr;  
}


void FileTree::Insert(std::string id, char tipo)
{
	if (IsEmpty()){
		m_Current = m_Root = new Directory(nullptr,"./", id, tipo);
	} else {
      Directory* temp = InsertInternal(GetCurrent(), id, tipo);
      if(tipo == 'a') m_Current->AddArquivo(temp);
      else m_Current->AddDiretorio(temp);
  }
}

Directory* FileTree::InsertInternal(Directory* parent, std::string id, char tipo)
{
  std::string path = GetCurrent()->GetPath() + '/' + id;
  Directory* node = new Directory(parent,path, id, tipo);
	return node;
}

void FileTree::Remove(std::string id, char tipo)
{
	RemoveInternal(m_Current, id, tipo);
}

void FileTree::RemoveInternal(Directory* node, std::string id, char tipo) 
{
  if (tipo == 'a')
    GetCurrent()->RemoveArquivo(id);
  else if (tipo == 'd')
    GetCurrent()->RemoveDiretorio(id);
  else
    return;
}

