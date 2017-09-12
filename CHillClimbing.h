#ifndef CHILLCLIMBING_H
#define CHILLCLIMBING_H

#include <vector>
#include "CGraph.h"

struct CVisit{
    int node_index;
    double distance_final_node;
    vector<int> path_indices;

    CVisit(int node_index, double distance_final_node);
    bool Push(int element);
    bool SearchPathIndices(int element);
};

// ==================================================

class CHillClimbing{
    private:
        vector<CVisit> new_visits;

    public:
        CGraph* m_graph;
        vector<CVisit> m_visit_stack;

        CHillClimbing(CGraph* graph);
        void PrintVisitStack();
        bool SortVisitStack();
        bool SortNewVisits();
        bool SearchPath(int starting_node_index, int final_node_index, vector<int> *solution);
};

#endif // CHILLCLIMBING_H
