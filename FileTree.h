// BST.h
#ifndef __FILETREE_H__
#define __FILETREE_H__

#include "Directory.h"

class FileTree
{
public:
	FileTree();
	~FileTree();

	Directory* GetRoot() const;

  Directory* GetCurrent() const;
  void SetCurrent(Directory* node);

	bool IsEmpty() const;
	void Clear();

	int GetHeight() const;

	std::string TraversePreOrder() const;
	std::string TraverseDepthOrder() const;

	Directory* Search(std::string id) const;
  void Insert(std::string id, char tipo);
	void Remove(std::string id, char tipo);

private:
	Directory* m_Root;
  Directory* m_Current;
	void Destroy(Directory *node);

	std::string TraversePreOrderInternal(Directory* node, int index) const;
	std::string TraverseDepthOrderInternal(Directory* node) const;

	Directory* SearchInternal(Directory* node, std::string &id) const;
	Directory* InsertInternal(Directory* parent, std::string id, char tipo);
  void RemoveInternal(Directory* node, std::string id, char tipo);

};

#endif
