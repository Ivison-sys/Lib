#include <bits/stdc++.h> 
#define nl << '\n' 
#define ll long long 
using namespace std; 
using vi = vector<int>;

string resp = "";

class Grafo {
public:
    vi vertices;
    vector<vector<int>> adjacentes;

    Grafo(vi vertices, vector<vector<int>> adjacentes){
        int c = 0;
        this->adjacentes = vector<vector<int>>(vertices.size(), vector<int>(vertices.size()));
        for(int i = 0; i < adjacentes.size(); i++){
            vi aux = adjacentes[i];
            for(int w = 0; w < aux.size(); w++){
                if(aux[w] != -1){
                    this->adjacentes[i][c] = w;
                    c++;
                }
            }
            c = 0;
        }
        this->vertices = vertices;
    }

    vi getAdjacentes(int v){
        return this->adjacentes[v];
    }
};

void dfs(Grafo &g, int v,vi &antecessor, vector<bool> &marcado){
    marcado[v] = true;
    vi adjacentes = g.getAdjacentes(v);
    for(auto &x: adjacentes){
        if(!marcado[x]){
            antecessor[x] = v;
            dfs(g, x, antecessor, marcado);
        }
    }
    
    resp = to_string(v) + " " + resp; 
}

void buscaProfundidade(Grafo &g){
    
    vector<bool> marcado(g.vertices.size(), false);
    vi antecessor(g.vertices.size(), -1);
    vi resp(g.vertices.size());

    for(int i = 0; i < g.vertices.size(); i++){
        if(!marcado[i]) dfs(g, i, antecessor, marcado);
    }
}

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0); 
    
    int n; cin >> n;
    vi vertices(n); for(int i = 0; i < n; i++) vertices[i] = i;
    vector<vector<int>> adjacentes(n, vector<int>(n, -1));
    int a; cin >> a;
    int r, l;
    while(a--){
        cin >> l >> r;
        adjacentes[l][r] = 1;
    }

    Grafo g(vertices, adjacentes);

    buscaProfundidade(g);
    cout << "Resposta: ";
    for(int i = 0; i < resp.size(); i++){
        if(resp[i] == ' ' && i != resp.size() -1 ) cout << ", ";
        else cout << resp[i];
    }
    cout nl;
    
    return 0; 
}