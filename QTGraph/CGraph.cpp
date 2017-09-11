#include "CGraph.h"

CNode::CNode(double x, double y){
    this->x = x;
    this->y = y;
}

CDistance::CDistance(int index_node_a, int index_node_b, double distance){
    this->index_node_a = index_node_a;
    this->index_node_b = index_node_b;
    this->distance = distance;
}

// ==================================================

CGraph::CGraph(int number_nodes, bool use_test){
    if(!use_test){
        m_number_nodes = number_nodes;

        GenerateNodes();

        for(int i = 0; i < number_nodes; i++)
            m_distances.push_back(vector<CDistance>());

        GenerateEdges();
    }
    else
        Test();
}

void CGraph::Test(){
    m_number_nodes = 8;

    m_nodes.emplace_back(2, 3);
    m_nodes.emplace_back(5, 7);
    m_nodes.emplace_back(6, 2);
    m_nodes.emplace_back(9, 2);
    m_nodes.emplace_back(10, 6);
    m_nodes.emplace_back(12, 2);
    m_nodes.emplace_back(13, 7);
    m_nodes.emplace_back(18, 6);

    for(int i = 0; i < m_number_nodes; i++){
        m_distances.push_back(vector<CDistance>());
    }

    m_distances[0].emplace_back(0, 1, Distance(0, 1));
    m_distances[0].emplace_back(0, 2, Distance(0, 2));

    m_distances[1].emplace_back(1, 0, Distance(1, 0));
    m_distances[1].emplace_back(1, 2, Distance(1, 2));
    m_distances[1].emplace_back(1, 4, Distance(1, 4));

    m_distances[2].emplace_back(2, 0, Distance(2, 0));
    m_distances[2].emplace_back(2, 1, Distance(2, 1));
    m_distances[2].emplace_back(2, 3, Distance(2, 3));

    m_distances[3].emplace_back(3, 2, Distance(3, 2));
    m_distances[3].emplace_back(3, 4, Distance(3, 4));
    m_distances[3].emplace_back(3, 5, Distance(3, 5));

    m_distances[4].emplace_back(4, 1, Distance(4, 1));
    m_distances[4].emplace_back(4, 3, Distance(4, 3));
    m_distances[4].emplace_back(4, 6, Distance(4, 6));

    m_distances[5].emplace_back(5, 3, Distance(5, 3));
    m_distances[5].emplace_back(5, 7, Distance(5, 7));

    m_distances[6].emplace_back(6, 4, Distance(6, 4));
    m_distances[6].emplace_back(6, 7, Distance(6, 7));

    m_distances[7].emplace_back(7, 6, Distance(7, 6));
    m_distances[7].emplace_back(7, 5, Distance(7, 5));
}

bool CGraph::SearchNode(int x, int y){
    for(int i = 0; i < m_nodes.size(); i++){
        if(m_nodes[i].x == x && m_nodes[i].y == y)
            return true;
    }

    return false;
}

bool CGraph::GenerateNodes(){
    int middle = m_number_nodes / 2;
    int subset_size = m_number_nodes / 4;

    int begin_x = 0;
    int begin_y = 0;

    for(int i = 0; i < 2; i++){
        begin_y = 0;

        for(int j = 0; j < 2; j++){

            for(int k = 0; k < subset_size; k++){ // Generando puntos del subconjunto
                int rand_x = begin_x + (rand() % middle);
                int rand_y = begin_y + (rand() % middle);

                while (SearchNode(rand_x, rand_y)){ // Para no tener puntos iguales
                    rand_x = begin_x + (rand() % middle);
                    rand_y = begin_y + (rand() % middle);
                }

                m_nodes.emplace_back(rand_x, rand_y);
            }

            begin_y += middle;
        }

        begin_x += middle;
    }

    return true;
}

bool CGraph::SearchEdge(int index_node_a, int index_node_b){
    for(int i = 0; i < m_distances[index_node_a].size(); i++){
        if(m_distances[index_node_a][i].index_node_b == index_node_b)
            return true;
    }

    return false;
}

double CGraph::Distance(int index_node_a, int index_node_b){
    double subtraction_1 = m_nodes[index_node_a].x - m_nodes[index_node_b].x;
    double subtraction_2 = m_nodes[index_node_a].y - m_nodes[index_node_b].y;

    return pow(pow(subtraction_1, 2) + pow(subtraction_2, 2), 0.5);
}

bool CGraph::GenerateEdges(){
    int subset_size = m_number_nodes / 4;

    for(int i = 0; i < m_nodes.size(); i += subset_size){
        for(int j = 0; j < subset_size; j++){
            for(int k = 0; k < 2; k++){
                int rand_index_node = i + (rand() % subset_size);

                while(rand_index_node == i+j || SearchEdge(i+j, rand_index_node) || m_distances[rand_index_node].size() >= 4)
                    rand_index_node = i + (rand() % subset_size);

                int current_distance = Distance(i+j, rand_index_node);;

                m_distances[i+j].emplace_back(i+j, rand_index_node, current_distance);
                m_distances[rand_index_node].emplace_back(rand_index_node, i+j, current_distance);
            }
        }
    }

    int index_current_subset = 0;

    for(int i = 0; i < 3; i++){ // Interconectando sub conjuntos
        int rand_index_node_1 = index_current_subset + (rand() % subset_size);
        index_current_subset += subset_size;
        int rand_index_node_2 = index_current_subset + (rand() % subset_size);

        int current_distance = Distance(rand_index_node_1, rand_index_node_2);

        m_distances[rand_index_node_1].emplace_back(rand_index_node_1, rand_index_node_2, current_distance);
        m_distances[rand_index_node_2].emplace_back(rand_index_node_2, rand_index_node_1, current_distance);
    }

    return true;
}
