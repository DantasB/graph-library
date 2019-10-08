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
#include <sstream> //Separa a string
#define INF 0x3f3f3f3f //Define um valor infinito

using namespace std;

struct grafoVectorComPeso{
  int numVertices;
  vector< pair<int, double> >* adjVector;
  vector<string> referentes;
};

grafoVectorComPeso constroiVectorComPeso(string arquivo, string refere){
  grafoVectorComPeso grafo;
  int numVertices;
  vector < pair<int, double> > *adjVector;
  int vertex1, vertex2;
  double peso;
  ifstream graphTexto(arquivo.c_str());
  //Esse é o próprio número de vértices
  graphTexto >> numVertices;
  grafo.numVertices = numVertices;
  //Cria o vetor de adjacência
  adjVector = new vector< pair<int, double> >[numVertices+1];
  vector<string> referentes(grafo.numVertices+1, "Ninguém");
  //Preenche o vetor de adjacência
  while(graphTexto>>vertex1>>vertex2>>peso){
    adjVector[vertex1].push_back(make_pair(vertex2, peso));
    adjVector[vertex2].push_back(make_pair(vertex1, peso));
  }
  //Ordena o vetor de Adjacência
  for(int i=0;i<numVertices+1;i++){
    sort(adjVector[i].begin(),adjVector[i].end());
  }
  grafo.adjVector = adjVector;

  ifstream nomes(refere.c_str());
  string str;
  while(getline(nomes,str)){
    str.erase(remove(str.begin(), str.end(), ','), str.end());
    replace(str.begin(), str.end(), ' ', '_');
    stringstream ss(str);
    int vertice;
    string nome;
    while (ss >> vertice >> nome){
      replace(nome.begin(), nome.end(), '_', ' ');
      referentes[vertice] = nome;
    }
  }
  grafo.referentes = referentes;
  return grafo;
}

void dijkstraVector(grafoVectorComPeso grafo, string start, string objective="-1"){
  int inicio = 0;
  int objetivo = -1;
  for(int i=1;i<=grafo.numVertices;i++){
    if (grafo.referentes[i]==start){
      inicio = i;
    }
  }
  if(objective != "-1"){
    for(int i=1;i<=grafo.numVertices;i++){
      if (grafo.referentes[i]==objective){
        objetivo = i;
      }
    }
  }
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
  distancia[inicio] = 0;
  //Define o pai da origem = -1
  pai[inicio] = -1;
  //Cria o conjunto de vértices a serem percorridos (vasp)
  set< pair<double, int> > vasp;
  //Insere o par distância origem no conjunto vasp
  vasp.insert(make_pair(distancia[inicio], inicio));
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
        if(vizinho == 10){
        }
        //Altera pai[i]
        pai[vizinho] = current_vertex;
        //Caso tenha achado um caminho melhor, ajusta a distância e insere no conjunto
        vasp.insert(make_pair(distancia[vizinho], vizinho));

      }
    }
  }
  //Cria um inteiro x
  int x=0;
  //Se o usuário definir um vetor objetivo
  if(objetivo == -1 && !control){
    //Para todos os vértices do grafo
    for (int i = 1; i < grafo.numVertices+1; i++){
      //x será seu novo vértice objetivo
      x = i;
      //Percorre x até chegar no vértice inicial
      if(x!=inicio){
        //Imprime o caminho de x até start
        cout<<"Vértice: "<< grafo.referentes[x]<<", Caminho até "<<grafo.referentes[inicio]<<": ";
        //Se tiver um caminho até x
        if (distancia[x] != INF){
          cout<<"[";
          while(x != inicio){
            //Cálculo a distância de x até start
            cout<<grafo.referentes[x]<<", ";
            //x agora é quem descobriu x
            x = pai[x];
          }
          cout<<grafo.referentes[x]<<"], "<<"Distância entre eles: ";
          printf("%.15g\n", distancia[i]);
        }
        //Se não tiver um caminho de x até start
        else{
          //Imprime INFINITO
          cout<<"[], "<<"Distância entre eles: "<<"INFINITO"<<endl;
        }
      }
    }
  }
  //Se tiver um objetivo
  else{
    //Se não tiver nenhum peso negativo
    if(!control){
      x = objetivo;
      //Enquanto o objetivo não for o começo
      if(x!=inicio){
        //Imprime o caminho até o começo
        cout<<"Vértice: "<< grafo.referentes[x]<<", Caminho até "<<grafo.referentes[inicio]<<": ";
        //Se tiver um caminho até x
        if (distancia[x] != INF){
          cout<<"[";
          while(x != inicio){
            //Cálculo a distância de x até start
            cout<<grafo.referentes[x]<<", ";
            //x agora é quem descobriu x
            x = pai[x];
          }
          cout<<grafo.referentes[x]<<"], "<<"Distância entre eles: ";
          printf("%.15g\n", distancia[objetivo]);
        }
        //Se não tiver um caminho de x até start
        else{
          //Imprime INFINITO
          cout<<"[], "<<"Distância entre eles: "<<"INFINITO"<<endl;
        }
      }
    }
  }
}

