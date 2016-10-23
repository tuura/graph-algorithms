#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "graph.h"

using namespace std;

// Mapping between node names and id numbers
map<string, int> ids;
vector<string> names;

// Register/lookup a node name
int s2i(string s)
{
	if (ids.count(s)) return ids[s];
	int newId = ids.size();
	names.push_back(s);
	return ids[s] = newId;
}

// Naive line-by-line parser of .graphml files from the standard input.
// TODO: improve to handle general .graphml files (use a standard library?)
// WARNING: the current version will crash on general .graphml files
Graph readGraph()
{
    Graph g;
    ids.clear();
    names.clear();
	string s;

	while(getline(cin, s))
		if (s.find("<node") != string::npos)
		{
			size_t posId = s.find("id=");
			size_t lenId = s.find('\"', posId + 4) - posId - 4;
			s2i(s.substr(posId + 4, lenId)); // register the node's name
		}
		else
		if (s.find("<edge") != string::npos)
		{
			size_t posSource = s.find("source=");
			size_t posTarget = s.find("target=");
			size_t lenSource = s.find('\"', posSource + 8) - posSource - 8;
			size_t lenTarget = s.find('\"', posTarget + 8) - posTarget - 8;

			int idSource = s2i(s.substr(posSource + 8, lenSource));
			int idTarget = s2i(s.substr(posTarget + 8, lenTarget));

			int newGraphSize = max(idSource + 1, idTarget + 1);
			if (g.size() < newGraphSize) g.resize(newGraphSize);

            g.connect(idSource, idTarget);
            g.connect(idTarget, idSource);
		}

	return g;
}
