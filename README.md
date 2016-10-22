# Graph algorithms
A collection of graph algorithms implemented in C++.

## Build

To build the network analyser run:
```
g++ -std=c++11 -O2 analyse.cpp -o analyse
```

## Run

Here is an example of running the network analyser:
```
$ ./analyse < network.graphml
Graph size: |V| = 1628, |E| = 53406.
Total number of reachable pairs of vertices: 2648756
Total distance between reachable pairs of vertices: 6759254
Diameter: 5
Accumulated radius: 6492
Runtime (microseconds): 205514
```
Here the _accumulated radius_ is the sum of maximum distances from each node.
