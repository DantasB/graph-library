#include <iostream> //Biblioteca para o uso do cout
#include <stdio.h> //Biblioteca para usar o get char
#include <ctime> //Biblioteca para medir o tempo de execução
#include <fstream> //Biblioteca para escrita e leitura de arquivos txt
#include <stack> //Biblioteca com implementação de pilha
#include <queue> //Biblioteca com implementação de fila
#include <vector> //Biblioteca com implementação de array dinâmico
#include <algorithm> //Biblioteca com implementação do sort
#include <string.h> //Biblioteca com implementação do memset
#include <utility>  //Biblioteca com implementação do pair
#include <set> //Biblioteca com implementação do set
#include <deque> //Biblioteca com implementação de deque

#define INF 0x3f3f3f3f //Define um valor infinito
using namespace std;

//Definições globais
vector<int> match;
vector<int> dist;
vector<double> d;

//Estruturas criadas
struct grafoVector{
  int numVertices;
  vector<int>* adjVector;
  bool bipartido;
  vector<int> bipartite_1;
  vector<int> bipartite_2;
};

struct grafoMatriz{
  int numVertices;
  bool **adjMatriz;
  bool bipartido;
  vector<int> bipartite_1;
  vector<int> bipartite_2;
};

struct grafoMatrizComPeso{
  int numVertices;
  double **adjMatriz;
  bool directed;
};

struct grafoVectorComPeso{
  int numVertices;
  vector< pair<int, double> >* adjVector;
  bool directed;
};

//Funções pré definidas
int componentesConexasMatriz(grafoMatriz grafo, bool salve);
int componentesConexasVector(grafoVector grafo, bool salve);

//Funções extras
bool comparaCC(vector<int> primeiro, vector<int> segundo){
   return primeiro.size() > segundo.size();
}

bool comparaSegundo(pair<int,int> a, pair<int,int> b){
  return (a.second < b.second);
}

vector<int> bfsCCMatriz(grafoMatriz grafo, int start, vector<int>&descoberto, int constante){
  //Cria um vector de componentes e adiciona o vertice que está iniciando a bfs
  vector<int> componentesMatriz;
  componentesMatriz.push_back(start);
  //Cria uma fila
  queue<int> fila;
  //Seta o start como descoberto
  descoberto[start] = constante;
  //Adiciona o start a fila
  fila.push(start);
  //Enquanto a fila não estiver vazia
  while (!fila.empty()) {
    //Pega o primeiro elemento da fila
    int vertex = fila.front();
    fila.pop();
    //Faz um iterator dos vizinhos da fila.front()
    for (int i=1;i<(int)grafo.numVertices+1;i++){
      //Vizinho é o *it
      int vizinho = i;
      //Se esse vizinho não tiver sido descoberto
      if (!descoberto[vizinho] && grafo.adjMatriz[vertex][vizinho]) {
        //Vizinho pertence a mesma componente conexa do start
        descoberto[vizinho] = constante;
        //Adiciona o vizinho ao final do vector de componentes
        componentesMatriz.push_back(vizinho);
        //Adiciona o vizinho a fila
        fila.push(vizinho);
      }
    }
  }
  //Retorna o componentes Matriz para adicionar a lista de componentes conexas
  return componentesMatriz;
}

vector<int> bfsCCVector(grafoVector grafo, int start, vector<int>&descoberto, int constante){
  //Cria um vector de componentes e adiciona o vertice que está iniciando a bfs
  vector<int> componentesVector;
  componentesVector.push_back(start);
  //Cria uma fila
  queue<int> fila;
  //Seta o start como descoberto
  descoberto[start] = constante;
  //Adiciona o start a fila
  fila.push(start);
  //Enquanto a fila não estiver vazia
  while (!fila.empty()) {
    //Pega o primeiro elemento da fila
    int vertex = fila.front();
    fila.pop();
    //Faz um iterator dos vizinhos da fila.front()
    for (int i=0;i<(int)grafo.adjVector[vertex].size();i++){
      //Vizinho é o *it
      int vizinho = i;
      //Se esse vizinho não tiver sido descoberto
      if (!descoberto[grafo.adjVector[vertex][vizinho]]) {
        //Vizinho pertence a mesma componente conexa do start
        descoberto[grafo.adjVector[vertex][vizinho]] = constante;
        //Adiciona o vizinho ao final do vector de componentes
        componentesVector.push_back(grafo.adjVector[vertex][vizinho]);
        //Adiciona o vizinho a fila
        fila.push(grafo.adjVector[vertex][vizinho]);
      }
    }
  }
  //Retorna o componentes Vector para adicionar a lista de componentes conexas
  return componentesVector;
}

bool bipartidoMatriz(grafoMatriz grafo){
  if(componentesConexasMatriz(grafo,false)>1){
    return 0;
  }
  //Cria um vetor de visitados
  int *visited;
  visited = new int[grafo.numVertices+1];
  //Define o vetor visitado = 0
  for(int i=0;i<=grafo.numVertices+1;i++){
    visited[i] = 0;
  }
  //Cria uma fila
  queue<int> fila;
  int start = 1;
  //Adiciona o start a fila
  fila.push(start);
  //Define o visited do start como 1
  visited[start]=1;
  //Enquanto a fila não estiver vazia
  while(!fila.empty()){
    //Tira o primeiro elemento da fila
    int v = fila.front();
    //cout<<v<<endl;
    fila.pop();
    //Para todos os vizinhos da fila
    for(int i=1;i<(int)grafo.numVertices+1;i++){
      if(grafo.adjMatriz[v][i]){
        if(visited[i]==0){
          if (visited[v] == 1){
            visited[i] = 2;
          }
          else{
            if(visited[v] ==2){
              visited[i] = 1;
            }
          }
          fila.push(i);
        }
        else{
          if(visited[i] == visited[v]){
            return false;
          }
        }
      }
    }
  }
  for(int i=0;i<grafo.numVertices+1;i++){
    if(visited[i]==1){
      grafo.bipartite_1.push_back(i);
    }
    if(visited[i]==2){
      grafo.bipartite_2.push_back(i);
    }
  }
  return true;
}

bool bipartidoVector(grafoVector grafo){
  if(componentesConexasVector(grafo,false)>1){
    return 0;
  }
  //Cria um vetor de visitados
  int *visited;
  visited = new int[grafo.numVertices+1];
  //Define o vetor visitado = 0
  for(int i=0;i<=grafo.numVertices+1;i++){
    visited[i] = 0;
  }
  //Cria uma fila
  queue<int> fila;
  int start = 1;
  //Adiciona o start a fila
  fila.push(start);
  //Define o visited do start como 1
  visited[start]=1;
  //Enquanto a fila não estiver vazia
  while(!fila.empty()){
    //Tira o primeiro elemento da fila
    int v = fila.front();
    //cout<<v<<endl;
    fila.pop();
    //Para todos os vizinhos da fila
    for(int i=0;i<(int)grafo.adjVector[v].size();i++){
      if(visited[grafo.adjVector[v][i]]==0){
        if (visited[v] == 1){
          visited[grafo.adjVector[v][i]] = 2;
        }
        else{
          if(visited[v] ==2){
            visited[grafo.adjVector[v][i]] = 1;
          }
        }
        fila.push(grafo.adjVector[v][i]);
      }
      else{
        if(visited[grafo.adjVector[v][i]] == visited[v]){
          return false;
        }
      }
    }
  }
  for(int i=0;i<grafo.numVertices+1;i++){
    if(visited[i]==1){
      grafo.bipartite_1.push_back(i);
    }
    if(visited[i]==2){
      grafo.bipartite_2.push_back(i);
    }
  }
  return true;
}

