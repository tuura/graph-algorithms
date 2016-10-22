#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

#include "graph.h"
#include "parse.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char *args[])
{
    ios::sync_with_stdio(false);
    Graph g(readGraph());
    cout << "Graph size: |V| = " << g.size() << ", |E| = " << g.countEdges() << ".\n";

    high_resolution_clock::time_point start = high_resolution_clock::now();

    int sum = 0;
    int pairs = 0;
    int diameter = 0;
    int accumulatedRadius = 0;
    for(int i = 0; i < g.size(); i++)
    {
        int radius = g.runBFS(i);
        accumulatedRadius += radius;
        diameter = max(diameter, radius);
        for(int j = 0; j < g.size(); j++)
            if (g.distance[j] != oo)
            if (g.distance[j] != 0)
            {
                pairs++;
                sum += g.distance[j];
            }
    }

    high_resolution_clock::time_point end = high_resolution_clock::now();

    cout << "Total number of reachable pairs of vertices: " << pairs << endl;
    cout << "Total distance between reachable pairs of vertices: " << sum << endl;
    cout << "Diameter: " << diameter << endl;
    cout << "Accumulated radius: " << accumulatedRadius << endl;

    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Runtime (microseconds): " << duration << endl;

    return 0;
}