double primVector(grafoVectorComPeso grafo, string inicial, bool salve=false){
  int origem = 1;
  for(int i=1;i<=grafo.numVertices;i++){
    if (grafo.referentes[i]==inicial){
      origem = i;
    }
  }
  //Cria um vector de custo de tamanho número de vértices
  vector <double> custo(grafo.numVertices+1, INF);
  //Define o custo da origem = 0
  custo[origem] = 0;
  int *grau;
  //Inicializa o vetor grau
  grau = new int[grafo.numVertices+1]();
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
    //Define p como a precisão do arquivo mstFile;
    streamsize p = mstFile.precision();
    //Adiciona todos os dados da mst
    //Altera a precisão do mstFile
    mstFile.precision(15);
    mstFile << "Custo total: "<<custo_total<<endl;
    //Retorna a precisão a precisão inicial do arquivo.
    mstFile.precision(p);
    for(int i=1;i<grafo.numVertices+1;i++){
      if (pai[i] != -1){
        mstFile<< "Vértice: "<< grafo.referentes[i] <<", Nível: "<< nivel[i]<<", Pai: "<< grafo.referentes[pai[i]]<<endl;
        //Calcula o grau de cada vértice
        if(nivel[i]!=0){
          grau[i]++;
          grau[pai[i]]++;
        }
      }
    }
    //Fecha o arquivo
    mstFile.close();
  }
  int maior = 0;
  int pessoa = 0;
  for(int i=1;i<=grafo.numVertices;i++){
    if(grau[i]>maior){
      maior = grau[i];
      pessoa = i;
    }
  }
  cout<<"Abaixo estão os graus máximos do grafo de colaboradores: "<<endl;
  cout<<"Colaborador: "<< grafo.referentes[pessoa]<<", Grau: "<<maior<<endl;
  grau[pessoa] = 0;
  maior = 0;
  for(int i=1;i<=grafo.numVertices;i++){
    if(grau[i]>maior){
      maior = grau[i];
      pessoa = i;
    }
  }
  cout<<"Colaborador: "<< grafo.referentes[pessoa]<<", Grau: "<<maior<<endl;
  grau[pessoa] = 0;
  maior = 0;
  for(int i=1;i<=grafo.numVertices;i++){
    if(grau[i]>maior){
      maior = grau[i];
      pessoa = i;
    }
  }
  cout<<"Colaborador: "<< grafo.referentes[pessoa]<<", Grau: "<<maior<<endl;
  //Retorna o custo total da mst
  return custo_total;
}

int main(){
  grafoVectorComPeso vector = constroiVectorComPeso("rede_colaboracao.txt", "rede_colaboracao_vertices.txt");
  clock_t start = clock();
  //getchar();
  cout<<primVector(vector,"Edsger W. Dijkstra", true)<<endl;
  clock_t end = clock();
  cout<< (double)(end-start)/CLOCKS_PER_SEC<< " segundos."<<endl;
}
