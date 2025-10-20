#include <iostream>
#define nl << '\n'
using namespace std;


class Tree{
private:
    Tree* raiz = nullptr;
    Tree* pai = nullptr;
    Tree* menor = nullptr;
    Tree* maior = nullptr;
    int value;

    Tree* createNo(int value){
        Tree* no = new Tree();
        no->value = value;
        return no;
    }

    Tree* seachTree(Tree* no, int value){
        while(no != nullptr && value != no->value){
            if(value < no->value){ no = no->maior;}
            else { no = no->menor; }
        }
        return no;
    }
    
    Tree* minino(Tree* no){
        while(no->menor != nullptr){
            no = no->menor;
        }
        return no;
    }

    Tree* sucessor(Tree* no){
        if(no->maior != nullptr){ return this->minino(no->maior); }
        Tree* aux = no->pai;

        while(aux != nullptr && no == aux->menor){
            no = pai;
            pai = pai->pai;
        }
        return pai;
    }

public:
    void insertNo(int value){
        Tree* no = createNo(value);
        if(this->raiz == nullptr){
            this->raiz = no;
            return;
        }
        Tree* temp = raiz;
        Tree* Pai = temp;
        while(temp != nullptr){
            if(temp->value > no->value){
                Pai = temp;
                temp = temp->menor;
                if(temp == nullptr){
                    Pai->menor = no;
                    no->pai = Pai;
                    return;
                }
            }
            else{
                Pai = temp;
                temp = temp->maior;
                if(temp == nullptr){
                    Pai->maior = no;
                    no->pai = Pai;
                    return;
                }
            }
        }
    }
    
    void emOrdem(Tree* no){
        if(no != nullptr){
            emOrdem(no->menor);
            cout << no->value << ", ";
            emOrdem(no->maior);
        }
    }
    void show(Tree* node, int nivel = 0) {
        if (node == nullptr) return;
        show(node->maior, nivel + 1);
        cout << string(nivel * 4, ' ') << node->value << '\n';
        show(node->menor, nivel + 1);
    }

    Tree* getRoot() { return raiz; }


};

int main(){
    Tree arvore;
    int cmd, value;
    
    
    do{
        cout << "(1) adiconar nos a arvore" nl;
        cout << "(2) Verificar em ordem" nl;
        cout << "(3) Verificar sucessor" nl;
        cout << "Digite comando: "; cin >> cmd;

        switch (cmd){
        case 1:
            
            break;
        default:
            break;
        }
        
    } while(cmd != -1);
    arvore.emOrdem(arvore.getRoot());

}
