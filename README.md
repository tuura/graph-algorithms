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
Radius: 3
Diameter: 5
Accumulated eccentricity: 6492
Runtime (microseconds): 190933
```
Here the _accumulated eccentricity_ is the sum of maximum distances from each node.

## Edge probabilities

You can specify the *edge probability* P that allows you to sample random subgraphs
from the analysed graph using the command-line flag `--edge-probability=P`. For
example:

```
$ ./analyse --edge-probability=0.9 < graph.graphml
Graph size: |V| = 1628, |E| = 48204.
Total number of reachable pairs of vertices: 2648756
Total distance between reachable pairs of vertices: 6910228
Radius: 3
Diameter: 6
Accumulated eccentricity: 6839
Runtime (microseconds): 176927
```

As you can see, the sampled subgraph contains only 48204 edges, which is
90.25% of all 53406 edges in the graph.

To write the resulting subgraph into a GraphML file, use command-line flag
`--write-file=FILENAME`, for example:
```
$ ./analyse --edge-probability=0.9 --write-file=subgraph.graphml < graph.graphml
```
