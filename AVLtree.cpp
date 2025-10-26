#include <iostream>
#define nl << '\n'
using namespace std;
// Terninar o caso da eliminação de um no com dois filhos
class AVLTree{
protected:
    AVLTree* raiz = nullptr;
    AVLTree* pai = nullptr;
    AVLTree* menor = nullptr;
    AVLTree* maior = nullptr;
    int fatorB = 0;

    AVLTree* createNo(int value){
        AVLTree* no = new AVLTree();
        no->value = value;
        return no;
    }

    AVLTree* seachAVLTree(AVLTree* no, int value){
        while(no != nullptr && value != no->value){
            if(value < no->value){ no = no->menor;}
            else { no = no->maior; }
        }
        return no;
    }
    
    AVLTree* minino(AVLTree* no){
        while(no->menor != nullptr){
            no = no->menor;
        }
        return no;
    }

    int calcFatorB(AVLTree* no){
        int altD = 0, altE = 0;
        AVLTree* maior = no->maior;
        AVLTree* menor = no->menor;
        while(maior != nullptr or menor != nullptr){
            if(maior != nullptr){ maior = maior->maior; altD++; }
            if(menor != nullptr){ menor = menor->menor; altE++; }
        }
        return altD - altE;
    }
    
    void fator(AVLTree* no){
        AVLTree* pai = no->pai;
        while(pai != nullptr){
            pai->fatorB = calcFatorB(pai);
            if(abs(pai->fatorB) > 1){
                AVLTree* filho = (pai->maior == nullptr) ? pai->menor : pai->maior;
                if(pai->fatorB == -2 && filho->fatorB == -1){
                    cout << "(Caso 1): ";
                    filho->maior = pai;
                    filho->pai = pai->pai;
                    pai->pai = filho;
                    pai->menor = nullptr;
                    if(filho->pai == nullptr){ this->raiz = filho; cout << "atual;";}
                    return;
                }
                if(pai->fatorB == 2 && filho->fatorB == 1){
                    cout << "(Caso 2): ";
                    filho->menor = pai;
                    filho->pai = pai->pai;
                    pai->pai = filho;
                    pai->maior = nullptr;
                    if(filho->pai == nullptr){ this->raiz = filho; cout << "atual;";}
                    return;
                }
                if(pai->fatorB == -2){
                    cout << "(Caso 3): ";
                    
                    if(pai->maior != nullptr && pai->maior->fatorB == 1){ filho = pai->maior; }
                    else{ filho = pai->menor; }

                    filho->maior->pai = pai->pai;
                    pai->pai = filho->maior;
                    filho->maior->maior = pai;
                    filho->pai = filho->maior;
                    filho->maior = (filho->maior->maior != nullptr) ? filho->maior->maior : filho->maior->menor;
                    filho->maior->menor = filho;
                    if(filho->pai == nullptr){ this->raiz = filho; cout << "atual;";}
                    return;
                }
            }
            else{ pai = pai->pai; }
        }
    }

public:
    int value;

    void insertNo(int value){
        AVLTree* no = createNo(value);
        if(this->raiz == nullptr){
            this->raiz = no;
            return;
        }
        AVLTree* temp = raiz;
        AVLTree* Pai = temp;
        while(temp != nullptr){
            if(temp->value > no->value){
                Pai = temp;
                temp = temp->menor;
                if(temp == nullptr){
                    Pai->menor = no;
                    no->pai = Pai;
                }
            }
            else{
                Pai = temp;
                temp = temp->maior;
                if(temp == nullptr){
                    Pai->maior = no;
                    no->pai = Pai;
                }
            }
        }
        fator(no);

        return;
    }

    void emOrdem(AVLTree* no){
        if(no != nullptr){
            cout << "{" << no->value << ", " << no->fatorB << "}" << " - ";
            emOrdem(no->menor);
            emOrdem(no->maior);
        }
    }
    
    void show(AVLTree* node, int nivel = 0) {
        if (node == nullptr) return;
        show(node->maior, nivel + 1);
        cout << string(nivel * 4, ' ') << node->value << '\n';
        show(node->menor, nivel + 1);
    }
    
    AVLTree* sucessor(int value){
        AVLTree* no = seachAVLTree(this->raiz, value);
        if(no == nullptr){ printf("Erro");}
        if(no->maior != nullptr){ return minino(no->maior); }
        AVLTree* aux = no->pai;

        while(aux != nullptr && no == aux->maior){
            no = aux;
            aux = aux->pai;
        }
        return aux;
    }
    
    void eliminar(int value){
        AVLTree* no = this->seachAVLTree(this->raiz, value);
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
            delete(no);
            return;
        }
        
        if(no->maior != nullptr && no->menor != nullptr){

        }
        
    }

    AVLTree* getRoot() { return raiz; }

};

int main(){
    AVLTree arvore;
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
                cout << "Sucessor de é " << value << ": " << ((arvore.sucessor(value) != nullptr) ? to_string(arvore.sucessor(value)->value) : "Ele já é o maior") nl;
                break;
            default:
                break;
        }
        
    } while(cmd != -1);
    arvore.emOrdem(arvore.getRoot());
}
