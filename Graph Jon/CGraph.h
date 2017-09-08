#ifndef CGRAPH_H
#define CGRAPH_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

using namespace std;

struct CNode{
    double x;
    double y;
    double father_x;
    double father_y;

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
        vector< vector<double> > matrix_ad;
        
        CGraph(int number_nodes);

        bool SearchNode(int x, int y);
        bool GenerateNodes();
        bool GenerateEdges();
        bool SearchEdge(int index_node_a, int index_node_b);
        CNode SearchNode1(int x, int y);
        double Distance(int index_node_a, int index_node_b);

        void convToMatrix();

        void searchBlindAux();
        void searchBlind(vector<vector<double>>,vector<CNode> &,int,int,int,int);
        int dist_min(int [], bool [],vector<CNode>);




};

#endif // CGRAPH_H
