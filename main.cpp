#include <iostream>
#include <unistd.h>
#include "FileManager.hpp"
#include <getopt.h>
#include <cstdlib>	
#include <cstdio>

/*
Lucas Damasceno da Cunha Lima (TIA: 32132611)
Lucas Paulo da Rocha (TIA: 32196628)
Thiago Aidar Figueiredo (TIA: 32144547)
Yiou Wu (TIA: 32123213)
*/

using namespace std;

void clear_screen() { //Usa CLS no console se o S.O é WIN, senão usa Clear.
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
} 

void PrintNode(Directory* node)
{
	if (node != nullptr) node->ListAll(node);
}

void ChangeDirectory(FileTree* tree)
{
  Directory** temp = tree->GetCurrent()->GetDiretorios();
  if (tree->GetCurrent()->GetAnterior() != nullptr)
    cout << "[0] " << tree->GetCurrent()->GetAnterior()->GetID() << endl;
  for(int i = 0; i < tree->GetCurrent()->GetSizeDir(); ++i){
    cout << "["<< i+1 <<"] " << temp[i]->GetID() << endl;
  }
  int index;
  cout << "\n Choose Directory: ";
  cin >> index;
  if(index == 0) tree->SetCurrent(tree->GetCurrent()->GetAnterior());
  else if (index >= 1 && index <= tree->GetCurrent()->GetSizeDir()) {
    tree->SetCurrent(temp[index-1]);
  }
}

void Insert(FileTree* tree)
{
	string id;
  char tipo;
	cout << "Insert name: ";
	cin >> id;
  cout << "Insert type: ";
	cin >> tipo;
  if(tipo == 'a' || tipo == 'd'){
	  tree->Insert(id, tipo);
  }
  else cout << "*** ERROR! Type invalid!\n";
}

void Remove(FileTree* tree)
{
	string id;
  char tipo;
  PrintNode(tree->GetCurrent());
	cout << "\n\nRemove file: ";
	cin >> id;
  cout << "Insert type: ";
	cin >> tipo;
	tree->Remove(id, tipo);
}

void TraversePreOrder(FileTree* tree)
{
	cout << "\n" << tree->TraversePreOrder() << '\n';
}

void TraverseDepthOrder(FileTree* tree)
{
  cout << "\n" << tree->TraverseDepthOrder();
}
void menu() {
  printf("  1 - Trocar pasta\n"
         "  2 - Salvar pasta em arvore\n"
         "  0 - Sair\n");
}

int main() {
  std::string path = ".";
  bool list_files = true;
  bool draw_tree = true;
  int opt;
  std::vector<std::string> ignore_dirs = {".cache", ".ccls-cache"};
  std::vector<std::string> ignore_extensions = {".h", ".h.blob", ".tcc", ".tcc.blob", ".blob"};
  FileTree* tree = new FileTree();
  do {
  	std::cout << " - Pasta atual: " << path << std::endl << std::endl;
  	menu();
  	cout << "  > ";
  	cin >> opt;
  	clear_screen();
    
    switch (opt) {
      case 1:{
        FileManager file(path);
      	cout << " - Pasta atual: " << path << std::endl << std::endl;
		    cout << " Pasta: ";
		    cin >> path;
		    clear_screen();
        break;
      }
      
      case 2:{
        FileManager file(path);
        tree->Insert("C:", 'd');
    		file.writeToFile(ignore_dirs, ignore_extensions, tree);
        
      	int option = 0;
      	do
      	{
      		cout << "\n[1] Insert\n"
      			<< "[2] Remove\n"
      			<< "[3] Change Current Directory\n"
      			<< "[4] Percurso em profundidade\n"
            << "[5] Percurso em largura\n"
      			<< "[0] Exit\nOption: ";
      		cin >> option;
          clear_screen();
      		switch (option)
        		{
        		case 1: 
              Insert(tree); 
              PrintNode(tree->GetCurrent());
              cout << endl;
              break;
              
        		case 2: 
              Remove(tree);
              clear_screen();
              PrintNode(tree->GetCurrent());
              cout << endl;
              break;
              
        		case 3: 
              ChangeDirectory(tree);
              PrintNode(tree->GetCurrent());
              cout << endl;
              break;
              
        		case 4: 
              cout << "\n" << tree->TraversePreOrder() << '\n';
              break;
            case 5:
              cout << "\n" << tree->TraverseDepthOrder() << '\n';
              break;
              
        		case 0: 
              opt = 0;
              break;
        	}
      	} while (option != 0);
        break;
      }
      case 0:
        break;
      
      default: 
        continue;
    }
  } while (opt != 0);  
  tree->Clear();
  delete tree;
  cout << "\n Tchau professor!! obrigado pelo semestre.";
  sleep(2);
  cout << "\n\n Assinado: ";
  sleep(2);
  cout << "\n\n - lucas daMASSAceno ᕙ(^▿^-ᕙ) ";
  sleep(2);
  cout << "\n - lucas rochaaa ᕦ(ò_óˇ)ᕤ ";
  sleep(2);
  cout << "\n - thiago figueiredo ٩(͡๏̯͡๏)۶ ";
  sleep(2);
  cout << "\n - Yiou Wu (●'◡'●) ";
  sleep(2);
  cout << "\n\n .";
  sleep(5);
  
  return 0;
}