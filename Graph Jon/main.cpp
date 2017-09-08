#include "CGraph.h"

int main()
{
    srand(time(NULL));

    CGraph my_graph(30);

    for(int i = 0; i < my_graph.m_number_nodes; i++){
        for(int j = 0; j < my_graph.m_distances[i].size(); j++){
            int index_node_a = my_graph.m_distances[i][j].index_node_a;
            int index_node_b = my_graph.m_distances[i][j].index_node_b;
            double distance = my_graph.m_distances[i][j].distance;

            int node_a_x = my_graph.m_nodes[index_node_a].x;
            int node_a_y = my_graph.m_nodes[index_node_a].y;

            int node_b_x = my_graph.m_nodes[index_node_b].x;
            int node_b_y = my_graph.m_nodes[index_node_b].y;

            cout << "( " << node_a_x << ", " << node_a_y << " )"
                 << "<-----" << distance << "----->"
                 << "( " << node_b_x << ", " << node_b_y << " )"
                 << endl;
        }

        

        cout << endl;
    }

    my_graph.convToMatrix();
    my_graph.searchBlindAux();

    return 0;
}
