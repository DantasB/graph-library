#include <iostream>
#include <ctime> //Biblioteca para medir o tempo de execução
#include <fstream> //Biblioteca para escrita e leitura de arquivos txt
#include <stack> //Biblioteca com implementação de pilha
#include <queue> //Biblioteca com implementação de fila
#include <string> //Biblioteca com implementação de string
#include <vector> //Biblioteca com implementação de array dinâmico
#include <algorithm> //Biblioteca com implementação do sort
#include <string.h> //Biblioteca com implementação do memset

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

struct grafoMatrizComPeso{
  int numVertices;
  float **adjMatriz;
};

struct grafoVectorComPeso{
  int numVertices;
  vector< pair<int, int> >* adjVector;
};

//Funções extras
bool comparaCC(vector<int> primeiro, vector<int> segundo){
   return primeiro.size() > segundo.size();
}

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

  return grafo;
}

grafoMatrizComPeso constroiMatrizComPeso(string arquivo){
  grafoMatrizComPeso grafo;
  int numVertices;
  float **adjMatriz;
  int *grau;
  int numArestas=0;
  int vertex1, vertex2;
  float peso;
  ifstream graphTexto(arquivo.c_str());
  //Esse é o próprio número de vértices
  graphTexto >> numVertices;
  grafo.numVertices = numVertices;
  //Cria a Matriz de Adjacência
  adjMatriz = new float*[numVertices+1];
  for (int i = 0; i < numVertices+1; i++){
        adjMatriz[i] = new float[numVertices+1];
  }

  //Zera a Matriz de Adjacência
  for(int i=0;i< numVertices+1; i++){
    memset(adjMatriz[i],false, numVertices+1);
  }

  //Cria um vetor de graus
  grau = new int[numVertices+1]();
  //Preenche a Matriz de Adjacência
  while(graphTexto>>vertex1>>vertex2>>peso){
    //Insere o par (vértice1, vértice2) na matriz
    adjMatriz[vertex1][vertex2]=peso;
    adjMatriz[vertex2][vertex1]=peso;
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

  //Imprime o grafo construido.
  /*
  for (int u = 0; u <= numVertices; u++) {
    cout << "Nó " << u << " faz adjacência com \n";
    for (int j=0; j<= numVertices;j++)
    {
      if (adjMatriz[u][j]>0){
        cout << "\tNó " << j << " Cujo peso da aresta ="
             << adjMatriz[u][j] << "\n";
      }
    }
    cout << "\n";
  }
  */
  return grafo;
}

grafoVectorComPeso constroiVectorComPeso(string arquivo){
  grafoVectorComPeso grafo;
  int numVertices;
  int *grau;
  vector < pair<int, int> > *adjVector;
  int numArestas=0;
  int vertex1, vertex2;
  float peso;
  ifstream graphTexto(arquivo.c_str());
  //Esse é o próprio número de vértices
  graphTexto >> numVertices;
  grafo.numVertices = numVertices;
  //Cria o vetor de adjacência
  adjVector = new vector< pair<int,int> >[numVertices+1];

  //Inicializa o vetor grau
  grau = new int[numVertices+1]();

  //Preenche o vetor de adjacência
  while(graphTexto>>vertex1>>vertex2>>peso){
    adjVector[vertex1].push_back(make_pair(vertex2, peso));
    adjVector[vertex2].push_back(make_pair(vertex1, peso));
    //Calcula o grau de cada vértice
    grau[vertex1]++;
    grau[vertex2]++;
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
  //Imprime o grafo construido.
  /*
  float v, w;
  for (int u = 1; u <= numVertices; u++) {
    cout << "Nó " << u << " faz adjacência com \n";
    for (auto it = adjVector[u].begin(); it!=adjVector[u].end(); it++)
    {
        v = it->first;
        w = it->second;
        cout << "\tNó " << v << " Cujo peso da aresta ="
             << w << "\n";
    }
    cout << "\n";
  }
  */
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
  ofstream bfsFile;
  bfsFile.open("bfsFile.txt");
  for(int i=1;i<(int)grafo.numVertices+1;i++){
    bfsFile<< "Vértice: "<< i <<", Nível: "<< nivel[i]<<", Pai: "<< pai[i]<<endl;
  }
  bfsFile.close();
}

void dfsMatriz(int start, grafoMatriz grafo){
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

int componentesConexasMatriz(grafoMatriz grafo){
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
  return constante;
}

//Funções para Vetor de Adjacência
void bfsVector(int start, grafoVector grafo){
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
  
  ofstream bfsFile;
  bfsFile.open("bfsFile.txt");
  for(int i=1;i<(int)grafo.numVertices+1;i++){
    bfsFile<< "Vértice: "<< i <<", Nível: "<< nivel[i]<<", Pai: "<< pai[i]<<endl;
  }
  bfsFile.close();

}

void dfsVector(int start, grafoVector grafo){
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
  for(int i=0;i<grafo.numVertices+1;i++){
    cout<<path[i]<<endl;
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

int componentesConexasVector(grafoVector grafo){
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
  return constante;
}

//Utilização pelo usuário(main)
int main(){
  //grafoMatriz matriz = constroiMatriz("as_graph.txt");
  grafoVector vector = constroiVector("dblp.txt");
  clock_t start = clock();
  //cout<<componentesConexasVector(vector)<<endl;
  cout<<componentesConexasVector(vector)<<endl;
  clock_t end = clock();
  cout<< (double)(end-start)/CLOCKS_PER_SEC<<endl;
}
