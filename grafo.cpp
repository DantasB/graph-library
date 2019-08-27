#include <bits/stdc++.h>
using namespace std;

void bfsMatriz(int start, bool **adjMatriz, size_t numVertices){
  ofstream bfsFile;
  bfsFile.open("bfsFile.txt");
  //Cria um vetor de niveis
  int *nivel;
  nivel = new int[numVertices+1];
  //Cria um vetor de pais
  int *pai;
  pai = new int[numVertices+1];
  //Define todos os níveis e pais como -1
  for(int i=0;i<(int)numVertices+1;i++){
    nivel[i]= -1;
    pai[i]= -1;
  }
  //Cria uma fila
  queue<int> fila;
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
    for(int i=1;i<(int)numVertices+1;i++){
      //Se o vizinho não for visitado
      if(adjMatriz[v][i] != 0 && (nivel[i] == -1)){
        //visita o vizinho e adiciona ele na fila
        nivel[i] = nivel[v]+1;
        pai[i] = v;
        bfsFile<< "Vértice: "<< i <<", Nível: "<< nivel[i]<<", Pai: "<< pai[i]<<endl;
        fila.push(i);
      }
    }
  }
  bfsFile.close();
}

void dfsMatriz(int start, bool **adjMatriz, size_t numVertices){
  ofstream dfsFile;
  dfsFile.open("dfsFile.txt");
  //Cria um vetor de niveis
  int *nivel;
  nivel = new int[numVertices+1];
  //Cria um vetor de pais
  int *pai;
  pai = new int[numVertices+1];
  //Cria um vetor de visitados
  bool *visited;
  visited = new bool[numVertices+1];
  //Define todos os níveis e pais como -1 e visitados como 0
  for(int i=0;i<(int)numVertices+1;i++){
    nivel[i]= -1;
    pai[i]= -1;
    visited[i] = 0;
  }
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
      for(int v=0; v<(int)numVertices+1; v++){
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

int grauMedio(int *grau, size_t numVertices){
  int soma=0;
  for(int i=1; i<(int)numVertices+1;i++){
    soma+= grau[i];
  }
  return soma/(numVertices-1);
}

int medianaGrau(int *grau, size_t numVertices){
  if (numVertices%2==0){
    return (grau[((int)numVertices/2)]+ grau[((int)numVertices/2)+1])/2;
  }
  else{
    return grau[((int)numVertices/2)+1];
  }
}

int distanciaMatriz(int v1, int v2, bool **adjMatriz, size_t numVertices){
  //Cria um vetor distâncias
  int *path;
  path = new int[numVertices+1];
  //Define todas as distâncias como -1;
  memset(path,-1,numVertices);
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
    for(int i=1;i<(int)numVertices;i++){
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

//int diametroMatriz(){}

void bfsCCMatriz(int start, bool **adjMatriz, size_t numVertices, int *conexas, int constante){
  //Cria uma fila
  queue<int> fila;
  //Visita o elemento start
  conexas[start]=constante;
  //Adiciona o start a fila
  fila.push(start);
  //Enquanto a fila não estiver vazia
  while(!fila.empty()){
    //Tira o primeiro elemento da fila
    int v = fila.front();
    fila.pop();
    //Para todos os vizinhos da fila
    for(int i=1;i<(int)numVertices+1;i++){
      //Se o vizinho não for visitado
      if(adjMatriz[v][i] != 0 && (conexas[i]==-1)){
        //visita o vizinho e adiciona ele na fila
        conexas[i]=constante;
        fila.push(i);
      }
    }
  }
}

int numeroCCMatriz(bool **adjMatriz, size_t numVertices){
  //Cria um vetor de componentes conexas
  int *conexas;
  conexas = new int[numVertices+1];
  //Define todos as conexas como -1
  for(int i=0;i<(int)numVertices+1;i++){
  conexas[i]=-1;
}
  int constante = 0;
  int resultado = 0;
  for(int i=1;i<(int)numVertices+1;i++){
    if (conexas[i]==-1){
      resultado++;
      bfsCCMatriz(i, adjMatriz, numVertices, conexas, constante);
      constante++;
    }
  }
  return resultado;
}

void bfsLista(int start, vector <int> *adjList, size_t numVertices){
  ofstream bfsFile;
  bfsFile.open("bfsFile.txt");
  //Cria um vetor de niveis
  int *nivel;
  nivel = new int[numVertices+1];
  //Cria um vetor de pais
  int *pai;
  pai = new int[numVertices+1];
  //Define todos os níveis e pais como -1
  for(int i=0;i<(int)numVertices+1;i++){
    nivel[i]= -1;
    pai[i]= -1;
  }
  //Cria uma fila
  queue<int> fila;
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
    for(int i=1;i<(int)adjList[v].size();i++){
      //Se o vizinho não for visitado
      if((nivel[adjList[v][i]] == -1) && pai[adjList[v][i] == -1]){
        //visita o vizinho e adiciona ele na fila
        nivel[adjList[v][i]] = nivel[v]+1;
        pai[adjList[v][i]] = v;
        bfsFile<< "Vértice: "<< adjList[v][i] <<", Nível: "<< nivel[adjList[v][i]]<<", Pai: "<< pai[adjList[v][i]]<<endl;
        fila.push(adjList[v][i]);
      }
    }
  }
  bfsFile.close();
}

int distanciaLista(int v1, int v2, vector <int> *adjList, size_t numVertices){
  //Cria um vetor distâncias
  int *path;
  path = new int[numVertices+1];
  //Define todas as distâncias como -1;
  memset(path,-1,numVertices);
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
    for(int i=1;i<(int)adjList[v].size();i++){
      //Se o vizinho tiver uma distância não definida
      if(path[adjList[v][i]]==-1){
        //Altera a distância e adiciona ele na fila
        path[adjList[v][i]] = path[v]+1;
        fila.push(adjList[v][i]);
      }
    }
  }
  return path[v2];
}

int main(){
  int numVertices;
  bool **adjMatriz;
  int *grau;
  vector <int> *adjList;
  int numArestas=0;
  int vertex1, vertex2;
  ifstream graphTexto("grafo.txt");
  char escolha;
  cout<<"Escolha uma representação:"<<endl;
  cout<<"Matriz de Adjacência (M)| Lista de Adjacência (L)"<<endl;
  cin>>escolha;
  //Esse é o próprio número de vértices
  graphTexto >> numVertices;

  if (escolha =='M'|| escolha == 'm'){
    //Cria a Matriz de Adjacência
    adjMatriz = new bool*[numVertices+1];
    for (int i = 0; i < numVertices+1; i++){
          adjMatriz[i] = new bool[numVertices+1];
    }

    //Zera a Matriz de Adjacência
    for (int i=0;i < numVertices+1; i++){
      for(int j=0;j< numVertices+1;j++){
          adjMatriz[i][j] = false;
      }
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

    ofstream graphFile;
    graphFile.open("graphFile.txt");

    graphFile<< "Esse é o número de vértices: "<<numVertices<<endl;
    graphFile<< "Esse é o número de arestas: "<<numArestas<<endl;
    //Após ordenado, o grau máximo é o ultimo elemento da lista
    graphFile<< "Esse é o grau máximo: "<<grau[numVertices]<<endl;
    //O grau mínimo será o primeiro elemento +1 (o primeiro será sempre 0)
    graphFile<< "Esse é o grau mínimo: "<<grau[1]<<endl;
    //O grau médio será o somatorio de cada grau dividido pelo numero de graus
    graphFile<< "Esse é o grau médio: "<<grauMedio(grau, numVertices)<<endl;
    graphFile<<"Essa é a mediana do grau: "<<medianaGrau(grau, numVertices)<<endl;

    graphFile.close();

    clock_t start = clock();
    bfsMatriz(1, adjMatriz, numVertices);
    clock_t end = clock();
    cout<< (double)(end-start)/CLOCKS_PER_SEC<<endl;

  }

  else if(escolha == 'L' || escolha == 'l'){
    //Cria a lista de adjacência
    adjList = new vector<int>[numVertices+1];
    //Inicializa o vetor grau
    grau = new int[numVertices+1]();
    //Preenche a lista de adjacência
    while(graphTexto>>vertex1>>vertex2){
      adjList[vertex1].push_back(vertex2);
      adjList[vertex2].push_back(vertex1);
      //Calcula o grau de cada vértice
      grau[vertex1]++;
      grau[vertex2]++;
      //Calcula o número de arestas
      numArestas++;
    }
    //Ordena o vetor grau em O(nlog(n))
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
    graphFile<< "Esse é o grau médio: "<<grauMedio(grau, numVertices)<<endl;
    graphFile<<"Essa é a mediana do grau: "<<medianaGrau(grau, numVertices)<<endl;

    graphFile.close();

    clock_t start = clock();
    bfsLista(1, adjList, numVertices);
    clock_t end = clock();
    cout<< (double)(end-start)/CLOCKS_PER_SEC<<endl;
  }

  else{
    cout<<"Essa representação não existe"<<endl;
  }

  return 0;
}
