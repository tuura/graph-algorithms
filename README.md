# Graph algorithms
A collection of graph algorithms implemented in C++. What's included:
* `graph.h` defines a simple data structure for graphs and several standard algorithms.
* `parse.h` provides a naive line-by-line parser for `.graphml` files. Beware: it only works
for a small subset of GraphML.
* `analyse.cpp` is a graph analyser, computing several metrics of a `.graphml` graph given
in the standard input.

## Build

To build the graph analyser run:
```
g++ -std=c++11 -O2 analyse.cpp -o analyse
```

## Run

Here is an example of running the graph analyser:
```
$ ./analyse < graph.graphml
Graph size: |V| = 1628, |E| = 53406.
Total number of reachable pairs of vertices: 2648756
Total distance between reachable pairs of vertices: 6759254
Diameter: 5
Accumulated radius: 6492
Runtime (microseconds): 205514
```
Here the _accumulated radius_ is the sum of maximum distances from each node.
