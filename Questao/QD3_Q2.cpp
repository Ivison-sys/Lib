#include <bits/stdc++.h>
#define nl << '\n'
#define ll long long
using namespace std;
using vi = vector<int>;

class Grafo {
public:
    vi vertices;
    vector<vi> adjacentes;

    Grafo(vi v, vector<vi> adj) {
        this->vertices = v;
        this->adjacentes = adj;
    }

   
    void adicionar_aresta(int u, int v) {
        adjacentes[u].resize(adjacentes[u].size() + 1);
        adjacentes[u][adjacentes[u].size() - 1] = v;
    }

   
    vi getAdjacentes(int v) {
        return adjacentes[v];
    }

    
    bool busca_largura(int start, int end) {
        int n = vertices.size();
        vector<bool> marcado(n, false);
        vi antecessor(n, -1);

        int fila[1000]; 
        int inicio = 0;
        int fim = 0;


        fila[fim] = start; 
        fim++;
        marcado[start] = true;

        while (inicio < fim) { 
            int v = fila[inicio];  
            inicio++;

            if (v == end) {
                int caminho[1000]; 
                int caminhoSize = 0;

                for (int i = v; i != -1; i = antecessor[i]) {
                    caminho[caminhoSize] = i;
                    caminhoSize++;
                }

     
                cout << "A=" << start << ",B=" << end << ": " nl;
                for (int i = caminhoSize - 1; i >= 0; i--) {  
                    cout << caminho[i];
                    if(i > 0) cout << ",";
                    else cout nl;
                }
                cout  nl;
                return true;
            }

            for (int u : getAdjacentes(v)) {
                if (!marcado[u]) {
                    marcado[u] = true;
                    antecessor[u] = v;
                    fila[fim] = u;  
                    fim++;
                }
            }
        }

        cout << "Não existe caminho entre " << start << " e " << end  nl;
        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; // Quantidade de vértices
    int Q; // Quantidade de arestas

    cin >> N;
    cin >> Q;

    vi lista_vertices(N);
    for (int i = 0; i < N; ++i) {
        lista_vertices[i] = i;
    }

    vector<vi> lista_adj(N);
    Grafo g(lista_vertices, lista_adj);

    for (int i = 0; i < Q; i++) {
        int u, v;
        cin >> u >> v;
        g.adicionar_aresta(u, v);
    }

    int inicio, fim;
    cin >> inicio;
    cin >> fim;

    g.busca_largura(inicio, fim);

    return 0;
}
