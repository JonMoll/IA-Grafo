#include "CHillClimbing.h"

CVisit::CVisit(int node_index, double distance_final_node){
    this->node_index = node_index;
    this->distance_final_node = distance_final_node;
}

bool CVisit::Push(int element){
    path_indices.push_back(element);

    return true;
}

bool CVisit::SearchPathIndices(int element){
    for(int i = 0; i < path_indices.size(); i++){
        if(path_indices[i] == element)
            return true;
    }

    return false;
}

// ==================================================

CHillClimbing::CHillClimbing(CGraph* graph){
    m_graph = graph;
}

void CHillClimbing::PrintVisitStack(){
    cout << "==================================================" << endl
         << "VISIT STACK:" << endl << endl;

    for(int i = 0; i < m_visit_stack.size(); i++){
        cout << "[ " << m_visit_stack[i].node_index << " ] "
             << "Distance final node: " << m_visit_stack[i].distance_final_node << endl
             << "[ " << m_visit_stack[i].node_index << " ] "
             << "Path indices (Size " << m_visit_stack[i].path_indices.size() << "): ";

        for(int j = 0; j < m_visit_stack[i].path_indices.size(); j++)
            cout << m_visit_stack[i].path_indices[j] << " ";

        cout << endl << endl;
    }

    cout << "==================================================" << endl;
}

bool CHillClimbing::SortVisitStack(){
    CVisit temp(0, 0);

    for(int j = 0; j < m_visit_stack.size(); j++){
        for(int i = 0; i < m_visit_stack.size()-1; i++){
            if(m_visit_stack[i].distance_final_node < m_visit_stack[i+1].distance_final_node){
                temp.node_index = m_visit_stack[i].node_index;
                temp.distance_final_node = m_visit_stack[i].distance_final_node;
                temp.path_indices = m_visit_stack[i].path_indices;

                m_visit_stack[i].node_index = m_visit_stack[i+1].node_index;
                m_visit_stack[i].distance_final_node = m_visit_stack[i+1].distance_final_node;
                m_visit_stack[i].path_indices = m_visit_stack[i+1].path_indices;

                m_visit_stack[i+1].node_index = temp.node_index;
                m_visit_stack[i+1].distance_final_node = temp.distance_final_node;
                m_visit_stack[i+1].path_indices = temp.path_indices;
            }
        }
    }

    return true;
}

bool CHillClimbing::SortNewVisits(){
    CVisit temp(0, 0);

    for(int j = 0; j < new_visits.size(); j++){
        for(int i = 0; i < new_visits.size()-1; i++){
            if(new_visits[i].distance_final_node < new_visits[i+1].distance_final_node){
                temp.node_index = new_visits[i].node_index;
                temp.distance_final_node = new_visits[i].distance_final_node;
                temp.path_indices = new_visits[i].path_indices;

                new_visits[i].node_index = new_visits[i+1].node_index;
                new_visits[i].distance_final_node = new_visits[i+1].distance_final_node;
                new_visits[i].path_indices = new_visits[i+1].path_indices;

                new_visits[i+1].node_index = temp.node_index;
                new_visits[i+1].distance_final_node = temp.distance_final_node;
                new_visits[i+1].path_indices = temp.path_indices;
            }
        }
    }

    return true;
}

bool CHillClimbing::SearchPath(int starting_node_index, int final_node_index, vector<int> *solution){
    int current_number_edges = m_graph->m_distances[starting_node_index].size();
    int last_visit;
    int current_parent_index = starting_node_index;
    int current_index_node;
    int current_distance;

    for(int i = 0; i < current_number_edges; i++){
        current_index_node = m_graph->m_distances[starting_node_index][i].index_node_b;
        current_distance = m_graph->Distance(current_index_node, final_node_index);

        m_visit_stack.emplace_back(current_index_node, current_distance);
        last_visit = m_visit_stack.size()-1;
        m_visit_stack[last_visit].Push(starting_node_index);
    }

    //cout << "--INICIANDO VISIT STACK" << endl;
    //PrintVisitStack();

    if(m_visit_stack.size() == 0){
        //cout << "No existe un camino." << endl;
        return false;
    }

    SortVisitStack();

    //cout << "--ORDENANDO VISIT STACK" << endl;
    //PrintVisitStack();

    int inf = 0;

    while(m_visit_stack.size() != 0 && m_visit_stack[last_visit].node_index != final_node_index){
        if (inf >= 500){
            //cout << "Bucle infinito" << endl;

            return false;
        }

        int last_visit_index = m_visit_stack[last_visit].node_index;
        current_number_edges = m_graph->m_distances[last_visit_index].size();

        for(int i = 0; i < current_number_edges; i++){
            current_index_node = m_graph->m_distances[last_visit_index][i].index_node_b;

            //if(current_index_node != current_parent_index){
            //if(!m_visit_stack[last_visit].SearchPathIndices(last_visit_index)){
            if(!m_visit_stack[last_visit].SearchPathIndices(last_visit_index) &&
               !m_visit_stack[last_visit].SearchPathIndices(current_index_node)){

                current_distance = m_graph->Distance(current_index_node, final_node_index);

                new_visits.emplace_back(current_index_node, current_distance);
                int last_new_visit = new_visits.size()-1;
                new_visits[last_new_visit].path_indices = m_visit_stack[last_visit].path_indices;
                new_visits[last_new_visit].Push(last_visit_index);
            }
        }

        current_parent_index = last_visit_index;
        m_visit_stack.pop_back();

        SortNewVisits();

        for(int i = 0; i < new_visits.size(); i++)
            m_visit_stack.push_back(new_visits[i]);

        last_visit = m_visit_stack.size()-1;

        new_visits.clear();

        inf++;

        //cout << "--METIENDO NUEVOS NODOS EN VISIT STACK" << endl;
        //PrintVisitStack();
    }

    if(m_visit_stack.size() == 0){
        //cout << "No existe un camino." << endl;
        return false;
    }

    //solution& = m_visit_stack[last_visit].path_indices;

    for(int i = 0; i < m_visit_stack[last_visit].path_indices.size(); i++)
        solution->push_back(m_visit_stack[last_visit].path_indices[i]);

    /*else{
        vector<int> path = m_visit_stack[last_visit].path_indices;

        for(int i = 0; i < path.size(); i++)
            cout << "Path: " << path[i] << endl;
    }*/

    return true;
}