bool bfsHopVector(grafoVector grafo){
  deque <int> fila;
  int k = INF;
  for(int u: grafo.bipartite_1){
    if(match[u] == u){
      fila.push_back(u);
      dist[u] =0;
    }
    else{
      dist[u] = INF;
    }
  }
  while(!fila.empty()){
    int n = fila.front();
    fila.pop_front();
    if(dist[n] < k){
      for(int i=0;i<(int)grafo.adjVector[n].size();i++){
        int v = grafo.adjVector[n][i];
        if(match[v]== v && k==INF){
          k = dist[n] + 1;
        }
        else if (dist[match[v]] == INF){
          dist[match[v]] = dist[n] +1;
          fila.push_back(match[v]);
        }
      }
    }
  }
  return (k!= INF);
}

bool dfsHopVector(grafoVector grafo, int n){

  for(int i=0;i<(int)grafo.adjVector[n].size();i++){
    int v = grafo.adjVector[n][i];
    if(match[v] == v || (dist[match[v]] == dist[n] +1 && dfsHopVector(grafo,match[v]))){
        match[v] = n;
        match[n] = v;
        return true;
    }
  }
  return false;
}

bool bfsHopMatriz(grafoMatriz grafo){
  deque <int> fila;
  int k = INF;
  for(int u: grafo.bipartite_1){
    if(match[u] == u){
      fila.push_back(u);
      dist[u] =0;
    }
    else{
      dist[u] = INF;
    }
  }
  while(!fila.empty()){
    int n = fila.front();
    fila.pop_front();
    if(dist[n] < k){
      for(int i=1;i<(int)grafo.numVertices+1;i++){
        if(grafo.adjMatriz[n][i]){
          int v = i;
          if(match[v]== v && k==INF){
            k = dist[n] + 1;
          }
          else if (dist[match[v]] == INF){
            dist[match[v]] = dist[n] +1;
            fila.push_back(match[v]);
          }
        }
      }
    }
  }
  return (k!= INF);
}

bool dfsHopMatriz(grafoMatriz grafo, int n){
  for(int i=1;i<grafo.numVertices+1;i++){
    if(grafo.adjMatriz[n][i]){
      int v = i;
      if(match[v] == v || (dist[match[v]] == dist[n] +1 && dfsHopMatriz(grafo,match[v]))){
        match[v] = n;
        match[n] = v;
        return true;
      }
    }
  }
  return false;
}


//Funções de construção das estruturas de dados
grafoVector constroiVector(string arquivo){
  grafoVector grafo;
  int numVertices;
  int *grau;
  vector <int> *adjVector;
  vector<int> bipartite_1;
  vector<int> bipartite_2;
  int numArestas=0;
  int vertex1, vertex2;
  bool bipartido;
  ifstream graphTexto(arquivo.c_str());
  //Esse é o próprio número de vértices
  graphTexto >> numVertices;
  grafo.numVertices = numVertices;
  //Cria o vetor de adjacência
  adjVector = new vector<int>[numVertices+1];

  //Inicializa o vetor grau
  grau = new int[numVertices+1]();

  //Preenche o vetor de adjacência
  while(graphTexto>>vertex1>>vertex2){
    adjVector[vertex1].push_back(vertex2);
    adjVector[vertex2].push_back(vertex1);
    //Calcula o grau de cada vértice
    grau[vertex1]++;
    grau[vertex2]++;
  }

  //Ordena o vetor grau em O(nlog(n))
  sort(grau, grau+numVertices+1);

  int soma=0;
  for(int i=1; i<(int)numVertices+1;i++){
    soma+= grau[i];
  }
  //Calcula o número de arestas
  numArestas=soma/2;

  ofstream graphFile;
  graphFile.open("graphFile.txt");
  graphFile<< "Esse é o número de vértices: "<<numVertices<<endl;
  graphFile<< "Esse é o número de arestas: "<<numArestas<<endl;
  //Após ordenado, o grau máximo é o ultimo elemento da lista
  graphFile<< "Esse é o grau máximo: "<<grau[numVertices]<<endl;
  //O grau mínimo será o primeiro elemento +1 (o primeiro será sempre 0)
  graphFile<< "Esse é o grau mínimo: "<<grau[1]<<endl;
  //O grau médio será o somatorio de cada grau dividido pelo numero de graus
  graphFile<< "Esse é o grau médio: "<<soma/(numVertices-1)<<endl;
  int mediana =0;
  if (numVertices%2==0){

    mediana = (grau[((int)numVertices/2)]+ grau[((int)numVertices/2)+1])/2;
  }
  else{
    mediana = grau[((int)numVertices/2)+1];
  }
  graphFile<<"Essa é a mediana do grau: "<<mediana<<endl;
  graphFile.close();
  grafo.adjVector = adjVector;
  bipartido = bipartidoVector(grafo);

  if(bipartido){
    int *visited;
    visited = new int[grafo.numVertices+1];
    //Define o vetor visitado = 0
    for(int i=0;i<=grafo.numVertices+1;i++){
      visited[i] = 0;
    }
    //Cria uma fila
    queue<int> fila;
    int start = 1;
    //Adiciona o start a fila
    fila.push(start);
    //Define o visited do start como 1
    visited[start]=1;
    //Enquanto a fila não estiver vazia
    while(!fila.empty()){
      //Tira o primeiro elemento da fila
      int v = fila.front();
      //cout<<v<<endl;
      fila.pop();
      //Para todos os vizinhos da fila
      for(int i=0;i<(int)grafo.adjVector[v].size();i++){
        if(visited[grafo.adjVector[v][i]]==0){
          if (visited[v] == 1){
            visited[grafo.adjVector[v][i]] = 2;
          }
          else{
            if(visited[v] ==2){
              visited[grafo.adjVector[v][i]] = 1;
            }
          }
          fila.push(grafo.adjVector[v][i]);
        }
      }
    }
    for(int i=0;i<grafo.numVertices+1;i++){
      if(visited[i]==1){
        bipartite_1.push_back(i);
      }
      if(visited[i]==2){
        bipartite_2.push_back(i);
      }
    }
  }

  grafo.bipartido = bipartido;
  grafo.bipartite_1 = bipartite_1;
  grafo.bipartite_2 = bipartite_2;

  for(int i=0;i<=grafo.numVertices;i++){
    match.push_back(-1);
    dist.push_back(-1);
  }

  return grafo;
}

