# Graph-Library
A library constructed using c++17 and some others libraries made by Bruno Dantas and Eduardo Guedes.

## Table of Contents:
- [How to use](#how-to-use)
  - [Method constroiVector](#method-constroiVector)
  - [Method constroiMatriz](#method-constroiMatriz)
- [Representations](#representations)
  - [Adjacency Vertex](#adjacency-vertex)
  - [Adjacency Matrix](#adjacency-matrix)
- [Functions](#functions)
  - [BFS](#bfs)
  - [DFS](#dfs)
  - [Connected Components](#connected-components)
  - [Diameter](#diameter)
  - [Distance](#distance)

## How to use
The library have two constructor methods that return us a type grafo. This type contains the number of Vertex and the graph built using the required structure.

### Method constroiVector
This method construct the representation of [Adjacency Vector](#adjacency-vector) and write every information of the graph in a txt file named (graphfile). This method returns a grafoVector type, so, be careful on define the variables.

### Method constroiMatriz
This method construct the representation of [Adjacency Matrix](#adjacency-matrix) and like the [Method constroiVector](#method-constroiVector) it writes a txt file named graphfile. This method returns a grafoMatriz type.

## Representations
This library can represent graphs using Adjacency Vector and Adjacency Matrix.

### Adjacency Vector
This representation was built using the std vector and the simple array in c++. Also knowed as Array of vector.
So, the user can add the max degree without problems about memory allocation.

### Adjacency Matrix
This representation was built using a 2D array, so it's necessary to determinate the number of elements (number of vertex) to be used in this data structure.

## Functions
Like every graph, there are some basic functions (All of the functions bellow were implemented on both representations supported by the library . There are:

### BFS
The BFS (Breadth First Search) can traverse the graph from the given node (start) and run every node connected to this vertex. This function can give us the spanning tree by giving the father (who discovered the node) and it's degree (father's degree +1). This function can also give us the shortest path from the node start to a vertex.

### DFS
The DFS (Depth First Search) can traverse the graph like the [BFS](#bfs) can give us the spanning tree but different from this one, it explores as far as possible in a branch and then come back to a fixed point.

### Connected Components
This function give us the number of Connected Components of a graph sorted by their size and the vertex that belongs to a specific component. The function works running a simple bfs in a vertex, and after, inside of a for loop, it's just check if the next one was visited. If yes, just check the next. If no, run the bfs for this vertex. And it's just repeat the process until the number of vertex is the maximum.

### Diameter
This function returns the diameter of a graph (The maximum minimum path between two vertex). So, the implementation consisted in run a [BFS](#bfs) for each vertex in the graph, so, it's possible to measure the maximum distance between two vertex starting from every nodes. 

### Distance
The Distance is the shortest path from a vertex a to a vertex b. So, the implementation consisted just in use a simple [BFS](#bfs) and measure the distance between a and b.

