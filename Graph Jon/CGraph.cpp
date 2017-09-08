#include "CGraph.h"

CNode::CNode(double x, double y){
    this->x = x;
    this->y = y;
    father_x=0;
    father_y=0;
}

CDistance::CDistance(int index_node_a, int index_node_b, double distance){
    this->index_node_a = index_node_a;
    this->index_node_b = index_node_b;
    this->distance = distance;
}

// ==================================================

CGraph::CGraph(int number_nodes){
    m_number_nodes = number_nodes;

    GenerateNodes();

    for(int i = 0; i < number_nodes; i++)
    m_distances.push_back(vector<CDistance>());
    
    
    for(int i = 0; i < number_nodes; i++)
    matrix_ad.push_back(vector<double>(number_nodes,0));

    GenerateEdges();
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
CNode CGraph::SearchNode1(int x, int y){
    for(int i = 0; i < m_nodes.size(); i++){
        if(m_nodes[i].x==x and m_nodes[i].y==y){
            return m_nodes[i];
        }
    }
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

void CGraph::searchBlindAux(){

    int rand1= rand() % m_nodes.size();
    int rand2= rand() % m_nodes.size();
    int begin_x= m_nodes[rand1].x;
    int begin_y= m_nodes[rand1].y;
    
    int end_x= m_nodes[rand2].x;
    int end_y= m_nodes[rand2].y;

    cout<<"De ("<<begin_x<<" , "<<begin_y<<")";
    cout<<"A ("<<end_x<<" , "<<end_y<<")"<<endl;

    searchBlind(matrix_ad,m_nodes,begin_x,begin_y,end_x,end_y);
    
}

void CGraph::searchBlind(vector<vector<double>> mtrx,vector<CNode> &vect ,int inx,int iny,int endx,int endy){
    int v;
    int dist[vect.size()]; int aux1;
    bool status[vect.size()];
    vector<CNode> path;

    for (int i = 0; i < vect.size(); i++)
        dist[i] = INT_MAX, status[i] = false;
    for(int j=0;j<vect.size();j++)
        if( vect[j].x==inx and vect[j].y==iny)
            aux1=j;
    dist[aux1] = 0;
   
    
    for (int i = 0; i < vect.size(); i++){
        int aux2 = dist_min(dist, status,vect);
        status[aux2] = true;
        for ( v = 0; v <vect.size(); v++){
        if (!status[v] and mtrx[aux2][v] and dist[aux2]!= INT_MAX 
             and dist[aux2]+mtrx[aux2][v] < dist[v]){
                dist[v] = dist[aux2] + mtrx[aux2][v];
                vect[v].father_x=vect[aux2].x;
                vect[v].father_y=vect[aux2].y;

            }
        // cout<<"vect: "<<vect[v].x<<" ";
        // if(vect[v].x==endx and vect[v].y==endy){
        //     break;
        // }
    }
    // cout<<endl;
    // if(vect[v].x!=endx and vect[v].y!=endy){
    //     cout<<"Error no es posible encontrar camino"<<endl;
    //     return;
    // }     
    

    }
    
    CNode tmp=SearchNode1(endx,endy);
    path.push_back(CNode(tmp.x,tmp.y));
    while(tmp.x!=inx and tmp.y!=iny ){
        // cout<<"data "<<tmp->m_data << " ";
        // cout<<"father "<<tmp->father << " - ";
        tmp=SearchNode1(tmp.father_x,tmp.father_y);
        path.push_back(CNode(tmp.x,tmp.y));
        }
    // print();
    cout<<endl<<"CAMINO CIEGO: "<<endl;
    for(int i=path.size()-1;i>=0;i--)
        cout<<"( "<<path[i].x<<" , "<<path[i].y<<")\n";
        cout<<endl;
    // print2(dist,in,vect);
}

    

int CGraph::dist_min(int dist[], bool status[],vector<CNode> vect){
    int min = INT_MAX, min_index;
    for (int i = 0; i < vect.size(); i++)
    if (status[i] == false and dist[i] <= min)
    min = dist[i], min_index = i;
    return min_index;
}



void CGraph::convToMatrix(){


for(int i=0;i<m_number_nodes;i++){
    int node_a,node_b;
    for(int j=0;j<m_distances[i].size(); j++){
        node_a=m_distances[i][j].index_node_a;
        node_b = m_distances[i][j].index_node_b;
        double distance = m_distances[i][j].distance;
        matrix_ad[node_a][node_b]=distance;
    }
}


    // for(int i = 0; i < m_number_nodes; i++){
    //     for(int j = 0; j < m_number_nodes; j++)
    //         cout<<matrix_ad[i][j]<<" ";
    //     cout<<endl;
    // }


}