grafoMatriz constroiMatriz(string arquivo){
  grafoMatriz grafo;
  int numVertices;
  bool **adjMatriz;
  int *grau;
  vector<int>bipartite_1;
  vector<int>bipartite_2;
  int numArestas=0;
  int vertex1, vertex2;
  bool bipartido;
  ifstream graphTexto(arquivo.c_str());
  //Esse é o próprio número de vértices
  graphTexto >> numVertices;
  grafo.numVertices = numVertices;
  //Cria a Matriz de Adjacência
  adjMatriz = new bool*[numVertices+1];
  for (int i = 0; i < numVertices+1; i++){
        adjMatriz[i] = new bool[numVertices+1];
  }

  //Zera a Matriz de Adjacência
  for(int i=0;i< numVertices+1; i++){
    memset(adjMatriz[i],false, numVertices+1);
  }

  //Cria um vetor de graus
  grau = new int[numVertices+1]();
  //Preenche a Matriz de Adjacência
  while(graphTexto>>vertex1>>vertex2){
    //Insere o par (vértice1, vértice2) na matriz
    adjMatriz[vertex1][vertex2]=true;
    adjMatriz[vertex2][vertex1]=true;
    //Calcula o grau de cada vértice
    grau[vertex1]++;
    grau[vertex2]++;
  }

  //Ordena em O(n.log(n)) o vetor de graus.
  sort(grau, grau+numVertices+1);

  int soma=0;
  for(int i=1; i<(int)numVertices+1;i++){
    soma+= grau[i];
  }

  //Calcula o número de arestas
  numArestas = soma/2;

  ofstream graphFile;
  graphFile.open("graphFile.txt");
  graphFile<< "Esse é o número de vértices: "<<numVertices<<endl;
  graphFile<< "Esse é o número de arestas: "<<numArestas<<endl;
  //Após ordenado, o grau máximo é o ultimo elemento da lista
  graphFile<< "Esse é o grau máximo: "<<grau[numVertices]<<endl;
  //O grau mínimo será o primeiro elemento +1 (o primeiro será sempre 0)
  graphFile<< "Esse é o grau mínimo: "<<grau[1]<<endl;
  //O grau médio será o somatorio de cada grau dividido pelo numero de graus
  graphFile<< "Esse é o grau médio: "<<soma/(numVertices-1)<<endl;
  int mediana =0;
  if (numVertices%2==0){

    mediana = (grau[((int)numVertices/2)]+ grau[((int)numVertices/2)+1])/2;
  }
  else{
    mediana = grau[((int)numVertices/2)+1];
  }
  graphFile<<"Essa é a mediana do grau: "<<mediana<<endl;

  graphFile.close();

  grafo.adjMatriz = adjMatriz;

  bipartido = bipartidoMatriz(grafo);
  grafo.bipartido = bipartido;

  if(bipartido){
    //Cria um vetor de visitados
    int *visited;
    visited = new int[grafo.numVertices+1];
    //Define o vetor visitado = 0
    for(int i=0;i<=grafo.numVertices+1;i++){
      visited[i] = 0;
    }
    //Cria uma fila
    queue<int> fila;
    int start = 1;
    //Adiciona o start a fila
    fila.push(start);
    //Define o visited do start como 1
    visited[start]=1;
    //Enquanto a fila não estiver vazia
    while(!fila.empty()){
      //Tira o primeiro elemento da fila
      int v = fila.front();
      //cout<<v<<endl;
      fila.pop();
      //Para todos os vizinhos da fila
      for(int i=1;i<(int)grafo.numVertices+1;i++){
        if(grafo.adjMatriz[v][i]){
          if(visited[i]==0){
            if (visited[v] == 1){
              visited[i] = 2;
            }
            else{
              if(visited[v] ==2){
                visited[i] = 1;
              }
            }
            fila.push(i);
          }
        }
      }
    }

    for(int i=0;i<grafo.numVertices+1;i++){
      if(visited[i]==1){
        bipartite_1.push_back(i);
      }
      if(visited[i]==2){
        bipartite_2.push_back(i);
      }
    }
  }

  grafo.bipartite_1 = bipartite_1;
  grafo.bipartite_2 = bipartite_2;

  for(int i=0;i<=grafo.numVertices;i++){
    match.push_back(-1);
    dist.push_back(-1);
  }

  return grafo;
}

grafoMatrizComPeso constroiMatrizComPeso(string arquivo, bool directed=false){
  grafoMatrizComPeso grafo;
  int numVertices;
  double **adjMatriz;
  int *grau;
  int numArestas=0;
  int vertex1, vertex2;
  double peso;
  ifstream graphTexto(arquivo.c_str());
  //Esse é o próprio número de vértices
  graphTexto >> numVertices;
  grafo.numVertices = numVertices;
  //Cria a Matriz de Adjacência
  adjMatriz = new double*[numVertices+1];
  for (int i = 0; i < numVertices+1; i++){
        adjMatriz[i] = new double[numVertices+1];
  }
  for(int i=0;i<=numVertices;i++){
    for(int j=0;j<=numVertices;j++){
      adjMatriz[i][j]=INF;
    }
  }
  //Cria um vetor de graus
  grau = new int[numVertices+1]();
  //Preenche a Matriz de Adjacência
  while(graphTexto>>vertex1>>vertex2>>peso){
    //Insere o par (vértice1, vértice2) na matriz
    adjMatriz[vertex1][vertex2]=peso;
    grau[vertex1]++;
    if(!directed){
      adjMatriz[vertex2][vertex1]=peso;
      grau[vertex2]++;
    }
  }

  //Ordena em O(n.log(n)) o vetor de graus.
  sort(grau, grau+numVertices+1);

  int soma=0;
  for(int i=1; i<(int)numVertices+1;i++){
    soma+= grau[i];
  }

  //Calcula o número de arestas
  numArestas = soma/2;

  ofstream graphFile;
  graphFile.open("graphFile.txt");
  graphFile<< "Esse é o número de vértices: "<<numVertices<<endl;
  graphFile<< "Esse é o número de arestas: "<<numArestas<<endl;
  //Após ordenado, o grau máximo é o ultimo elemento da lista
  graphFile<< "Esse é o grau máximo: "<<grau[numVertices]<<endl;
  //O grau mínimo será o primeiro elemento +1 (o primeiro será sempre 0)
  graphFile<< "Esse é o grau mínimo: "<<grau[1]<<endl;
  //O grau médio será o somatorio de cada grau dividido pelo numero de graus
  graphFile<< "Esse é o grau médio: "<<soma/(numVertices-1)<<endl;
  int mediana =0;
  if (numVertices%2==0){

    mediana = (grau[((int)numVertices/2)]+ grau[((int)numVertices/2)+1])/2;
  }
  else{
    mediana = grau[((int)numVertices/2)+1];
  }
  graphFile<<"Essa é a mediana do grau: "<<mediana<<endl;

  graphFile.close();

  grafo.adjMatriz = adjMatriz;

  grafo.directed = directed;

  return grafo;
}

grafoVectorComPeso constroiVectorComPeso(string arquivo, bool directed=false){
  grafoVectorComPeso grafo;
  int numVertices;
  int *grau;
  vector < pair<int, double> > *adjVector;
  int numArestas=0;
  int vertex1, vertex2;
  double peso;
  ifstream graphTexto(arquivo.c_str());
  //Esse é o próprio número de vértices
  graphTexto >> numVertices;
  grafo.numVertices = numVertices;
  //Cria o vetor de adjacência
  adjVector = new vector< pair<int, double> >[numVertices+1];

  //Inicializa o vetor grau
  grau = new int[numVertices+1]();

  //Preenche o vetor de adjacência
  while(graphTexto>>vertex1>>vertex2>>peso){
    adjVector[vertex1].push_back(make_pair(vertex2, peso));
    grau[vertex1]++;
    if(!directed){
      adjVector[vertex2].push_back(make_pair(vertex1, peso));
      grau[vertex2]++;
    }
  }

  //Ordena o vetor grau em O(nlog(n))
  sort(grau, grau+numVertices+1);

  //Ordena os vértices por peso
  for(int i=0;i<=numVertices;i++){
    sort(adjVector[i].begin(),adjVector[i].end(),comparaSegundo);
  }

  int soma=0;
  for(int i=1; i<(int)numVertices+1;i++){
    soma+= grau[i];
  }

  //Calcula o número de arestas
  numArestas=soma/2;

  ofstream graphFile;
  graphFile.open("graphFile.txt");
  graphFile<< "Esse é o número de vértices: "<<numVertices<<endl;
  graphFile<< "Esse é o número de arestas: "<<numArestas<<endl;
  //Após ordenado, o grau máximo é o ultimo elemento da lista
  graphFile<< "Esse é o grau máximo: "<<grau[numVertices]<<endl;
  //O grau mínimo será o primeiro elemento +1 (o primeiro será sempre 0)
  graphFile<< "Esse é o grau mínimo: "<<grau[1]<<endl;
  //O grau médio será o somatorio de cada grau dividido pelo numero de graus
  graphFile<< "Esse é o grau médio: "<<soma/(numVertices-1)<<endl;
  int mediana =0;
  if (numVertices%2==0){

    mediana = (grau[((int)numVertices/2)]+ grau[((int)numVertices/2)+1])/2;
  }
  else{
    mediana = grau[((int)numVertices/2)+1];
  }
  graphFile<<"Essa é a mediana do grau: "<<mediana<<endl;
  graphFile.close();
  grafo.adjVector = adjVector;
  grafo.directed = directed;
  return grafo;
}

