# Graph-Library
A library constructed using c++17 and some others libraries made by Bruno Dantas and Eduardo Guedes.

## Table of Contents:
- [How to use](#how-to-use)
  - [Method constroiVector](#method-constroiVector)
  - [Method constroiVectorComPeso](#method-constroiVectorComPeso)  
  - [Method constroiMatriz](#method-constroiMatriz)
  - [Method constroiMatrizComPeso](#method-constroiMatrizComPeso)
- [Representations](#representations)
  - [Adjacency Vertex](#adjacency-vertex)
  - [Adjacency Matrix](#adjacency-matrix)
- [Functions](#functions)
  - [BFS](#bfs)
  - [DFS](#dfs)
  - [Connected Components](#connected-components)
  - [Diameter](#diameter)
  - [Distance](#distance)
  - [Dijkstra](#dijkstra)
  - [Prim](#prim)
  - [Eccentricity](#eccentricity)
- [Extra](#extra)
- [Case Studies](#case-studies)


## How to use
The library have two constructor methods that return us a type grafo. This type contains the number of Vertex and the graph built using the required structure.

### Method constroiVector
This method construct the representation of [Adjacency Vector](#adjacency-vector) and write every information of the graph in a txt file named (graphfile). This method returns a grafoVector type, so, be careful on define the variables.

### Method constroiVectorComPeso
Like the [constroiVector](#method-constroiVector), this method construct the representation of [Adjacency Vector](#adjacency-vector) and write every information of the graph in a txt file named (graphfile). The main difference is that the data structure is representes using Array of Vector and the Vector contains a pair (neighbor, weight).This method returns a grafoVectorComPeso type. 

### Method constroiMatriz
This method construct the representation of [Adjacency Matrix](#adjacency-matrix) and like the [Method constroiVector](#method-constroiVector) it writes a txt file named graphfile. This method returns a grafoMatriz type.

### Method constroiMatrizComPeso
Like the [constroiVector](#method-constroiVector), this method construct the representation of [Adjacency Matrix](#adjacency-matrix) and write every information of the graph in a txt file named (graphfile). The main difference is that the data structure is representes using 2D array of integers, that the integer represent the weight between the vertex.This method returns a grafoMatrizComPeso type. 

## Representations
This library can represent graphs using Adjacency Vector and Adjacency Matrix.

### Adjacency Vector
This representation was built using the std vector and the simple array in c++. Also knowed as Array of vector.
So, the user can add the max degree without problems about memory allocation.

### Adjacency Matrix
This representation was built using a 2D array, so it's necessary to determinate the number of elements (number of vertex) to be used in this data structure.

## Functions
Like every graph, there are some basic functions (All of the functions bellow were implemented on both representations supported by the library) . There are:

### BFS
The BFS (Breadth First Search) can traverse the graph from the given node (start) and run every node connected to this vertex. This function can give us the spanning tree by giving the father (who discovered the node) and it's degree (father's degree +1). This function can also give us the shortest path from the node start to a vertex. This implementation have a boolean that enable the user save a txt file containing the spanning tree.

### DFS
The DFS (Depth First Search) can traverse the graph like the [BFS](#bfs) can give us the spanning tree but different from this one, it explores as far as possible in a branch and then come back to a fixed point.This implementation have a boolean that enable the user save a txt file containing the spanning tree.

### Connected Components
This function give us the number of Connected Components of a graph sorted by their size and the vertex that belongs to a specific component. The function works running a simple bfs in a vertex, and after, inside of a for loop, it's just check if the next one was visited. If yes, just check the next. If no, run the bfs for this vertex. And it's just repeat the process until the number of vertex is the maximum.This implementation have a boolean that enable the user save a txt file containing the Connected Components sorted in a decrescent way.

### Diameter
This function returns the diameter of a graph (The maximum minimum path between two vertex). So, the implementation consisted in run a [BFS](#bfs) for each vertex in the graph, so, it's possible to measure the maximum distance between two vertex starting from every nodes. 

### Distance
The Distance is the shortest path from a vertex a to a vertex b. So, the implementation consisted just in use a simple [BFS](#bfs) and measure the distance between a and b.

### Dijkstra
The Dijkstra is a way to traverse the graph like the [BFS](#bfs) and [DFS](#dfs), but the difference is that the algorithm choose the shortest path between a vertex and its neighbors. This implementation also return us the distance and path to every vertex in the graph (if there's no argument objective) or return just the distance and path to a vertex objective. OBS: only workable if your graph is weighted and its weight are positive.

### Prim
The Prim is a algorithm able to build a MST (Minimum Spanning Tree).It's like the [BFS](#bfs) and [DFS](#dfs) spanning tree, but the difference is that the algorithm choose the shortest cost of a edge to traverse the graph. This implementation have a bool "salve" that enable the user save the MST in a external txt file. In this file contais the MST total cost, every vertex and their parent/level.

### Eccentricity
The Eccentricity is the longest shortest path between 2 vertex. In this implementation, it calculates the Eccentricity of a given vertex, so it just uses the [Dijkstra](#dijkstra) algorithm and pick up the longest distance in the distancia vector(Vector that contains the information of every distance from start vertex).

## Extra
The [colaboradores.cpp](https://github.com/DantasB/Graph-Library/blob/master/colaboradores.cpp) have the same implementation of the [graph.cpp](https://github.com/DantasB/Graph-Library/blob/master/grafo.cpp), but the data structure uses strings instead of integers. That's why one of the cases given by our professor had this requirement.

## Case Studies:
"Below you can see all the case studies used"
- Unweighted graph:
  - [as_graph.txt](https://www.cos.ufrj.br/~daniel/grafos/data/as_graph.txt)
  - [dblp.txt](https://www.cos.ufrj.br/~daniel/grafos/data/dblp.txt)
  - [live_journal.txt](https://www.cos.ufrj.br/~daniel/grafos/data/live_journal.txt)
- Weighted graph:
  - [grafo_1.txt](https://www.cos.ufrj.br/~daniel/grafos/data/grafo_1.txt)
  - [grafo_2.txt](https://www.cos.ufrj.br/~daniel/grafos/data/grafo_2.txt)
  - [grafo_3.txt](https://www.cos.ufrj.br/~daniel/grafos/data/grafo_3.txt)
  - [grafo_4.txt](https://www.cos.ufrj.br/~daniel/grafos/data/grafo_4.txt)
  - [grafo_5.txt](https://www.cos.ufrj.br/~daniel/grafos/data/grafo_5.txt)
  - [rede_colaboracao.txt](https://www.cos.ufrj.br/~daniel/grafos/data/rede_colaboracao.txt)
  - [rede_colaboracao_vertices.txt](https://www.cos.ufrj.br/~daniel/grafos/data/rede_colaboracao_vertices.txt)

