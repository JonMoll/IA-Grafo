#ifndef CGRAPH_H
#define CGRAPH_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>

using namespace std;

struct CNode{
    double x;
    double y;

    CNode(double x, double y);
};

struct CDistance{
    int index_node_a;
    int index_node_b;
    double distance;

    CDistance(int index_node_a, int index_node_b, double distance);
};

// ==================================================

class CGraph{
    public:
        int m_number_nodes;
        vector<CNode> m_nodes;
        vector< vector<CDistance> > m_distances;

        CGraph(int number_nodes, bool use_test);
        void Test();

        bool SearchNode(int x, int y);
        bool GenerateNodes();
        bool GenerateEdges();
        bool SearchEdge(int index_node_a, int index_node_b);
        double Distance(int index_node_a, int index_node_b);
};

#endif // CGRAPH_H