//Funções para Matriz de Adjacência
void bfsMatriz(int start, grafoMatriz grafo, bool salve=false, int objetivo = -1){
  //Cria um vetor de niveis
  int *nivel;
  nivel = new int[grafo.numVertices+1];
  //Cria um vetor de pais
  int *pai;
  pai = new int[grafo.numVertices+1];
  //Define todos os níveis como -1 e pais como 0;
  for(int i=0;i<(int)grafo.numVertices+1;i++){
    nivel[i]=-1;
  }
  memset(pai, 0, grafo.numVertices+1);
  //Cria uma fila
  queue<int> fila;
  //Adiciona o start a fila
  fila.push(start);
  //Define o Nivel do start como 0
  nivel[start]=0;
  pai[start]=-1;
  //Enquanto a fila não estiver vazia
  while(!fila.empty()){
    //Tira o primeiro elemento da fila
    int v = fila.front();
    fila.pop();
    //Para todos os vizinhos da fila
    for(int i=1;i<(int)grafo.numVertices+1;i++){
      //Se o vizinho não for visitado
      if(grafo.adjMatriz[v][i] && nivel[i]==-1){
        //visita o vizinho e adiciona ele na fila
        nivel[i] = nivel[v]+1;
        pai[i] = v;
        fila.push(i);
      }
    }
  }
  if(salve){
    ofstream bfsFile;
    bfsFile.open("bfsFile.txt");
    for(int i=1;i<(int)grafo.numVertices+1;i++){
      bfsFile<< "Vértice: "<< i <<", Nível: "<< nivel[i]<<", Pai: "<< pai[i]<<endl;
    }
    bfsFile.close();
    //Cria um arquivo mstFile
    //Cria um inteiro x
    int x=0;
    //x será seu novo vértice objetivo
    x = objetivo;
    if(x!=-1){
      ofstream shortestPath;
      shortestPath.open("shortestPath.txt");
      //Percorre x até chegar no vértice inicial
      if(x!=start){
        //Imprime o caminho de x até start
        shortestPath<<"Vértice: "<< x<<", Caminho até "<<start<<": ";
        //Se tiver um caminho até x
        if (nivel[x] !=-1){
          shortestPath<<"[";
          while(x != start){
            //Cálculo a distância de x até start
            shortestPath<<x<<", ";
            //x agora é quem descobriu x
            x = pai[x];
          }
          shortestPath<<x<<"]";
        }
        //Se não tiver um caminho de x até start
        else{
          //Imprime INFINITO
          shortestPath<<"[], "<<"Distância entre eles: "<<"INFINITO"<<endl;
        }
      }
    }
  }
}

void dfsMatriz(int start, grafoMatriz grafo, bool salve=false){
  //Cria um vetor para inverter os itens a adicionar na pilha
  vector<int>addPilha;
  //Cria um vetor de niveis
  int *nivel;
  nivel = new int[grafo.numVertices+1];
  //Cria um vetor de pais
  int *pai;
  pai = new int[grafo.numVertices+1];
  //Cria um vetor de visitados
  bool *visited;
  visited = new bool[grafo.numVertices+1];
  //Define todos os níveis e pais como -1 e visitados como 0
  for(int i=0;i<(int)grafo.numVertices+1;i++){
    nivel[i]=-1;
  }
  //memset(nivel,-1, grafo.numVertices+1);
  memset(pai,0, grafo.numVertices+1);
  memset(visited,0,grafo.numVertices+1);
  //Cria uma pilha
  stack <int> pilha;
  //Adiciona start a pilha;
  pilha.push(start);
  //Define o Nivel do start como 0 e pai do start como -1
  nivel[start]=0;
  pai[start]=-1;
  //Enquanto a pilha não estiver vazia
  while(!pilha.empty()){
    //Retira o elemento do topo da pilha
    int u= pilha.top();
    pilha.pop();
    //Verifica se o topo da pilha já foi visitado
    if (!visited[u]){
      //Visita o topo da pilha
      visited[u] = true;
      //Para todas as vizinhanças do topo da pilha
      for(int v=1; v<(int)grafo.numVertices+1; v++){
        if(grafo.adjMatriz[u][v]){
          //Se o vértice ainda não tem um pai
          if (!visited[v]){
            pai[v] = u;
            nivel[v] = nivel[u]+1;
          }
          //Adiciona a vizinhança ao vector addPilha
          addPilha.push_back(v);
        }
      }
      //Inverte os itens a serem adicionados a pilha
      for (vector<int>::const_iterator i = (addPilha.end() -1); i >= addPilha.begin(); --i){
        pilha.push(*i);
      }
      //Zera o vector addPilha
      addPilha.clear();
    }
  }
  if(salve){
    ofstream dfsFile;
    dfsFile.open("dfsFile.txt");
    for(int i=1;i<(int)grafo.numVertices+1;i++){
      dfsFile<< "Vértice: "<< i <<", Nível: "<< nivel[i]<<", Pai: "<< pai[i]<<endl;
    }
    dfsFile.close();
  }
}

int distanciaMatriz(int v1, int v2, grafoMatriz grafo){
  //Cria um vetor distâncias
  int *path;
  path = new int[grafo.numVertices+1];
  //Define todas as distâncias como -1;
  for(int i=0;i<(int)grafo.numVertices;i++){
    path[i]=-1;
  }
  queue<int> fila;
  //Adiciona o start a fila
  fila.push(v1);
  //Define a distância até o start em 0
  path[v1]=0;
  //Enquanto a fila não estiver vazia
  while(!fila.empty()){
    //Tira o primeiro elemento da fila
    int v = fila.front();
    fila.pop();
    //Para todos os vizinhos da fila
    for(int i=1;i<(int)grafo.numVertices+1;i++){
      //Se o vizinho tiver uma distância não definida
      if(grafo.adjMatriz[v][i] != 0 && path[i]==-1){
        //Altera a distância e adiciona ele na fila
        if (i == v2){
          return path[v] + 1;
        }
        path[i] = path[v]+1;
        fila.push(i);
      }
    }
  }
  return path[v2];
}

int diametroMatriz(grafoMatriz grafo){
    //Cria uma constante maior nível
    int maiornivel=0;
    //Cria um vetor de niveis
    int *nivel;
    nivel = new int[grafo.numVertices+1];
    //Define todos os níveis -1
    for(int i=0;i<(int)grafo.numVertices+1;i++){
      nivel[i]=-1;
    }
    //Cria uma fila
    queue <int> fila;
    for(int start=1; start<(int)grafo.numVertices+1;start++){
      //Adiciona o start a fila
      fila.push(start);
      //Define o Nivel do start como 0
      nivel[start]=0;
      //Enquanto a fila não estiver vazia
      while(!fila.empty()){
        //Tira o primeiro elemento da fila
        int v = fila.front();
        fila.pop();
        //Para todos os vizinhos da fila
        for(int i=1;i<(int)grafo.numVertices+1;i++){
          //Se o vizinho não for visitado
          if(nivel[v]>maiornivel){
            maiornivel=nivel[v];
          }
          if(grafo.adjMatriz[v][i] && nivel[i]==-1){
            //visita o vizinho e adiciona ele na fila
            nivel[i] = nivel[v]+1;
            fila.push(i);
          }
        }
      }

      for(int i=0;i<(int)grafo.numVertices+1;i++){
        nivel[i]=-1;
      }
    }
    return maiornivel;
}

int componentesConexasMatriz(grafoMatriz grafo, bool salve=false){
  //Cria um vector de tamanho numVertices+1 e seta todos como 0
  vector <int> descoberto (grafo.numVertices+1, 0);
  //Cria um vector de vector com as componente conexas do grafo
  vector < vector <int> > verticesCC;
  //Seta uma constante como 0
  int constante = 0;
  //Para todos os vértices do grafo
  for(int i = 1; i < grafo.numVertices+1; i++) {
    //Se o vértice não foi descoberto
    if (!descoberto[i]){
      //Adiciona 1 a constante (será o label dessa componente conexa)
      constante++;
      //Roda uma bfs para essa componente conexa e adiciona ao VerticesCC
      verticesCC.push_back( bfsCCMatriz(grafo, i , descoberto, constante));
    }
  }
  if(salve){
    ofstream saida;
    saida.open("connectedComponents.txt");
    saida << "Número de componentes conexas: "<<verticesCC.size()<<"\n"<<endl;
    sort(verticesCC.begin(), verticesCC.end(), comparaCC);
    for (int i = 0; i < (int)verticesCC.size(); i++) {
      saida <<"Tamanho da "<<i+1<<"ª Componente conexa: "<< verticesCC[i].size()<<endl;
      saida <<"Abaixo estão os vértices que a compõem:"<<endl;
      for(int j=0; j< (int)verticesCC[i].size();j++){
        saida <<verticesCC[i][j]<<" ";
      }
      saida<<endl;
    }
  }
  return constante;
}

