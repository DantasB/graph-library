#include <bits/stdc++.h>

#define MAXN 32386
bool adjMatriz[MAXN][MAXN];
int grau[MAXN];
bool visited[MAXN];
int nivel[MAXN];
int pai[MAXN];

using namespace std;

void BFSMatriz(int start){
  ofstream bfsFile;
  bfsFile.open("bfsFile.txt");
  //Define todos os visitados como 0;
  memset(visited,false,MAXN);
  //Define todos os níveis como -1;
  memset(nivel,-1,MAXN);
  //Define todos os pais como -1;
  memset(pai,-1,MAXN);
  //Cria uma fila
  queue<int> fila;
  //Visita o elemento start
  visited[start]=true;
  //Adiciona o start a fila
  fila.push(start);
  //Define o Nivel do start como 0
  nivel[start]=0;
  bfsFile<<"Vértice: "<< start <<", Nível: "<< nivel[start]<<", Pai: "<< pai[start]<<endl;
  //Enquanto a fila não estiver vazia
  while(!fila.empty()){
    //Tira o primeiro elemento da fila
    int v = fila.front();
    fila.pop();
    //Para todos os vizinhos da fila
    for(int i=0;i<MAXN;i++){
      //Se o vizinho não for visitado
      if(adjMatriz[v][i] != 0 && (!visited[i])){
        //visita o vizinho e adiciona ele na fila
        visited[i] = true;
        nivel[i] = nivel[v]+1;
        pai[i] = v;
        bfsFile<< "Vértice: "<< i <<", Nível: "<< nivel[i]<<", Pai: "<< pai[i]<<endl;
        fila.push(i);
      }
    }
  }
  bfsFile.close();
}

void DFSMatriz(int start){
  ofstream dfsFile;
  dfsFile.open("dfsFile.txt");
  //Define todos os vértices como não visitados
  memset(visited,false,MAXN);
  //Define todos os níveis como -1;
  memset(nivel,-1,MAXN);
  //Define todos os pais como -1;
  memset(pai,-1,MAXN);
  //Cria uma pilha
  stack <int> pilha;
  //Adiciona start a pilha;
  pilha.push(start);
  //Define o Nivel do start como 0
  nivel[start]=0;
  dfsFile<< "Vértice: "<< start <<", Nível: "<< nivel[start]<<", Pai: "<< pai[start]<<endl;
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
      for(int v=0; v<MAXN; v++){
        if(adjMatriz[u][v]!=0){
          //Se o vértice ainda não tem um pai
          if (pai[v]==-1){
            pai[v] = u;
            nivel[v] = nivel[u]+1;
            dfsFile<< "Vértice: "<< v <<", Nível: "<< nivel[v]<<", Pai: "<< pai[v]<<endl;
          }
          //Adiciona a vizinhança a pilha
          pilha.push(v);
        }
      }
    }
  }
  dfsFile.close();
}

int grauMedio(int list[]){
  int soma=0;
  for(int i=0; i<MAXN;i++){
    soma+= grau[i];
  }
  return soma/(MAXN-1);
}

int medianaGrau(int list[], int numVertices){
  if (numVertices%2==0){
    return (grau[(numVertices/2)]+ grau[(numVertices/2)+1])/2;
  }
  else{
    return grau[(numVertices/2)+1];
  }
}

int distancia(int v1, int v2){
  //Define todos os visitados como -1;
  memset(visited,false,MAXN);
  //Define todas as distâncias como -1;
  memset(path,-1,MAXN);
  queue<int> fila;
  //Visita o elemento start
  visited[v1]=true;
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
    for(int i=0;i<MAXN;i++){
      //Se o vizinho tiver uma distância não definida
      if(adjMatriz[v][i] != 0 && path[i]==-1){
        //Altera a distância e adiciona ele na fila
        path[i] = path[v]+1;
        fila.push(i);
      }
    }
  }
  return path[v2];
}

int main(){
  int numVertices;
  int numArestas=0;
  int vertex1, vertex2;
  ifstream graphTexto("grafo.txt");

  //Esse é o próprio número de vértices
  graphTexto >> numVertices;
  //Zera a Matriz de Adjacência
  memset(adjMatriz,false,numVertices);

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

  ofstream graphFile;
  graphFile.open("graphFile.txt");

  graphFile<< "Esse é o número de vértices: "<<numVertices<<endl;
  graphFile<< "Esse é o número de arestas: "<<numArestas<<endl;
  //Após ordenado, o grau máximo é o ultimo elemento da lista
  graphFile<< "Esse é o grau máximo: "<<grau[numVertices]<<endl;
  //O grau mínimo será o primeiro elemento +1 (o primeiro será sempre 0)
  graphFile<< "Esse é o grau mínimo: "<<grau[1]<<endl;
  //O grau médio será o somatorio de cada grau dividido pelo numero de graus
  graphFile<< "Esse é o grau médio: "<<grauMedio(grau)<<endl;
  graphFile<<"Essa é a mediana do grau: "<<medianaGrau(grau, numVertices)<<endl;

  graphFile.close();

  clock_t start = clock();
  BFSMatriz(1);
  clock_t end = clock();
  cout<< (double)(end-start)/CLOCKS_PER_SEC<<endl;
}

