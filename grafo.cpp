#include <iostream>
#include <ctime>
#include <fstream>
#include <stack>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>
#include <list>

using namespace std;

//Estruturas criadas
struct grafoVector{
  int numVertices;
  vector<int>* adjVector;
};

struct grafoMatriz{
  int numVertices;
  bool **adjMatriz;
};

//Funções de construção das estruturas de dados
grafoVector constroiVector(string arquivo){
  grafoVector grafo;
  int numVertices;
  int *grau;
  vector <int> *adjVector;
  int numArestas=0;
  int vertex1, vertex2;
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
    //Calcula o número de arestas
    numArestas++;
  }

  //Ordena o vetor grau em O(nlog(n))
  sort(grau, grau+numVertices+1);

  //Ordena o vetor de Adjacência
  for(int i=0;i<numVertices+1;i++){
    sort(adjVector[i].begin(),adjVector[i].end());
  }

  int soma=0;
  for(int i=1; i<(int)numVertices+1;i++){
    soma+= grau[i];
  }

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
  return grafo;
}

grafoMatriz constroiMatriz(string arquivo){
  grafoMatriz grafo;
  int numVertices;
  bool **adjMatriz;
  int *grau;
  int numArestas=0;
  int vertex1, vertex2;
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
    //Calcula o número de arestas
    numArestas++;
  }

  //Ordena em O(n.log(n)) o vetor de graus.
  sort(grau, grau+numVertices+1);

  int soma=0;
  for(int i=1; i<(int)numVertices+1;i++){
    soma+= grau[i];
  }

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

  return grafo;
}

//Funções para Matriz de Adjacência
void bfsMatriz(int start, grafoMatriz grafo){
  //Cria um vetor de niveis
  int *nivel;
  nivel = new int[grafo.numVertices+1];
  //Cria um vetor de pais
  int *pai;
  pai = new int[grafo.numVertices+1];
  //Define todos os níveis e pais como -1
  for(int i=0;i<(int)grafo.numVertices+1;i++){
    nivel[i]=-1;
    pai[i]=-1;
  }
  //memset(nivel, -1, grafo.numVertices+1);
  //memset(pai, 0, grafo.numVertices+1);
  //Cria uma fila
  queue<int> fila;
  //Adiciona o start a fila
  fila.push(start);
  //Define o Nivel do start como 0
  nivel[start]=0;
  pai[start]=0;
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
  ofstream bfsFile;
  bfsFile.open("bfsFile.txt");
  for(int i=1;i<(int)grafo.numVertices+1;i++){
    bfsFile<< "Vértice: "<< i <<", Nível: "<< nivel[i]<<", Pai: "<< pai[i]<<endl;
  }
  bfsFile.close();
}

void dfsMatriz(int start, grafoMatriz grafo){
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
    pai[i]=-1;
  }
  //memset(nivel,-1, grafo.numVertices+1);
  //memset(pai,-1, grafo.numVertices+1);
  memset(visited,0,grafo.numVertices+1);
  //Cria uma pilha
  stack <int> pilha;
  //Adiciona start a pilha;
  pilha.push(start);
  //Define o Nivel do start como 0
  nivel[start]=0;
  pai[start]=0;
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
        if(grafo.adjMatriz[u][v]!=0){
          //Se o vértice ainda não tem um pai
          if (pai[v]==-1){
            pai[v] = u;
            nivel[v] = nivel[u]+1;
          }
          //Adiciona a vizinhança a pilha
          pilha.push(v);
        }
      }
    }
  }

  ofstream dfsFile;
  dfsFile.open("dfsFile.txt");
  for(int i=1;i<(int)grafo.numVertices+1;i++){
    dfsFile<< "Vértice: "<< i <<", Nível: "<< nivel[i]<<", Pai: "<< pai[i]<<endl;
  }
  dfsFile.close();
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
    int maiornivel;
    maiornivel =0;
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

/*
void bfsCCMatriz(int start, grafoMatriz grafo, int constante, int visited[]){
  //Cria um vetor de niveis

  //Cria uma fila
  queue<int> fila;
  //Adiciona o start a fila
  fila.push(start);
  //Define o Nivel do start como 0
  visited[start]=constante;
  //Enquanto a fila não estiver vazia
  while(!fila.empty()){
    //Tira o primeiro elemento da fila
    int v = fila.front();
    fila.pop();
    //Para todos os vizinhos da fila
    for(int i=1;i<(int)grafo.numVertices+1;i++){
      //Se o vizinho não for visitado
      if(grafo.adjMatriz[v][i] && visited[i]<0){
        //visita o vizinho e adiciona ele na fila
        visited[i] = constante;
        fila.push(i);
      }
    }
  }
}
*/