//Funções para Vetor de Adjacência
void bfsVector(int start, grafoVector grafo, bool salve=false, int objetivo = -1){
  //Cria um vetor de niveis
  int *nivel;
  nivel = new int[grafo.numVertices+1];
  //Cria um vetor de pais
  int *pai;
  pai = new int[grafo.numVertices+1];
  //Define todos os níveiscomo -1
  for(int i=0;i<(int)grafo.numVertices+1;i++){
    nivel[i]=-1;
  }
  //Define o vetor pai como 0
  memset(pai, 0, grafo.numVertices+1);
  //Cria uma fila
  queue<int> fila;
    //Adiciona o start a fila
    fila.push(start);
    //Define o Nivel do start como 0
    nivel[start]=0;
    pai[start]=-1;
    //Enquanto a fila não estiver vazia
    while(!fila.empty()){
      //Tira o primeiro elemento da fila
      int v = fila.front();
      fila.pop();
      //Para todos os vizinhos da fila
      for(int i=0;i<(int)grafo.adjVector[v].size();i++){
        //Se o vizinho não for visitado
        if((nivel[grafo.adjVector[v][i]] == -1)){
          //visita o vizinho e adiciona ele na fila
          nivel[grafo.adjVector[v][i]] = nivel[v]+1;
          pai[grafo.adjVector[v][i]] = v;
          fila.push(grafo.adjVector[v][i]);
        }
      }
    }
  if(salve){
    ofstream bfsFile;
    bfsFile.open("bfsFile.txt");
    for(int i=1;i<(int)grafo.numVertices+1;i++){
      bfsFile<< "Vértice: "<< i <<", Nível: "<< nivel[i]<<", Pai: "<< pai[i]<<endl;
    }
    bfsFile.close();
    //Cria um arquivo mstFile
    //Cria um inteiro x
    int x=0;
    //x será seu novo vértice objetivo
    x = objetivo;
    if(x!=-1){
      ofstream shortestPath;
      shortestPath.open("shortestPath.txt");
      //Percorre x até chegar no vértice inicial
      if(x!=start){
        //Imprime o caminho de x até start
        shortestPath<<"Vértice: "<< x<<", Caminho até "<<start<<": ";
        //Se tiver um caminho até x
        if (nivel[x] !=-1){
          shortestPath<<"[";
          while(x != start){
            //Cálculo a distância de x até start
            shortestPath<<x<<", ";
            //x agora é quem descobriu x
            x = pai[x];
          }
          shortestPath<<x<<"]";
        }
        //Se não tiver um caminho de x até start
        else{
          //Imprime INFINITO
          shortestPath<<"[], "<<"Distância entre eles: "<<"INFINITO"<<endl;
        }
      }
    }
  }
}

void dfsVector(int start, grafoVector grafo, bool salve=false){
  //Cria o vector addPilha
  vector<int>addPilha;
  //Cria um vetor de niveis
  int *nivel;
  nivel = new int[grafo.numVertices+1];
  //Cria um vetor de pais
  int *pai;
  pai = new int[grafo.numVertices+1];
  //Cria um vetor de visitados
  bool *visited;
  visited = new bool[grafo.numVertices+1];
  //Define todos os níveis e pais como -1
  for(int i=0;i<(int)grafo.numVertices+1;i++){
    nivel[i]=-1;
  }
  //memset(nivel,-1,grafo.numVertices+1);
  memset(pai,0,grafo.numVertices+1);
  memset(visited,0,grafo.numVertices+1);

  //Cria uma pilha
  stack <int> pilha;
  //Adiciona start a pilha;
    pilha.push(start);
    //Define o Nivel do start como 0
    nivel[start]=0;
    pai[start]=-1;
    while (pilha.empty()!= 1){
      int u = pilha.top();
      pilha.pop();
      if (visited[u] == 0){
          visited[u] = 1;
          for (int i=0;i<(int)grafo.adjVector[u].size();i++){
              if(!visited[grafo.adjVector[u][i]]){
                nivel[grafo.adjVector[u][i]] = nivel[u]+1;
                pai[grafo.adjVector[u][i]] = u;
              }
              //Adiciona o vetor adjacente ao addPilha
              addPilha.push_back(grafo.adjVector[u][i]);
          }
      }
      //Inverte o vetor addPilha e adiciona os itens a pilha.
      for (vector<int>::const_iterator i = (addPilha.end() -1); i >= addPilha.begin(); --i){
        pilha.push(*i);
      }
      //Limpa o vetor addPilha
      addPilha.clear();
    }
  if(salve){
    ofstream dfsFile;
    dfsFile.open("dfsFile.txt");
      for(int i=1;i<(int)grafo.numVertices+1;i++){
          dfsFile<< "Vértice: "<< i <<", Nível: "<< nivel[i]<<", Pai: "<< pai[i]<<endl;
    }
    dfsFile.close();
  }
}

int distanciaVector(int v1, int v2, grafoVector grafo){
  //Cria um vetor distâncias
  int *path;
  path = new int[grafo.numVertices+1];
  //Define todas as distâncias como -1;
  for(int i=0;i<(int)grafo.numVertices;i++){
    path[i]=-1;
  }
  queue<int> fila;
  //Adiciona o start a fila
  fila.push(v1);
  //Define a distância até o start em 0
  path[v1]=0;
  //Enquanto a fila não estiver vazia
  while(!fila.empty()){
    //Tira o primeiro elemento da fila
    int v = fila.front();
    fila.pop();
    //Para todos os vizinhos da fila
    for(int i=0;i<(int)grafo.adjVector[v].size();i++){
      //Se o vizinho tiver uma distância não definida
      if(path[grafo.adjVector[v][i]]==-1){
        //Altera a distância e adiciona ele na fila
        if (grafo.adjVector[v][i] == v2){
          return path[v] + 1;
        }
        path[grafo.adjVector[v][i]] = path[v]+1;
        fila.push(grafo.adjVector[v][i]);
      }
    }
  }
  return path[v2];
}

int diametroVector(grafoVector grafo){
    //Cria uma constante maior nível
    int maiornivel=0;
    //Cria um vetor de niveis
    int *nivel;
    nivel = new int[grafo.numVertices+1];
    //Define todos os níveis -1
    for(int i=0;i<(int)grafo.numVertices+1;i++){
      nivel[i]=-1;
    }
    //Cria uma fila
    queue <int> fila;
    int start;
    for(start=1; start<(int)grafo.numVertices+1;start++){
      //Adiciona o start a fila
      fila.push(start);
      //Define o Nivel do start como 0
      nivel[start]=0;
      //Enquanto a fila não estiver vazia
      while(!fila.empty()){
        //Tira o primeiro elemento da fila
        int v = fila.front();
        fila.pop();
        //Para todos os vizinhos da fila
        for(int i=0;i<(int)grafo.adjVector[v].size();i++){
          //Se o vizinho não for visitado
          if(nivel[v]>maiornivel){
            maiornivel=nivel[v];
          }
          if((nivel[grafo.adjVector[v][i]] == -1)){
            //visita o vizinho e adiciona ele na fila
            nivel[grafo.adjVector[v][i]] = nivel[v]+1;
            fila.push(grafo.adjVector[v][i]);
          }
        }
      }

      for(int i=0;i<(int)grafo.numVertices+1;i++){
        nivel[i]=-1;
      }
    }
    return maiornivel;
}

