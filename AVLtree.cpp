#include <iostream>
#define nl << '\n'
using namespace std;

class AVLtree {
protected:
    AVLtree* raiz = nullptr;
    AVLtree* pai = nullptr;
    AVLtree* menor = nullptr;
    AVLtree* maior = nullptr;
    int value;
    int altura = 1; // cada nó começa com altura 1

    // ---- Funções auxiliares ----
    AVLtree* createNo(int value) {
        AVLtree* no = new AVLtree();
        no->value = value;
        return no;
    }

    // Retorna o máximo de dois inteiros (sem usar <algorithm>)
    int maximo(int a, int b) {
        return (a > b) ? a : b;
    }

    int getAltura(AVLtree* no) {
        return no ? no->altura : 0;
    }

    void updateAltura(AVLtree* no) {
        if (no)
            no->altura = 1 + maximo(getAltura(no->menor), getAltura(no->maior));
    }

    int fatorB(AVLtree* no) {
        return no ? getAltura(no->menor) - getAltura(no->maior) : 0;
    }

    // ---- Rotações ----
    AVLtree* rotacaoDireita(AVLtree* y) {
        AVLtree* x = y->menor;
        AVLtree* T2 = x->maior;

        x->maior = y;
        y->menor = T2;

        if (T2) T2->pai = y;

        x->pai = y->pai;
        y->pai = x;

        updateAltura(y);
        updateAltura(x);

        return x;
    }

    AVLtree* rotacaoEsquerda(AVLtree* x) {
        AVLtree* y = x->maior;
        AVLtree* T2 = y->menor;

        y->menor = x;
        x->maior = T2;

        if (T2) T2->pai = x;

        y->pai = x->pai;
        x->pai = y;

        updateAltura(x);
        updateAltura(y);

        return y;
    }

    // ---- Rebalanceamento ----
    AVLtree* rebalancear(AVLtree* no) {
        updateAltura(no);
        int fb = fatorB(no);

        // Casos de rotação:
        if (fb > 1 && fatorB(no->menor) >= 0) {
            // Left Left
            return rotacaoDireita(no);
        }
        if (fb > 1 && fatorB(no->menor) < 0) {
            // Left Right
            no->menor = rotacaoEsquerda(no->menor);
            return rotacaoDireita(no);
        }
        if (fb < -1 && fatorB(no->maior) <= 0) {
            // Right Right
            return rotacaoEsquerda(no);
        }
        if (fb < -1 && fatorB(no->maior) > 0) {
            // Right Left
            no->maior = rotacaoDireita(no->maior);
            return rotacaoEsquerda(no);
        }
        return no;
    }

    // ---- Inserção recursiva ----
    AVLtree* insertRec(AVLtree* no, int value) {
        if (!no) return createNo(value);

        if (value < no->value) {
            no->menor = insertRec(no->menor, value);
            no->menor->pai = no;
        } else if (value > no->value) {
            no->maior = insertRec(no->maior, value);
            no->maior->pai = no;
        } else {
            return no; // valor duplicado
        }

        return rebalancear(no);
    }

    // ---- Busca ----
    AVLtree* seachTree(AVLtree* no, int value) {
        while (no != nullptr && value != no->value) {
            if (value < no->value) no = no->menor;
            else no = no->maior;
        }
        return no;
    }

    // ---- Remoção ----
    AVLtree* minino(AVLtree* no) {
        while (no->menor != nullptr)
            no = no->menor;
        return no;
    }

    AVLtree* eliminarRec(AVLtree* no, int value) {
        if (!no) return nullptr;

        if (value < no->value)
            no->menor = eliminarRec(no->menor, value);
        else if (value > no->value)
            no->maior = eliminarRec(no->maior, value);
        else {
            // Nó encontrado
            if (!no->menor || !no->maior) {
                AVLtree* temp = no->menor ? no->menor : no->maior;
                if (!temp) {
                    delete no;
                    return nullptr;
                } else {
                    temp->pai = no->pai;
                    delete no;
                    return temp;
                }
            } else {
                AVLtree* sucessor = minino(no->maior);
                no->value = sucessor->value;
                no->maior = eliminarRec(no->maior, sucessor->value);
            }
        }

        return rebalancear(no);
    }

public:
    void insertNo(int value) {
        raiz = insertRec(raiz, value);
        raiz->pai = nullptr;
    }

    void eliminar(int value) {
        raiz = eliminarRec(raiz, value);
        if (raiz) raiz->pai = nullptr;
    }

    AVLtree* getRoot() { return raiz; }

    // ---- Impressões ----
    void emOrdem(AVLtree* no) {
        if (no != nullptr) {
            emOrdem(no->menor);
            cout << no->value << ", ";
            emOrdem(no->maior);
        }
    }

    void show(AVLtree* node, int nivel = 0) {
        if (node == nullptr) return;
        show(node->maior, nivel + 1);
        cout << string(nivel * 4, ' ') << node->value << '\n';
        show(node->menor, nivel + 1);
    }
};


int main() {
    AVLtree arvore;
    int cmd, value = 0;
    do {
        cout << "(1) Inserir valor" nl;
        cout << "(2) Mostrar em ordem" nl;
        cout << "(3) Mostrar árvore" nl;
        cout << "(4) Remover valor" nl;
        cout << "Digite comando (-1 para sair): ";
        cin >> cmd;
        
        switch (cmd) {
            case 1:
                while(value != -1){
                    cout << "Valor: ";
                    cin >> value;
                    if(value == -1) break;
                    arvore.insertNo(value);
                }
                value = 0;
                break;
            case 2:
                cout << "Em ordem: ";
                arvore.emOrdem(arvore.getRoot());
                cout nl;
                break;
            case 3:
                cout << "Estrutura da árvore:" nl;
                arvore.show(arvore.getRoot());
                break;
            case 4:
                cout << "Remover valor: ";
                cin >> value;
                arvore.eliminar(value);
                break;
        }
    } while (cmd != -1);
}