/*
void componentesConexasMatriz(grafoMatriz grafo){
  list <int>*conexos;
  conexos = new list<int>;
  int *pointerVector;
  pointerVector = new int[grafo.numVertices+1];
  for(int i=1;i<(int)grafo.numVertices+1;i++){
    conexos.push_front(i);
    pointerVector[i]= &conexos.front();
  }

  int constante = 0;
  int *visited;
  visited = new int[grafo.numVertices+1];
  for(int i=0;i<(int)grafo.numVertices+1;i++){
    visited[i]=-1;
  }
  for(int i=1;i<(int)conexos.size();i++){
    int start = conexos.front();
    conexos.pop_front();
    bfsCCMatriz(start,grafo,constante, visited);
    constante++;
  }
}
*/

//Funções para Vetor de Adjacência
void bfsVector(int start, grafoVector grafo){
  //Cria um vetor de niveis
  int *nivel;
  nivel = new int[grafo.numVertices+1];
  //Cria um vetor de pais
  int *pai;
  pai = new int[grafo.numVertices+1];
  //Define todos os níveis e pais como -1
  for(int i=0;i<(int)grafo.numVertices+1;i++){
    nivel[i]=-1;
    pai[i]=-1;
  }
  //memset(nivel, -1, grafo.numVertices+1);
  //memset(pai, 0, grafo.numVertices+1);
  //Cria uma fila
  queue<int> fila;
  //Adiciona o start a fila
  fila.push(start);
  //Define o Nivel do start como 0
  nivel[start]=0;
  pai[start]=0;
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
  ofstream bfsFile;
  bfsFile.open("bfsFile.txt");
  for(int i=1;i<(int)grafo.numVertices+1;i++){
    bfsFile<< "Vértice: "<< i <<", Nível: "<< nivel[i]<<", Pai: "<< pai[i]<<endl;
  }
  bfsFile.close();
}

void dfsVector(int start, grafoVector grafo){
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
    pai[i]=-1;
  }
  //memset(nivel,-1,grafo.numVertices+1);
  //memset(pai,-1,grafo.numVertices+1);
  memset(visited,0,grafo.numVertices+1);

  //Cria uma pilha
  stack <int> pilha;
  //Adiciona start a pilha;
  pilha.push(start);
  //Define o Nivel do start como 0
  nivel[start]=0;
  pai[start]=0;
  while (pilha.empty()!= 1){
    int u = pilha.top();
    pilha.pop();
    if (visited[u] == 0){
        visited[u] = 1;
        for (int i=0;i<(int)grafo.adjVector[u].size();i++){
            if(pai[grafo.adjVector[u][i]]==-1){
              nivel[grafo.adjVector[u][i]] = nivel[u]+1;
              pai[grafo.adjVector[u][i]] = u;
            }
            pilha.push(grafo.adjVector[u][i]);
        }
    }
  }
  ofstream dfsFile;
  dfsFile.open("dfsFile.txt");
    for(int i=1;i<(int)grafo.numVertices+1;i++){
        dfsFile<< "Vértice: "<< i <<", Nível: "<< nivel[i]<<", Pai: "<< pai[i]<<endl;
  }
  dfsFile.close();
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
    for(int i=1;i<(int)grafo.adjVector[v].size();i++){
      //Se o vizinho tiver uma distância não definida
      if(path[grafo.adjVector[v][i]]==-1){
        //Altera a distância e adiciona ele na fila
        path[grafo.adjVector[v][i]] = path[v]+1;
        fila.push(grafo.adjVector[v][i]);
        if (grafo.adjVector[v][i] == v2){
          return path[v2];
        }
      }
    }
  }
  return path[v2];
}

int diametroVector(grafoVector grafo){
    //Cria uma constante maior nível
    int maiornivel;
    maiornivel =0;
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

/*
void componentesConexasVector(){}
*/

int main(){
  grafoVector vector = constroiVector("live_journal.txt");
  //grafoMatriz matriz = constroiMatriz("as_graph.txt");
  clock_t start = clock();
  bfsVector(1,vector);
  //bfsMatriz(1,matriz);
  clock_t end = clock();
  cout<< (double)(end-start)/CLOCKS_PER_SEC<<endl;
}