int componentesConexasVector(grafoVector grafo, bool salve=false){
  //Cria um vector de tamanho numVertices+1 e seta todos como 0
  vector <int> descoberto (grafo.numVertices+1, 0);
  //Cria um vector de vector com as componente conexas do grafo
  vector < vector <int> > verticesCC;
  //Seta uma constante como 0
  int constante = 0;
  //Para todos os vértices do grafo
  for(int i = 1; i < grafo.numVertices+1; i++) {
    //Se o vértice não foi descoberto
    if (!descoberto[i]){
      //Adiciona 1 a constante (será o label dessa componente conexa)
      constante++;
      //Roda uma bfs para essa componente conexa e adiciona ao VerticesCC
      verticesCC.push_back(bfsCCVector(grafo, i , descoberto, constante));
    }
  }
  if(salve){
    ofstream saida;
    saida.open("connectedComponents.txt");
    saida << "Número de componentes conexas: "<<verticesCC.size()<<"\n"<<endl;
    sort(verticesCC.begin(), verticesCC.end(), comparaCC);
    for (int i = 0; i < (int)verticesCC.size(); i++) {
      saida <<"Tamanho da "<<i+1<<"ª Componente conexa: "<< verticesCC[i].size()<<endl;
      saida <<"Abaixo estão os vértices que a compõem:"<<endl;
      for(int j=0; j< (int)verticesCC[i].size();j++){
        saida <<verticesCC[i][j]<<" ";
      }
      saida<<endl;
    }
  }
  return constante;
}

//Funções para Matriz de Adjacência com peso
double primMatriz(grafoMatrizComPeso grafo, int origem, bool salve=false){
  //Cria um vector de custo de tamanho número de vértices
  vector <double> custo(grafo.numVertices+1, INF);
  //Define o custo da origem = 0
  custo[origem] = 0;
  //Cria vector inteiro com os pais = -1
  vector <int> pai (grafo.numVertices+1, -1);
  //Cria vector inteiro com nível = 0
  vector <int> nivel (grafo.numVertices+1, 0);
  //Cria vector boleano visitado = false
  vector < bool > visitado (grafo.numVertices+1, false);
  //Cria o conjunto de pair (peso,vértice) com os vértices a serem percorridos (vasp)
  set< pair<double, int> > vasp;
  //Insere o par peso, vértice no conjunto
  vasp.insert(make_pair(custo[origem], origem));
  //Define o pai da origem como 0
  pai[origem] = 0;
  //Enquanto o conjunto tiver termos a serem percorridos
  while(!vasp.empty()){
    //Escolhe o vértice de menor distância
    //Pega o peso do vértice de menor distância
    double current_cost = vasp.begin()->first;
    //Pega o vértice de menor distância
    int current_vertex = vasp.begin()->second;
    //Visita o vértice
    visitado[current_vertex] = true;
    //Remove o vértice do set e marca, indicando que foi percorrido
    vasp.erase(make_pair(current_cost, current_vertex));
    //Itera sobre os vizinhos do vértice atual sendo percorrido
    for (int i = 1; i < grafo.numVertices+1; i++){
        //Caso tenha achado um caminho melhor, ajusta a distância e insere no conjunto
        if (grafo.adjMatriz[current_vertex][i]!= INF){
          //Se o custo de i > peso da aresta entre vértice atual e i
          //E, se ele não tiver sido visitado
          if (custo[i] > grafo.adjMatriz[current_vertex][i] && !visitado[i]){
            //Altera o custo.
            custo[i] = grafo.adjMatriz[current_vertex][i];
            //Adiciona o par(custo, vértice)
            vasp.insert(make_pair(custo[i], i));
            //Altera o pai
            pai[i] = current_vertex;
            //Altera o nível
            nivel[i] = nivel[current_vertex]+1;
          }
        }
    }
  }
  //Define uma variável que armazenará o custo_total da mst
  double custo_total = 0;
  //Itera sobre todos os vértices do grafo
  for (int i = 1; i <= grafo.numVertices; i++){
    if(custo[i]!= INF){
      custo_total += custo[i];
    }
  }
  //Se o usuário escolher salvar
  if(salve){
    //Cria um arquivo mstFile
    ofstream mstFile;
    mstFile.open("mstfile.txt");
    //Adiciona todos os dados da mst
    //Altera a precisão do mstFile
    mstFile.precision(15);
    mstFile << "Custo total: "<<custo_total<<endl;
    for(int i=1;i<grafo.numVertices+1;i++){
      if (pai[i] != 0){
        mstFile<< i <<" "<< pai[i]<<" "<<custo[i]<<endl;
      }
    }
    //Fecha o arquivo
    mstFile.close();
  }
  //Retorna o custo total da mst
  return custo_total;
}

void dijkstraMatriz(grafoMatrizComPeso grafo, int start, bool salve=false, int objective=-1){
  //Cria uma variável controle
  bool control = 0;
  //Cria um vector de distancia de tamanho número de vértices
  vector <double> distancia(grafo.numVertices+1, INF);
  //Cria um array de pai
  int *pai;
  pai = new int[grafo.numVertices+1];
  //Define o pai de todos os vértices como 0
  memset(pai,0,grafo.numVertices+1);
  //Define a distância da origem = 0
  distancia[start] = 0;
  //Define o pai da origem = -1
  pai[start] = -1;
  //Cria o conjunto de vértices a serem percorridos (vasp)
  set< pair<double, int> > vasp;
  //Insere o par distância origem no conjunto vasp
  vasp.insert(make_pair(distancia[start], start));
  //Enquanto o conjunto tiver termos a serem percorridos
  while(!vasp.empty()){
    //Pega os vértices de menor distância
    double current_dist = vasp.begin()->first;
    //Se tiver peso negativo, para o código
    if(current_dist < 0){
      cout<<"Para executar dijkstra todos os pesos devem ser maiores que 0"<<endl;
      //Seta controle = 1
      control =1;
      break;
    }
    int current_vertex = vasp.begin()->second;
    //Remove o vértice do set e marca, indicando que foi percorrido
    vasp.erase(make_pair(current_dist, current_vertex));
    //Itera sobre os vizinhos do vértice atual
    for (int i = 1; i < grafo.numVertices+1; i++){
        //Caso tenha achado um caminho melhor, ajusta a distância e insere no conjunto
        //Se existir a aresta.
        if (grafo.adjMatriz[current_vertex][i]>0){
          //Se a distância de i for maior que a distância de seu vizinho + peso da aresta entre eles
          if (distancia[i] > distancia[current_vertex] + grafo.adjMatriz[current_vertex][i]){
            //Altera pai[i]
            pai[i] = current_vertex;
            //Altera distância[i]
            distancia[i] = distancia[current_vertex] + grafo.adjMatriz[current_vertex][i];
            //Insere o par distancia[i], i no conjunto
            vasp.insert(make_pair(distancia[i], i));
          }
        }
    }
  }
  //Se o usuário quiser salvar os caminhos em um arquivo .txt
  if (salve){
    //Cria um arquivo mstFile
    ofstream shortestPath;
    shortestPath.open("shortestPath.txt");
    //Define p como a precisão do arquivo mstFile;
    streamsize p = shortestPath.precision();
    //Cria um inteiro x
    int x=0;
    //Se o usuário definir um vetor objetivo
    if(objective == -1 && !control){
      //Para todos os vértices do grafo
      for (int i = 1; i < grafo.numVertices+1; i++){
        //x será seu novo vértice objetivo
        x = i;
        //Percorre x até chegar no vértice inicial
        if(x!=start){
          //Imprime o caminho de x até start
          shortestPath<<"Vértice: "<< x<<", Caminho até "<<start<<": ";
          //Se tiver um caminho até x
          if (distancia[x] != INF){
            shortestPath<<"[";
            while(x != start){
              //Cálculo a distância de x até start
              shortestPath<<x<<", ";
              //x agora é quem descobriu x
              x = pai[x];
            }
            shortestPath<<x<<"], "<<"Distância entre eles: ";
            //Altera a precisão do shortestPath
            shortestPath.precision(15);
            shortestPath<<distancia[i]<<endl;
            //Retorna a precisão a precisão inicial do arquivo.
            shortestPath.precision(p);
          }
          //Se não tiver um caminho de x até start
          else{
            //Imprime INFINITO
            shortestPath<<"[], "<<"Distância entre eles: "<<"INFINITO"<<endl;
          }
        }
      }
    }
    //Se tiver um objetivo
    else{
      //Se não tiver nenhum peso negativo
      if(!control){
        x = objective;
        //Enquanto o objetivo não for o começo
        if(x!=start){
          //Imprime o caminho até o começo
          shortestPath<<"Vértice: "<< x<<", Caminho até "<<start<<": ";
          //Se tiver um caminho até x
          if (distancia[x] != INF){
            shortestPath<<"[";
            while(x != start){
              shortestPath<<x<<", ";
              //x agora é quem descobriu x
              x = pai[x];
            }
            shortestPath<<x<<"], "<<"Distância entre eles: ";
            //Altera a precisão do shortestPath
            shortestPath.precision(15);
            shortestPath<<distancia[objective]<<endl;
            //Retorna a precisão a precisão inicial do arquivo.
            shortestPath.precision(p);
          }
          //Se não tiver um caminho de x até start
          else{
            //Imprime INFINITO
            shortestPath<<"[], "<<"Distância entre eles: "<<"INFINITO"<<endl;
          }
        }
      }
    }
    //Fecha o arquivo
    shortestPath.close();
  }
}

