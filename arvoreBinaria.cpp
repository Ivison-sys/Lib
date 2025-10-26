#include <iostream>
#define nl << '\n'
using namespace std;
// Terninar o caso da eliminação de um no com dois filhos
class Tree{
protected:
    Tree* raiz = nullptr;
    Tree* pai = nullptr;
    Tree* menor = nullptr;
    Tree* maior = nullptr;

    Tree* createNo(int value){
        Tree* no = new Tree();
        no->value = value;
        return no;
    }

    Tree* seachTree(Tree* no, int value){
        while(no != nullptr && value != no->value){
            if(value < no->value){ no = no->menor;}
            else { no = no->maior; }
        }
        return no;
    }
    
    Tree* minino(Tree* no){
        while(no->menor != nullptr){
            no = no->menor;
        }
        return no;
    }

public:
    int value;

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
    Tree* sucessor(int value){
        Tree* no = seachTree(this->raiz, value);
        if(no == nullptr){ printf("Erro");}
        if(no->maior != nullptr){ return minino(no->maior); }
        Tree* aux = no->pai;

        while(aux != nullptr && no == aux->maior){
            no = aux;
            aux = aux->pai;
        }
        return aux;
    }
    
    void eliminar(int value){
        Tree* no = this->seachTree(this->raiz, value);
        // O no é uma folha
        if(no->maior == no->menor && no->menor == nullptr){
            if(no->pai == nullptr) { this->raiz == nullptr; }
            if(no->pai->maior == no){ no->pai->maior = nullptr; }
            else { no->pai->menor == nullptr; }
            free(no);
            return;
        }
        // O no tem apenas um filho
        if(no->maior == nullptr || no->menor == nullptr){
            if(no->pai == nullptr) { this->raiz = (no->maior == nullptr) ? no->menor : no->maior; }
            else if(no->maior != nullptr) { // O no só tem o maior filho
                if(no->value > no->pai->value){  // O no a sair é o maior do seu pai
                    no->pai->maior = no->maior;
                    no->maior->pai = no->pai;
                }
                else{ 
                    no->pai->menor = no->maior;
                    no->maior->pai = no->pai;
                }
            }
            else{ // O no só tem o menor filho
                if(no->value > no->pai->value){  // O no a sair é o maior do seu pai
                    no->pai->maior = no->menor;
                    no->menor->pai = no->pai;
                }
                else{ 
                    no->pai->menor = no->menor;
                    no->menor->pai = no->pai;
                }
            }
            free(no);
            return;
        }
        
        if(no->maior != nullptr && no->menor != nullptr){

        }
        
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
                do{
                    cout << "Valor: "; cin >> value;
                    if(value != -1){
                        arvore.insertNo(value);
                    }
                } while(value != -1);
                break;
            case 2:
                cout << "Caminahndo em ordem!" nl;
                arvore.emOrdem(arvore.getRoot());
                cout nl;
                break;
            case 3:
                cout << "Verificar sucessor" nl;
                cout << "Digite o valor: "; cin >> value;
                cout << "Sucessor de é " << value << ": " << arvore.sucessor(value)->value nl;
                break;
            default:
                break;
        }
        
    } while(cmd != -1);
    arvore.emOrdem(arvore.getRoot());
}
