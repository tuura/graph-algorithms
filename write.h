#pragma once
#include <cstdio>
#include <vector>

#include "graph.h"

using namespace std;

// Write a .graphml file to the standard input.
void writeGraph(const Graph &g)
{
	puts("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	puts("<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">");
	puts("<graph id=\"G\" edgedefault=\"undirected\">");

	for(int i = 0; i < g.c.size(); i++) printf("  <node id=\"%d\">\n  </node>\n", i + 1);

	int cnt = 0;
	for(int i = 0; i < g.c.size(); i++)
	for(int j = 0; j < g.c[i].size(); j++)
	{
		int i2 = g.c[i][j];
		if (i2 < i) continue;

		cnt++;
		printf("  <edge id=\"%d\" source=\"%d\" target=\"%d\">\n  </edge>\n", cnt, i + 1, i2 + 1);
	}
  	puts("</graph>");
	puts("</graphml>");
}
