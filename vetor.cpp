#include <bits/stdc++.h> 
#define nl << '\n' 
#define ll long long 
using namespace std; 

class Vetor{
public:
    int size = 0;
    int capacidade = 0;
    int* p = nullptr;

    Vetor(int capacidadeP){
        capacidade = capacidadeP;
        size = capacidadeP;
        p = (int*) malloc(sizeof(int) * capacidadeP);
    }

    void reacolar(int t){
        int* aux = this->p;
        this->p = (int*) realloc(aux, (sizeof(int)*t));  
        if(this->p == nullptr) cout << "Erro de alocação" nl;
    }

    void pushBack(int value){
        if(this->size >= this->capacidade) this->reacolar(this->capacidade+this->capacidade);
        this->p[size] = value;
        size++;
    }

};


int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0); 
    
    int n; cin >> n;
    Vetor b(n);

    for(int i = 0; i < n; i++){
        cin >> b.p[i];
    }

    for(int i = 0; i < n; i++){
        cout << b.p[i] << " ";
    }

    cout nl;
    
    return 0; 
}