double eccentricityMatriz(grafoMatrizComPeso grafo, int start){
  //Cria um vector de distância de tamanho número de vértices +1
  vector <double> distancia(grafo.numVertices+1, INF);
  //Define a distância até start = 0
  distancia[start] = 0;
  //Cria o conjunto de vértices a serem percorridos (vasp)
  set< pair<double, int> > vasp;
  vasp.insert(make_pair(distancia[start], start));
  //Enquanto o conjunto tiver termos a serem percorridos
  while(!vasp.empty()){
    //Escolhe os vértices de menor distância
    double current_dist = vasp.begin()->first;
    //Se a distância for negativa
    if(current_dist < 0){
      //Para o código
      cout<<"Para executar dijkstra todos os pesos devem ser maiores que 0"<<endl;
      break;
    }
    int current_vertex = vasp.begin()->second;
    //Remove o vértice do set e marca, indicando que foi percorrido
    vasp.erase(make_pair(current_dist, current_vertex));
    //Itera sobre os vizinhos do vértice atual
    for (int i = 1; i < grafo.numVertices+1; i++){
        if (grafo.adjMatriz[current_vertex][i]>0){
          //Se a distância do vértice visitado for maior que distância de quem descobriu ele mais o peso entre eles
          if (distancia[i] > distancia[current_vertex] + grafo.adjMatriz[current_vertex][i]){
            //Altera a distância de i
            distancia[i] = distancia[current_vertex] + grafo.adjMatriz[current_vertex][i];
            //Insere o par distância e vértice i no conjunto
            vasp.insert(make_pair(distancia[i], i));
          }
        }
    }
  }
  //Define uma váriavel minimo
  double min = 0;
  //Percorre todos os vizinhos
  for (int i = 1; i < grafo.numVertices+1; i++){
    //Pega a distância máxima
    if(distancia[i]>min && distancia[i] != INF){
      min = distancia[i];
    }
  }
  //Retorna a maior distância
  return min;
}

//Funções para Vetor de Adjacência com peso
double primVector(grafoVectorComPeso grafo, int origem, bool salve=false){
  //Cria um vector de custo de tamanho número de vértices
  vector <double> custo(grafo.numVertices+1, INF);
  //Define o custo da origem = 0
  custo[origem] = 0;
  //Cria vector inteiro com os pais = -1
  vector <int> pai (grafo.numVertices+1, -1);
  //Cria vector inteiro com nível = 0
  vector <int> nivel (grafo.numVertices+1, 0);
  //Cria vector boleano visitado = false
  vector < bool > visitado (grafo.numVertices+1, false);
  //Cria o conjunto de pair (peso,vértice) com os vértices a serem percorridos (vasp)
  set< pair<double, int> > vasp;
  //Insere o par peso, vértice no conjunto
  vasp.insert(make_pair(custo[origem], origem));
  //Define o pai da origem como 0
  pai[origem] = 0;
  //Enquanto o conjunto tiver termos a serem percorridos
  while(!vasp.empty()){
    //Escolhe o vértice de menor distância
    //Pega o peso do vértice de menor distância
    double current_cost = vasp.begin()->first;
    //Pega o vértice de menor distância
    int current_vertex = vasp.begin()->second;
    //Visita o vértice
    visitado[current_vertex] = true;
    //Remove o vértice do set e marca, indicando que foi percorrido
    vasp.erase(make_pair(current_cost, current_vertex));
    //Itera sobre os vizinhos do vértice atual sendo percorrido
    for (vector <pair <int,double> > ::iterator it = grafo.adjVector[current_vertex].begin(); it!=grafo.adjVector[current_vertex].end(); ++it){
      int vizinho = it->first;
      double peso = it->second;
      //Caso tenha achado um caminho melhor, ajusta a distância e insere no conjunto
      //Se o custo de i > peso da aresta entre vértice atual e i
      //E, se ele não tiver sido visitado
      if (custo[vizinho] > peso && !visitado[vizinho]){
        //Altera o custo.
        custo[vizinho] = peso;
        //Adiciona o par(custo, vértice)
        vasp.insert(make_pair(custo[vizinho], vizinho));
        //Altera o pai
        pai[vizinho] = current_vertex;
        //Altera o nível
        nivel[vizinho] = nivel[current_vertex]+1;
      }
    }
  }
  //Define uma variável que armazenará o custo_total da mst
  double custo_total = 0;
  //Itera sobre todos os vértices do grafo
  for (int i = 1; i <= grafo.numVertices; i++){
    if(custo[i]!= INF){
      custo_total += custo[i];
    }
  }
  //Se o usuário escolher salvar
  if(salve){
    //Cria um arquivo mstFile
    ofstream mstFile;
    mstFile.open("mstfile.txt");
    //Adiciona todos os dados da mst
    //Altera a precisão do mstFile
    mstFile.precision(15);
    mstFile << "Custo total: "<<custo_total<<endl;
    //Retorna a precisão a precisão inicial do arquivo.
    for(int i=1;i<grafo.numVertices+1;i++){
      if (pai[i] > 0){
        mstFile<< i <<" "<< pai[i]<<" "<<custo[i]<<endl;
      }
    }
    //Fecha o arquivo
    mstFile.close();
  }
  //Retorna o custo total da mst
  return custo_total;
}

