#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cstdio>

#include "graph.h"
#include "parse.h"
#include "write.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char *args[])
{
    double edgeProbability = 1.0, ep;
    bool writeFile = false;
    char filename[100];
    if (argc >= 2)
    {
        if (sscanf(args[1], "--edge-probability=%lf", &ep) == 1) edgeProbability = ep;
        if (argc == 3)
        {
            if (sscanf(args[2], "--write-file=%s", filename) == 1) writeFile = true;
        }
    }

    ios::sync_with_stdio(false);
    Graph g(readGraph(edgeProbability));
    cout << "Graph size: |V| = " << g.size() << ", |E| = " << g.countUndirectedEdges() << ".\n";

    high_resolution_clock::time_point start = high_resolution_clock::now();

    int sum = 0;
    int pairs = 0;
    int radius = oo;
    int diameter = 0;
    int accumulatedEccentricity = 0;
    for(int i = 0; i < g.size(); i++)
    {
        int eccentricity = g.runBFS(i);
        accumulatedEccentricity += eccentricity;
        radius   = min(radius  , eccentricity);
        diameter = max(diameter, eccentricity);
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
    cout << "Radius: " << radius << endl;
    cout << "Diameter: " << diameter << endl;
    cout << "Accumulated eccentricity: " << accumulatedEccentricity << endl;

    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Runtime (microseconds): " << duration << endl;

    if (writeFile)
    {
        puts("\nWriting file...");
        freopen(filename, "w", stdout);
        writeGraph(g);
        fflush(stdout);
    }

    return 0;
}