void dijkstraVector(grafoVectorComPeso grafo, int start, bool salve=false, int objective=-1){
  //Cria uma variável controle
  bool control = 0;
  //Cria um vector de distancia de tamanho número de vértices
  vector <double> distancia(grafo.numVertices+1, INF);
  //Cria um array de pai
  int *pai;
  pai = new int[grafo.numVertices+1];
  //Define o pai de todos os vértices como 0
  memset(pai,0,grafo.numVertices+1);
  //Define a distância da origem = 0
  distancia[start] = 0;
  //Define o pai da origem = -1
  pai[start] = -1;
  //Cria o conjunto de vértices a serem percorridos (vasp)
  set< pair<double, int> > vasp;
  //Insere o par distância origem no conjunto vasp
  vasp.insert(make_pair(distancia[start], start));
  //Enquanto o conjunto tiver termos a serem percorridos
  while(!vasp.empty()){
    //Pega os vértices de menor distância
    double current_dist = vasp.begin()->first;
    //Se tiver peso negativo, para o código
    if(current_dist < 0){
      cout<<"Para executar dijkstra todos os pesos devem ser maiores que 0"<<endl;
      //Controle = 1
      control=1;
      break;
    }
    int current_vertex = vasp.begin()->second;
    //Remove o vértice do set e marca, indicando que foi percorrido
    vasp.erase(make_pair(current_dist, current_vertex));
    //Itera sobre os vizinhos do vértice atual
    for (vector <pair <int,double> > ::iterator it = grafo.adjVector[current_vertex].begin(); it!=grafo.adjVector[current_vertex].end(); ++it){
      int vizinho = it->first;
      double peso = it->second;
      //Se a distância de i for maior que a distância de seu vizinho + peso da aresta entre eles
      if (distancia[vizinho] > distancia[current_vertex] + peso){
        //Altera distância[i]
        distancia[vizinho] = distancia[current_vertex] + peso;
        //Altera pai[i]
        pai[vizinho] = current_vertex;
        //Caso tenha achado um caminho melhor, ajusta a distância e insere no conjunto
        vasp.insert(make_pair(distancia[vizinho], vizinho));

      }
    }
  }
  //Se o usuário quiser salvar os caminhos em um arquivo .txt
  if (salve){
    //Cria um arquivo mstFile
    ofstream shortestPath;
    shortestPath.open("shortestPath.txt");
    //Define p como a precisão do arquivo mstFile;
    streamsize p = shortestPath.precision();
    //Cria um inteiro x
    int x=0;
    //Se o usuário definir um vetor objetivo
    if(objective == -1 && !control){
      //Para todos os vértices do grafo
      for (int i = 1; i < grafo.numVertices+1; i++){
        //x será seu novo vértice objetivo
        x = i;
        //Percorre x até chegar no vértice inicial
        if(x!=start){
          //Imprime o caminho de x até start
          shortestPath<<"Vértice: "<< x<<", Caminho até "<<start<<": ";
          //Se tiver um caminho até x
          if (distancia[x] != INF){
            shortestPath<<"[";
            while(x != start){
              //Cálculo a distância de x até start
              shortestPath<<x<<", ";
              //x agora é quem descobriu x
              x = pai[x];
            }
            shortestPath<<x<<"], "<<"Distância entre eles: ";
            //Altera a precisão do shortestPath
            shortestPath.precision(15);
            shortestPath<<distancia[i]<<endl;
            //Retorna a precisão a precisão inicial do arquivo.
            shortestPath.precision(p);
          }
          //Se não tiver um caminho de x até start
          else{
            //Imprime INFINITO
            shortestPath<<"[], "<<"Distância entre eles: "<<"INFINITO"<<endl;
          }
        }
      }
    }
    //Se tiver um objetivo
    else{
      //Se não tiver nenhum peso negativo
      if(!control){
        x = objective;
        //Enquanto o objetivo não for o começo
        if(x!=start){
          //Imprime o caminho até o começo
          shortestPath<<"Vértice: "<< x<<", Caminho até "<<start<<": ";
          //Se tiver um caminho até x
          if (distancia[x] != INF){
            shortestPath<<"[";
            while(x != start){
              shortestPath<<x<<", ";
              //x agora é quem descobriu x
              x = pai[x];
            }
            shortestPath<<x<<"], "<<"Distância entre eles: ";
            //Altera a precisão do shortestPath
            shortestPath.precision(15);
            shortestPath<<distancia[objective]<<endl;
            //Retorna a precisão a precisão inicial do arquivo.
            shortestPath.precision(p);
          }
          //Se não tiver um caminho de x até start
          else{
            //Imprime INFINITO
            shortestPath<<"[], "<<"Distância entre eles: "<<"INFINITO"<<endl;
          }
        }
      }
    }
    //Fecha o arquivo
    shortestPath.close();
  }
}

double eccentricityVector(grafoVectorComPeso grafo, int start){
  //Cria um vector de distância de tamanho número de vértices +1
  vector <double> distancia(grafo.numVertices+1, INF);
  //Define a distância até start = 0
  distancia[start] = 0;
  //Cria o conjunto de vértices a serem percorridos (vasp)
  set< pair<double, int> > vasp;
  //Insere o par distância, origem no conjunto
  vasp.insert(make_pair(distancia[start], start));
  //Enquanto o conjunto tiver termos a serem percorridos
  while(!vasp.empty()){
    //Escolhe os vértices de menor distância
    double current_dist = vasp.begin()->first;
    //Se a distância for negativa
    if(current_dist < 0){
      //Para o código
      cout<<"Para executar dijkstra todos os pesos devem ser maiores que 0"<<endl;
      break;
    }
    int current_vertex = vasp.begin()->second;
    //Remove o vértice do set e marca, indicando que foi percorrido
    vasp.erase(make_pair(current_dist, current_vertex));
    //Itera sobre os vizinhos do vértice atual
    for (vector <pair <int,double> > ::iterator it = grafo.adjVector[current_vertex].begin(); it!=grafo.adjVector[current_vertex].end(); ++it){
      int vizinho = it->first;
      double peso = it->second;
      //Caso tenha achado um caminho melhor, ajusta a distância e insere no conjunto
      if (distancia[vizinho] > distancia[current_vertex] + peso){
        //Altera a distância de i
        distancia[vizinho] = distancia[current_vertex] + peso;
        //Insere o par distância e vértice i no conjunto
        vasp.insert(make_pair(distancia[vizinho], vizinho));
      }
    }
  }
  //Define uma váriavel minimo
  double min = 0;
  //Percorre todos os vizinhos
  for (int i = 1; i < grafo.numVertices+1; i++){
    //Pega a distância máxima
    if(distancia[i]>min && distancia[i] != INF){
      min = distancia[i];
    }
  }
  //Retorna a maior distância
  return min;
}

//Funções para Vetor de Adjacência grafos bipartidos
int HopcroftkarpVector(grafoVector grafo, bool salve=false){
  if(!grafo.bipartido){
    cout<<"O grafo não é bipartido"<<endl;
    return 0;
  }
  int result =0;
  for(int v=0;v<=grafo.numVertices;v++){
    match[v] = v;
  }
  while(bfsHopVector(grafo)){
    for(int v: grafo.bipartite_1){
      if(match[v] == v && dfsHopVector(grafo,v)){
        ++result;
      }
    }
  }
  //Se o usuário escolher salvar
  if(salve){
    //Cria um arquivo matchingFile
    ofstream matchingFile;
    matchingFile.open("matchingfile.txt");
    //Adiciona todos os dados do emparelhamento
    for(int i=1;i<grafo.numVertices+1;i++){
      if (match[i] > 0){
        matchingFile<< i <<" "<< match[i]<<endl;
      }
    }
    //Fecha o arquivo
    matchingFile.close();
  }
  return result;
}

//Funções para Matriz de Adjacência grafos bipartidos
int HopcroftkarpMatriz(grafoMatriz grafo, bool salve=false){
  if(!grafo.bipartido){
    cout<<"O grafo não é bipartido"<<endl;
    return 0;
  }
  int result =0;
  for(int v=0;v<=grafo.numVertices;v++){
    match[v] = v;
  }
  while(bfsHopMatriz(grafo)){
    for(int v: grafo.bipartite_1){
      if(match[v] == v && dfsHopMatriz(grafo,v)){
        ++result;
      }
    }
  }
  //Se o usuário escolher salvar
  if(salve){
  //Cria um arquivo matchingFile
  ofstream matchingFile;
  matchingFile.open("matchingfile.txt");
  //Adiciona todos os dados do emparelhamento
  for(int i=1;i<grafo.numVertices+1;i++){
    if (match[i] > 0){
      matchingFile<< i <<" "<< match[i]<<endl;
    }
  }
  //Fecha o arquivo
  matchingFile.close();
}
  return result;
}


//Utilização pelo usuário(main)
int main(){
  grafoVector vector = constroiVector("grafo_teste.txt");
  grafoMatriz matriz = constroiMatriz("grafo_teste.txt");
  clock_t start = clock();
  //getchar();
  cout<<HopcroftkarpVector(vector)<<endl;
  cout<<HopcroftkarpMatriz(matriz)<<endl;
  clock_t end = clock();
  cout<<"Tempo HopcroftKarp: "<<(double)(end-start)/CLOCKS_PER_SEC<< " segundos."<<endl;

}
